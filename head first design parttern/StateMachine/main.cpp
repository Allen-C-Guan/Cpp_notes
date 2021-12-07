//
// Created by Allen on 7/12/21.
//
#include "gumball_machine.h"
int main ()
{
    GumballMachine* gbm = GumballMachine::GetGumBallMachineObj();
    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();

    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();

    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();

    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();

    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();


    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();

    gbm->insertQuarter();
    gbm->turnCrank();
    gbm->dispense();
}
