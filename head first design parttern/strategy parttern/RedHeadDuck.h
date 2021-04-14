//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_REDHEADDUCK_H
#define HEAD_FIRST_DESIGN_PARTTERN_REDHEADDUCK_H
#include <iostream>
#include "Duck.h"
class RedHeadDuck : public Duck{
public:
    RedHeadDuck():Duck(){}
    void display() const override {
        std::cout << "this is RedHeadDuck" << std::endl;
    }
};

#endif //HEAD_FIRST_DESIGN_PARTTERN_REDHEADDUCK_H
