//
// Created by leind on 2/17/16.
//

#ifndef STOCKMARKETANALYSIS_STOCKS_TABLE_H
#define STOCKMARKETANALYSIS_STOCKS_TABLE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

/**
 * Print a pretty table into your output of choice.
 * Usage:
 * TablePrinter tp(&std::cout);
 * tp.AddColumn("Name", 25);
 * tp.AddColumn("Age", 3);
 * tp.addColumn("Position", 30);
 * tp.printHeader();
 * tp << "Dat Chu" << 25 << "Research Assistant";
 * tp << "John Doe" << 26 << "Professional Anonymity";
 * tp << "Jane Doe" << tp.SkipToNextLine();
 * tp << "Tom Doe" << 7 << "Student";
 * tp.printFooter();
 *
 * TODO: Add support for padding in each table cell
 * */
namespace stocktable
{
    // To use in operator overload <<
    class endl {};
    
    class TablePrinter
    {
    public:
        TablePrinter(std::ostream * output, const std::string & separator = "|");
        ~TablePrinter();

        int getNumColumns() const;
        int getTableWidth() const;
        void setSeparator(const std::string &separator);

        void addColumn(const std::string &header_name, int column_width);
        void printHeader();
        void printFooter();

        TablePrinter& operator<<(endl input)
        {
            while (j_ != 0){
                *this << "";
            }
            return *this;
        }

        // Can we merge these?
        TablePrinter& operator<<(float input);
        TablePrinter& operator<<(double input);

        template<typename T> TablePrinter& operator<<(T input)
        {
            if (j_ == 0)
                *out_stream_ << "|";

            // Leave 3 extra space: One for negative sign, one for zero, one for decimal
            *out_stream_ << std::setw(column_widths_.at(j_))
            << input;

            if (j_ == getNumColumns() - 1)
            {
                *out_stream_ << "|\n";
                i_ = i_ + 1;
                j_ = 0;
            } else {
                *out_stream_ << separator_;
                j_ = j_ + 1;
            }

            return *this;
        }

    private:
        void printHorizontalLine();

        template<typename T> void outputDecimalNumber(T input);

        std::ostream * out_stream_;
        std::vector<std::string> column_headers_;
        std::vector<int> column_widths_;
        std::string separator_;

        int i_; // index of current row
        int j_; // index of current column

        int table_width_;
    };

}

#endif //STOCKMARKETANALYSIS_STOCKS_TABLE_H
