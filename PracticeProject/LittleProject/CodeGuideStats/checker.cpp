//
// Created by g00594152 on 2021/7/26.
//

#include "code guide stats/checker.h"
#include <algorithm>
namespace CodeGuideStats {
    int Checker::CountKeyWords(const char* keyWords, const char* substr)
    {
        int cnter = 0;
        while ((substr = std::strstr(substr, keyWords)) != NULL) {
            cnter++;
            substr++;
        }
        return cnter;
    }

    void Checker::Sort(StatsResult& statsResult)
    {
        std::sort(std::begin(statsResult.details), std::end(statsResult.details),
                [](const StatsDetail &lhs, const StatsDetail &rhs) { return lhs.count > rhs.count;});
    }

    void Checker::CheckResult(const StatsParas& statsParas, StatsResult& statsResult)
    {
        // step1: 检查rules，子类自己实现，父类只控流程！
        CheckItems(statsParas, statsResult);
        // step2. sort结果
        Sort(statsResult);
    }
}



