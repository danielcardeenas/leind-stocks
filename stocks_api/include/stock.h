//
// Created by leind on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_SYMBOL_H
#define STOCKMARKETANALYSIS_SYMBOL_H

#include <iostream>

class Stock {
private:
    std::string _symbol;
    std::string _name;
    std::string _sector;
    std::string _industry;

public:
    // Ctors
    Stock();
    Stock(std::string symbol, std::string name, std::string sector, std::string industry): _symbol(symbol), _name(name), _sector(sector), _industry(industry) {}

    // Methods
    std::string getName();
    std::string getSymbol();
    std::string getSector();
    std::string getIndustry();

    // Operators
    bool operator ==(const Stock& rhs) const { return this->_symbol == rhs._symbol;}
};


#endif //STOCKMARKETANALYSIS_SYMBOL_H
