/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <codes.h>
#include <quote.h>
#include <stocks_table.h>

void runTableTest();
int runApiTest();

using namespace std;

int main()
{
    runApiTest();
    //runTableTest();
    return 0;
}

int runApiTest()
{
    // all Yahoo! Finance quote types are implemented (this is just a sample)
    std::string petr4Quotes = quote::getLatestQuotesCsv("BIMBOA.MX",
                                                        {
                                                                quote::QuoteType::symbol,
                                                                quote::QuoteType::earningsShare,
                                                                quote::QuoteType::peRatio,
                                                        });
    std::cout << petr4Quotes << "\n" << std::endl;
    // quote ranges can be daily, weekly, monthly, or dividends only
    std::string petr4HistoricalPrices = quote::getHistoricalQuotesCsv("BIMBOA.MX",
                                                                      2016, 2, 15,
                                                                      2016, 2, 17,
                                                                      quote::RangeType::daily);
    std::cout << petr4HistoricalPrices << std::endl;
    return 0;
}

void runTableTest()
{
    stocktable::TablePrinter tp(&std::cout);
    tp.addColumn("Symbol", 15);
    tp.addColumn("Value", 10);

    // Table content
    tp.printHeader();
    for (auto &code : Codes::BVMSymbols)
    {
        tp << code << "56.3";
    }
    tp.printFooter();
}