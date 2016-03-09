//
// Created by leind on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_QUARTER_H
#define STOCKMARKETANALYSIS_QUARTER_H

#include <iostream>

enum ValueProperty {Open, High, Low, Close, Volume};

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

    /*
     * Constructorr when getting data from WIKI:
     * Receives json array:
     * ["YYYY-MM-DD", 1.93]
     * And enum ValueProperty to map the value with the desired property:
     * Volume, High, Low, Close, etc...
     *
     * @returns: <string, double> pair
     * */
    template <typename T>
    data_stock(T json, ValueProperty valueProperty) {

        int i = 0;
        switch (valueProperty) {
            case Open:
                for (auto element : json) {
                    if (i == 0)
                        date = element;
                    if (i == 1)
                        value = element;

                    i++;
                }
            break;

            case High:
                for (auto element : json) {
                    if (i == 0)
                        date = element;
                    if (i == 2)
                        value = element;

                    i++;
                }
            break;

            case Low:
                for (auto element : json) {
                    if (i == 0)
                        date = element;
                    if (i == 3)
                        value = element;

                    i++;
                }
            break;

            case Close:
                for (auto element : json) {
                    if (i == 0)
                        date = element;
                    if (i == 4)
                        value = element;

                    i++;
                }
            break;

            case Volume:
                for (auto element : json) {
                    if (i == 0)
                        date = element;
                    if (i == 5)
                        value = element;

                    i++;
                }
            break;
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
