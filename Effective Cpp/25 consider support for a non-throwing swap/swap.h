//
// Created by Allen on 2021/7/4.
//

#ifndef EFFECTIVE_CPP_SWAP_H
#define EFFECTIVE_CPP_SWAP_H9
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Foo {
public:
    std::vector<int> array;
};

class FooManger {
public:
    FooManger():pF_(nullptr) {}
    FooManger(Foo *pF) : pF_(pF) {}
    ~FooManger() {
        delete pF_;
    }
    void swap(FooManger &rhs) noexcept {
        using std::swap;    // 无脑局部声明std::swap
        swap(this->pF_, rhs.pF_);
    }
    void print() const {
        for (auto val : pF_->array) {
            std::cout << val << std::endl;
        }
    }
    FooManger(const FooManger&) = default; // 这里先这么写，这么写是不恰当的，但是本例子只是为了证明swap，顾不深入copy的写法
private:
    Foo *pF_ = nullptr;
};

namespace std {
    template<>
    void swap(FooManger &rhs, FooManger &lhs) noexcept { // 必须声明是noexcept的
        rhs.swap(lhs);
    }
}

/*
 * ************ 定制自定义类型的swap函数 *******************
 * 由于std::swap函数的本质，就是利用局部变量作为第三章，用copy的方式，将两者交换，其实现方法是模板
 * 因此，若自定义的类型内容十分多的时候，有必要通过指针的swap来高效swap！
 *
 * 具体实现方法：
 * 1. 用自己成员函数实现一个自定义swap函数
 * 2. 将自定义的swap函数，特例化到std::swap模板中去！
 *
 * 优点：
 * 1. 我们不用外部函数来swap，因为swap通常需要private权限，与其声明friend，不如直接用member function
 * 2. std空间不允许我们自行修改的，但是允许我们模板特例化！！我们如果把自定义类型的swap函数特例化在std空间中
 *  是不是就可以像使用标准类型一样使用我们的swap函数，用的时候不用区分类型，无脑声明std即可！
 *
 */

int main() {
    Foo *f1 = new Foo;
    f1->array.push_back(1);

    Foo *f2 = new Foo;
    f2->array.push_back(2);

    FooManger fMng1(f1);
    FooManger fMng2(f2);
    fMng1.print();
    fMng2.print();

    std::swap(fMng1, fMng2);

    fMng1.print();
    fMng2.print();


}
#endif //EFFECTIVE_CPP_SWAP_H
