//
// Created by Allen on 2021/2/18.
//

#ifndef C___PRIMER_SWAP_H
#define C___PRIMER_SWAP_H
#include <iostream>
using namespace std;

class Foo {
public:
    friend void swap(Foo &, Foo &);
    Foo(string s = ""):val(0), s(new string(s)){}
    ~Foo() {  // 开辟内存就要析构函数
        delete s;
        cout << "s has been deleted" << endl;
    }
    Foo(const Foo &);  // 要析构函数，就要copy函数，像值类，新开内存
    Foo& operator=(Foo); // 这里我们采用swap实现安全的operator

    string* GetS() {
        return s;
    }
private:
    int val;
    string *s;
};

// 重写swap函数
inline void swap(Foo &lhs, Foo & rhs) {
    using std::swap;
    swap(lhs.s, rhs.s);
    swap(lhs.val, rhs.val); // 这两个都调用的是std::swap

}

class Goo {
public:
    friend void swap(Goo &, Goo &);
private:
    Foo f;
    int a;
};

/*              自定义swap！
 * 当class中存在内存分配的时候，swap一定要自己定义！因为内存的新建，交换，删除是没有意义的，不如直接让指针互换来的方便
 * 要想做到这一点需要
 * 1。 将对应版本的swap函数在类中声明为friend
 * 2。 swap的使用要裸使用，不要带有作用域名称。
 * 3.  必须内联，swap会被频繁使用。
 *
 * 注意：
 * swap永远不要带作用域符号，这是为了让swap能够选择到最合适的版本，从而达到优化的作用。
 * 因此我们只要在函数内作用域中声明一下std的swap，这样所有swap版本在函数内都是可见的，都处于互相overloading的状态，
 * 因此只要我们大胆的只管用swap，编译器会通过函数最优匹配的方式选择最合适的版本。
 *
 */
inline void swap(Goo &lhs, Goo &rhs) {
    using std::swap;
    swap(lhs.f, rhs.f); // 这里用的是Foo版本的swap
    swap(lhs.a, rhs.a); // 这里用的是std::swap版本的。
}



/*
 *  用swap实现安全赋值计算
 *  原理在于：对于类值的类而言，利用与copy而来的局部变量的swap，让自己的内存与局部变量的内存产生了互换，而局部变量的内存会
 *  在函数结束的，带着被换来的旧内存被销毁！在强调一遍，这个前提是类值的类，指针的行不行还要在研究。
 *
 *  该方法可以保证，赋值之后，
 *  1。旧内存被自动的，且安全释放，
 *  2。自我赋值是安全的
 *
 *  实现方法
 * 1。入参必须是值传递  // 新建局部变量
 * 2。像值一样的类
 * 3。swap *this和other //交换，随后局部变量other拿着this的旧值自毁类。
 */
Foo::Foo(const Foo& other) :s(new string(*other.s)), val(other.val){}

Foo& Foo::operator=(Foo other) {
    swap(other, *this);
    return *this;
}


int main() {
    Foo f1("allen");
    Foo f2("cecilia");
    cout << f1.GetS() << ", " << f2.GetS() << endl; // 这就避免了新建，copy， 赋值，销毁的过程
    swap(f1, f2);
    cout << f1.GetS() << ", " << f2.GetS() << endl;

    f2 = f1; // f2的旧内存自然就被释放了。
}

#endif //C___PRIMER_SWAP_H
