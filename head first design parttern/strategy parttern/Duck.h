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
/*
     * ****************************   策略模式   *******************************
     *
     * 策略模式的精髓在于，将子类中特有的部分，从**（虚）函数** 变成了**接口类型的成员变量 + 调用接口的真函数**。
     * 这种做法既可以保证超类中包含了子类中的所有相同的接口属性，也可以让子类之间的个性属性互相解耦。
     *
     * 在面向对象设计的过程中，类型的组合要优于继承，这里我们是将一个行为接口类和一个实体接口类组合了起来，而不是采用多级
     * 继承的形式来设计的！ 这种设计模式通常更优于继承！方便维护，易读，过多的继承会导致继承混乱。
     *
     * 该策略模式实现的原理有两个
     * 1. 成员变量解耦子类之间的关系
     * 首先我们要知道，成员变量和函数在继承体系中的最大区别在于，成员变量在子类中是互不影响的，而函数在子类之间是互相影响的。如果超类中
     * 的某个函数发生了变化，则所有子类都受影响，导致子类之间互相耦合。但成员变量不同，子类可以有自己特有的成员变量。
     *
     * 2. 接口类的成员变量可以实现子类的个性化特征
     * 成员变量固然是好，但是由于子类个性化的需求，需要成员变量可以有个性化的定制，因此我们将成员变量设计成接口类，而每个子类有自己
     * 的接口实现。而父类中只需要调用接口即可保证子类的个性被保留。
     *
     * 通过如上两个设计，将成员变量的解耦特性 + 接口的个性化 可以将函数解耦！
     *
     *
     * 优点：
     * 1. 相比于超类的实函数
     *      超类如果采用实函数，则子类的个性化需要对父类进行覆盖，而如果多个子类同时拥有与父类不同的，但在子类之间确是相同的特性的时候，
     *      所有子类都要采用相同的方法覆盖父类，这让代码重复率高！
     *      更严重的是，父类的修改导致子类之间不好维护。
     *      而且由于你的实现是利用函数完成的，这意味着你的行为在运行的时候无法更改，因为运行时候，你不能重写函数啊！
     *
     * 2. 相比于超类的虚函数
     *      这意味着所有子类都要重写父类，代码重复更严重。
     *
     *  但我们的接口却不一样，具有相同个性的子类之间可以共用一个接口实现，且互相没有耦合。
     *  而且在运行的时候，我们可以重新给行为赋值来改变其行为。因为成员变量在运行的时候可以被更改！
     *
     *  扩展：
     *  在这种设计模式下，当我需要扩展的时候
     *  只要新实现一个接口类，然后子类初始化的时候，新写一个采用这个新实现的接口类即可
     *  如果子类行为扩展，只要超类里多个属性，在子类里新增接口即可
     *
     */
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
