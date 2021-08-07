//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_WASHROOMLIGHT_H
#define HEAD_FIRST_DESIGN_PARTTERN_WASHROOMLIGHT_H
#include "Light.h"
#include <iostream>
class WashRoomLight : public Light{
public:
    WashRoomLight() = default;
    ~WashRoomLight() = default;
    void on() override
    {
        std::cout << "washroom light on" << std::endl;
    }
    void off() override
    {
        std::cout << "washroom light off" << std::endl;
    }
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_WASHROOMLIGHT_H
