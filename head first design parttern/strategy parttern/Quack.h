//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_QUACK_H
#define HEAD_FIRST_DESIGN_PARTTERN_QUACK_H
#include "QuackBehavior.h"
#include <iostream>

class Quack : public QuackBehavior {
    void quack() override {
        std::cout << "gua gua" << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_QUACK_H
