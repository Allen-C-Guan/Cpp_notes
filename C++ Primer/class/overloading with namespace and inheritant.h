//
// Created by Allen on 16/2/21.
//

#ifndef C___PRIMER_OVERLOADING_WITH_NAMESPACE_AND_INHERITANT_H
#define C___PRIMER_OVERLOADING_WITH_NAMESPACE_AND_INHERITANT_H
#include <iostream>

using namespace std;

/*
 *                          继承的作用域
 * 继承中，派生类的作用域是内嵌在父类中的，这就导致同名隐藏的问题，尽而导致重载的问题。
 * 对于内嵌结构中，内作用域和外作用域之间是不存在overloading的，因为重载的名字要求一致，但是他们实际的名字是不同的（Base:: func, Derived::func)
 * 因此继承中，同样，派生类和父类中的同名是不存在overloading而言的，一旦出现重名，父类所有重名部分直接隐藏掉。
 * as a result, 要想使用overloading，要么子类中一个都不覆盖（不重新定义一个与父类重名的函数），这样父类的所有重载的函数都会暴露在子类中了。
 * 要么你把所有父类中的函数都覆盖一遍，这样相当于不用父类了，我自己也有自己的完全相同的一套了，自理更生了。父类的函数就继续隐藏着好了。
 *
 * 因此，如上所示，貌似对于overloading而言，因为同名隐藏的缘故，就没有overloading一说了！！
 * 为此c++提供了一种利用"using + 类::function_name"的声明的方式，来将父类所有重名函数在子类中不隐藏，也可见！
 * 这样overloading也可以实现"继承"了，即子类可以自己定义特有的overloading就行了，不用管父类了。
 *
 *
 *                      作用域重名的隐藏
 * 作用域的重名隐藏主要是编译器变量搜索的机制造成的，编译器的重名搜索主要以两步完成。
 * 1. 变量搜索
 * 2. 类型检查
 * 最致命的是，先变量搜索，而后类型检查，并且即使类型检查失败了，也不继续变量搜索了！！！这就是为什么内嵌结构中，外层重名会被隐藏的原因了。
 * 因为子类中一旦找到了，即使子类中类型不匹配，并且父类中存在类型匹配的也不会被找到，因此造成搜索失败！
 *
 * 变量搜索主要分两步：
 * 1. 确定静态类型
 * 2. 根据静态类型确定的作用域向外层作用域搜索同名变量（函数）
 * 因此静态类型决定了变量搜索的最内层作用域，变量搜索不会在向内层作用域搜索的。
 *
 * 类型检查分两步：
 * 1. 类型是否匹配（函数调用是否合法），此时一定是名字匹配上了的，如果类型匹配上了，就可以调用了。
 * 2. 是否是虚函数：
 *          1). 如果是虚函数 +  引用or指针，编译器产生可以在运行时才确定哪个版本的代码供运行时使用。
 *          2). 如果不是1)，则直接确定所调用版本。
 *
 */
class Base {
public:
    void Print(int a) {
        cout << "this is Base with int" << endl;
    }
    void Print(float a) {
        cout << "this is Base with float" << endl;
    }
};

class Derived : public Base {
public:
    using Base::Print; // 但是我这一声明，整个一族同名函数在子类中都可见了！ 父类重名函数不在隐藏了。
    void Print() {
        cout << "this is Derived with void" << endl; // 由于名字查找导致了作用域隐藏了同名的父类函数，
    }
};

int main() {
    Derived d;
    d.Print(1); // 这调用的就是base中的版本
}

#endif //C___PRIMER_OVERLOADING_WITH_NAMESPACE_AND_INHERITANT_H
