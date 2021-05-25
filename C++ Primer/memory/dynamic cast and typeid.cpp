#include <iostream>

/*
 * **********************  运行时类型识别  ************************
 * RTTI主要由两个运算符来实现的：
 * 1. typeid 运算符，用户返回表达式的类型
 * 2. dynamic_cast 运算符，将基类的指针，或者引用*安全*的转换成派生类的指针或者引用。
 *
 * 通常情况下，我们要采用虚函数来管理类型，而不是使用RTTI。 虚函数意味着，只要你遵守编译的
 * 规则来写虚函数，编译器会帮你管理类型属性与成员函数的调用，不需要程序员来管理。
 * 而RTTI意味着，程序员手动管理类型。
 *
 * 因此RTTI适合：我们想使用基类对象的指针或引用来执行某个派生类操作并且该操作不是虚函数时！
 * （因为并不是所有时候都可以使用虚函数来实现多态的）
 *
 * ******************** dynamic_cast 运算符 **************************
 * 两个概念：
 * 1. upcast: 继承体系中，向父类方向cast
 * 2. downcast：继承体系中，想子类方向cast
 *
 * 功能：
 * dynamic_cast的提出是为了解决downcast的问题的，因为upcast通常都是安全的，我们可以使用static_cast来安全的完成。
 * 但是downcast并不总是安全的，downcast只有当该内存下的类型真的是该子类的时候，才是安全的，否则就是不安全的。
 *
 * 同时dynamic_cast还可以完成交叉转换，比如Derived1 和 Derived2 都继承与Base, 则我们可以写
 * Derive1 *pd1 = dynamic_cast<Derived1*> pd2;
 * 返回的是nullptr。
 * 但是：
 * Derive1 *pd1 = static_cast<Derived1*> pd2;
 * 则会编译报错！！！
 *
 * 因此dynamic_cast 会让编译器检查downcast是否安全，如果安全，则会cast过去，而如果不安全，则会抛出异常，阻止你去cast
 *
 * 使用方法：
 * dynamic_cast<type*>(e); // e必须是个有效指针
 * dynamic_cast<type&>(e); // e必须是个左值引用
 * dynamic_cast<type&&>(e); // e必须不能是左值
 *
 * type必须是类类型，通常情况下要含有虚函数。
 *
 * 如下三种中其中一种，则会dynamic_cast成功
 * 1. e是type的公有派生类（upcast)
 * 2. e是type的公有基类（downcast）
 * 3. e是就是type类型
 *
 * 当转换失败的时候
 * 1. 如果是指针，则会返回nullptr
 * 2. 如果是引用，则会抛出异常bad_cast异常。
 *
 *
 */

class Base {
public:
    virtual void print() {
       std::cout << "Base" << std::endl;
    }
};

class Derived1 : public Base {
public:
    virtual void print() override {
        std::cout << "Derived1" << std::endl;
    }
};

class Derived2 : public Base {
public:
    virtual void print() override {
        std::cout << "Derived2" << std::endl;
    }
};


void test_dynamic_cast_for_ptr() {
    Derived1 d1;
    Derived1 *pd = &d1;
    Base *pb = &d1; // 将其变成base指针
    /**************************** downcast ************************************/

    /******************* derived1类型的base指针，downcast为derived1类型 *************/
   std::cout << "derived1 type obj with base ptr, downcast to derived1 type" << std::endl;

   // dynamic cast
   // 实际是derived1，因此可以成功从base cast成为derived1类型 downcast! 符合条件的时候是安全的
   if(Derived1* pd1 = dynamic_cast<Derived1*>(pb)) {
       pd1->print();
   } else {
       std::cout << "nullptr" << std::endl;
   }

   // static cast
   Derived1 *pd1Static = static_cast<Derived1*>(pb);  // static and dynamic 好像是相同的
   pd1Static->print();

   /******************* derived1类型的base指针，crosscast为derived2类型 *************/
    std::cout << "derived1 type obj with base ptr, crosscast to derived2 type" << std::endl;

    // dynamic cast
    // 实际是derived1的obj，没法cast成为derived2，交叉cast会被dynamic校验住
    if(Derived2 *pd2 = dynamic_cast<Derived2*>(pb)) {
        pd2->print();
    } else {
        std::cout << "nullptr" << std::endl;
    }

    // static cast
    Derived2 *pd2Static = static_cast<Derived2*>(pb); // 这里就不同了啊， 你static cast的虽然成功了，但是结果是毫无道理的，无意义的
    pd2Static->print();

    /******************* 同类型指针  ************************/
    std::cout << "same type cast" << std::endl;
    if(Base *pb2 = dynamic_cast<Base*>(pb)) {
        pb2->print();
    } else {
        std::cout << "nullptr" << std::endl;
    }

    /**************************** upcast ************************************/
    std::cout << "upcast" << std::endl;
    if (Base *pb = dynamic_cast<Base*>(pd)) {
        pb->print();
    } else {
        std::cout << "nullptr" << std::endl;
    }

    Base *pb2 = static_cast<Base*>(pd);
    pb2->print();
}



/*
 * ********************************* typeid **********************************
 * typeid(e) 是一种可以在运行时，或者编译期，获得任意表达式或类型名字的类型的运算符。
 *
 * 当e存在虚函数的时候，则typeid表达式会在运行的时候确定其动态类型，反之，当e不存在虚函数的时候，则typeid
 * 表达式会在编译期的时候，根据其静态类型获取typeid(e)的运算结果。
 *
 * 注意：
 * 如果是在编译期确定运算类型，（没有虚函数，与静态类型保持一致），此时typeid(e)这个表达式并没有通过计算获得，而是
 * 直接通过编译器来获取其结果，而不是通过对typeid(e)求解获得的，因此这意味着，此时e是一个无效指针也无所谓，静态类型
 * 的获取不依赖于e是否有效！
 *
 * 如果存在虚函数，如果e是一个指针的解引用，就必须要保证e的解引用是有效的。否则会抛出bad_typeid的异常。
 *
 * 对于函数指针和数组，typeid(e)的结果并不会退化为指针，会保留函数类型和数组类型的
 *
 */


void test_typeid () {
    Base *b = new Base;
    Derived1 *d1 = new Derived1;
    Derived2 *d2 = new Derived2;
    Base *b1 = d1;
    Base *b2 = d2;

    // 类型判定
    if(typeid(*b1) == typeid(Derived1)) { // 指针判定
        std::cout << "b1 type is Derived1" << std::endl;  // 走这里
    } else {
        std::cout << "b1 type is not Derived" << std::endl;
    }

    if(typeid(*b2) == typeid(Derived1)) {
        std::cout << "b2 type is Derived1" << std::endl;
    } else {
        std::cout << "b2 type is not Derived" << std::endl;  // 走这里
    }

    if(typeid(*b1) == typeid(Base)) {
        std::cout << "b1 type is Base" << std::endl;
    } else {
        std::cout << "b1 type is not Base" << std::endl; // 走这里！ 就是说base和derived不属于同一个类型
    }

}


int main ()
{
    test_dynamic_cast_for_ptr();
    test_typeid();

}
