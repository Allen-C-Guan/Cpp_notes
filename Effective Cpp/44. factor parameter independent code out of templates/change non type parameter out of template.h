//
// Created by Allen on 2021/7/18.
//

#ifndef EFFECTIVE_CPP_CHANGE_NON_TYPE_PARAMETER_OUT_OF_TEMPLATE_H
#define EFFECTIVE_CPP_CHANGE_NON_TYPE_PARAMETER_OUT_OF_TEMPLATE_H
#include <iostream>
/*
 * ************************** 将于参数无关的代码抽离template  *********************
 * 对于非类型模板参数而言，其造成的代码膨胀，是可以通过设计来避免的，简单的方法就是以函数参数获class成员变量
 * 来替换template参数！
 *
 * 比如你的模板参数为
 * template <typename T, std::size_t n>
 *
 * 那么你完全可以将其改为
 * template <typename T> 然后把n作为函数入参来传入的，从而避免代码的膨胀。
 *
 * 当设计到内存的时候，也可以通过指针的形式，将内存存储起来，从而避免代码膨胀
 *
 */
int main ()
{

}
#endif //EFFECTIVE_CPP_CHANGE_NON_TYPE_PARAMETER_OUT_OF_TEMPLATE_H
