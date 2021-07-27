//
// Created by g00594152 on 2021/7/26.
//

#include "code guide stats/checker_factory.h"
#include "code guide stats/checker.h"
#include "code guide stats/code_secure_checker.h"
#include "code guide stats/code_style_checker.h"
namespace CodeGuideStats
{
    CheckerFactory::CheckerFactory(GUIDE_CATEGORY category) : category_(category) {}
    std::unique_ptr<Checker> CheckerFactory::CreateClassifier()
    {
        switch (category_) {
            case GUIDE_CATEGORY_CODESTYLE_STYLE:
                return std::make_unique<CodeStyleChecker>();
            case GUIDE_CATEGORY_SECURE_CODING:
                return std::make_unique<CodeSecureChecker>();
            default:
                return nullptr;
        }
    }

    CheckerFactory& CheckerFactory::GetInstance()
    {
        // 线程不安全的singleton
        static CheckerFactory checkerFactory;
        return checkerFactory;
    }
}
