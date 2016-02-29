//
// Created by playfulplay on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_QUANDL_H
#define STOCKMARKETANALYSIS_QUANDL_H

#include <iostream>
#include <vector>
#include "stock.h"
#include "databases/database.h"

namespace leind
{
    class quandl {
    private:
        std::string _authCode;
        std::string baseUrl = "https://www.quandl.com/api/v3/datasets/";
    public:
        void auth(std::string& authCode);
        std::string buildProxyAuth();
        std::vector<stock> getAllStocksFromDatabase(database::SupportedDatabase database);
    };

}

#endif //STOCKMARKETANALYSIS_QUANDL_H
