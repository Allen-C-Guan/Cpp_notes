//
// Created by Allen on 2021/7/4.
//

#ifndef EFFECTIVE_CPP_MINIZE_CASTING_H
#define EFFECTIVE_CPP_MINIZE_CASTING_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>

/*
 * *************************  尽量少用casting  ****************************
 * 1. 少做cast，多少会影响效率，特别是dynamic cast，其效率会很低
 * 2. 试图把cast封装在函数内部，不对外暴露
 * 3. 使用新式的cast而不是旧的
 *
 *
 *
 */


/*
 * 错误1：乱用cast
 */

class Foo {
public:
    Foo (int a) : a_(a) {}
private:
    int a_;
};

void printFoo(Foo f)
{
    // todo
}

void test1 () // 乱用cast
{
    printFoo(static_cast<Foo>(1)); // 这虽然和Foo(1)的效果一样，但就是很蠢
};


/*
 * 错误2：对子类指针用static_cast
 * static_cast<Base>(*this)的结果是用this的copy构造函数在构造一个副本，然后调用副本的add函数
 * 这和你的预期（更改this的值）完全不一致的！！这是非常愚蠢的行为
 */
class Base
{
public:
    virtual void AddVal() {
        val++;
    }
    int val = 10;

    virtual void print()  // 父类中什么也不做！
    {
        // do nothing
    }
};
class Derived : public Base
{
public:
    void AddAndPrint()
    {
        static_cast<Base>(*this).AddVal();
        std::cout << val << std::endl;
    }

    void print() override  // 有些子类override，有些子类不override，这样就避免了动态cast
    {
        std::cout << "this is base" << std::endl;
    }
};

void test2 ()
{
    Derived d;
    d.AddAndPrint();
}

/*
 * *******************  更换设计来避免使用dynamic_cast  *****************
 * 你之所以需要dynamic-cast，是因为你手里只有Base指针，可是你有需要使用个别子类独有的方法或者成员
 * 因此你就需要使用dynamic_cast，但dynamic_cast的性能比较差，我们可以通过设计来避免动态转换
 *
 * 最常用的方法就是：将子类功能提升到父类中去，并在父类中提供default值（什么都不做），
 * 那么只有个别子类重写了该方法，而其他子类不重写该方法。这样，即使你手里只有父类指针。
 * 你也可以无脑调用该接口，而不用去做dynamic_cast了。
 *
 */



int main()
{
    test2();
}
#endif //EFFECTIVE_CPP_MINIZE_CASTING_H
