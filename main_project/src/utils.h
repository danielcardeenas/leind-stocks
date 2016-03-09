//
// Created by leind on 08/03/16.
//

#ifndef STOCKMARKETANALYSIS_UTILS_H
#define STOCKMARKETANALYSIS_UTILS_H

#include <iostream>

namespace utils {
    // Calculationis
    //=============================================================

    // Returns increase in %
    double diferentialIncrease(double past, double current);


    // Dates managment stuff.
    // DO NOT TOUCH THIS IS SACRED
    //=============================================================

    // Returns now's time
    struct tm* getNow();

    // Gets date as string in format: YYYY-MM-DD
    std::string dateToString(struct tm* date);

    // Adds number of days to current date
    struct tm* addDays(struct tm* date, int days);
}

#endif //STOCKMARKETANALYSIS_UTILS_H
