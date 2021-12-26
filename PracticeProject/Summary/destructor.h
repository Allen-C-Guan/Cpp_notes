//
// Created by Allen on 26/12/21.
//

#ifndef SUMMARY_DESTRUCTOR_H
#define SUMMARY_DESTRUCTOR_H
#include <iostream>

namespace {
    class A {
    public :
        A() { std::cout <<  "A has been constructed" << std::endl;}
        ~A() { std::cout <<  "A has been destroyed" << std::endl;}
    };

    class B {
    public:
        B() { std::cout <<  "B has been constructed" << std::endl;}
        ~B() {std::cout << "B has been destroyed" << std::endl;}
    };

    class C {
    public:
        C() { std::cout <<  "C has been constructed" << std::endl;}
        ~C() {
            std::cout << "C has been destroyed" << std::endl;
        }

        // 通过声明顺序看出，其构造顺序为，先初始化a，接着是b，（这也是构造函数扩张的例子），最后执行构造函数内容，打印C
        // 其析构顺序正好返回来，先执行函数体，打印c，在析构b，在析构a。
        A a;
        B b;
    };
}


void TestDestructor () {
    {
        C c;
    }
    std::cout << "\n" << std::endl;


};
#endif //SUMMARY_DESTRUCTOR_H
