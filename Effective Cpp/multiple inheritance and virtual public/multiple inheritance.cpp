#include <iostream>


/*
 *                      **********   虚继承   *********
 * 虚继承的目的是为了解决多继承带来的二义性而提出的概念。当继承树存在类似于如下的结构时。
 *          A
 *         / \
 *        B   C
 *         \ /
 *          D
 * 此时我们可以发现， B中含有全部的A的信息，而C中也含有全部的A的信息，而D含有全部的B和C的信息，换句话说，D中包换了2份的A和一份的
 * B特有的信息，和C的一份特有信息。
 * 此时，如果D想要获取A的成员变量。就会有二义性，即到底是从D->B->A 还是 D->C->A呢？而虚继承就是为了解决这个问题的。
 *
 * 我们让B和C来虚继承A，此时D内就会只有一份A的信息。因此也就不会存在二义性了。
 *
 * 因此这里virtual表示的含义是，允许其他类和他共享基类。在这里，如果B用了virtual，表示B愿意和其他类share他们的父亲A，而C如果也愿意的话，
 * 此时D在继承B和C的特有信息的时候，发现B和C都愿意share他们的基类，那么B和C的公共部分A就只会被D获取到一份。因此不在存在二义性。
 *
 * 但这个逻辑有个反人类的地方在于，我们要对B和C进行虚继承，D才会享有虚继承带来的红利。有点前人栽树后人乘凉的感觉。D的虚继承对于A的二义性
 * 没有任何帮助。换句话说虚继承只会影响采用了虚继承的类下一代的子类，而对当前类没有影响。
 *
 */


using namespace std;

class A {
public:
    int m_a = 1;
};

class B : virtual public A{
public:
    int m_b = 2;
};

class C : virtual public A{
public:
    int m_c = 3;
};

class D : public B, public C {
public:
    int m_D = 4;
};




int main () {

    D d;
    cout << d.m_a << endl;

}