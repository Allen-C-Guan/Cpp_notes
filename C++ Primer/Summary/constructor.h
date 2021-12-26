//
// Created by Allen on 26/12/21.
//

#ifndef SUMMARY_CONSTRUCTOR_H
#define SUMMARY_CONSTRUCTOR_H
#include <iostream>
namespace constructor{
    class Bar {
    public:
        Bar() : c(10) {}

        int c;
    };

    class Foo {
    public:
        int a;  // 编译器不需要对内置类型进行初始化，因为a（内置类型）的初始化只需要知道a占内存的大小即可。
        double b;
        Bar bar; // 但是如果不生成一个合成默认构造函数，其bar成员不知道该如何初始化，因此Foo会合成一个默认构造函数。

        // 其默认构造函数长的如下这样
//    Foo() : bar(Bar()) {}
        // 这个默认构造函数会调用bar的默认构造函数来初始化bar的内容，因此该默认构造函数中会包含一次函数调用！！
    };


// 该类型，由于其成员均为内置类型，因此编译器只需要知道int a和int b的内存大小即可，因此，不需要做任何除了分配内存之外的额外事情，
// 即可完成Goo的实例化，因此Goo不会合成默认构造函数。因此Goo的实例化的过程中，编译器不会做任何事情。因此a和b的值都是未定义的。
    class Goo {
    public:
        int a;
        int b;
    };

    class Base {
    public:
        Base() : a(3), b(4) {}

        int a;
        int b;
    };

    class Derived : public Base {
    public:
        Derived() : c(5) {}
        // 实际上 这个构造函数被扩张为如下部分：
//    Derived(): Base(), c(9) {}

    public :
        int c;
    };
}

void TestConstructor() {
    using namespace constructor;
    Foo f;
    std::cout << "f.a = " << f.a << std::endl;
    std::cout << "f.b = "<< f.b << std::endl;
    std::cout << "f.bar.c = " << f.bar.c << std::endl;

    Goo g;
    std::cout << "\ng.a = " << g.a << std::endl;
    std::cout << "g.b = "<< g.b << std::endl;

    Derived d;
    std::cout << "\nderived.a = " << d.a << std::endl;
    std::cout << "derived.b = " << d.b << std::endl;
    std::cout << "derived.c = " << d.c << std::endl;
}

#endif //SUMMARY_CONSTRUCTOR_H
