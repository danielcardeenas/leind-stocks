/**
 * I'm the stone that the builder refused
 * I'm the visual, the inspiration
 * Who made the lady sing the blues
 * */

#include <iostream>
#include <codes.h>
#include <quote.h>
#include <stocks_table.h>

void runQuoteTests();
void runApiTest();
std::string getThisQuarter(const std::string&);
std::string getPastQuarter(const std::string&);
std::vector<std::string> miniParseCSV(std::string&);
double getCloseValue(std::string& str);

int main() {
    runApiTest();
    return 0;
}

// Tests
//==============================================================================
void runApiTest()
{
    stocktable::TablePrinter tp(&std::cout);
    tp.addColumn("Symbol", 15);
    tp.addColumn("C Growth", 17);

    tp.printHeader();
    for (auto &code : Codes::BVMSymbols) {
        std::string nowQuarter = getThisQuarter(code);
        std::string pastQuarter = getPastQuarter(code);

        double now = getCloseValue(nowQuarter);
        double before = getCloseValue(pastQuarter);
        double dif = now - before;
        double percent = (dif/now) * 100;

        // Print
        if (percent > 25)
            tp << code << std::to_string(percent).append("%");
    }
    tp.printFooter();
}

void runQuoteTests()
{
    std::string petr4Quotes = quote::getLatestQuotesCsv("BIMBOA.MX",
                                                        {
                                                                quote::QuoteType::symbol,
                                                                quote::QuoteType::earningsShare,
                                                                quote::QuoteType::peRatio,
                                                        });
    std::cout << petr4Quotes << "\n" << std::endl;
}

// Move this methods to a header or utils class or whatever the fuck man.
// Just don't leave this shit here
//==============================================================================
std::string getPastQuarter(const std::string& code)
{
    return quote::getHistoricalQuotesCsv(code,
                                         2014, 12, 31,
                                         2014, 12, 31,
                                         quote::RangeType::monthly);
}

std::string getThisQuarter(const std::string& code)
{
    // Get last quarter reported
    return quote::getHistoricalQuotesCsv(code,
                                         2015, 12, 31,
                                         2015, 12, 31,
                                         quote::RangeType::monthly);
}

double getCloseValue(std::string& str)
{
    std::vector<std::string> vector = miniParseCSV(str);
    double d;
    std::stringstream ss(vector.at(vector.size() - 1));

    // Convert
    ss >> d; return d;
}

std::vector<std::string> miniParseCSV(std::string& str)
{
    std::stringstream ss(str);
    std::vector<std::string> result;

    while( ss.good() )
    {
        std::string substr;
        getline(ss, substr, ',');
        result.push_back(substr);
    }

    return result;
}