//
// Created by leind on 08/03/16.
//

#include "canslim.h"
#include "../utils.h"
#include "../model/data_stock.h"

using quandl = leind::quandl::core;

// Returns increase in % of current ROE from last year's
double canslim::roeIncrease()
{
    // Fetch data
    // ===================================================================
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/3gxlh"}); // SF1/AAPL_ROE_MRT
    auto json = json::parse(response.text);

    // Set data
    // ===================================================================
    data_stock lastYear(json["dataset"]["data"][4]);
    data_stock thisYear(json["dataset"]["data"][0]);

    return utils::diferentialIncrease(lastYear.value, thisYear.value);
}

// Returns increase in % of current Free cash flow [FCF] against EPS
double canslim::cashFlowAgainstEPSIncrease()
{
    //auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4ql45"}); // SF1/AAPL_FCF_MRY

    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4p33p"}); // SF1/AAPL_FCFPS_MRY
    auto json = json::parse(response.text);
    data_stock cashFlowPerShare(json["dataset"]["data"][0]);

    response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4ma0t"}); // SF1/AAPL_EPS_MRY
    json = json::parse(response.text);
    data_stock currentEPS(json["dataset"]["data"][0]);

    return utils::diferentialIncrease(currentEPS.value, cashFlowPerShare.value);
}

// Very similar to cashFlowEPS against EPS, but this one is used in Quarterly analysis
// From: Inestopedia.com
bool canslim::isQualityStock()
{
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4ttml"}); // SF1/AAPL_FCFPS_MRQ
    auto json = json::parse(response.text);
    data_stock cashFlowPerShare(json["dataset"]["data"][0]);

    response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/34m8d"}); // SF1/AAPL_EPS_MRQ
    json = json::parse(response.text);
    data_stock currentEPS(json["dataset"]["data"][0]);

    return cashFlowPerShare > currentEPS;
}

bool canslim::checkVolumeChanges(Stock& stock)
{
    // Look if the stock is in the database WIKI because we are looking it in another database
    std::vector<std::string> symbols = leind::database::wiki::getAllSymbols();
    if (!(std::find(symbols.begin(), symbols.end(), stock.getSymbol()) != symbols.end()))
    {
        std::cout << stock.getSymbol() << " - " << "Stock not in database" << std::endl;
        return false;
    }

    // Volume changes over the last 3 months
    // Fetch data
    // ===================================================================
    quandl q;
    q.auth("qsoHq8dWs24kyT8pEDSy");
    auto json = json::parse(q.request(
                        "WIKI/" + stock.getSymbol(),
                        utils::dateToString(utils::addMonths(utils::getNow(), -3)),
                        utils::dateToString(utils::getNow())
                        ));

    // Volume changes over the last 50 days
    // Set data
    // ===================================================================
    std::vector<data_stock> stocks;
    int dataSize = json["dataset"]["data"].size();

    // Used to calculate the average trading volume over the last 50 days
    long long lastDaysVol = 0;

    for (int i = 1; i < dataSize; ++i)
    {
        data_stock storeStock(json["dataset"]["data"][i], ValueProperty::Volume);
        stocks.push_back(storeStock);

        // Ignore the first value
        if (i > 0)
            lastDaysVol += storeStock.value;
    }

    //for (int i = 0; i < dataSize; ++i) { std::cout << std::to_string(stocks[i].value) << " - " << stocks[i].date << std::endl; }

    lastDaysVol = lastDaysVol / (dataSize - 1);
    double increaseAverage90 = utils::diferentialIncrease(lastDaysVol, stocks[0].value);

    // Volume changes over the last 3 months
    // Validate data
    // ===================================================================
    if (increaseAverage90 >= 40)
    {
        std::cout << "Big volume change: " << std::to_string(increaseAverage90) << std::endl;
        return true;
    }
    else
    {
        std::cout << "Not big volume change: " << std::to_string(increaseAverage90) << std::endl;
        return false;
    }
}

bool canslim::checkDebtoToEquity(Stock& stock)
{
    // Fetch data
    // ===================================================================
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/420bn"}); // SF1/AAPL_DE_ARY
    auto json = json::parse(response.text);

    // Set data
    // From last two years to current
    // ===================================================================
    data_stock actualDebt(json["dataset"]["data"][0]);
    data_stock firstDebt(json["dataset"]["data"][1]);
    data_stock secondDebt(json["dataset"]["data"][2]);

    double averagePastDebt = (firstDebt.value + secondDebt.value) / (json["dataset"]["data"].size() - 1);
    if (actualDebt.value < averagePastDebt)
    {
        std::cout << "Debt to equity ratio got lower!";
        return true;
    }
    else
    {
        std::cout << "Debt to equity ratio got bigger!";
        return false;
    }
}

