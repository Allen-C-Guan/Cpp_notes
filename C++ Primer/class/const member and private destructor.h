//
// Created by Allen on 2021/2/17.
//

#ifndef C___PRIMER_CONST_MEMBER_AND_PRIVATE_DESTRUCTOR_H
#define C___PRIMER_CONST_MEMBER_AND_PRIVATE_DESTRUCTOR_H
#include <iostream>

using namespace std;

class Foo {
public:
    /* const val的成员类 */
    const int constVal;
    Foo(int a):constVal(a){  // const 值的存在让constructor必须要对const值进行初始化, 而且只能使用初始化列表来初始化，
        // 因为初始化列表是在instance建立和函数体运行前执行的！
    }
    Foo(const Foo &other):constVal(other.constVal) {
        // 同理这里也必须要显示的初始化const的值

    }
    Foo():constVal(10){};

    /*     删除的destructor     */
    ~Foo() = delete; // destructor被隐藏了，说明我们不允许销毁这个类的实例，因此我们不能在stack上实例化
};

int main() {
//    Foo f; // 既然无法消除，就不能在stack上实例化这个instance，因为实例化也意味着早晚一定会调用destructor的，
//              但实际上没有destructor。因此就会报错，你正在尝试调用一个不存在的function。

    Foo *f = new Foo(); // 但是我们可以在heap上实例话这个instance
//    delete f;  // 虽然你能在heap上实例化，但是你不能删除，因为你试图调用一个不存在的function（~Foo();)

}
#endif //C___PRIMER_CONST_MEMBER_AND_PRIVATE_DESTRUCTOR_H
