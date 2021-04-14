//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_FLYWITHWINGS_H
#define HEAD_FIRST_DESIGN_PARTTERN_FLYWITHWINGS_H
#include "FlyBehavior.h"
#include <iostream>
class FlyWithWings : public FlyBehavior {
public:
    void fly() override {
        std::cout << "flying with wings"  << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_FLYWITHWINGS_H
