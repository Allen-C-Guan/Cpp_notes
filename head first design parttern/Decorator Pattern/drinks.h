//
// Created by Allen on 2021/7/25.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_DRINKS_H
#define HEAD_FIRST_DESIGN_PARTTERN_DRINKS_H
#include "Beverage.h"
#include <string>
class HouseBlend : public Beverage
{
public:
    HouseBlend() = default;
    float cost() override;
    std::string getDescription() override
    {
        return "HouseBlend";
    }
    ~HouseBlend() = default;
};

class DarkRoast : public Beverage
{
public:
    DarkRoast() = default;
    ~DarkRoast() = default;
    float cost() override;
    std::string getDescription() override
    {
        return "DarkRoast";
    }
};

#endif //HEAD_FIRST_DESIGN_PARTTERN_DRINKS_H
