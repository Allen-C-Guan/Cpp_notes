//
// Created by Allen on 2021/7/25.
//

#include "decrator.h"
float Milk::cost()
{
    return 0.2 + obj_->cost();
}
float Mocha::cost()
{
    // 组合的嵌套的内层递归求解
    return 0.5 + obj_->cost();
}

std::string Milk::getDescription()
{
    return "Milk + " + obj_->getDescription();
}

std::string Mocha::getDescription()
{
    return "Mocha + " + obj_->getDescription();
}