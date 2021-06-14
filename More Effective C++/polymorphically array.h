//
// Created by Allen on 2021/6/14.
//

#ifndef MORE_EFFECTIVE_C___POLYMORPHICALLY_ARRAY_H
#define MORE_EFFECTIVE_C___POLYMORPHICALLY_ARRAY_H
#include <iostream>
/*
 * ******* 不要用处理多态的方式处理数组  ********
 * 这种方式依赖编译器的行为，C++对此是没有定义的行为！
 * 这是因为，数组的索引，本质上是指针偏移的语法糖而已，而父类与子类size通常是不一致的。那么
 * 当你使用父类指针来索引子类数组的时候，由于其偏移量是父类的size，而不是子类的size，这会导致
 * 偏移出现了错误，从而出现未定义的行为！
 *
 * 但是对于有些编译器，比如g++，当父类存在虚函数的时候，由于vptr和vtable以及vtable中的typeid的存在
 * 让其数组的索引对应的偏移量根据typeid的实际类型来做出改变，从而让多态数组得以正常运行！
 *
 * 但我们尽量还是不要依赖编译器的行为来设计！
 *
 * 当我们真的需要批量处理的时候，可以采用指针数组的形式，而不是对象数组
 *
 */
class Base {
public:
    int a;
//    virtual ~Base() = default; // 当没有虚函数的时候，偏移量就会按照base的size来处理
};

class Derived : public Base{
public:
    float b;
};

void Print(Base b[]) {
    for (int i = 0; i < 5; i++) {
        std::cout << b[i].a << std::endl;
    }
}


int main() {
    Derived dArr[5];
    dArr[0].a = 1;
    dArr[1].a = 2;
    dArr[2].a = 3;
    dArr[3].a = 4;
    dArr[4].a = 5;
    Print(dArr);
    std::cout << "Ending" << std::endl;
    return 0;
}

#endif //MORE_EFFECTIVE_C___POLYMORPHICALLY_ARRAY_H
