//
// Created by Allen on 2021/7/18.
//

#ifndef EFFECTIVE_CPP_ALL_COMPATIBLE_TEMPLATE_TYPE_H
#define EFFECTIVE_CPP_ALL_COMPATIBLE_TEMPLATE_TYPE_H
#include <iostream>
/*
 * *************************** 运用成员函数模板接受所有兼容类型  ********************************8
 * 当我们模板一个类的时候，要考虑其兼容类型，那么我们需要
 * 1. 使用"泛化copy构造成员函数"（只有成员函数才可以做到类型转换）生成 "所有兼容类型"
 * 2. 一旦定义了泛化copy构造函数，就需要声明非模板的copy构造函数和copy assignment函数，否则默认函数会被泛化所替代
 *
 * 泛化copy构造函数：
 * 比如当我们设计一个模板类的时候，不免要考虑与其他类型（包括同模板但不同模板参数的类型，和不同模板的类型的兼容性），那么我们
 * 如何才能完成这项功能呢？就是通过泛化copy 构造函数。
 *
 * 试想内存管理类比如：
 * smart_ptr<T>，通过对模板的了解，我们知道， smart_ptr<Base> 和 smart_ptr<Derived> 是两种不同的类型, 两种类型是
 * 丝毫没有任何关系的，就和Foo 和 Goo的关系一样，尽管作为内存管理类，其管理的真实内存之间是由继承关系的，但是因为你封了
 * 一个管理类，导致其两者实例化之后没有任何关系。
 *
 * 但是我们知道，Base* 和 Derived* 之间是可以隐式转换的！那么作为内存管理类，却限制了被管理内容的优秀的兼容性，这是很
 * 难使用的。
 *
 * 那么我们有什么办法可以恢复两者之间的关系呢？
 *
 * 就采用泛化copy构造函数：
 */
template <typename T>
class SmartPtr1
{
    template<typename U>
    SmartPtr1(const SmartPtr1<U> &other); // 泛化copy构造函数
};

/*
 * 如上就是一个泛化构造函数，由于U和T是两个不同的类型，因此，这个copy构造函数可以兼容世界上的任何
 * smartPtr1实例化出的类型。
 *
 * 这里并没有声明为一个explicate，就是为了让其可以和内置指针行为一致。
 *
 * 但是问题就来了，任何类型？？我只想兼容raw ptr兼容的类型，比如继承关系指针，除此之外的类型我不想
 * 兼容啊！换句话说，泛化copy构造函数给的比我们想要的还多，他甚至能把smartptr<string>
 * 变成 smartPtr<double>！！
 *
 * 因此我们需要加一层编译时候就可以确定的校验，这层校验就是"raw指针的隐式转换"是否合法！
 *
 */
template<typename T> class WeakPtr;
template <typename T>
class SmartPtr
{
public:
    template<typename U>
    SmartPtr(const SmartPtr<U> &other) : rowPtr(other.get()) // 泛化copy构造函数 + 内置类型转换
    {
        // copy 操作
    };
    SmartPtr(SmartPtr const & r); // 本类型的copy构造函数要声明出来，否则会被泛化模板生成！

    // 与其他类型的转换要声明explicit
    template<typename U>
    explicit SmartPtr(U* p);  // row 指针

    template<typename U>
    explicit SmartPtr(WeakPtr<U> const& r); // weakPtr的拷贝

    T* get()
    {
        return rowPtr;
    }
private:
    T* rowPtr;
};

/*
 * 上面加了一层内置类型转换的操作！如果U类型的row指针可以初始化T类型的row指针，则当前其管理类的
 * 转换也可以完成，否则编译会报错，不允许你转换！
 *
 * 但是我们只认为相同内存管理类的不同模板参数之间，才可以进行隐式类型转换，不同的管理类之间，即使类型
 * 一致也不应该存在隐式转换，因为其内存管理方式不一致！因此应该都声明为explicit的
 *
 * 同时因为泛化copy模板的产生，导致本类型的默认拷贝构造函数永远不会被生成，因此，如果你需要与泛化
 * 不一致的同类型copy，则需要自己定义，否则一定会被泛化接管！
 */
int main ()
{

}
#endif //EFFECTIVE_CPP_ALL_COMPATIBLE_TEMPLATE_TYPE_H
