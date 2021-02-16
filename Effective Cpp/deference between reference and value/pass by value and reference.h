//
// Created by Allen on 31/1/21.
//

#ifndef EFFECTIVE_CPP_PASS_BY_VALUE_AND_REFERENCE_H
#define EFFECTIVE_CPP_PASS_BY_VALUE_AND_REFERENCE_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;


/*
 *          pass by reference 与 pass by value 之间不只是多了copy这么简单
 * 当出现继承关系的时候，pass by value 可能会影响多态的使用！！！！！ slicing problem
 * 这是因为pass by value遇见多态的时候，会产生用derived class初始化一个base class的情况。而一旦初始化了base class，那么你的多态就
 * 完全就没有了，不管什么derived class传入，都会被归一话为base class。
 */
class Base {
public:
    virtual void Print() const{
        cout << "this is Base" << endl;
    }
};
class Derived : public Base{
public:
    virtual void Print() const override {
        cout << "this is Derived" << endl;
    }
};

void PrintClassNameWrong(const Base b) { //wrong 会把所有derived 都变成base
    b.Print();                      // const instance 只能调用这个instance的const函数！！！！
}

void PrintClassNameRightByRef(const Base &b){ //正确，会保留多态
    b.Print();
}
void PrintClassNameRightByPtr(const Base *b){
    b->Print();
}
int test() {
    Derived d;
    PrintClassNameWrong(d);
}

#endif //EFFECTIVE_CPP_PASS_BY_VALUE_AND_REFERENCE_H
