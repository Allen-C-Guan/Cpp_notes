#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <map>
#include <string>
#include <cassert>
#include <memory>
class Foo {
public:
    int a = 0;
    int b = 1;
    void printa() {
        std::cout << a << std::endl;
    }
    void printb() {
        std::cout << b << std::endl;
    }

    void print(void (Foo::*printFunc)()) {
        (this ->*printFunc)();
    }

    virtual void printVirtual1() {
        std::cout <<"this is virtual func1" << std::endl;
    }

    virtual void printVirtual2() {
        std::cout <<"this is virtual func2" << std::endl;
    }

    static void staticPrint() {
        std::cout << "this is static print" << std::endl;
    }
};

/*
 * 普通函数指针实际上保存的是函数体的开始地址，因此也称"代码指针"，以区别于 C/C++ 最常用的数据指针。
 * 而类成员函数指针就不仅仅是类成员函数的内存起始地址，还需要能解决因为 C++ 的多重继承、虚继承而带来的类实例地址的调整问题，
 * 所以类成员函数指针在调用的时候一定要传入类实例对象。
 */

void print() {}
int main() {
    Foo f;
    f.print(&Foo::printb);

    // 非虚成员函数指针的声明
    // 不同函数指针声明和初始
    void(*normalPtr)() = print;
    // 要在函数指针声明的基础上加上作用域，如果我只想申请一个普通函数指针则，且要对函数指针进行取值
    void(Foo::*ptr)() = &Foo::printa;
    // 成员函数指针的使用
    // 成员函数指针要绑定成员后才可以使用，且使用的时候要用 ".*" 而不是直接 "."
    (f.*ptr)();

    // 虚函数指针
    void(Foo::*virtualFuncPtr)() = &Foo::printVirtual1;
    // 虚函数的调用同样通过实例来调用
    (f.*virtualFuncPtr)();

    // 静态成员函数指针声明
    // static成员函数的本质和非成员函数指针没有任何区别，只是取值方式有区别而已，使用也没有任何区别
    // 这也佐证了，static函数只不过是作用域在类内的不同函数而已
    void (*staticPtr)() = &Foo::staticPrint;
    staticPtr();
}
