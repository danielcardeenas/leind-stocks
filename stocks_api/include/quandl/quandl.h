//
// Created by leind on 26/02/16.
//

#ifndef STOCKMARKETANALYSIS_QUANDL_H
#define STOCKMARKETANALYSIS_QUANDL_H

#include <iostream>
#include <vector>
#include <json.hpp>
#include "stock.h"

using json = nlohmann::json;

namespace leind
{
    namespace quandl
    {
        class core {
        private:
            std::string _authCode = "";
            std::string _baseUrl = "https://www.quandl.com/api/v3/datasets/";
        public:
            core();

            void auth(std::string authCode);
            std::string request(std::string code);
            std::string request(std::string code, std::string startDate, std::string endDate);
            std::string buildRequestUrl(std::string& code);
            std::string buildRequestUrl(std::string& code, std::string& startDate, std::string& endDate);
        };
    }

}

#endif //STOCKMARKETANALYSIS_QUANDL_H
