/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <stocks_table.h>
#include <cpr/api.h>
#include <json.hpp>
#include <libstocks.h>

void runTableTest();
void runCurlJsonTest();
int outputCurr();

void runSymbolsTest();

using json = nlohmann::json;
using quandl = leind::quandl::core;

int main() {
    //runTableTest();
    //runCurlJsonTest();
    //outputCurr();
    runSymbolsTest();
    return 0;
}

void runSymbolsTest() {
    std::vector<std::string> symbols = leind::database::sf1::getAllSymbols();
    for (auto &symbol : symbols) // access by reference to avoid copying
    {
        std::cout << symbol << std::endl;
    }
}

void runCurlJsonTest() {
    auto response = cpr::Get(cpr::Url{"https://api.myjson.com/bins/34m8d"}); // SF1/AAPL_EPS_MRQ
    auto json = json::parse(response.text);
    std::cout << json.dump(4) << std::endl;
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