//
// Created by leind on 2/17/16.
//

#include "stocks_table.h"

namespace stocktable {
    TablePrinter::TablePrinter(std::ostream * output, const std::string & separator){
        out_stream_ = output;
        i_ = 0;
        j_ = 0;
        separator_ = separator;
        table_width_ = 0;
    }

    TablePrinter::~TablePrinter() {}

    int TablePrinter::getNumColumns() const
    {
        return column_headers_.size();
    }

    int TablePrinter::getTableWidth() const
    {
        return table_width_;
    }

    void TablePrinter::setSeparator(const std::string &separator)
    {
        separator_ = separator;
    }

    void TablePrinter::addColumn(const std::string &header_name, int column_width)
    {
        if (column_width < 4){
            throw std::invalid_argument("Column size has to be >= 4");
        }

        column_headers_.push_back(header_name);
        column_widths_.push_back(column_width);
        table_width_ += column_width + separator_.size(); // for the separator
    }

    void TablePrinter::printHorizontalLine()
    {
        *out_stream_ << "+"; // the left bar

        for (int i=0; i<table_width_-1; ++i)
            *out_stream_ << "-";

        *out_stream_ << "+"; // the right bar
        *out_stream_ << "\n";
    }

    void TablePrinter::printHeader()
    {
        printHorizontalLine();
        *out_stream_ << "|";

        for (int i=0; i < getNumColumns(); ++i){
            *out_stream_ << std::setw(column_widths_.at(i)) << column_headers_.at(i).substr(0, column_widths_.at(i));
            if (i != getNumColumns() - 1){
                *out_stream_ << separator_;
            }
        }

        *out_stream_ << "|\n";
        printHorizontalLine();
    }

    void TablePrinter::printFooter()
    {
        printHorizontalLine();
    }

    TablePrinter& TablePrinter::operator<<(float input)
    {
        outputDecimalNumber<float>(input);
        return *this;
    }

    TablePrinter& TablePrinter::operator<<(double input)
    {
        outputDecimalNumber<double>(input);
        return *this;
    }

    template<typename T> void
    TablePrinter::outputDecimalNumber(T input)
    {
        // If we cannot handle this number, indicate so
        if (input < 10*(column_widths_.at(j_)-1) || input > 10*column_widths_.at(j_))
        {
            std::stringstream string_out;
            string_out << std::setiosflags(std::ios::fixed)
            << std::setprecision(column_widths_.at(j_))
            << std::setw(column_widths_.at(j_))
            << input;

            std::string string_rep_of_number = string_out.str();

            string_rep_of_number[column_widths_.at(j_)-1] = '*';
            std::string string_to_print = string_rep_of_number.substr(0, column_widths_.at(j_));
            *out_stream_ << string_to_print;
        }
        else
        {

            // determine what precision we need
            int precision = column_widths_.at(j_) - 1; // leave room for the decimal point
            if (input < 0)
                --precision; // leave room for the minus sign

            // leave room for digits before the decimal?
            if (input < -1 || input > 1){
                int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
                precision -= num_digits_before_decimal;
            }
            else
                precision --; // e.g. 0.12345 or -0.1234

            if (precision < 0)
                precision = 0; // don't go negative with precision

            *out_stream_ << std::setiosflags(std::ios::fixed)
            << std::setprecision(precision)
            << std::setw(column_widths_.at(j_))
            << input;
        }

        if (j_ == getNumColumns() - 1)
        {
            *out_stream_ << "|\n";
            i_ = i_ + 1;
            j_ = 0;
        }
        else
        {
            *out_stream_ << separator_;
            j_ = j_ + 1;
        }
    }
}