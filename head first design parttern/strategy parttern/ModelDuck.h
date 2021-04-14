//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_MODELDUCK_H
#define HEAD_FIRST_DESIGN_PARTTERN_MODELDUCK_H
#include "Duck.h"
#include "memory"
#include "FlyNoWay.h"
#include "MuteQuack.h"
#include "iostream"
class ModelDuck : public Duck {
public:
    ModelDuck()
            :Duck(std::make_unique<FlyNoWay>(), std::make_unique<MuteQuack>()) {
    }
    void display () const override {
        std::cout << "this is ModelDuck" << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_MODELDUCK_H
