//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_MALLARDDUCK_H
#define HEAD_FIRST_DESIGN_PARTTERN_MALLARDDUCK_H
#include <iostream>
#include <memory>
#include "Duck.h"
#include "FlyWithWings.h"
#include "Squeak.h"
class MallardDuck : public Duck {
public:
    MallardDuck() : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Squeak>()) {}
    void display() const override  {
        std::cout << "this is MallardDuck" << std::endl;
    };
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_MALLARDDUCK_H
