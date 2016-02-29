/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <stocks_table.h>
#include <cpr/api.h>
#include <json.hpp>

using json = nlohmann::json;

void runTableTest();
void runCurlJsonTest();

int main() {
    runTableTest();
    runCurlJsonTest();
    return 0;
}

void runCurlJsonTest() {
    auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
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