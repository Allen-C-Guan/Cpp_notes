//
// Created by Allen on 2021/4/14.
//

#include "FlyBehavior.h"
#include <iostream>
class FlyNoWay : public FlyBehavior {
public:
    void fly() override {
        std::cout << "fly no ways" << std::endl;
    }
};