#include <iostream>
#include <string>
/*
 * smart pointer的诉求（这里假定就是一个unique_pointer，不计数）
 * 1. 有强烈的类型属性（类型不同的指针之间不可以互相换）
 * 2. 使用起来要像内建指针一样方便（可以使用"->" 和 "*")
 * 3. 但又不可以太像，否则隐式转换会很让人头痛，使用者也会忘记自己使用的是智能指针！ 因此不要给dumb pointer提供隐式转换操作符！！！
 */
template <class T>
class SmartPointer {
public:
    SmartPointer(T* realPtr = nullptr);
    ~SmartPointer();
    T* operator->();
    T& operator*();

    // unique_ptr不允许copy！！暂且也不实现move（不是这里讨论的重点）
    SmartPointer(const SmartPointer &) = delete;
    SmartPointer(const SmartPointer &&) = delete;
    SmartPointer &operator= (const SmartPointer &) = delete;
    operator void*(); // 隐式类型转换为指针，为了校验是否是nullptr, 这种替换是很不好的，会造成SmartPointer<Apple>类型和SmartPointer<Orange>之间是可以比较的
    template<class newType>
    operator SmartPointer<newType>(); // 用于smartpointer和raw pointer类型的隐式转换。

private:
    T *pointee;
};
template<class T>
SmartPointer<T>::SmartPointer(T* realPtr) : pointee(realPtr)
{
}

template<class T>
SmartPointer<T>::~SmartPointer()
{
    delete pointee;
    pointee = nullptr;
}

template<class T>
T* SmartPointer<T>:: operator->()
{
    return pointee;
}

template<class T>
T& SmartPointer<T>::operator*()
{
    return *pointee;
}

template<class T>
SmartPointer<T>::operator void *()
{
    return static_cast<void*>(pointee);
}

/*
 * 这个函数对于smartpointer在继承体系中的使用是至关重要的！！！
 * 这里的思想：其类型转换工作通过constructor托管给了内置类型了，还给C++语法来执行！
 *
 * 该指针类型转换的动作将转换的工作交给SmartPointer<newType>的构造函数来完成了！！
 * 当newType是T的父类或者T类型的时候，该转换就会天然支持！！因为C++语法机制会在constructor的入参处自动完成 Derived* -> Base*类型的转换。
 * 当转换无法完成的时候，就会编译报错！
 *
 * 其流程如下：
 * 1. 寻找单一变脸的constructor
 * 2. 寻找隐式转换符，发现找不到
 * 3. 寻找模板函数，这时候发现了一个，然后实例化：
 * 4. 调用该模板转换符，然后调用constructor：:SmartPointer(NewType* pointee) : newTypePointee(pointee)
 * 5. 精髓就发生在这里！！newTypePointee 和 pointee 均是原生指针，如果 newTypePointee(pointee)合法，
 *      则说明从原生指针的角度可以转换，则智能指针也可以！！这就将类型转换的工作交给了内置类型！！！（内置类型可以转换必须是继承树向上转换才可以）
 */
template<class T> // 声明是个模板类的成员函数
template<class newType> // 声明模板类的模板成员函数的类型
SmartPointer<T>::operator SmartPointer<newType>() // SmartPointer<T>::表明类的作用域
{
    return SmartPointer<newType>(pointee);
}
class Foo {
public:
    std::string s = "Allen";
};

class Goo : public Foo
{
};
int main ()
{
    SmartPointer<Foo> smartF = new Foo;
    std::cout << smartF->s << std::endl; // 调用关系为(smartF.operator->())->s;
    std::cout << (*smartF).s << std::endl;

    SmartPointer<Foo> smartF2 = SmartPointer<Goo>();
    // 如上的类型转换，实际的类型转换工作和下面的这个类型转换工作是一样的。因为其类型转换工作通过constructor托管给了内置类型了
    Foo *pF;
    Goo *pG;
    pF = pG;

}
