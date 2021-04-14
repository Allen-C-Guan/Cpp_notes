//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_SQUEAK_H
#define HEAD_FIRST_DESIGN_PARTTERN_SQUEAK_H
#include "QuackBehavior.h"
#include <iostream>
class Squeak : public QuackBehavior {
    void quack () override {
        std::cout << "zhi zhi" << std::endl;
    }
};

#endif //HEAD_FIRST_DESIGN_PARTTERN_SQUEAK_H
