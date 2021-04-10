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
 * ************************  函数调用运算符  *************************
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
 *
 *
 *
 * ***************************** function **********************************
 * function<return_type(arg1_type, arg2_type)> f = callable_obj;
 * function的功能是为了统一可调用对象的类型的一个接口类型。
 *
 * 通过函数调用运算符，以及lambda的学习，我们发现，函数调用运算符，lambda，函数貌似都可以用同一类形式来调用
 * 比如如下三种方法：
 */

// 函数调用符
struct MyCmpStruct {
    bool operator() (int lhs, int rhs){
        return lhs < rhs;
    }
};
// lambda表达式
auto MyCmpLambda = [](int lhs, int rhs) -> bool{return lhs < rhs;};
// 函数调用
bool MyCmpFunction (int lhs, int rhs) {
    return lhs < rhs;
}

// 证明这三种类型都可以用几乎完全相同形式的去使用
void ProveFunction() {
    int lhs = 0, rhs = 10;
    MyCmpStruct myCmpStruct;
    bool ret = myCmpStruct(lhs, rhs);
    bool ret2 = MyCmpLambda(lhs, rhs);
    bool ret3 = MyCmpFunction(lhs, rhs);
}

/*
 * 通过以上三个例子可以发现，虽然以上三种可调用类型属于不同的类型，但是调用形式（使用方法）确实相同的，那么有没有一种方法可以将以上三种调用
 * 通过一个接口将类型形式统一化！！
 * 注意：虽然使用起来几乎没差，但是从语法上来讲，这三种类型不同，会导致类型上无法统一，类型上无法统一就没法放到容器中！！！！（容器只能
 * 接受完全相同的类型，差一点也不行）
 *
 * function的作用
 * function的作用就是为了解决上面的问题，function提供了一个更高层的，对可调用对象的统一化的抽象接口。他可以将所有可调用对象，根据return
 * 类型，入参类型来归一化类型，只要有相同的返回和入参类型，就是相同的function类型！！
 *
 * 使用方法：
 * function<bool(int, int)> f1 = MyCmpStruct(); // 加个括号就会初始化一个临时可调用对象
 * function<bool(int, int)> f2 = MyCmpLambda;
 * function<bool(int, int)> f3 = MyCmpFunction;
 * std::vector<std::function<bool(int, int)>> cmpVec = {f1, f2, f3};
 *
 * 而这时f1,f2,f3就是完全相同的类型了，这就可以把他们放到vector里了
 *
 * function的重载
 * 我们可以看到function的赋值（初始）是通过可调用对象的名字赋值的，但对于被重载的函数而言，会造成二义性。
 * 这时候我们用函数指针来代替原函数名字作为赋值的对象即可避免。
 */



// 这只是个为了证明operator()可以被重载的例子，并没有什么卵用
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

void MyCmpFunction() {

}

int main ()
{
    Foo f;
    std::cout << f(99) << std::endl;
    std::cout << f(55.6) << std::endl;
    std::function<bool(int, int)> f1 = MyCmpStruct();
    std::function<bool(int, int)> f2 = MyCmpLambda;
    // 函数重载
    bool(*pf)(int, int) = MyCmpFunction;
    std::function<bool(int, int)> f3 = pf;
    std::vector<std::function<bool(int, int)>> cmpVec = {f1, f2, f3};
    std::cout << "end" << std::endl;

}