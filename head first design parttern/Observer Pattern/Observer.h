//
// Created by Allen on 2021/4/22.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_OBSERVER_H
#define HEAD_FIRST_DESIGN_PARTTERN_OBSERVER_H
class Observer {
public:
    virtual void update (int temperature, int humidity, int pressure) = 0;
};




#endif //HEAD_FIRST_DESIGN_PARTTERN_OBSERVER_H
