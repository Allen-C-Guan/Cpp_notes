//
// Created by Allen on 2021/7/10.
//

#ifndef EFFECTIVE_CPP_HIDING_NAME_H
#define EFFECTIVE_CPP_HIDING_NAME_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>

/*
 * *****************************  避免遮掩继承而来的名字  ***************************
 * 在C++遮掩规则所做的唯一的事情就是：遮掩名字！ 至于类型是否一致，编译器丝毫不在意！
 *
 * C++编译器搜索名字的顺序：
 * local -> Derived -> Base -> global
 *
 * 我们看下面这个例子，我们发现，尽管在C++体系中，子类应该继承父类的所有成员，但是所有父类中命名为mf1
 * 和mf3中的函数都被子类中的同名函数遮掩掉了！！！换句话说，从名字查找的角度来看，(实际上子类还是可以显示调用的）
 * Base::mf1和Base::mf3不再被Derived继承了！！
 *
 * 并且我们发现，上述名字遮掩规则，对于函数signature不同的，不管是virtual或者non-virtual的全部
 * 适用。又是那句话，编译器只看名字，不看类型！
 *
 * 因此我们发现，作用域的名字遮掩会导致子类无法直接overloading父类的函数（overloading意味着重名，而重名
 * 意味着名称覆盖），但是从继承的角度来看，这种性质破坏了继承的诉求->子类可以获得父类的一切！
 *
 * 那么名字遮掩有什么好处？标准协会为什么要名字遮掩？
 * 这是为了防止derived class不小心重载了疏远的base class（曾曾曾爷爷）的函数，而这是程序员所不知道的。
 *
 * 那么如何重载呢？
 * using 可以帮忙，既让Base相关的函数在Derived作用域内见
 */

class Base
{
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int) {
        std::cout << "Based" << std::endl;
    }
    virtual void mf2() {
        std::cout << "Based" << std::endl;
    }
    void mf3 () {
        std::cout << "Based" << std::endl;
    }
    void mf3 (double) {
        std::cout << "Based" << std::endl;
    }
};

class Derived : public Base
{
public:
    using Base::mf1;
    using Base::mf3;  // 这里的using 只有名字即可，因为我们名字遮掩的原因就是名字，只要Base中该名字在Derived中可见即可
    // 从这之后，子类就可以overloading这两个名字的函数了！
    virtual void mf1() {
        std::cout << "derived" << std::endl;
    }
    void mf3() {
        std::cout << "derived" << std::endl;
    }
    void mf4() {
        std::cout << "derived" << std::endl;
    }
};
int main()
{
    Derived d;
    d.mf1();
//    d.mf1(9);   // 这是不行的，因为名字的遮掩
    d.mf2();
//    d.mf3(10);  // 这个也不行

}
#endif //EFFECTIVE_CPP_HIDING_NAME_H
