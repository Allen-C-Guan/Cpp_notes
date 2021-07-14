//
// Created by Allen on 2021/7/14.
//

#ifndef EFFECTIVE_CPP_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_H
#define EFFECTIVE_CPP_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_H
#include <memory>
#include <iostream>
/*
 * ************************* 了解typename的双重意义  ***************************
 * typename在模板中，起到一个指导编译器类型推断的作用！其可以告诉编译器某个嵌套从属名称是个类型而不是变量。
 *
 * 从属名称：(T::const_iterator)
 * 当template中出现的名称如果相依于某个template参数，称之为从属名称
 *
 * 嵌套从属名称：
 * 如果一个从属名称在class内呈嵌套状，则称之为嵌套从属名称
 *
 * 嵌套从属类型名称：(T::const_iterator)
 * 如果一个嵌套从属名称实际上是一个类而不是一个变量名，则称之为嵌套从属类型名称
 *
 * 因此，T::const_iterator，因为依赖于T，所以是个从属名称，又因为const_iterator是嵌套于T之内的，
 * 所以是个嵌套从属名称， 他本身又是个类型，而不是变量，因此是个嵌套从属类型名称。
 *
 * 在C++编译器解析模板的时候，当遇到如下这种情况时候会有两种可行的解释：
 * T::const_iterator* x;
 *
 * 1. 默认编译器会解析为：T::const_iterator 乘以 x，（恰巧外面有x变量）
 * 2. 声明一个T::const_iterator的指针变量为x
 *
 * 编译器是没有任何办法区分的，因此他怎么办呢？
 *
 * 编译器会默认：所有内嵌从属名称均不是个类型！而是个变量！
 * 因此编译器缺省行为就是解释1！但实际上我们需要的解释是解释2，这时候怎么办呢？
 * 我们需要在内嵌从属类型名称的前面加上typename，来声明该内嵌从属名称是个类型！而不是一个变量！
 *
 *
 * 例外：
 * 1. typename不能在base class list出现
 * 2. typename也不能在 member initialization list内出现。
 *
 *
 */
int x;
template <typename T>
void print2nd(const T& container)
{
    if (container.size() >= 2) {
        typename T::const_iterator iter(container.begin());
        iter++;
        int value = *iter; // value这个变量不依赖于T的类型

    }

    T::const_iterator* x;  // 默认编译器会解析为：T::const_iterator 乘以 x，恰巧外面有x变量就坏了
    typename T::const_iterator* x; // 这是声明一个T::const_iterator的指针变量为x
}

int main ()
{

}
#endif //EFFECTIVE_CPP_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_H
