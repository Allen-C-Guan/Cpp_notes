//
// Created by g00594152 on 2021/7/26.
//

#ifndef CODEGUIDESTATS_CHECKER_FACTORY_H
#define CODEGUIDESTATS_CHECKER_FACTORY_H
#include "CodeGuideStats.h"
#include "checker.h"
#include <memory>

namespace CodeGuideStats
{
    // 工厂接口，根据类型，生产出相应的checker。
    class CheckerFactory
    {
    public:
        explicit CheckerFactory() = default;
        explicit CheckerFactory(GUIDE_CATEGORY category);
        // 生产checker接口
        std::unique_ptr<Checker> CreateClassifier();
        // 重置checker类型接口
        void SetCateGory(GUIDE_CATEGORY category)
        {
            category_ = category;
        }

        // 单例模式
        static CheckerFactory& GetInstance();
        CheckerFactory(const CheckerFactory&) = delete;
        CheckerFactory& operator= (const CheckerFactory&) = delete;
        CheckerFactory& operator= (CheckerFactory&&) noexcept = delete;
        CheckerFactory(CheckerFactory&&) noexcept = delete;
    private:
        GUIDE_CATEGORY category_;
    };
}

#endif //CODEGUIDESTATS_CHECKER_FACTORY_H
