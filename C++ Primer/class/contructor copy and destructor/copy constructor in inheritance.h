//
// Created by Allen on 2021/2/28.
//

#ifndef C___PRIMER_COPY_CONSTRUCTOR_IN_INHERITANCE_H
#define C___PRIMER_COPY_CONSTRUCTOR_IN_INHERITANCE_H
#include <iostream>
class Base {
public:
    Base(){};
    Base(const Base &) = delete; // 父类没有copy constructor，子类也不能copy，因为子类也要copy父类的一部分
    ~Base() = delete; // 基类destructor被删除了，父类和子类都不能copy也不能初始化，因为一旦初始化就删除不了了
};

class Derived : public Base {

};
int main() {
    Derived d;
    Derived d1(d);
}
#endif //C___PRIMER_COPY_CONSTRUCTOR_IN_INHERITANCE_H
