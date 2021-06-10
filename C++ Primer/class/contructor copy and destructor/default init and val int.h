//
// Created by Allen on 2021/3/14.
//

#ifndef C___PRIMER_DEFAULT_INIT_AND_VAL_INT_H
#define C___PRIMER_DEFAULT_INIT_AND_VAL_INT_H
#include <iostream>
/*
 * 默认初始化与值初始化的区别
 * 默认初始化会产生变量可能产生未定义的行为！而值初始化总会给变量默认的初值！
 *
 * 默认初始化指的是：定义变量时没有指定初值时进行的**初始化操作**；该操作可能会导致变量初值为定义
 * ie. int a;
 *
 * 值初始化：值初始化是指使用了**初始化器**（即使用了圆括号或花括号）但却没有提供初始值的情况。变量初值被定义为默认值。
 * ie. int a = int();
 * 
 * 当你存在初始化动作的时候，等于在告诉编译器，你希望编译器能给与该对象进行初始化（默认初始化，默认构造函数，或者内置类型的0值初始化），
 * 但是如果你连这个动作都没有，那意味着，你并没有要求编译器对初始值做任何约束，你得到的将都是脏数据！！
 * 
 * 因此，默认初始化和值初始化的区别并不在于是否给出了初值（因为都没有给初值），而在于是否给出了初始化操作。
 * 值初始化给出了初始化操作（调用了初始化器），只是没给值而已。但默认初始化连初始化操作都没给出。
 * 
 *
 *
 * 那么两者分别在什么情况下会发生呢？
 *
 * 内置类型：
 * 默认初始化：作用块之内数组或者变量都时候，int a; 会导致未定义。
 * 值初始化：作用块之外（全局变量），或静态变量时候，被执行值初始化。因为该值被存储在静态内存中
 *
 *
 * 类类型：
 * 值初始化：没有类成员的类，在任何作用域都会执行值初始化！即调用默认构造函数或者合成构造函数来初始化。
 *  tips：默认构造函数：指的就是没有入参都构造函数，既可以是自定义都默认构造函数，也可以是编译器给的合成构造函数。
 * 默认初始化：
 * 1。类类型中都类成员，且使用该类使用了合成构造函数
 * 2。类成员，在没有在构造函数中显示的初始化的时候。
 *
 * array：
 * 给定数量少于size的时候，剩余的内容被执行值初始化
 *
 * 合成构造函数对于含有类类型成员的类而言，是非常不可靠的！！因为合成构造函数不能保证任何时候该类的初始化都会进行值初始化。
 */

class InFoo{
public:
    int a;
    std::string s;
};
class Foo {
public:
    int a;
    double d;
    std::string s;
    InFoo i;
};

int g_int;
Foo g_f;
int main()
{
    // 内置类型
    int local_int;
    static int local_static_int;
    // global 和 static由于是存在特殊的内存区域中的，因此是一定会被值初始化的
    std::cout << g_int << std::endl;
    std::cout << local_static_int << std::endl;
    // 但放在stack中但local var却因为运行速度但要求，没有被值初始化。值是为定义的
    std::cout << local_int << std::endl;

    // 类类型在作用块时（stack上的时候）
    // 类类型，在没有类类型成员的时候，总会执行值初始化，即调用合成构造函数或默认构造函数对每个内置类型进行值初始化。
    // 但当类类型存在类类型成员的时候，且没有默认构造函数的时候，会调用合成构造函数，此时不会对内置类型进行值初始化！内置类型是为定义。

    // 但类类型是静态或者global的时候，依然会被值初始化的！不管有没有类类型成员！
    Foo local_f;
    static Foo local_static_f;
    std::cout << "g_f" << std::endl;
    std::cout << g_f.a << std::endl;
    std::cout << g_f.d << std::endl;
    std::cout << g_f.s << std::endl;
    std::cout << g_f.i.a << std::endl;
    std::cout << g_f.i.s << std::endl;

    std::cout << "local_f" << std::endl; // 未定义
    std::cout << local_f.a << std::endl;// 未定义
    std::cout << local_f.d << std::endl;// 未定义
    std::cout << local_f.s << std::endl;// 未定义
    std::cout << local_f.i.a << std::endl; // 有定义
    std::cout << local_f.i.s << std::endl; // 有定义

    std::cout << "local_static_f" << std::endl;
    std::cout << local_static_f.a << std::endl;
    std::cout << local_static_f.d << std::endl;
    std::cout << local_static_f.s << std::endl;
    std::cout << local_static_f.i.a << std::endl;
    std::cout << local_static_f.i.s << std::endl;
}
#endif //C___PRIMER_DEFAULT_INIT_AND_VAL_INT_H