// TODO: implement this shit nigga
bool canslim::checkBuyBack(Stock &stock)
{
    return true;
}

// CANSLIM Call methods
// ===========================================================================================================

// TODO: Find another strong stock in the same group to confirm the industry is good
bool canslim::CAnalysis(bool useAccelerating, bool useAccelerating10, bool useSalesGrowth, bool useQualityStock)
{
    std::cout << "C Analysis:" << std::endl;

    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/34m8d"}); // SF1/AAPL_EPS_MRQ
    //auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/114q3"}); // SF1/EFII_EPS_MRQ
    auto json = json::parse(response.text);

    data_stock thisQuarter(json["dataset"]["data"][0]);
    data_stock lastYearQuarter(json["dataset"]["data"][4]);

    // First things first.
    // Current quarterly EPS when compared to the prior year's same quarter
    double diffQuarters = utils::diferentialIncrease(lastYearQuarter.value, thisQuarter.value);

    // Begin the validations
    // ===================================================================

    // Search for acceleration over the last 3 quarters
    if (useAccelerating)
    {
        // Needed if useAccelerating
        data_stock secondPastQuarter(json["dataset"]["data"][1]);
        data_stock thirdPastQuarter(json["dataset"]["data"][2]);

        bool isAccelerating = thisQuarter > secondPastQuarter && secondPastQuarter > thirdPastQuarter;

        if (isAccelerating) { std::cout << "Is accelerating!" << std::endl; }
        else { std::cout << "Is NOT accelerating!" << std::endl; return false; }
    }

    // Search for an acceleration over the last 10 quarters
    // 50% increase setted
    if (useAccelerating10)
    {
        // Fill last 10 quarters
        std::vector<data_stock> quarters10;
        for (int i = 0; i < 10; ++i) { quarters10.push_back(data_stock(json["dataset"]["data"][i])); }

        int acceleratingNeeded = 50; // Percent
        bool isAccelerating = false;

        for (int i = 0; i < 10; ++i)
        {
            if (utils::diferentialIncrease(quarters10[(i + 1)].value, quarters10[i].value) > acceleratingNeeded)
            {
                isAccelerating = true;
                break;
            }
        }

        if (isAccelerating) { std::cout << "Is accelerating10!" << std::endl; }
        else { std::cout << "Is NOT accelerating10" << std::endl; return false; }
    }

    // From investopedia.com
    if (useQualityStock)
    {
        bool isQualityStock = canslim::isQualityStock();

        if (isQualityStock) { std::cout << "Is a quality stock!" << std::endl; }
        else { std::cout << "Is NOT quality stock" << std::endl; return false; }
    }

    // Search for sales increase over 25%
    if (useSalesGrowth)
    {
        bool isEnoughSales = false;

        auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/55r17"}); // SF1/AAPL_REVENUE_MRQ
        //auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4q3rf"}); // SF1/EFII_REVENUE_MRQ
        auto json = json::parse(response.text);

        data_stock thisQuarter(json["dataset"]["data"][0]);
        data_stock secondQuarter(json["dataset"]["data"][1]);
        data_stock thirdQuarter(json["dataset"]["data"][2]);

        if (utils::diferentialIncrease(secondQuarter.value, thisQuarter.value) >= 25)
            isEnoughSales = true;


        // If sales are not up to 25% check if at least accelerating over the last 3 quarters
        if (!isEnoughSales)
            isEnoughSales = thisQuarter > secondQuarter && secondQuarter > thirdQuarter;

        std::cout << utils::diferentialIncrease(secondQuarter.value, thisQuarter.value) << std::endl;
        std::cout << utils::diferentialIncrease(thirdQuarter.value, secondQuarter.value) << std::endl;

        if (isEnoughSales) { std::cout << "Enough sales!" << std::endl; }
        else { std::cout << "NOT enough sales" << std::endl; return false; }
    }

    if (diffQuarters >= 25) { return true; }
    else { return false; }
}

