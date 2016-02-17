/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include "stocks/codes.h"
#include "table/table_printer.h"

void runTableTest();

using namespace std;

int main()
{
    runTableTest();
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