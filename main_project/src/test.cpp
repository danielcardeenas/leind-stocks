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
#include "utils.h"

void runDateTests();
void runTableTest();
void runSymbolsTest();
void runQuandlTest();
void runStocksTest();

using json = nlohmann::json;
using quandl = leind::quandl::core;

int main() {
    //runTableTest();
    //runSymbolsTest();
    //runQuandlTest();
    //runStocksTest();
    //runDateTests();
    //std::cout << canslim::CAnalysis(false, true, true, true) << std::endl;
    //std::cout << canslim::AAnalysis(false, false, true) << std::endl;
    //std::cout << canslim::SAnalysis(Stock("AAPL"), true, true) << std::endl;
    std::cout << canslim::IAnalysis(Stock("EFII")) << std::endl;
}

void runDateTests()
{
    std::cout << utils::dateToString(utils::getNow()) << std::endl;
    std::cout << utils::dateToString(utils::addDays(utils::getNow(), -30)) << std::endl;
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
    std::vector<std::string> symbols = leind::database::wiki::getAllSymbols();
    for (auto &symbol : symbols) // access by reference to avoid copying
    {
        std::cout << symbol << std::endl;
    }

    std::cout << symbols.size() << std::endl;
}

void runStocksTest()
{
    std::vector<Stock> stocks = leind::database::sf1::getAllStocks();
    for (auto &stock : stocks) // access by reference to avoid copying
    {
        std::cout << stock.getName() << " - " << stock.getSector() << std::endl;
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
