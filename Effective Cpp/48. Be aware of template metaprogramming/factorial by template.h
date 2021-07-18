//
// Created by Allen on 2021/7/18.
//

#ifndef EFFECTIVE_CPP_FACTORIAL_BY_TEMPLATE_H
#define EFFECTIVE_CPP_FACTORIAL_BY_TEMPLATE_H
#include <iostream>
#include <string>

/*
 * template 本身就是一个图灵完备机，也就说是，理论上，我们可以做到，编译结束的时候，结果就已经算出来了，
 * 根本不需要运行时计算！
 *
 * 比如如下一个例子，这就是用编译时间来换运行时间的一个例子
 */
template<unsigned n>
struct Factorial
{
    enum {value = n * Factorial<n-1>::value};
};

template<>
struct Factorial <0>
{
    enum {value = 1};
};

int main ()
{
    std::cout << Factorial<5>::value << std::endl;
    std::cout << Factorial<10>::value << std::endl;
}
#endif //EFFECTIVE_CPP_FACTORIAL_BY_TEMPLATE_H
