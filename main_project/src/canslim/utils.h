//
// Created by leind on 08/03/16.
//

#ifndef STOCKMARKETANALYSIS_UTILS_H
#define STOCKMARKETANALYSIS_UTILS_H

namespace utils {
    double diferentialIncrease(double past, double current) {
        return ((current - past) / past) * 100;
    }
}

#endif //STOCKMARKETANALYSIS_UTILS_H
