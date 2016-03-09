//
// Created by leind on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_CANSLIM_H
#define STOCKMARKETANALYSIS_CANSLIM_H

#include <iostream>
#include <libstocks.h>
#include <cpr/api.h>
#include <quandl/quandl.h>

namespace canslim
{
    // Returns increase in % of current ROE from last year's
    double roeIncrease();

    // Returns increase in % of current Free cash flow [FCF] against EPS
    double cashFlowAgainstEPSIncrease();

    // Very similar to cashFlowEPS against EPS
    // From: Inestopedia.com
    bool isQualityStock();

    // If accelerating, will check if the last three quarters have growths
    bool CAnalysis(bool useAccelerating = false, bool useQualityStock = false);

    // if useFiveYears = false, check only 3 years
    bool AAnalysis(bool useFiveYears = false, bool useReturnOfEquity = false, bool useCashFlow = false);

    // Supply and demand
    bool SAnalysis(std::string stock);
}

#endif //STOCKMARKETANALYSIS_CANSLIM_H
