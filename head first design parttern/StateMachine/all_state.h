//
// Created by Allen on 7/12/21.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_ALL_STATE_H
#define HEAD_FIRST_DESIGN_PARTTERN_ALL_STATE_H
#include "state.h"
class GumballMachine;
class SoldState : public State {
public:
    // 要求每个实体的状态子类都掌握同一个gumballMachine，这样state状态可以反过来操控gumballMachine的状态和行为
    SoldState(GumballMachine *gumballMachine) : gumballMachine_(gumballMachine) {};

    // 每个实体的状态子类都只管自己当前状态下的所有行为，不需要管其他状态下的行为。这里面说的行为，不光是自身的操作，还包括操作machine的行为。
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
private:
    GumballMachine *gumballMachine_;
};

class SoldOutState : public State {
public:
    SoldOutState(GumballMachine *gumballMachine) : gumballMachine_(gumballMachine) {};
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
private:
    GumballMachine *gumballMachine_;
};

class NoQuarterState : public State {
public:
    NoQuarterState(GumballMachine *gumballMachine) : gumballMachine_(gumballMachine) {};
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
private:
    GumballMachine *gumballMachine_;
};

class HasQuarterState : public State {
public:
    HasQuarterState(GumballMachine *gumballMachine) : gumballMachine_(gumballMachine) {};
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
private:
    GumballMachine *gumballMachine_;
};

#endif //HEAD_FIRST_DESIGN_PARTTERN_ALL_STATE_H
