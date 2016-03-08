//
// Created by playfulplay on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_CANSLIM_H
#define STOCKMARKETANALYSIS_CANSLIM_H

#include <iostream>
#include <libstocks.h>
#include <cpr/api.h>

#include "../model/quarter.h"
#include "utils.h"

namespace canslim
{
    // Returns increase in % from current ROE from last year's
    double roeIncrease()
    {
        // Fetch data
        // ===================================================================
        auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/3gxlh"}); // SF1/AAPL_ROE_MRT
        auto json = json::parse(response.text);

        // Set data
        // ===================================================================
        data_stock lastYear(json["dataset"]["data"][4]);
        data_stock thisYear(json["dataset"]["data"][0]);

        return diferentialIncrease(lastYear.value, thisYear.value);
    }

    // If accelerating, will check if the last three quarters have growths
    bool CAnalysis(bool useAccelerating)
    {
        std::cout << std::endl;

        auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/34m8d"}); // SF1/AAPL_EPS_MRQ
        auto json = json::parse(response.text);

        data_stock thisQuarter(json["dataset"]["data"][0]);
        data_stock lastYearQuarter(json["dataset"]["data"][4]);

        double diff = diferentialIncrease(lastYearQuarter.value, thisQuarter.value);

        // Needed if useAccelerating
        data_stock secondPastQuarter(json["dataset"]["data"][1]);
        data_stock thirdPastQuarter(json["dataset"]["data"][2]);


        // Begin the validations
        // ===================================================================
        if (useAccelerating)
        {
            bool isAccelerating = thisQuarter > secondPastQuarter && secondPastQuarter > thirdPastQuarter;

            if (isAccelerating) { std::cout << "Is accelerating!" << std::endl; }
            else { std::cout << "Is NOT accelerating!" << std::endl; return false; }
        }

        if (diff < 25) { return false; }
        else { return true; }
    }

    // if useFiveYears = false, check only 3 years
    bool AAnalysis(bool useFiveYears, bool useReturnOfEquity)
    {
        std::cout << std::endl;

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
        bool fifthToFourth = diferentialIncrease(fifthYear.value, fourthYear.value) >= 25;
        bool fourthToThird = diferentialIncrease(fourthYear.value, thirdYear.value) >= 25;
        bool thirdToSecond = diferentialIncrease(thirdYear.value, secondYear.value) >= 25;
        bool secondToFirst = diferentialIncrease(secondYear.value, firstYear.value) >= 25;

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
            return false;

        if (useReturnOfEquity)
        {
            bool isEnoughROE = roeIncrease() >= 17;
            if (!isEnoughROE) { std::cout << "Not enough ROE increase" << std::endl; return false; }
        }

        return true;
    }
}

#endif //STOCKMARKETANALYSIS_CANSLIM_H
