#include <iostream>
#include <cstdio>


/* ********************  虚函数与重写  *************************
 * 虚函数的原理在于，任何存在虚函数的类都会有一个vptr， 而这个vptr指向专属本类的vtable，而这个vtable罗列了当前类下所有成员函数位置
 * 每个成员函数在vtable中都有唯一对应的地址。而当调用成员函数的时候，会通过vptr找到vtable，而后在vtable中找到对应的成员函数的地址，
 * 然后调用对应的函数。
 * 
 * 当子类override父类方法的时候，vtable中对应的函数地址就会被覆盖（替换）成子类的方法地址，如果没有override则会使用父类的成员函数地址。
 * 且虚函数按照其声明顺序放于表中，父类的虚函数在子类的虚函数前。替换不会改变vtable的顺序，且vtable本质就是一个函数指针array！
 * 
 * 当继承发生的时候，vptr是会被继承的，当用父类指针或者引用来调用子类成员函数的时候，由于是引用和指针的关系，vtable用的还是子类的，
 * 因此当发生调用的时候，依然遵循着vtable中的设定来调用，因此如果子类override父类方法后，成员函数指针从父类函数被替换成子类成员函数指针的时候，
 * 由于覆盖和子类vtable的原因，仍然会调用子类的成员函数，而不是父类的，而这就是多态实现的理论基础。
 * 
 * 总结为： 必须用子类object的内存来调用成员函数，才可实现动态绑定，因为vptr是子类的，且vtable被替换掉了。
 *
 * 注意：
 * 1. 每一个类都有虚表
 *
 * 2. 虚表可以继承，如果子类没有重写虚函数，那么子类虚表中仍然会有该函数的地址，只不过这个地址指向的是基类的虚函数实现，如果基类有3个虚函数，
 * 那么基类的虚表中就有三项(虚函数地址)，派生类也会虚表，如果重写了相应的虚函数，那么虚表中的地址就会被替换，指向自身的虚函数实现，
 *
 * 3. 派生类的虚表中虚地址的排列顺序和基类的虚表中虚函数地址排列顺序相同。
 *
 */
class Derived;
class Base {
public:
    void init() {
        virtual_print();
        non_virtual_print();
    }
    virtual void virtual_print() {
        std::cout << "this is base virtual print" << std::endl;
    }

    void non_virtual_print() {
        std::cout << "this is base non virtual print" << std::endl;
    }
    /*
     * **************  重定义和重写的区别和工作流程  ****************
     * 函数匹配与调用有两个机制：
     * 1. 函数名称的匹配： 指的是从被调用的作用域开始由内到外的搜索（派生类的作用域嵌套在父类作用域之内），当搜索到匹配的函数以后停止搜索。
     *      因此函数搜索的顺序就决定了，函数匹配过程存在隐藏的可能，既内层作用域的同名函数会隐藏外部作用域的同名函数。 
     * 2. 虚函数的匹配： 通过vptr指向的vtable来确定函数的选择！ 子类的override会替换（覆盖）父类的同名函数。 只有通过明确的指示，才可以
     *      调用父类的函数。
     * 
     * 
     * 重定义的特性是：隐藏！隐藏的原理是通过作用域查找来隐藏的，既从当前作用域来查找的时候，一下就找到了，也就不往其他地方去找了。
     * 重写的特性是：覆盖！，既vtable中函数指针的替换（覆盖)
     * 当print是虚函数的时候，Derived的vtable中的print函数指针就从父类print函数地址，被替换成了子类print函数指针地址了，因此当
     * 调用virtual_print函数的时候，
     * 1. 从vptr中找到vtable，
     * 2. 从vtable中找到virtual_print指针地址，
     * 3. 用virtual_print指针地址，找到函数Derived::virtual_print()函数
     * 4. 最后调用Derived::virtual_print()函数。
     *
     * 当print不是虚函数的时候，这时候叫重定义，对于重定义的函数，采用函数匹配机制来进行隐藏的，因此流程是这样的，
     * 1. 在被调用的作用域(base class 内部进行函数匹配)开始，non_virtual_print()函数，
     * 2. non_virtual_print()函数在base中被找到
     * 3. 调用Base::non_virtual_print()函数
     *
     */
};

class Derived : public Base {
public:
    void virtual_print() override {
        std::cout << "this is Derived" << std::endl;
    }
    void non_virtual_print() {
        std::cout << "this is derived non virtual print" << std::endl;
    }
};

int main ()
{
    Derived d;
    d.init();
}
