//
// Created by Allen on 26/12/21.
//

#ifndef SUMMARY_COPY_AND_MOVE_H
#define SUMMARY_COPY_AND_MOVE_H
#include <iostream>
namespace copy_and_move{
    class Foo {
    public:
        Foo() :a(1), b(2) { std::cout << "constructor is running" << std::endl;}
        /*
         * copy 构造函数的入参强制要求是引用类型，这是因为，如果类型为值传递，这意味着，当外部调用copy构造函数的时候，在copy构造函数
         * 执行之前，要先对入参进行一次值传递，而值传递的前提是你要完成copy。
         *
         * 因此这意味着，copy构造函数执行的前提是这个对象先要被copy一份！！这是个循环依赖！，因此如果你真的不写引用，那么copy构造函数
         * 会递归的调用自己，直到爆栈。
         */
        Foo(const Foo& other) : a(other.a), b(other.b) {std::cout << "copy constructor is running" << std::endl;}
        Foo& operator= (const Foo& other) {
            this->a = other.a;
            this->b = other.b;
            std::cout << "assigment operator is running" << std::endl;
            return *this;
        }
        /*
         * 移动构造函数与copy构造函数的区别在于入参类型，而代码在实际执行的时候，也是根据入参类型而进行函数匹配的。
         * 当入参类型是个右值引用的时候，就会调用移动语义。否则会调用copy语义
         *
         * 注意移动构造函数如果不抛出异常，请显示的声明noexcept，否则有些不允许抛出异常的场景，移动语义将退化成copy语义来执行。因为copy一般
         * 不会抛出异常。
         */
        Foo(const Foo&& other) noexcept: a(other.a), b(other.b) {std::cout << "move constructor is running" << std::endl;}
        Foo& operator=(const Foo&& other) noexcept {
            this->a = other.a;
            this->b = other.b;
            std::cout << "move assignment is running" << std::endl;
            return *this;
        }
    private:
        int a;
        int b;
    };
}

void TestCopyAndMove ()
{
    using namespace copy_and_move;
    Foo a;
    Foo b = a; // copy 构造，因为b第一次被分配内存，需要的是构造
    b = a; // 赋值，因为b已经有内存了，现在是要修改内存中的内容，因此是赋值

    Foo c = std::move(b); // 移动构造，因此std::move(b)的类型是 Foo&&,
    c = std::move(a); // 移动赋值

}



#endif //SUMMARY_COPY_AND_MOVE_H
