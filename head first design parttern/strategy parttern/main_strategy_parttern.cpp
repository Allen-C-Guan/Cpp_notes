//
// Created by Allen on 2021/4/14.
//
#include <memory>
#include "Duck.h"
#include "MallardDuck.h"
#include "FlyRocketPowered.h"

int main () {
    MallardDuck mallardDuck;
    mallardDuck.performFly();
    mallardDuck.performQuack();
    mallardDuck.display();
    mallardDuck.swim();
    mallardDuck.setFlyBehavior(std::make_unique<FlyRocketPowered>());
    mallardDuck.performFly();
}
