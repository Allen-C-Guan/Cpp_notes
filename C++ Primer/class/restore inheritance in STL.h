//
// Created by Allen on 2021/2/28.
//

#ifndef C___PRIMER_RESTORE_INHERITANCE_IN_STL_H
#define C___PRIMER_RESTORE_INHERITANCE_IN_STL_H
#include <iostream>
#include <vector>

/*          ****** vector中存放相同继承体系下的不同类型 ******
 *
 *  vector只能接受完全相同的类型，即使不同类型之间有相同的父类，也没法完整存储，
 *  如果你强行存储的结果就是，子类被截断！
 *
 *  为了解决这个问题，我们只能往vector里存放指针，而不是obj，使用的时候可以利用多态来保证元素可以正常被调用
 */

class Base {
public:
    Base(){};
    virtual void Print() const{
        std::cout << "this is Base" << std::endl;
    }
};

class Derived : public Base {
    void Print() const override{
        std::cout << "this is Derived" << std::endl;
    }
};
int main() {
    std::vector<std::shared_ptr<Base>> v;
    v.push_back(std::make_shared<Base>());
    v.push_back(std::make_shared<Derived>());
    // 虽然我们make_ptr的对象是Derived，但经过push_back之后，也会被隐式转换为Base的share_ptr指针
    // 因此实际上，存放在vector内的仍然是完全相同的类型。
    v[0]->Print();
    v[1]->Print();

    std::vector<Base> v2;
    v2.push_back(Base());
    v2.push_back(Derived());

    v2[0].Print();
    v2[1].Print(); // 这就是存放obj而非ptr的结果，会导致子类被截断的！丧失了自己的特性。
}
#endif //C___PRIMER_RESTORE_INHERITANCE_IN_STL_H
