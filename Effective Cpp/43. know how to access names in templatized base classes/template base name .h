//
// Created by Allen on 2021/7/18.
//

#ifndef EFFECTIVE_CPP_TEMPLATE_BASE_NAME_H
#define EFFECTIVE_CPP_TEMPLATE_BASE_NAME_H
#include <iostream>

/*
 * ****************************** 学习处理模板化基类内的名称  *****************************
 * 编译器对于模板化基类中原则为：
 * 编译器在处理继承模板父类的子类的时候，会拒绝模板化基类内寻找继承而来的名字！因此从名字搜索的角度而言，编译器处理
 * 模板继承和非模板继承是不同的！
 *
 * 为何编译器会拒绝在模板化基类中寻找名字？
 * 我们知道，在非模板类中，当编译器无法在子类中找到名字的时候，就会去父类中寻找，这是因为，编译器可以通过"名称"+signature
 * 来确定父类函数是否可以被调用！因此编译器就会自信的去找，然后判定是否可以调用！如果signature不符合，则编译报错
 *
 * 但是在模板类中，是否可以被调用就显得不是那么的明显，在非模板函数中，"名称"+"signature"是非模板函数的接口，但在模板函数中
 * 模板的接口是"隐性的"！是通过是面向编译的接口规则！
 *
 * 比如下面的例子：
 * void sendClearMsg()的接口为拥有模板参数必须拥有 sendClear()成员函数！
 * 那么当LoggingMsgSender 作为子类继承了以后呢？按道理讲，其必然继承了void sendClear()这个接口，也就是说起，
 * 那我作为子类，我调用父类这个必然存在的接口你为何不让我调用？
 *
 * 问题就出现在模板特例化！
 *
 * 试想我特例化了如下Foo的模板！这个特例化的模板中呢，并不会存在sendclear()接口，那么对于当前这个特例化模板而言，
 * void sendClearMsg()是否可以调用sendClearMsg()函数呢？？
 * 当然是不可以的了！！！
 *
 * 简单点来说，非模板继承的爹原则性很强，通过函数名+signature可唯一确定，而模板类的爹却由于模板特例化的原因，导致模板爹
 * 多种多样，且没有任何原则! 因此编译器将default行为设置为不信任模板爹。
 *
 * 因此我们可以说，模板特例化让模板的继承过程中的隐性接口得到了破坏，这会导致编译器在没有实例化之前，是没有办法判定
 * 父类是否一定会存在某个接口的！， 那么对于这种情况，编译器有两个处理办法：
 *  1. 实例化的过程中，判定接口是否可以用
 *  2. 编译器的名称查找的缺省行为，压根就不会去模板基类去寻找名字！
 *
 * 那么C++编译器当然是选择后者！这是C++委员会的原则，问题要提早暴露！
 *
 * 总结一下：
 * 由于模板特例化的原因，模板基类甚至可以啥都没有，啥都不一样，因此编译器直接拒绝了去模板基类里查找。除非你声明让他去找！
 *
 *
 *
 */
class MsgInfo;
template <typename Company>
class MsgSender
{
public:
    void sendClear()  // 这个函数的接口为：company类必须拥有sendCleartext() 成员函数！
    {
        Company c;
        c.sendCleartext();
    }
};
// 特例化模板Foo，其sendClear并不需要sendCleartext()作为隐形接口！
class Foo;
template<>
class MsgSender<Foo>
{
public:
    void sendClear() = delete; // 我就不要这个接口
};

template<typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
    void sendClearMsg()
    {
//        sendClear();  // 模板基类，无法直接调用其父类中的接口！
        // 方法1：this
        this->sendClear(); // 对编译器声明，我保证父类中一定会有这个接口的，你去找吧！

        // 方法2: using
        // 注意这个用法和名字遮掩不一致，这是在告诉编译器需要进入base class作用域查找
        using MsgSender<Company>::sendClear; // 明确告诉编译器其位于父类中。

        // 方法3: 直接指明作用域
        MsgSender<Company>::sendClear();

    }
};

int main ()
{

}
#endif //EFFECTIVE_CPP_TEMPLATE_BASE_NAME_H