// TODO: Earnings should be stable and consistent from year to year over the last three years
bool canslim::AAnalysis(bool useFiveYears, bool useReturnOfEquity, bool useCashFlow)
{
    std::cout << "A Analysis:" << std::endl;

    // Fetch data
    // ===================================================================
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/4ma0t"}); // SF1/AAPL_EPS_MRY
    auto json = json::parse(response.text);

    // Set data
    // ===================================================================
    data_stock fifthYear(json["dataset"]["data"][4]);
    data_stock fourthYear(json["dataset"]["data"][3]);
    data_stock thirdYear(json["dataset"]["data"][2]);
    data_stock secondYear(json["dataset"]["data"][1]); // second most recent
    data_stock firstYear(json["dataset"]["data"][0]); // most recent

    // Optimal yearly increase: 25%
    bool fifthToFourth = utils::diferentialIncrease(fifthYear.value, fourthYear.value) >= 25;
    bool fourthToThird = utils::diferentialIncrease(fourthYear.value, thirdYear.value) >= 25;
    bool thirdToSecond = utils::diferentialIncrease(thirdYear.value, secondYear.value) >= 25;
    bool secondToFirst = utils::diferentialIncrease(secondYear.value, firstYear.value) >= 25;

    // If only using last three years, ignore these two years [4th, 5th]
    if (!useFiveYears) { fifthToFourth = true; fourthToThird = true; }

    // If the next year showed new high when the yearly increase is < 25%
    // Then let it slide only one time [slides]
    int slides = 0;
    if (!fifthToFourth)
    {
        slides++;
        if (thirdYear > fifthYear) {fifthToFourth = true; }
    }

    if (!fourthToThird)
    {
        slides++;
        if (secondYear > fourthYear) { fourthToThird = true; }
    }

    if (!thirdToSecond)
    {
        slides++;
        if (firstYear > thirdYear) { thirdToSecond = true; }
    }


    // Begin the validations
    // ===================================================================
    if (slides > 1) { std::cout << "Too much slides" << std::endl; return false; }

    if (!(fifthToFourth && fourthToThird && thirdToSecond && secondToFirst))
    {
        std::cout << "Not enough primary annual growing" << std::endl;
    }

    if (useReturnOfEquity)
    {
        bool isEnoughROE = canslim::roeIncrease() >= 17;
        if (!isEnoughROE) { std::cout << "Not enough ROE increase" << std::endl; return false; }
    }

    if (useCashFlow)
    {
        bool isEnoughCashFlow = canslim::cashFlowAgainstEPSIncrease() >= 20;
        if (isEnoughCashFlow) { std::cout << "Enough Cashflow" << std::endl; }
        else { std::cout << "Not enough Cashflow" << std::endl; return false; }
    }

    return true;
}

// Supply and demand, reducing its debt as a percent of equity
// TODO: Pick the ones with less shares
bool canslim::SAnalysis(Stock stock, bool useVolumeChanges, bool useDebtRatio, bool useBuyBack)
{
    std::cout << "S Analysis:" << std::endl;

    bool isVolumeChanged = true;
    bool isDebtReduced = true;
    bool isBuyBack = true;

    if (useVolumeChanges) { isVolumeChanged = canslim::checkVolumeChanges(stock); }
    if (useDebtRatio) { isDebtReduced = canslim::checkDebtoToEquity(stock); }
    if (useBuyBack) { isBuyBack = canslim::checkBuyBack(stock); }

    return isVolumeChanged && isDebtReduced && isBuyBack;
}

// Leader or laggard
//TODO: Buy among the top two or three stocks in a strong industry group
bool canslim::LAnalysis(Stock stock)
{

}

// Insitutions holding
bool canslim::IAnalysis(Stock stock)
{
    std::cout << "I Analysis:" << std::endl;

    // Fetch data
    // This one uses Yahoo finance info
    // Data scraped with Import.io
    // ===================================================================
    auto response = cpr::Get(cpr::Url{utils::buildMajorHoldersQuery(stock.getSymbol())});
    auto json = json::parse(response.text);

    // Set data
    // ===================================================================
    stock.setMajorHoldersData(json["results"][0]["data"]);

    // Uncomment to verify results
    //std::cout << stock.getPercentHeldByOwners() << std::endl;
    //std::cout << stock.getPercentHeldByInstitutions() << std::endl;
    //std::cout << stock.getPercentFloatHeldByInstitutions() << std::endl;
    //std::cout << stock.getNumberOfInstitutionsHolding() << std::endl;

    return true;
}
