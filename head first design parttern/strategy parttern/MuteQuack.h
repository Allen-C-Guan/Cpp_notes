//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_MUTEQUACK_H
#define HEAD_FIRST_DESIGN_PARTTERN_MUTEQUACK_H
#include "QuackBehavior.h"
#include <iostream>
class MuteQuack : public QuackBehavior{
    void quack () override {
        std::cout << "silence" << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_MUTEQUACK_H
