//
// Created by Allen on 2021/7/25.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_BEVERAGE_H
#define HEAD_FIRST_DESIGN_PARTTERN_BEVERAGE_H
#include <string>
class Beverage
{
public:
    virtual std::string getDescription() = 0;
    virtual float cost() = 0;
protected:

};

#endif //HEAD_FIRST_DESIGN_PARTTERN_BEVERAGE_H
