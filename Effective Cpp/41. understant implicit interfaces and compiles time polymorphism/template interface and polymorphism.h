//
// Created by Allen on 2021/7/14.
//

#ifndef EFFECTIVE_CPP_TEMPLATE_INTERFACE_AND_POLYMORPHISM_H
#define EFFECTIVE_CPP_TEMPLATE_INTERFACE_AND_POLYMORPHISM_H

/*
 * ******************************* 了解隐式接口和编译期多态 *****************************
 * 我们知道，非模板是有接口和多态的，接口就是一个函数的signature，而多态是virtual function的vtable在运行时来实现的。
 * 其实模板也是有接口和多态的，只是接口是隐式的，多态是编译期的！
 *
 * 先讨论接口！
 * 比如：
 * 非模板函数：
 * void doProcessing(widget &w)
 * {
 *      if (w.size() > 10 && w != someNastyWidget) {
 *          widget temp(w);
 *          temp.normalize();
 *          temp.swap(w);
 *      }
 * }
 *
 * 那么这个函数的接口是"显示的"！既：
 *
 * void doProcessing(widget &w);
 * return的是void，入参是widget类型的单个入参，函数名字为doProcessing
 * 只有完全符合这个接口的类型才是能调用该函数！这就这个函数的接口！
 *
 *
 * 那么对于模板函数：
 * template <typename T>
 * void doProcessing(T &w)
 * {
 *      if (w.size() > 10 && w != someNastyWidget) {
 *          T temp(w);
 *          temp.normalize();
 *          temp.swap(w);
 *      }
 * }
 *
 * 由于T似乎可以是任何类型，因此他的signature将不在是显示的，光看signature，似乎任何类型都可以调用此函数，那么
 * 我们说的模板函数的signature指的是什么？
 *
 * 我们说的signature指的是 T类型必须符合以下几条：
 * 1. T有size()成员函数，并且返回一个数
 * 2. T可以使用 != 来互相比较
 * 3. T有copy函数
 * 4. T有normalize()成员函数
 * 5. T有swap()成员函数
 *
 * 编译才能过！因此以上特征都是这个模板函数的隐式接口！
 *
 * 隐式接口：隐式接口并不基于函数签名式，而是由*有效表达式*组成！ 换句话说，隐式接口是从编译跑过的角度来定义的接口！
 *
 *
 * *********** 什么是模板的多态！********
 * 当以*不同的tempalte参数（模板重载）*具现化function template，会导致调用不同的函数，这便是所谓的编译期多态！
 * 因此模板的多态利用*模板函数重载*来实现的！因此模板的多态发生在编译期！
 *
 * 换句话说：模板的多态类似于"哪一个重载函数被调用"， 而非模板多态是"哪个virtual函数该被绑定"
 *
 */

#endif //EFFECTIVE_CPP_TEMPLATE_INTERFACE_AND_POLYMORPHISM_H
