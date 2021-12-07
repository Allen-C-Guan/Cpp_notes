#include "all_state.h"
#include <iostream>
#include "gumball_machine.h"
// SoldState
void SoldState::insertQuarter()
{
    std::cout << "plz wait, we are already giving you a gumball" << std::endl;
}

void SoldState::ejectQuarter()
{
    std::cout << "sorry, you already turned the crank" << std::endl;
}

void SoldState::turnCrank()
{
    std::cout << "turning twice doesn't get you another gumball" << std::endl;
}

void SoldState::dispense()
{
    gumballMachine_->releaseBall();
    if(gumballMachine_->GetCount() > 0) {
        gumballMachine_->SetState(gumballMachine_->GetNoQuarterState());
    } else {
        std::cout << "oops, out of gumballs!" << std::endl;
        gumballMachine_->SetState(gumballMachine_->GetSoldOutState());
    }
}

// SoldOutState
void SoldOutState::insertQuarter()
{
    std::cout << "you cann't insert a quarter, the machine is sold out" << std::endl;
}

void SoldOutState::ejectQuarter()
{
    std::cout << "you cann't eject, you haven't insert a quarter yet" << std::endl;
}

void SoldOutState::turnCrank()
{
    std::cout << "you turned, but there are no gumballs" << std::endl;
}

void SoldOutState::dispense()
{
    std::cout << "no gumball dispensed" << std::endl;
}

// NoQuarterState
void NoQuarterState::insertQuarter()
{
    std::cout << "you inserted a quarter" << std::endl;
    gumballMachine_->SetState(gumballMachine_->GetHasQuarterState());
}

void NoQuarterState::ejectQuarter()
{
    std::cout << "You haven't inserted a quarter" << std::endl;
}

void NoQuarterState::turnCrank()
{
    std::cout << "you turned, but this is no quarter" << std::endl;
}

void NoQuarterState::dispense()
{
    std::cout << "you need to pay first" << std::endl;
}

// HasQuarterState
void HasQuarterState::insertQuarter()
{
    std::cout << "you can not insert another quarter" << std::endl;
}

void HasQuarterState::ejectQuarter()
{
    std::cout << "Quarter returned" << std::endl;
    gumballMachine_->SetState(gumballMachine_->GetNoQuarterState());
}

void HasQuarterState::turnCrank()
{
    std::cout << "you tured..." << std::endl;
    gumballMachine_->SetState(gumballMachine_->GetSoldState());
}

void HasQuarterState::dispense()
{
    std::cout << "no gumball dispensed" << std::endl;
}