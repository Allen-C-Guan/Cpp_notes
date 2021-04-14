//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_DUCK_H
#define HEAD_FIRST_DESIGN_PARTTERN_DUCK_H

#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "FlyWithWings.h"
#include "Quack.h"
#include "memory"

class Duck {
private:
    std::unique_ptr<FlyBehavior> pFly;
    std::unique_ptr<QuackBehavior> pQuack;
public:
    Duck(std::unique_ptr<FlyBehavior> flyBehavior = std::make_unique<FlyWithWings>(),
         std::unique_ptr<QuackBehavior> quackBehavior = std::make_unique<Quack>());
    virtual ~Duck() = default;
    Duck(const Duck&) = delete;
    Duck& operator= (const Duck&) = delete;

    void swim() const;
    void performQuack() const;
    void performFly() const;
    void setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior);
    void setQuackBehavior(std::unique_ptr<QuackBehavior> quackBehavior);
    virtual void display() const = 0;
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_DUCK_H
