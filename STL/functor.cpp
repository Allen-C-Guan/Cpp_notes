//
// Created by Allen on 2021/10/10.
//

#include <iostream>

/*
 * ********************************** functor ************************************
 * functor的主要功能为：产生一个对象，并以此对象为算法的一个参数。
 * 与函数指针的区别：函数指针无法满足STL对抽象性的要求！也不能满足软件积木的要求。函数指针无法和STL其他组件搭配，
 * 产生更灵活的变化。
 *
 * 从实现的观点来看，functor本质上就是一个行为类似函数的对象。为了让行为类似函数，类别定义中必须自定义function call
 * 算子！
 *
 * 从算法作用的角度来看：functor最主要的功能是扮演"策略"角色！，使算法更加的灵活。让算法策略像积木一样被串接。
 *
 */

/*
 * 一元操作符的基类，要去所有一元操作的functor都要继承该类，继承起到3个作用：
 * 1. 继承约束了一元操作符的模板参数类型的个数。
 * 2. 在继承声明的时候就确定了入参类型和出参类型
 * 3. 在父类中将如入参和出参类型归一化为内置重命名类型，便于适配。
 */
template <typename Arg, typename Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <typename T>
struct negate : public unary_function<T, T> {
    T operator() (T x) {
        return -x;
    }
};

template <typename Predicate>
struct unary_negate {
    // 这里我们就可以用内置类型来声明入参类型。
    bool operator() (const typename Predicate::argument_type &x) const {
        // 同时我们可以实现functor的封装和组合。这里我们封装了一下Predicate，就可以对外展现出不一样得行为。
        // 这就是functor相比于function pointer的优点了。
        bool result =  Predicate()(x);
        return result;
    }
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x + y;
    }
};

template <class T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x - y;
    }
};

// 首先这里Comp并没有必要用reference，这是因为Comp本身并没有成员变量，因此copy比引用反而要快一些。
// 在C++标准库中，T和comp是用两个模板参数来表征的。这是为了让Comp能自由组合
template <class T, class Comp>
T CalcResult(T x, T y, Comp op)
{
    return op(x, y);
}

// 当然你也可以用一个类型类表示
template <class Comp>
typename Comp::result_type CalcResult2(typename Comp::first_argument_type x,
        typename Comp::second_argument_type y, Comp op)
{
    return op(x, y);
}

int main() {
    negate<int> negator;
    unary_negate<negate<int>> unary_negator;
    std::cout << unary_negator(0) << std::endl;

    std::cout << plus<int>()(2, 4) << std::endl;
    // 还可以这么用
    plus<int>::result_type a;
    plus<int>::first_argument_type b;
    plus<int>::second_argument_type c;

    // 这里就是2个参数的使用方法，我觉得还是两个参数的用起来比较好。
    auto result = CalcResult<int>(9, 6, plus<int>());
    std::cout << result << std::endl;
    
    // 这是一个参数的使用方法。
    auto result2 = CalcResult2<plus<int>>(9, 6, plus<int>());
    std::cout << result2 << std::endl;
    return 0;
}

