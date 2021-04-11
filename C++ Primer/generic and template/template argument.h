#include <iostream>
/*
 * *****************************   模板参数  ******************************
 * 模板参数与作用域：
 * 模板参数的作用域从模板声明开始，到声明或者定义之后
 *
 * 模板参数与变量：
 * 模板参数和普通参数和变量对于编译器而言都是一样的，因此模板参数也不能和普通参数和变量重名，且模板参数也会在作用域中
 * 隐藏作用域外同名参数或者变量名。
 *
 * 类的类型成员：
 * 对于模板而言，编译器是没法区分类的类型成员和static成员的。
 *      这是因为，与非模板类不同的是，模板类只有在实例化的时候 编译器才可以获得该模板类的定义，而类型成员和static成员在
 *      形式上是完全一致的，此时编译器由于不知道模板的定义，因此无法区分。而非模板类，由于编译器总是已知非模板类的全部定义，
 *      因此可以根据定义来区分static成员与类型成员。
 *
 * template<typename T>
 * T::value_type func() {...};
 * 这里没有写出模板类的定义，编译器和你一样，也不知道，请问你如何确定T::value_type是static变量还是类内定义的类内类型？
 * 你是没法区分的！
 * 编译器在你不制定的情况下，将这种形式的都当做static成员变量！而不是类内类型。那这里明显是类内类型，我们如何表示呢？
 *
 * template<typename T>
 * typename T::value_type func() {...};
 * 我们在这个参数前加上typename，声明这是个类型而不是变量，那么这个类型是T类内的类型。
 *
 *
 *
 * ******************************   默认模板实参 与 可调用对象作为模板参数  ***********************************
 * 新的c++标准既允许给类模板提供默认实参，也允许给函数模板提供模板。
 * 如下是利用模板，将*可调用类型*作为模板参数，因此这个函数就可以指定可调用对象！
 *
 *
 * *******************************    成员模板   ************************
 * 1. 非模板类的成员模板
 *      就比一般的成员函数多个自己成员的模板而已
 * 2. 模板类的成员模板
 *      要声明两个模板，先声明类模板，再声明成员模板
 *      使用的时候： 我们只要给出类模板的参数即可，函数模板参数编译器可以根据实参类型推断出，不需要指出！
 *
 *
 */


template<typename T = int, typename F = std::less<T>>
bool compare(const T &lhs, const T &rhs, F f = F()) {
    return f(lhs, rhs);
}

template<typename T>
struct Greater {
    bool operator() (const T &lhs, const T &rhs) {
        return lhs > rhs;
    }
};




template<typename T>
bool myCmpFunc (const T &lhs, const T &rhs) {
    return lhs < rhs;
}

auto lambda = [](const int &lhs, const int &rhs) {return lhs < rhs;};




/*
 * ***************************  控制实例化   ************************
 * 模板的实例化是在使用的时候完成的，而对于独立编译的c++而言，这导致即使相同类型的模板也可能会像普通的obj一样，在不同的
 * 编译单元中被实例化很多次。那么这会导致代码的急剧膨胀，因此我们可以通过控制实例化来避免重复实例化。
 *
 * 原理在于：
 * 1. 首先，你要保证该模板被实例化过
 * 2. 当使用extern的时候，就等于告诉编译器，你别在编译了，等linking的时候，让linker去找把，linker肯定能找到的。
 *
 * 采用如上手段，就可以只实例化一次，所有编译单元共用那一份实例化的内容。类似于单例模式！
 */

// 类的实例化
template class Greater<int>;
// 函数的实例化
template bool myCmpFunc(const int&, const int&);

// 类的声明
//extern template class Greater<int>;
//extern template bool myCmpFunc(const int&, const int&);


int main () {
    bool ret = compare<>(2,1);
    bool ret2 = compare<int, Greater<int>>(2, 1);
    bool ret3 = compare<int, decltype(myCmpFunc<int>)>(2, 1, myCmpFunc);
    bool ret4 = compare<int, decltype(lambda)>(2, 1, lambda);

    // 如上三种类型，均可以表达成如下形式！
    bool ret5 = compare<int, bool(const int&, const int&)>(2, 1, lambda);
    std::cout << "end" << std::endl;
}