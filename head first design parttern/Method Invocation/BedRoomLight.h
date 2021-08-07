//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_BEDROOMLIGHT_H
#define HEAD_FIRST_DESIGN_PARTTERN_BEDROOMLIGHT_H
#include "Light.h"
#include <iostream>
class BedroomLight : public Light
{
public:
    BedroomLight() = default;
    ~BedroomLight() = default;
    void on() override
    {
        std::cout << "Bedroom Light On" << std::endl;
    }

    void off() override
    {
        std::cout << "Bedroom Light Off" << std::endl;
    }
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_BEDROOMLIGHT_H
