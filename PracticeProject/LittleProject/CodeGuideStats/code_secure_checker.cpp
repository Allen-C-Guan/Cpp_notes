//
// Created by g00594152 on 2021/7/26.
//

#include "code guide stats/code_secure_checker.h"
namespace CodeGuideStats
{
    void CodeSecureChecker::CheckItems (const StatsParas& statsParas, StatsResult& statsResult)
    {
        int abortCnt = CountKeyWords("abort", statsParas.codeSegment);
        int detailIndex = statsResult.detailsCount;
        if (abortCnt != 0) {
            statsResult.details[detailIndex].item = GUIDE_ITEM_DONOT_USE_ABORT;
            statsResult.details[detailIndex].count += abortCnt;
            statsResult.detailsCount++;
        }
    }
}
