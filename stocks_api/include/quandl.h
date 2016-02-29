//
// Created by leind on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_QUANDL_H
#define STOCKMARKETANALYSIS_QUANDL_H

#include <iostream>
#include <vector>
#include "stock.h"

namespace leind
{
    namespace quandl {

        class core {
        private:
            std::string _authCode;
            std::string baseUrl = "https://www.quandl.com/api/v3/datasets/";
        public:
            void auth(std::string& authCode);
            std::string buildProxyAuth();
        };
    }

}

#endif //STOCKMARKETANALYSIS_QUANDL_H
