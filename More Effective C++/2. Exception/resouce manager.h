//
// Created by Allen on 2021/6/14.
//

#ifndef MORE_EFFECTIVE_C___RESOUCE_MANAGER_H
#define MORE_EFFECTIVE_C___RESOUCE_MANAGER_H
#include <iostream>
#include <string>
/*
 * ********************** 用内存管理类管理row pointer ************************
 * 虽然我们不能完全避免指针的使用，但我们至少不应该使用局部对象的指针！这是危险且难以管理的。
 * 最简单的解决方法就是 包装一个管理类，而后通过管理类的栈上生命周期来帮忙管理这个局部对象的
 * 指针！！
 */


class Foo {
public:
    Foo() {
        std::cout << "Foo has been constructed" << std::endl;
    }
    ~Foo () {
        std::cout << "Foo has been destored" << std::endl;
    }
    int getA() {
        return a;
    }
    int a;
};

class FooManager {
public:
    FooManager(Foo *pf) : pf_(pf) {}
    ~FooManager() {
        delete pf_;
    }
    operator Foo* () { // 用转换函数来让管理类使用起来和原始pointer一样
        return this->pf_;
    }
    // 管理类要考虑其copy 和 assignment的管理，要小心管理
    FooManager(const FooManager&) = delete;
    FooManager& operator= (const FooManager&) = delete;

private:
    Foo *pf_;
};


void Print(Foo* pf) { // 当存在类型转换的时候，这个函数签名的函数也可以作用于管理类！！
    std::cout << pf->getA() << std::endl;
}

int main ()
{
    {
        FooManager f(new Foo());
        Print(f);
    }
}
#endif //MORE_EFFECTIVE_C___RESOUCE_MANAGER_H
