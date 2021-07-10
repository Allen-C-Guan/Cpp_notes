//
// Created by Allen on 2021/7/10.
//

#ifndef EFFECTIVE_CPP_DIFFERENTIATE_BETWEEN_ITF_AND_IMPLEMENT_H
#define EFFECTIVE_CPP_DIFFERENTIATE_BETWEEN_ITF_AND_IMPLEMENT_H
#include <iostream>
/*
 * ****************************  区分接口继承和实现继承  ***********************************
 * 在继承体系中，子类继承父类也可以分成两部分，继承接口，继承实现，那么我们该如何选择继承接口和继承实现的呢？
 * 先说原则：
 *
 * 1. 子类只继承接口，请使用pure function
 *  当父类无法为此函数提供合理的缺省实现的时候，因此只允许子类继承父类的接口，而必须完成属于自己的实现！pure function
 *  就可以实现该诉求
 *
 * 2. 子类继承了该函数的接口和缺省实现，impure function
 *  当父类可以给出一个合理的缺省实现的时候，子类可以自行选择是否重写自己的实现，还是使用父类缺省的实现，此时就应该使用
 *  impure function
 *
 * 3. 子类需要继承函数的接口以及一份强制性实现,该实现在继承体系中就不应该被改变，non-virtual function
 *  当你觉得该函数的接口和实现在继承体系中，就是不该被改变（包括接口和实现都应该不变），这个时候就需要使用non-virtual
 *  function来实现
 *
 * 我们举例说明！
 *
 */

class Shape {  // shape是一个抽象的类，不是某一个具体的类，因此他是一个抽象类，也不允许实例化
public:
    virtual void draw() = 0;  // 我们认为任何具体的图形都应该有自己的draw的方式，没有办法提供一个合理的缺省值

    virtual void error() // 我们认为当某个具体的形状出现异常的时候，都应该要处理异常，如果子类不提供自己特有的处理
                         // 异常的实现，则父类会接管异常处理的实现。
    {
        // do something
    }

    int objectId() { // 任何具体的形状都会通过相同的算法获取自己的ID，该算法在整个shape体系就不该有不同，因此父类
                     // 强制子类同时继承了接口和具体实现，
        // do something
    }
};


/*
 * ******************** 切断接口与缺省实现之间的联系 **********************
 * 首先为何我们会有这么奇怪的诉求？
 *
 * 试想：抽象类airplane，有子类：空客，波音，和直升机等。
 * airplane提供接口
 * virtual void fly () = 0;
 * 而绝大部分子类对于fly的实现都一致，都是用翅膀来飞。于是我们似乎可以给子类提供一个缺省实现，于是我们
 * 将fly从pure function 改为 impure function了。
 * virtual void fly ( ) { // 用翅膀飞 }
 *
 * 可是当我们设计直升机的时候，也忘了override fly了，导致直升机的飞行行为也是用翅膀飞，当我们调用接口
 * helicopter.fly()的时候，就会酿成大祸！！！
 *
 * 那么上面的设计到底是哪里出现了问题呢？
 * 问题不在于Airplane提供了缺省实现，而在于子类并没有说"我就要父类的缺省实现"就已经继承了父类的实现！
 * 换句话说就是，父类给子类默默的安排了子类不想要的实现，但是子类却浑然不知。如何解决上面的问题呢？
 *
 * 既切断接口和缺省实现的联系！！！！！，只有子类说我要的时候，才可以继承父类的接口，如果子类没说要，
 * 就必须要重写实现！！
 *
 * 具体实现方法：
 * 父类的public中只提供接口（pure virtual)！protect中提供缺省实现（non-virtual），子类如果想要父类的实现
 * 需要override 接口，并在接口中调用缺省实现！
 *
 * 举例：
 */

class AirPlane
{
public:
    virtual void fly() = 0;
protected:
    void defaultFly() { // 这个必须是protected，因为使用飞机的人才不关系你怎么飞的呢
        // 用翅膀来飞
    }
};

class AirBus : public AirPlane
{
public:
    void fly() override
    {
        defaultFly();   // 这里AirBus主动说我就要defaultFly的行为，且这么写是inline的，也保证了性能
    }
};

class Helicopter : public AirPlane
{
public:
    void fly () override // 这里Helicopter可没说我要defaultFly行为，如果不自己重写，就会报错！
    {
        // 螺旋升天。。
    }
};

/*
 * ************ 通过给pure function 提供实现来减少命名污染 *************
 * 上面我们用defaultFly 函数来将default 实现和interface切割开，虽然效果很好，但是你为啥要新搞一个名字
 * 我用的时候记这么多名字太恶心了，为了解决这个问题，我们可以给pure function提供实现！
 *
 * 下面就是了，fly在声明的时候明明就是个pure function，但是我依然可以给他提供定义，那么在Boeing类里
 * 就可以直接调用了，这种写法就避免再起一个名字了，用的时候也比较无脑，省心！
 *
 */
void AirPlane::fly()
{
    std::cout << "fly with default" << std::endl;
}

class Boeing : public AirPlane
{
public:
    void fly () override
    {
        AirPlane::fly();
    }
};

int main ()
{
    Boeing b;
    b.fly();
}
#endif //EFFECTIVE_CPP_DIFFERENTIATE_BETWEEN_ITF_AND_IMPLEMENT_H
