//
// Created by Allen on 2021/4/14.
//

#include "Duck.h"
#include <iostream>
Duck::Duck(std::unique_ptr<FlyBehavior> flyBehavior, std::unique_ptr<QuackBehavior> quackBehavior)
        :pFly(std::move(flyBehavior)), pQuack(std::move(quackBehavior)) {

}

void Duck::swim() const {
    std::cout << "I am swimming" << std::endl;
}


void Duck::performFly() const {
    pFly->fly();
}

void Duck::performQuack() const {
    pQuack->quack();
}

void Duck::setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior) {
    pFly = std::move(flyBehavior);
}

void Duck::setQuackBehavior(std::unique_ptr<QuackBehavior> quackBehavior) {
    pQuack = std::move(quackBehavior);
}