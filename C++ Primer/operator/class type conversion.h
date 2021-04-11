#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>
#include <functional>

/*
 * *************************   类型转换   **************************
 * 我们之前利用constructor，已经实现了从其他类型的数据，转换成为当前类型的数据的过程了。那么
 * 今天这里要介绍的是 把当前类型的数据转换成为其他类型的数据。既：
 * Foo f = Foo(g); // constructor 完成的
 * Goo g = f; // 类型转换函数完成的（不需要Goo有可以从Foo到Goo的constructr）
 *
 * 使用方法：
 * operator changedToType() const {
 *      return changedToType的obj;
 * }
 * 如上所示，注意事项：
 * 1. 不能声明return的type，return type已经被 changedToType指定了
 * 2. 必须是const的
 * 3. 不能有入参，因为是匿名转换，本就不能有入参。
 * 4. 必须是成员函数
 * 5. 类型转换不能是数组和函数，但是指针和引用是可以的！
 *
 * explicit的类型转换
 * 我们可以把类型转换函数声明为explicit，这时候，编译器不会自动的进行隐式转换，需要程序员显示的调用static cast来完成类型转换！
 * Goo g = static_cast<Foo> f;
 *
 *
 * 类型转换的使用原则：
 * 1. 严格的一一映射关系
 *      当我们使用类型转换的时候，要保证当前类型和其他类型之间有**严格的一一映射关系**！！
 *      换句话说，只有当你认为，全天下，从A类型到B类型的转换，只有唯一一种合理的映射关系的时候，才可以采用类型转换，否则请用成员函数代替。
 *
 *      这是因为类型转换通常都是隐性的，阅读者和使用者可能不会去查看转换逻辑，那么如果类型转换的映射关系可能存在多种理解形式，这给使用者
 *      和阅读者带来很大的困扰。比如你要转换一个时间单位，那么这个转换可以是以秒计，也可以以分计，两种都可以，使用者就很迷惑。而如果你使用
 *      函数来转换可以写 ChangeToMin(), ChangeToSec()，这比隐式转换来的直观很多
 * 2. 避免类型转换出现二义性
 *      1). 类型转换的重复定义： 若A中定义了constructor可以把B变成A，而B中又重载了operator()用来把B变成A。如果这时候你调用了
 *          A a = b;
 *          这时候就出现了二义性，该表达式的含义是把B类变成A类，但是在你代码里呈现了两条路径，既A的constructor与B的重载运算符。
 *          这时候，在编译器看来就出现了二义性，因为不管是哪种方法，在编译器看来都是完美匹配，没法区分孰优孰劣。
 *
 *      2). 转换目标是内置类型的时候时候容易出现二义性：
 *          不要定义多个从自定义类到内置类型的转换函数！！
 *
 *          试想你有个类A，你希望A既可以被转换成int，也可以被转换成double，于是你定义了两个类型转换
 *          1. operator int() const;
 *          2. operator double() const;
 *
 *          这时候如果你调用
 *          long double ld = a; // a 是 A的实例
 *          对于编译器而言就是二义性了，不管是int 还是double， 都不能跟 long double完美匹配，且对于编译器而言，这两种转换没有优劣之分
 *          这就出现了二义性。
 *
 *          正确的做法是你只有一个int或者double的转换函数就行了，其余的类型转换交给编译器来决定，编译器会把double变成int也好，还是变成
 *          long double也好，由编译器来决定，而不是你来决定。
 * 解决方法：
 * 1. 不要重复定义类型转换，在A中如果定义了，那么在B中就不要再定义了
 * 2. 类类型和内置类型的转换中，只能定义类类型和内置类型其中的一个转换，不能让类类型和多种内置类型互相转换。
 *
 */
class Goo {
public:
    double d = 3.14;
    Goo(){}
    Goo(double d):d(d){}
};

class Foo {
public:
    int a = 10;
    Foo() = default;
    Foo(const Goo &g):a(g.d) {} // 从其他类型（Goo）转换成为当前类型（Foo）

    explicit operator Goo() const { // explicit 的情况下需要调用static_cast来完成。
        return Goo(a); // 从当前类型（Foo）转换成其他类型（Goo）
    }
};


int main () {
    Foo f;
    Goo g;
    Foo f2g = g;
    Goo g2f = static_cast<Goo>(f);
}