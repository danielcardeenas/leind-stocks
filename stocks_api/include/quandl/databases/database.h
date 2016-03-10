//
// Created by leind on 29/02/16.
//

#ifndef STOCKMARKETANALYSIS_DATABASE_H
#define STOCKMARKETANALYSIS_DATABASE_H

#include <iostream>
#include <vector>
#include <unistd.h>

#include "../../stock.h"

namespace leind
{
    namespace database
    {
        // SF1 Database only features
        //============================
        class sf1 {
        private:
            static std::string _symbolsFile;
            static std::string _symbolsUrl;

            static std::string getFilePath();
            static std::string getFileFromWeb();

        public:
            static std::vector<std::string> getAllSymbols();
            static std::vector<Stock> getAllStocks();
        };

        // WIKI Database only features
        //============================
        class wiki {
        private:
            static std::string _symbolsFile;
            static std::string _symbolsUrl;

            static std::string getFilePath();
            static std::string getFileFromWeb();

        public:
            static std::vector<std::string> getAllSymbols();
        };
    }
}


#endif //STOCKMARKETANALYSIS_DATABASE_H
