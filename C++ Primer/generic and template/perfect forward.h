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
// 这里首先a无论如何也是会被推导为引用的（右值或者左值引用），而forward会保留引用特性（特别是右值引用），那么这时候我们的映射关系为
// a 为值传递或者左值引用时， std::forward<T>(a)为左值引用
// a 为右值时，std::forward<T>(a)为右值引用
// 那么我们发现，对比a的类型，当a是值传递的时候，std::forward<T>(a)的类型与a类型不一致！多了一个左值引用，然而这个差异正是我们想要的！！
// 因为引用的多出来正是将forward的内容绑定在原来内容上，而不是copy，那么至于func要如何获取这个内容，那是func的事情！

// 试想不管std::forward<T>(a)的类型不管是int还是int&的时候，传入到func中的类型还不是取决于func的signature，当signature是值传递的时候
// int& 和int到func里是一样的，都是值传递。
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



/*
 * 输入类型  转发类型  函数入参类型
 * int -> int& -> int
 * int& -> int& -> int&
 * int&& -> int&& -> int&&
 *
 * 完美转发主要做的工作就是通过第一层的映射，将入参类型进行保持，然后转发给函数。
 * 这里不好理解的就是int类型，我们发现int类型在转发的时候发生了变化，变化为int&，但是这个int&的引用
 * 会在函数入参类型为int的时候就丢掉。
 *
 * 我可以这么理解，这个转发中间层，只是把原类型原封不动的抓取，因此int被映射成int&，那么具体你函数是需要
 * val，还是需要引用，还是右值引用，那你自己说了算。
 */
template<typename F, typename T>
void funForward(F func, int& a) {
    func(std::forward<int&>(a));
}

void func(int a) {

}

int test()
{
    // 这就是int值传递的类型的真实过程
    int a;
    int &aRef = a;
    func(aRef);
    return 0;
}
