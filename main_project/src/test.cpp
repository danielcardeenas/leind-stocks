/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <stocks_table.h>
#include <json.hpp>

#include <quandl/quandl.h>
#include <quandl/databases/database.h>
#include "canslim/canslim.h"

void runTableTest();
void runSymbolsTest();
void runQuandlTest();

using json = nlohmann::json;
using quandl = leind::quandl::core;

int main() {
    //runTableTest();
    //runSymbolsTest();
    //runQuandlTest();
    std::cout << "C analysis:" << canslim::CAnalysis(false) << std::endl << std::endl;
    std::cout << "A analysis:" << canslim::AAnalysis(false, false) << std::endl << std::endl;
    return 0;
}

void runQuandlTest()
{
    quandl q;
    q.auth("qsoHq8dWs24kyT8pEDSy");
    auto json = json::parse(q.request("WIKI/FB"));
    std::cout << json.dump(4) << std::endl;
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