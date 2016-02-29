//
// Created by playfulplay on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_DATABASES_H
#define STOCKMARKETANALYSIS_DATABASES_H

#include <iostream>
#include <vector>

namespace database {
    enum SupportedDatabase { SF1 };

    class SF1 {
    public:
        // Tab delimited
        const std::string allSymbolsFile = "sf1_tickers.txt";
        const std::string allSymbolsFileUrl = "http://www.sharadar.com/meta/tickers.txt";
    };
}

#endif //STOCKMARKETANALYSIS_DATABASES_H
