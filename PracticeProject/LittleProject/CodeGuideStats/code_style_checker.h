//
// Created by g00594152 on 2021/7/26.
//

#ifndef CODEGUIDESTATS_CODE_STYLE_CHECKER_H
#define CODEGUIDESTATS_CODE_STYLE_CHECKER_H
#include "checker_factory.h"
#include "checker.h"
namespace CodeGuideStats
{
    using namespace CodeGuideStats;
    class CodeStyleChecker final : public Checker
    {
    public:
        CodeStyleChecker() = default;
        void CheckItems (const StatsParas& statsParas, StatsResult& statsResult) override;
    };
}

#endif //CODEGUIDESTATS_CODE_STYLE_CHECKER_H
