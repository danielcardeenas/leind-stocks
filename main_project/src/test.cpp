/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <stocks_table.h>
#include <libstocks.h>
#include <cpr/cprtypes.h>
#include <cpr/api.h>

void runTableTest();
void runSymbolsTest();
void runQuandlTest();
void CAnalysis();

using json = nlohmann::json;
using quandl = leind::quandl::core;

int main() {
    //runTableTest();
    //runSymbolsTest();
    //runQuandlTest();
    CAnalysis();
    return 0;
}

void runQuandlTest()
{
    quandl q;
    q.auth("qsoHq8dWs24kyT8pEDSy");
    auto json = json::parse(q.request("WIKI/FB"));
    std::cout << json.dump(4) << std::endl;
}

void CAnalysis()
{
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/34m8d"}); // SF1/AAPL_EPS_MRQ
    auto json = json::parse(response.text);

    //std::cout << json["dataset"]["data"] << std::endl;

    int i = 0;
    for (auto element : json["dataset"]["data"][0]) {
        std::cout << element << std::endl;
        i++;
    }

    i = 0;
    for (auto element : json["dataset"]["data"][4]) {
        std::cout << element << std::endl;
        i++;
    }
}

void runSymbolsTest()
{
    std::vector<std::string> symbols = leind::database::sf1::getAllSymbols();
    for (auto &symbol : symbols) // access by reference to avoid copying
    {
        std::cout << symbol << std::endl;
    }
}

// Tests
//==============================================================================
void runTableTest()
{
    stocktable::TablePrinter tp(&std::cout);
    tp.addColumn("Symbol", 15);
    tp.addColumn("C Growth", 17);

    tp.printHeader();
    tp << "AS" << std::to_string(34).append("%");
    tp.printFooter();
}