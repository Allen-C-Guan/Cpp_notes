#include <iostream>
/*
 * **********************************  模板参数的推断  **********************************
 *
 * *************   模板函数的类型转换   ****************
 * 对于模板函数而言，模板通常是生成一个新的模板实例，而不是进行类型转换。除非以下三种情况之一：
 * 1. 顶层const可以被忽略
 * 2. 数组到指针的转换
 * 3. 函数指针到指针的转换
 * 注意，数组的引用不会将类型转换成指针，但是值传递会将类型转换成指针类型。
 *
 * **************************  当返回类型也是模板参数的时候  *****************************
 * 当返回类型也是模板参数的时候，由于函数使用的时候，返回类型是不指定的，因此编译器无法指定，因此需要使用者来指定
 * 1. 当返回类型是可以确定的时候，直接和类函数一样指定就好了，但注意，设计模板顺序的时候，把return的模板参数放前面
 * 2. 当返回类型不确定的时候，需要采用尾后返回类型
 *      template<typename It>
 *      auto func(It beg, It end) -> decltype(*beg) {}
 *      注意：对迭代器的解引用得到的一定是引用！
 *
 *      之所以用尾后返回类型，只是单纯的因为，beg的声明在It beg，但使用decltype(*beg)却在前面，而用来尾后
 *      返回以后，这顺序就可以了。
 *
 */

int main () {


}