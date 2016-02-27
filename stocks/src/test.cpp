/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <stocks_table.h>

void runQuoteTests();
void runTableTest();
std::string getThisQuarter(const std::string&);
std::string getPastQuarter(const std::string&);
std::vector<std::string> miniParseCSV(std::string&);
double getCloseValue(std::string& str);

int main() {
    return 0;
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