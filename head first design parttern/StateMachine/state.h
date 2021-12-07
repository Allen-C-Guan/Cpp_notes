//
// Created by Allen on 7/12/21.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_STATE_H
#define HEAD_FIRST_DESIGN_PARTTERN_STATE_H
class State {
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
};



#endif //HEAD_FIRST_DESIGN_PARTTERN_STATE_H
