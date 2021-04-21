#include <iostream>
#include <string>

/*
 * ****************************************   模板实参的推断   ******************************************
 * 模板推断的例外主要体现在对引用的推断上。
 * 当模板参数存在右值引用的时候，会存在两个引用推断的例外
 * 1. 左值传给 T&& 的时候， T推断为 *左值引用* 类型
 * 2. 简介创建引用的引用的时候，引用会被折叠
 *
 * 如何理解这两个例外呢？
 * 1. 当int传递给T&&的时候， T被推断为int&，因此此时 T&&的类型是 int& &&
 * 2. 由于int& &&是通过间接的方式创建的，因此int& &&中的后两个引用符号被折叠了，于是就成为了int&
 * 因此，我们发现，当int被绑定到T&&的时候，T&&的最终类型是int&，（既不是int，也不是int&&）
 *
 * 折叠的映射类型是：
 * X& &(T&&, int&, T = int), X& &&(T&&, int, T = int&), X&& & (T&, int&&, T = int&&??)都将折叠成类型X&；
 * X&& &&折叠成X&&；
 *
 * 作用：
 * 通过如上两个例外，我们可以实现将任何类型的值绑定到T&&类型上，不管是左值还是右值，均可以绑定到其上。
 * 而这就是所说的万能引用，无论左值还是右值，绑定到其上以后，都会变成左值引用或者右值引用类型！
 * 而这也正是std::move()得以实现的最基本的原理！
 *
 * 缺点：
 * 我们可以发现，对于万能引用而言，虽然万能，但是T的推断一会是int&（当入参是左值的时候），一会是int（当入参是int&），这
 * 让我们写代码的时候很头痛。
 * 因此，对于万能引用，我们除了在模板转发和模板重载的时候会使用，其余的时候不会使用。
 * 我们与之替代的使用对模板函数的overloading来避免使用万能引用！
 * template<typename T> void f(T&&);
 * template<typename T> void f(const T&);
 *
 * 如上两个函数会保证你调用f的时候，不会出现万能引用的情况！，因为左值和右值会分开调用两个不同的函数，而不是通过万能引用来复用的。
 *
 */


/*
 * 万能引用的困扰
 */

template<typename T> void func(T&& val) {
    T t = val;
    t++;
    if(val == t) {
        std::cout << "equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
}

int main () {
    int a = 5;
    func(a); // T是int&， 因此t是val的引用，结果必然是equal
    func(std::move(a)); // T是int，因此t是val的值传递，结果必然是not equal
}


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

    }
};