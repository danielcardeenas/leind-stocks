//
// Created by leind on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_SYMBOL_H
#define STOCKMARKETANALYSIS_SYMBOL_H

#include <iostream>

class Stock {
private:
    // Basic info
    std::string _symbol;
    std::string _name;
    std::string _sector;
    std::string _industry;

    // Major holders info
    double _percentHeldByOwners;
    double _percentHeldByIntitutions;
    double _percentFloatHeldByIntitutions;
    int _numberOfInstitutionsHolding;

    // Table info
    long long shares;

public:
    // Ctors
    Stock();
    Stock(std::string symbol): _symbol(symbol) {}
    Stock(std::string symbol, std::string name): _symbol(symbol), _name(name) {}
    Stock(std::string symbol, std::string name, std::string sector, std::string industry): _symbol(symbol), _name(name), _sector(sector), _industry(industry) {}

    // Getters & Setters
    // =========================================================================
    std::string getName();
    std::string getSymbol();
    std::string getSector();
    std::string getIndustry();

    void setName(std::string name);
    void setSymbol(std::string symbol);
    void setSector(std::string sector);
    void setIndustry(std::string industry);

    double getPercentHeldByOwners();
    double getPercentHeldByInstitutions();
    double getPercentFloatHeldByInstitutions();
    double getNumberOfInstitutionsHolding();

    void setPercentHeldByOwners(double _percentHeldByOwners);
    void setPercentHeldByInstitutions(double _percentHeldByIntitutions);
    void setPercentFloatHeldByInstitutions(double _percentFloatHeldByIntitutions);
    void setNumberOfInstitutionsHolding(int _numberOfInstitutionsHolding);

    long long getSharesQty();

    void setSharesQty(long long shares);

    // Funcitons
    // =========================================================================

    // Receives json scraped from Yahoo finance, using Import.io
    // Sets its major holders info
    template <typename T>
    void setMajorHoldersData(T json)
    {
        int i = 0;
        for (auto element : json) {
            if (i == 0)
                _percentHeldByOwners = element;
            else if (i == 1)
                _percentHeldByIntitutions = element;
            else if (i == 2)
                _percentFloatHeldByIntitutions = element;
            else if (i == 3)
                _numberOfInstitutionsHolding = element;

            i++;
        }
    }

    // Operators
    bool operator ==(const Stock& rhs) const { return this->_symbol == rhs._symbol;}
};


#endif //STOCKMARKETANALYSIS_SYMBOL_H
