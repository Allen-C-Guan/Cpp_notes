#include <iostream>

using namespace std;

class Foo {
public:
    int a;
    mutable int callTimes = 0;
    Foo () {
        a = 0;
    }

    void PrintFoo () const {
        cout << a << endl;
    }
    void PrintFoo () {
        a ++;
        cout << a << endl;
    }

    void aPlusPlus () {
        a++;
    }

    const int& getAReference() const {
        callTimes++;
        return a;
    }
    int getAReference() { //用non-const来调用const的方法
        return static_cast<int> (static_cast<const Foo>(*this).getAReference());
    }
};

void Print(const Foo& f) {

    cout << f.getAReference() << endl;
}

/*
 * *******************  关于const member function的讨论  ************************
 *
 * 我们为什么需要const member function？
 * 1. 安全（不多说了）
 * 2. 为了const reference实参的调用！！（当然也是为了安全）
 *
 * 比如上面的print函数，那么作为print函数，你的入参就应该是const的，可是，这大大限制了入参对象的发挥！
 * 因为const的对象只能调用const函数！！，这意味着大量的non-const member function在当前函数中失去了作用。
 * 因此如果我们想在print中去调用某个功能，那就必须要将这个功能（成员函数）定义为const的！
 *
 * const 函数的 non-const 重载
 * 当返回值是const reference的时候，我们通常还会对这个函数进行non_const的重载，这是因为有时候我们需要返回的是const。
 * 但有时候我们还需要对返回值进行修改呢！这时候，就需要对const版本的进行重载。
 *
 * const_cast的使用
 * 既然说到重载，那如果const的版本代码量有100行，难道你就因为一个const，就要copy这100行代码吗？ 这时候就需要通过
 * const_cast来让non_const版本的去调用const版本来避免代码的重复！
 * 但记住，反过来是不可以的！！！！
 *
 * mutable的使用
 * 刚才我们说了，有时候const member function是外部使用约束，我们必须要声明其为const，不声明外部就无法使用！！
 * 但是我们有时候又不得不在这个函数中更改其成员变量，这种外部约束和需求约束冲突的时候，就可以用mutable来避免了！
 *
 */


int main() {
    const Foo f1;
    Foo f2;
    cout << f1.getAReference() << endl;
    cout << f2.getAReference() << endl;
    std::cout << "ENDING" << std::endl;
    return 0;
}

