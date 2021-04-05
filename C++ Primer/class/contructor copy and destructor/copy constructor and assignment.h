//
// Created by Allen on 2021/2/17.
//

#ifndef C___PRIMER_COPY_CONSTRUCTOR_AND_ASSIGNMENT_H
#define C___PRIMER_COPY_CONSTRUCTOR_AND_ASSIGNMENT_H
#include <iostream>

using namespace std;

/*
 *                  拷贝和赋值的区别
 * 拷贝和赋值的区别在于左侧实例是否已经存在，如果左侧实例已经存在，我们用赋值的方式修改已经存在的实例的内容，这叫赋值。
 * 而如果此时左侧的实例根本不存在，你想通过已有的实例，通过copy的方式创建一份新的实例，这就是拷贝。
 * 例如：
 *  Foo f2 = f1; // 这就是拷贝，因为在这句话之前，f2压根不存在
 *
 * 在例如：
 *  Foo f1;
 *  Foo f2;
 *  f2 = f1; // 这就是赋值，因为f2已经存在了，但是我们想修改f2的内容，使f2的内容和f1的内容相同，因此是赋值。
 *
 *  实现上的区别
 *  那么在实现上，赋值和拷贝最大的区别在于是否需要处理即将修改的实例内部的旧（原）内容。赋值需要修改，而拷贝不需要修改。
 *  更具体一点说，赋值可能需要先删除原内容，而后copy新内容，但是拷贝不需要删除原内容，因为没有原内容。
 *
 *  特殊考虑：
 *  由于赋值存在原内容，因此涉及到原内容的删除，这就不得不考虑自我赋值的情况，该情况可能会导致先删除自己，在用被删除的
 *  自己来赋值自己的情况。
 *  为了解决这种问题，我们采用如下三步走：
 *  1。入参变量copy到局部变量中
 *  2。删除原内容
 *  3。用局部变量赋值新内容。
 *
 *
 *                      拷贝和直接初始化的区别
 * 既然拷贝是建立新实例，而constructor也是创建新实例，那么两者有何区别？
 *
 * 形式上：
 * 拷贝有等号，直接初始化没有等号
 * 例如：
 * Foo f1 = f2; // 拷贝
 * Foo f1(f2); // 直接初始化
 *
 * 编译过程的不同：
 * 直接初始化中，我们要求编译器使用普通函数匹配来选择最匹配的构造函数（包括copy constructor在内constructor）。
 * 拷贝中，我们要求编译器只能使用拷贝初始化，如果需要转化，会进行类型转换的（既然是类型转换，就不是函数匹配了，
 * 因为函数匹配要求类型尽可能一致），而不是寻求更佳的函数匹配。
 *
 * 但是实际上有些编译器会绕过copy函数，使用直接初始化来代替拷贝函数，这是编译器的行为，不是C++语法要求。
 *
 *
 *                  定义行为像值的类
 * 行为像类还是像指针主要取决于copy和赋值是如何对待指针成员的。
 * 如果每份对象都有独属于自己的状态，各个拷贝之间互相不影响，则该类就是像值一样的类。
 * 这就需要注意两点：
 * 1。 拷贝和赋值函数中要开辟新内存，
 * 2。 析构函数可以自己释放自己heap上的成员，因为该内存是自己独享的，只要自己不用了，就可以大胆释放。不用考虑是否有别人在用这块内存。
 *
 */
class Foo {
public:
    Foo(string s, int val):m_name(new string(s)), m_val(val){}
    Foo(const Foo &other): m_name(new string(*other.m_name)), m_val(other.m_val){
        // 这里不需要考虑自我赋值的问题，也就不需要处理原成员内容。
    }
    Foo& operator=(const Foo &other) {
        string *newMName = new string(*other.m_name);  // 先初始化个局部变量存放新的
        delete m_name;                                 // 删除旧的
        m_name = newMName;                             // 新的更新过去
        m_val = other.m_val;                           // 只要处理指针就行了，变量可以直接覆盖。
        return *this;
    }
    ~Foo(){
        delete m_name;  // 像值一样的类，由于每个类都有自己独立的资源，不用共享，因为自己可以释放自己。
    }
private:
    string *m_name;
    int m_val;
};

int main() {
    Foo f1("allen", 28); // 直接初始化，调用构造函数
    Foo f0(f1); // 直接初始化，函数匹配到copy构造函数，并构造出f0
    Foo f2 = f1; // copy构造函数
    f2 = f2;    // 赋值，而且是自我赋值。
}

#endif //C___PRIMER_COPY_CONSTRUCTOR_AND_ASSIGNMENT_H
