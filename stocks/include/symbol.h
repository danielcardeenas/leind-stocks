//
// Created by leind on 2/15/16.
//
#ifndef STOCKMARKETANALYSIS_SYMBOL_H
#define STOCKMARKETANALYSIS_SYMBOL_H

#include <iostream>
#include <vector>

class Symbol {
public:
    std::string code;
    std::string name;
    Symbol(std::string& code, const std::string& name): code(code), name(name){}
};


#endif //STOCKMARKETANALYSIS_SYMBOL_H
