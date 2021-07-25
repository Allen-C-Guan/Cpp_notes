//
// Created by Allen on 2021/7/25.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_DECRATOR_H
#define HEAD_FIRST_DESIGN_PARTTERN_DECRATOR_H
#include "Beverage.h"
#include <memory>
#include <utility>

class Milk : public Beverage
{
public:
    Milk(std::shared_ptr<Beverage> obj):obj_(std::move(obj))
    {
    }
    float cost() override;
    // 不能放在constructor内试图去改变base中的内容，那你也要维护其何时删除！放在这里和cost一样，递归的现用现取
    std::string getDescription() override;
private:
    std::shared_ptr<Beverage> obj_;
};

class Mocha : public Beverage
{
public:
    Mocha(std::shared_ptr<Beverage> obj) :obj_(std::move(obj))
    {
    }
    float cost() override;
    std::string getDescription() override;
private:
    std::shared_ptr<Beverage> obj_;
};

#endif //HEAD_FIRST_DESIGN_PARTTERN_DECRATOR_H
