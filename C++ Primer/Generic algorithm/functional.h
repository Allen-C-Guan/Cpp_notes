//
// Created by Allen on 2021/3/7.
//

#ifndef C___PRIMER_FUNCTIONAL_H
#define C___PRIMER_FUNCTIONAL_H
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
/*
     * *****************    bind    ***************
     * auto newCallable = bind(callable, arg_list);
     * callable表示函数，argList是callable按顺序的入参。
     * bind 是一种函数适配器，作用是将一个可调用对象，变成一个新的调用对用对象，从而适应不同的参数列表。
     * 不严格的说，bind就是函数的一种封装，该封装可以让函数的入参列表发生变化。减少，更改顺序！
     *
     * 若auto g = std::bind(f, a, b, std::placeholders::_2, c, std::placeholders::_1);
     * 他可以把g(std::placeholders::_1, std::placeholders::_2) 映射为
     * f(a, b, std::placeholders::_2, c, std::placeholders::_1)来使用！
     *
     * 这里std::placeholders::_n表示的这个newCallable的传入参数的位置（位置从1开始计数）
     * 但arg_list的顺序必须和callable的顺序一致。
     *
     */
int func1(std::string s, int val, double d) {
    return val > d ? val : static_cast<int> (d);
}

int main() {

    auto funcBind = std::bind(func1, "allen", std::placeholders::_1, 3.14);
    int ret = funcBind(2); // 这就呈现了一个完全不同的函数了。你根本不知道内层函数是需要三个参数的。




}
#endif //C___PRIMER_FUNCTIONAL_H
