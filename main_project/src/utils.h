//
// Created by leind on 08/03/16.
//

#ifndef STOCKMARKETANALYSIS_UTILS_H
#define STOCKMARKETANALYSIS_UTILS_H

#include <iostream>

namespace utils {
    // Calculationis
    // ============================================================

    // Returns increase in %
    double diferentialIncrease(double past, double current);


    // Dates managment stuff.
    // DO NOT TOUCH THIS IS SACRED
    // ============================================================

    // Returns now's time
    struct tm* getNow();

    // Gets date as string in format: YYYY-MM-DD
    std::string dateToString(struct tm* date);

    // Adds number of days to current date
    struct tm* addDays(struct tm* date, int days);

    // Adds number of months to current date
    struct tm* addMonths(struct tm* date, int months);

    // CANSLIM related
    // ============================================================

    // Yahoo Finance web scrap using Import.io
    // Returns the url who gets the major holders info
    std::string buildMajorHoldersQuery(std::string stock);
}

#endif //STOCKMARKETANALYSIS_UTILS_H
