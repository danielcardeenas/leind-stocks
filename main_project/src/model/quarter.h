//
// Created by playfulplay on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_QUARTER_H
#define STOCKMARKETANALYSIS_QUARTER_H

#include <iostream>

struct data_stock {
    std::string date;
    double value;

    /*
     * Constructor:
     * Receives json array:
     * ["YYYY-MM-DD", 1.93]
     *
     * @returns: <string, double> pair
     * */
    template <typename T>
    data_stock(T json) {
        int i = 0;
        for (auto element : json) {
            if (i == 0)
                date = element;
            else
                value = element;

            i++;
        }
    }

    friend bool operator < (const data_stock& x, const data_stock& y);
    friend bool operator > (const data_stock& x, const data_stock& y);
};

bool operator < (const data_stock& x, const data_stock& y) {
    return x.value < y.value;
}

bool operator > (const data_stock& x, const data_stock& y) {
    return x.value > y.value;
}

#endif //STOCKMARKETANALYSIS_QUARTER_H
