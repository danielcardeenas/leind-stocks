//
// Created by playfulplay on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_SYMBOL_H
#define STOCKMARKETANALYSIS_SYMBOL_H

#include <iostream>


class stock {
private:
    std::string _symbol;
    std::string _name;

public:
    // Ctors
    stock(std::string symbol): _symbol(symbol) {}
    stock(std::string symbol, std::string name): _symbol(symbol), _name(name) {}

    // Methods
    std::string getName();
    std::string getSymbol();
};


#endif //STOCKMARKETANALYSIS_SYMBOL_H