//
// Created by g00594152 on 2021/7/26.
//

#ifndef CODEGUIDESTATS_CHECKER_H
#define CODEGUIDESTATS_CHECKER_H
#include "CodeGuideStats.h"
#include <cstring>
#include <string>

namespace CodeGuideStats {
    class Checker
    {
    public:
        Checker() = default;
        virtual ~Checker() = default;
        // 对外接口，父类控流程，子类负责实现具体的item检查
        void CheckResult(const StatsParas& statsParas, StatsResult& statsResult);

    protected:
        // 父类提供统一的算法实现
        void Sort(StatsResult& statsResult);
        int CountKeyWords(const char* keyWords, const char* substr);

    private:
        // NVI设计模式，子类只能实现自己的check规则，不可以干扰流程
        virtual void CheckItems (const StatsParas& statsParas, StatsResult& statsResult) = 0;
    };
}

#endif //CODEGUIDESTATS_CHECKER_H
