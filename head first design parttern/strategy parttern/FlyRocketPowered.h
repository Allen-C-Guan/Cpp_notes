//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_FLYROCKETPOWERED_H
#define HEAD_FIRST_DESIGN_PARTTERN_FLYROCKETPOWERED_H
#include "FlyBehavior.h"
#include <iostream>
class FlyRocketPowered : public FlyBehavior{
public:
    void fly() override {
        std::cout << "flying with rocket" << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_FLYROCKETPOWERED_H
