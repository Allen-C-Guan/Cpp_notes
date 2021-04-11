#include <iostream>
/*
 * **************************  函数类型与函数指针  **********************
 */

template<typename T> void Foo(T t) { }


int func(const int&, int&);
int main () {
    // 对应的函数指针是
    int(*pt)(const int&, int&) = func;
    // 对应的函数类型是
    // int(const int&, int&);
    Foo<int(const int&, int&)>(func);
    Foo<int(const int&, int&)>(*pt); // 函数指针解引用以后也是函数类型

    // 函数类型不能作为实参，但是函数指针可以作为实参返回，或者入参，但是函数类型可以作为模板的实参！！因为他是类型！

    typedef decltype(func) func2; // func2是函数类型
    typedef decltype(func) *pfunc; //pfunc是函数指针类型！
}