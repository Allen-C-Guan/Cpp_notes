#include <iostream>
#include <string>

/* 对于copy函数的两个点
 * 1. copy函数要覆盖到所有的成员变量，因此如果修改了成员变量，那么构造函数和copy函数都要进行修改
 * 2. copy函数还要调用父类的copy函数保证父类中的信息也被copy过来了。否则会调用父类的**无参constructor**，而不是**copy constructor**
 *
 * **************************************************************************************
 *          在类copy函数可以接触到其他obj的私有变量
 * 产生这种疑惑的原因是自己对私有成员变量的理解有误，封装是编译期的概念，是针对类型而非对象的，
 * 在类的成员函数中可以访问 **同类型实例对象** 的 **私有成员变量**．
 *
 * 访问限制标号是针对类而不是针对一个类的不同对象，只要同属一个类就可以不用区分同一个类的不同对象。因为 是类的成员函数，
 * 所以有权限访问私有数据成员。如果是在main函数中直接，那肯定就会报错了，不能访问，因为这是在类外不能访问私有数据成员。
 * 一个类的成员函数可以访问这个类的私有数据成员，我们要理解这个对类的访问限制，而不是针对对象。
 */
using namespace std;
class Base {
public:
    Base () {}
    Base (int val, string s): val_(val), s_(s) {}
    virtual ~Base () {}

    Base(const Base &other): val_(other.val_), s_(other.s_) {}
    Base& operator= (const Base &other) {
        val_ = other.val_;
        s_ = other.s_;
        return *this;
    }
private:
    int val_;
    string s_;
};

class Derived : public Base{
public:
    Derived(double dval) : dval_(dval), Base(3,"Allen") {}  //base有午餐构造器的时候可以不用explicit调用父类构造函数，默认调用父类无参构造器

    Derived(const Derived& other)
    :Base(other), dval_(other.dval_){}   // 这里如果不调用base的copy constructor的话，就会调用base的默认constructor，而不是base的copy constructor
                                        // 那就导致被拷贝的obj和传入的obj的base信息不同
    Derived& operator= (const Derived &other) {
        Base::operator=(other);
        dval_ = other.dval_;
        return *this;
    }
private:
    double dval_;
};

int main () {
    Derived d(4);
    Derived d2 = d;
}


// 这是错的表达形式，该形式没有调用父类的constructor，导致父类的变量没有正常被copy。而调用了父类的无参constructor的例子
class BaseWorry {
public:
    BaseWorry() :m_val(-1), m_name("default"){
    };
    BaseWorry(const BaseWorry& other) :m_val(other.m_val), m_name(other.m_name){
    }

public:
    int m_val;
    string m_name;
};


class DerivedWorry : public BaseWorry {
public:
    DerivedWorry():BaseWorry(), m_ID(0) {};
    DerivedWorry(const DerivedWorry& other) : m_ID(other.m_ID){
    }

public:
    int m_ID;
};

int main2() {
    DerivedWorry d1;
    d1.m_name = "allen";
    d1.m_val = 9;
    d1.m_ID = 1234;

    DerivedWorry d2 = DerivedWorry(d1);
    cout << d2.m_val << endl;
    cout << d2.m_name << endl;
    cout << d2.m_ID << endl;

}