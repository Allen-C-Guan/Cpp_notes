//
// Created by g00594152 on 2021/7/26.
//

#include "code guide stats/CodeGuideStats.h"
#include "code guide stats/checker_factory.h"


using namespace CodeGuideStats;
bool CodeGuideStats::CodeGuideStats(const StatsParas& statsParas, StatsResult& statsResult)
{
    // 获取一个工厂单例
    CheckerFactory &factory = CheckerFactory::GetInstance();
    factory.SetCateGory(GUIDE_CATEGORY_CODESTYLE_STYLE);

    // 新建一个codestyle checker
    std::unique_ptr<Checker> checker = factory.CreateClassifier();
    // code style 检查
    checker->CheckResult(statsParas, statsResult);

    // 更改工厂配置为生产secure checker
    factory.SetCateGory(GUIDE_CATEGORY_SECURE_CODING);
    // 生成一个secure checker
    checker = factory.CreateClassifier();
    // secure style 检查
    checker->CheckResult(statsParas, statsResult);
    return statsResult.detailsCount != 0;
}




