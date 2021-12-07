//
// Created by Allen on 7/12/21.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_GUMBALL_MACHINE_H
#define HEAD_FIRST_DESIGN_PARTTERN_GUMBALL_MACHINE_H
#include "all_state.h"
#include <iostream>

class GumballMachine {
public:
    static GumballMachine* GetGumBallMachineObj() {
        GumballMachine* instance = new GumballMachine();
        return instance;
    }
    void releaseBall() {
        std::cout << "a gumball comes rolling out the slot..." << std::endl;
        if (count != 0) {
            count--;
        }
    }
public:
    // 所有的工作都交给currState来完成，currState不但负责动作，还负责维护GumballMachine的当前state。GumballMachine就变成一个空壳了。
    // 状态维护和动作都交给state了
    void insertQuarter()
    {
        currState->insertQuarter();
    }

    void ejectQuarter()
    {
        currState->ejectQuarter();
    }

    void turnCrank()
    {
        currState->turnCrank();
    }

    void dispense()
    {
        currState->dispense();
    }

public:
    // TODO 验证一下直接将子类指针cast为父类指针有没有什么问题？
    inline void SetState(State *newState) {
        currState = newState;
    }

    // 这里，你的成员是实例，如果你声明了const函数，意味着你的实例就是const的，你也不可以返回非底层const的成员指针
    inline State* const GetSoldState() {
        return &soldState;
    }

    inline State* const GetSoldOutState() {
        return &soldOutState;
    }

    inline State* const GetNoQuarterState() {
        return &noQuarterState;
    }

    inline State* const GetHasQuarterState() {
        return &hasQuarterState;
    }
    inline int GetCount() const {
        return count;
    }
private:
    SoldState soldState;
    SoldOutState soldOutState;
    NoQuarterState noQuarterState;
    HasQuarterState hasQuarterState;
    State *currState;
    int count;
private:
    // 创建一个单例模式
    GumballMachine():
        soldState(this),
        soldOutState(this),
        noQuarterState(this),
        hasQuarterState(this),
        currState(&noQuarterState),
        count(5) {}
    GumballMachine(const GumballMachine&) = delete;
    GumballMachine& operator= (const GumballMachine&) = delete;
    ~GumballMachine() = default;
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_GUMBALL_MACHINE_H
