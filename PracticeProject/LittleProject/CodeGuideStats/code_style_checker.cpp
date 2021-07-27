//
// Created by g00594152 on 2021/7/26.
//

#include "code guide stats/code_style_checker.h"
namespace CodeGuideStats
{
    void CodeStyleChecker::CheckItems (const StatsParas& statsParas, StatsResult& statsResult)
    {
        // 检查typedef
        int typedefCnt = CountKeyWords("typedef", statsParas.codeSegment);
        int detailIndex = statsResult.detailsCount;
        if (typedefCnt != 0) {
            statsResult.details[detailIndex].item = GUIDE_ITEM_USED_TYPEDEF;
            statsResult.details[detailIndex].count += typedefCnt;
            statsResult.detailsCount++;
        }
        // 检查if(0)
        int ifZeroCnt = CountKeyWords("if (0) ", statsParas.codeSegment);
        if (ifZeroCnt != 0) {
            statsResult.details[detailIndex].item = GUIDE_ITEM_IF_ZERO;
            statsResult.details[detailIndex].count += typedefCnt;
            statsResult.detailsCount++;
        }
    }
}

