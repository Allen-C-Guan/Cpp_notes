#include <iostream>
#include <string>

/*
 * ******************  函数调用运算符  *****************
 * 函数调用运算符指的是：行为像函数一样的类，但更灵活，并可以储存状态
 *
 * 实用性；
 * 函数调用运算符可以作为泛型算法的实参。通过建立一个行为像函数一样的临时对象，来作为算法的操作部分
 *
 * 使用方法：
 * 1. 定义一个带有operator()的成员函数即可！
 *  例如，Foo定义了operator(), 这意味着Foo的任何实例比如f0, f1, f2等，都可以f0(a,b), f1(c),的去使用了.
 * 2. operator可以被重载，只要signature不完全一致即可
 *
 */

// 这只是个例子，并没有什么卵用
class Foo {
public:
    // 一个可以将任何int都转换成f中的int的函数
    int operator() (int otherInt) {
        return a;
    }
    // 一个可以将任何double 都转换成f中的double的函数
    double operator() (double otherD) {
        return d;
    }

    int a = 100;
    double d = 3.14;
};



int main ()
{
    Foo f;
    std::cout << f(99) << std::endl;
    std::cout << f(55.6) << std::endl;
}