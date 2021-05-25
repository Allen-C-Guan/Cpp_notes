#include <iostream>

/*
 * ***********************************  使用RTTI  ********************************************
 * RTTI (run-time type identification) 运行时类型识别！
 * 该方法是一种在运行时确定类型的方式，根据类型的不同，来执行不同的代码。
 * 其实现的前提就是dynamic_cast 和 typeid。
 *
 * 在实际应用的过程中，我们通常是将所有子类，归一化为父类指针或者父类引用来批量处理， 那么这时候如果我有诉求说，我要根据其动态类型的不同
 * 来执行不同的代码逻辑的时候，就需要RTTI技术来完成。
 *
 * 首先从静态类型上来看，所有的对象的类型均是统一的父类类型。那么要想根据动态类型来执行不同的代码逻辑就要分两步来完成
 * 1. 确定该对象的动态类型
 * 2. 将其静态类型cast成与动态类型一致。而后才可以使用其子类特有的部分的成员
 *
 * 要想实现上面的两步，就要依赖RTTI中两个最主要的技术
 * 1. typeid，用来确定动态类型
 * 2. dynamic_cast 来完成类型的转换
 *
 * 应用场景：
 * 貌似如上所说，可以使用虚函数来完成啊，你看你的逻辑不就是，子类归一化为父类，但子类要有自己的特性，而这个特性就是虚函数啊！
 * 而且虚函数的机制要比RTTI的机制要好很多，安全可靠，编译器管理类型，RTTI需要手动管理类型。
 *
 * 但问题在于，有时候虚函数就是无法做到！！比如：
 *
 * 你需要一个类型敏感的判等函数，因此你想重载一个operator==, 那么为了复用代码，你写成：
 * bool operator== (Base &lhs, Base &rhs);
 * 这样的形参让所有base继承树下的类型都可以作为入参。
 * 然后你body里面的实际对比二者区别的功能想做成虚函数，将实际判等的工作交给虚函数来实现，于是你得到
 * bool operator== (Base &lhs, Base &rhs) {
 *      lhs.equal(rhs);
 * }
 *
 * 然后你开始写虚函数：
 * class Base {
 *  virtual bool equal(Base &b){
 *      // 判等b和*this的所有成员
 *  }
 * };
 *
 * class Derived : public Base{
 *  bool equal(Base &b) override { // 这就有问题了，你说你要用虚函数，所以这里形参类型必须是Base&
 *      // 那你这里判个毛线啊？ 静态类型是Base，所有Derived类型中独有的部分都无法判等！
 *  }
 * }
 *
 */

class Base {
public:
    int a;
    double d;
    virtual bool equal(Base &b) {  // 必须是虚函数，因为dynamic cast要求必须有虚函数，没有vptr，dynamic cast没法实现
        return a == b.a && d == b.d;
    }
};

class Derived : public Base {
public:
    long l;
    bool equal(Base &d) override { // 这里需要重写
        if (Base::equal(d)) {
            const Derived &r = dynamic_cast<const Derived&>(d); // 调用这个函数的前提在于类型一定时一致的，因此这里一定不会抛出异常
            return this->l == r.l; // cast为当前类后，就可以对比当前类型特有的数据部分了
        }
        return false;
    }
};

bool operator== (Base &lhs, Base &rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs); // 必须要先判类型是否一致，后判成员变量是否一致
}



int main ()
{
    Derived d1;
    d1.l = 10; d1.a = 1; d1.d = 5;
    Derived d2 = d1;
    // 类型一致，且所有成员都一致
    bool res = d1 == d2;
    std::cout << res << std::endl;

    // 类型一致，但特有部分不一致
    d2.l = 1000;
    res = d1 == d2;
    std::cout << res << std::endl;

    // 类型一致，但base部分就不一致了
    d2.a = 100;
    res = d1 == d2;
    std::cout << res << std::endl;
    
    // 类型不一致
    Base b;
    res = b == d1;
    std::cout << res << std::endl;

}
