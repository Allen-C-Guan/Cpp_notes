//
// Created by Allen on 16/2/21.
//

#ifndef C___PRIMER_FRIEND_IN_CLASS_H
#define C___PRIMER_FRIEND_IN_CLASS_H
#include <iostream>

// 可访问性是自己管自己的，包括嵌在派生类的基类部分也是由基类自己负责的。

using namespace std;
class Derived;

class Foo {
    friend class Base;
private:
    int f_private;
};

class Base {
    friend void PrintBPrivate(Derived d);
    // 我们在base里声明了入参是derived的friend函数，表明这个函数中的所有base部分，包括嵌入在derived的base部分，
    // 都可以获得访问base的全部权限。
private:
    int b_private = 100;
protected:
    int b_protected;
public:
    int b_public;
    int GetFooPrivate(Foo f){
        return f.f_private;
    }
};



class Derived : public Base{
    // 因为访问性是自己管理自己的权限，因此就会发生一个奇怪的现象，在PrintBPrivate函数中，我们可以通过derived实例来获取base中的private变量
    // 但在derived内部却无法获得base中private的变量。 而这一切就是因为，访问性永远是自己管理自己的部分，函数是base的friend，那函数就可以
    // 获得base部分，不管这个base是独立的，还是内嵌在derived中的。
    // 而derived虽然继承来base，但是derived并不是base的friend，就无权访问base部分了。

//    int GetFooP(Foo f) {
//        return f.f_private;  // 这里就不行，因为Foo只任base是friend，不认Derived，而继承也并不会继承friend。
//                             // 继承不继承friend也是为了维护访问权限自己管自己的原则。
//    }
//
};

void PrintBPrivate(Derived d){
    cout << d.b_private << endl;
}
int main() {
    Derived d;
    PrintBPrivate(d);

    std::cout << "ENDING" << std::endl;
    return 0;
}

#endif //C___PRIMER_FRIEND_IN_CLASS_H
