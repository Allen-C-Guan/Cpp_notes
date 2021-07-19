#include <iostream>
#include <string>
#include <vector>
#include <map>
/*
 * ******************************** 将constructor和non-member function虚化 **********************************
 * 假如我们有这样的一个诉求，就是对于继承体系
 * 父类：Base， 子类 Derived1, Derived2 这种体系下，
 * 我想统一调用一个接口，用来生成obj，这个obj的诉求就是，如果你是Derived1的类型，则你生成一个Derive1类型，如果你是Derived2
 * 就生成一个derived2类型。
 *
 * 为了满足如上诉求，首先“统一接口” + “继承体系” 就让你想到虚函数，而生成一个新的obj就让你想到构造函数。
 * 但是问题就在于构造函数不能使用虚函数！
 *
 * 但是C++对于override有个口子，就是子类override父类的函数的时候，将return的父类指针替换为子类指针也是可以的！这就给我们提供
 * 了一个实现的方法！
 * 
 * 我们利用这个口子，包装一个copy constructor，这个函数具有多态，且可以返回子类指针，而其内部调用的都是各自自己的copy constructor
 * 又因为我们这里调用的是各自的copy constructor，因此这个copy行为还是被统一管理的。
 * 
 * ******************************* non member function 的虚化行为 ****************************
 * 这个比较简单，当我们有时候必须需要non member function， 又想实现多态的时候，只要
 * 
 * 非虚函数壳子 + 虚函数的实际工作 + inline声明
 * 
 * 就可以将非虚函数包装成虚函数的样子！
 * 
 */
class Base
{
public:
    Base():a(0){}
    Base(const Base &other) : a(other.a){}
    virtual Base* clone() // 虚函数，而且返回值为Base指针
    { 
        return new Base(*this); // clone函数中调用其copy构造函数
    }
private:
    int a;
};

class Derived : public Base
{
public:
    Derived():Base(){}
    Derived(const Derived &other):Base(other)
    {
        std::cout << "this is Derived copy constructor" << std::endl;
    }
    virtual Derived* clone() override // 虚函数，而且返回值为Derived指针
    {
        return new Derived(*this); // clone函数中调用其copy构造函数
    }
};

class Derived2 : public Base
{
public:
    Derived2():Base(){}
    Derived2(const Derived2 &other):Base(other)  
    {
        std::cout << "this is Derived2 copy constructor" << std::endl;
    }
    virtual Derived2* clone() override  // 虚函数，而且返回值为Derived2指针
    {
        return new Derived2(*this); // clone函数中调用其copy构造函数
    }
};

int main() {
    // 这里有个父类指针数组，我们就可以对其进行批量构造了啊！
    Base* bArr[3] = {new Base(), new Derived, new Derived2};
    for (auto it : bArr) {
        it->clone();
    }

    std::cout << "ENDING" << std::endl;
}
