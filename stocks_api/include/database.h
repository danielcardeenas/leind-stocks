//
// Created by playfulplay on 29/02/16.
//

#ifndef STOCKMARKETANALYSIS_DATABASE_H
#define STOCKMARKETANALYSIS_DATABASE_H

#include <iostream>
#include <vector>
#include <unistd.h>

namespace leind {

    namespace database {
        // SF1 Database only features
        //============================
        class sf1 {
        private:
            static std::string getFilePath();

        public:
            static std::vector<std::string> getAllSymbols();
        };
    }
}


#endif //STOCKMARKETANALYSIS_DATABASE_H
