//
// Created by playfulplay on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_QUARTER_H
#define STOCKMARKETANALYSIS_QUARTER_H

#include <iostream>

typedef std::pair<std::string, double> t_quarter;

/*
 * Receives json array:
 * ["YYYY-MM-DD", 1.93]
 *
 * @returns: <string, double> pair
 * */
template <typename T>
t_quarter buildQuarter(T json)
{
    t_quarter quarter;
    int i = 0;
    for (auto element : json) {
        if (i == 0)
            quarter.first = element;
        else
            quarter.second = element;

        i++;
    }

    return quarter;
}

#endif //STOCKMARKETANALYSIS_QUARTER_H
