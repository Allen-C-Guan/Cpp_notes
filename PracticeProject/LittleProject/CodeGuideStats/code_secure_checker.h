//
// Created by g00594152 on 2021/7/26.
//

#ifndef CODEGUIDESTATS_CODE_SECURE_CHECKER_H
#define CODEGUIDESTATS_CODE_SECURE_CHECKER_H
#include "checker_factory.h"
#include "checker.h"
namespace CodeGuideStats
{
    class CodeSecureChecker final : public Checker
    {
    public:
        CodeSecureChecker () = default;
        void CheckItems (const StatsParas& statsParas, StatsResult& statsResult) override;
    };
}
#endif //CODEGUIDESTATS_CODE_SECURE_CHECKER_H
