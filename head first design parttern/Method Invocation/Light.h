//
// Created by Allen on 2021/8/7.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_LIGHT_H
#define HEAD_FIRST_DESIGN_PARTTERN_LIGHT_H
#include <iostream>

class Light {
public:
    Light() = default;
    virtual ~Light() = default;
    virtual void on() = 0;
    virtual void off() = 0;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_LIGHT_H
