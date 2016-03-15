//
// Created by leind on 01/03/16.
//

#ifndef STOCKMARKETANALYSIS_CANSLIM_H
#define STOCKMARKETANALYSIS_CANSLIM_H

#include <iostream>
#include <algorithm>
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
    // From: Investopedia.com
    bool isQualityStock();

    // Check volume changes above 50%
    // Used in S analysis
    bool checkVolumeChanges(Stock& stock);

    // Debt to equity ratio, check if its getting lower
    // Used in S analysis
    bool checkDebtoToEquity(Stock& stock);

    // If accelerating, will check if the last three quarters have growths
    bool CAnalysis(bool useAccelerating = false, bool useAccelerating10 = false, bool useSalesGrowth = false, bool useQualityStock = false);

    // if useFiveYears = false, check only 3 years
    bool AAnalysis(bool useFiveYears = false, bool useReturnOfEquity = false, bool useCashFlow = false);

    // TODO: Companies whose stocks are emerging form price consolidations patterns and
    // are close to or, actually touching new high price are usually best
    // pag. 28
    //bool NAnalysis();

    // Supply and demand, reducing its debt as a percent of equity
    bool SAnalysis(Stock stock, bool = false, bool useDebtRatio = false);

    // Leader or laggard
    bool LAnalysis(Stock stock);

    // Institutions holding
    bool IAnalysis(Stock stock);
}

#endif //STOCKMARKETANALYSIS_CANSLIM_H
