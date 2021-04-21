#include <iostream>
#include <string>
/*
 * **********************************  完美转发  ***********************************
 * 转发的目的是：
 * 将实参的值和实参的*完整类型*（包括左值，右值属性，const属性）完全保留，将参数进行转发出去。
 *
 * 转发的关键在于，会有一个模板函数作为中间层进行转发，如果加入中间层后，会导致函数的行为与直接调用的时候行为不一致，就不是完美转发。
 *
 * 主要利用如下几个性质：
 * 1. 引用（左值，右值）会保留参数类型的const 和 左值引用的信息（但不能保证右值特性（因为右值引用本身就是左值））。
 * 2. 万能引用可以匹配所有类型
 * 3. std::forward() 可以保留用户的左右值特性（为了保留右值特性）
 *
 * 因此完美转发的原型在于：
 * template <typename Type> intermediary(Type &&arg) {
 *      finalFunc(std::forward<Type>(arg));
 * }
 *
 */
void funcRef(int &a) {
    a++;
}

template<typename F, typename T>
void interFunc(F func, T a) { // 推断出T的类型是int，此时a是通过值传递获得的，
    func(a); // 但实际上直接调用的func的目的是为了更改a的值，由于中间层的存在，你给func一个copy的a传进去了，导致
            // 导致直接调用func和使用中间层转发后调用func的行为不一致，这个中间层是不合理的
}

template<typename F, typename T>
void interFuncRef(F func, T &&a) { // 万能引用会将int值变成int&，此时调用中间层的行为和直接调用func的行为就保持一致了
    func(a); // 这里a是引用，引用也会保持a的const特性，尽管这里a不是const，但如果是const的，到这也是保留了const属性的
}              // 但是这里没办处理右值引用，因为即使a是右值引用，右值引用也是左值，因此这么做只能保留左值引用和const的效果，保证不了右值引用


void funcRefRef(int &&a) {
    a++;
}

template<typename F, typename T>
void interFuncRefWithForward(F func, T &&a) {
    func(std::forward<T>(a));
}


int main () {
    int a = 0;
    interFunc(funcRef, a);
    std::cout << a << std::endl;

    a = 0;
    interFuncRef(funcRef, a);
    std::cout << a << std::endl;

    interFuncRefWithForward(funcRefRef, 0);
}