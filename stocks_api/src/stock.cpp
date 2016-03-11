//
// Created by leind on 26/02/16.
//

#include "stock.h"

std::string Stock::getName() { return _name; }
std::string Stock::getSymbol() { return _symbol; }
std::string Stock::getSector() { return _sector; }
std::string Stock::getIndustry() { return _industry; }

void Stock::setName(std::string name) { this->_name = name; }
void Stock::setSymbol(std::string symbol) { this->_symbol = symbol; }
void Stock::setSector(std::string sector) { this->_sector = sector; }
void Stock::setIndustry(std::string industry) { this->_industry = industry; }

double Stock::getPercentHeldByOwners() { return _percentHeldByOwners; }
double Stock::getPercentHeldByInstitutions() { return _percentHeldByIntitutions; }
double Stock::getPercentFloatHeldByInstitutions() { return _percentFloatHeldByIntitutions; }
double Stock::getNumberOfInstitutionsHolding() { return _numberOfInstitutionsHolding; }

void Stock::setPercentHeldByOwners(double percentHeldByOwners) { this->_percentHeldByOwners = percentHeldByOwners; }
void Stock::setPercentHeldByInstitutions(double percentHeldByIntitutions) { this->_percentHeldByIntitutions = percentHeldByIntitutions; }
void Stock::setPercentFloatHeldByInstitutions(double percentFloatHeldByIntitutions) { this->_percentFloatHeldByIntitutions = percentFloatHeldByIntitutions; }
void Stock::setNumberOfInstitutionsHolding(int numberOfInstitutionsHolding) { this->_numberOfInstitutionsHolding = numberOfInstitutionsHolding; }
