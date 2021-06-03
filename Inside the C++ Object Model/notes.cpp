#include <time.h>
#include <chrono>
#include <iostream>   // std::cout
/*
 * ***************************  构造语义学  ************************************
 */
class Foo {
public:
    int a;
    double d;
    Foo () : a(0), d(0){} // 合成默认构造函数是不会构造a和d的，因为编译器认为内置类型的初始化的诉求是程序员的，而不是编译器的，编译器不默认初始化他也不耽误我编译
};
/*
 * 合成默认构造函数会在需要的时候构造出来，那么什么是需要？
 * 1. 当使用的时候，合成默认构造函数只有当你用的时候，才会被合成出来，且是inline的
 * 2. 需要指的是编译器需要，而不是程序员需要，比如在Bar里，你提供了Bar的默认构造函数，在这个时候，编译器需要对f成员进行默认构造，可是你没给啊
 *      这时候编译器就会给你合成一个完整的默认构造函数，将f来默认构造出来
 *      那么至于a，对不起，a的初值是什么并不是编译器需要，是程序员的需要！！而程序员的需要，是不会被合成默认构造函数的！
 */
class Bar {
public:
    Foo f;
    int a;
    Bar() : a(0){} // 构造器的扩张！！ 这里我们虽然只初始化了a，但是编译器会根据编译需要，将f的默认初始化也放到这个构造函数内！
};

void test_default_constructor() {
    Foo f;
    std::cout << f.a << std::endl;
    std::cout << f.d << std::endl;

    Bar b;
    std::cout << b.f.a << std::endl;
    std::cout << b.f.d << std::endl;
}

/*
 * ************ 对于派生类的默认初始化  ***************
 * 1. 构造函数
 * 如果子类没有显示的调用父类构造函数，那么子类的构造函数会隐式的调用父类的默认构造函数来构造父类部分
 * 因此可以看成父类部分也是子类的一个成员，那么当你没有显示初始化父类的时候，编译器会给你默认初始化父类的
 *
 * 2. 对于有virtual function的情况
 * 如果存在虚函数，那么即使你不给出默认构造函数，编译器也一定会生成一个，因为vptr和vtbl无论如何也要被构造出来！
 * 并且要保证，其中的vtbl中对应的虚函数要换成子类自己的成员函数的ptr！
 *
 * 3. 有virtual base 的情况
 * 对于存在虚继承父类的情况，编译器一定要保证，在编译器，父类的数据在每一个子类中的位置可以安排妥当！
 * 否则子类无法调用父类的数据！
 *
 * 那么对于多重继承而言，cfront编译器是将父类以指针的形式存放在子类对象中的，当需要父类数据的时候，
 * 子类可以通过指针索取到其父类数据！
 *
 */
class Base {
public:
    int a;
    double b;
    Base() : a(0), b(0) {}
};

class Derived : public Base {
public:
    int c;
    Derived() : c(0) {}
};

void test_Derived_default_constructor () {
    Derived d;
    std::cout << d.a << std::endl;
    std::cout << d.b << std::endl;
}

/*
 * ************************  copy 构造函数  **************************
 * 对于没有指出copy构造函数的类而言，编译器是有可能给合成一个拷贝构造函数的。但也可以不合成。
 *
 * 同样copy构造函数是在“需要”的时候，才会被合成出来！
 * 那么什么是需要？
 * 当该类可以通过bitwise copy semantics（位逐次拷贝）来创造的时候，就不会合成copy构造函数！
 *
 * 那么什么是bitwise copy semantics?
 * bitwise copy semantics指的是 如果编译器可以通过对内存按位逐位拷贝的方式来构造一个对象的时候
 * 就叫bitwise copy semantics!
 * 同时对于bitwise copy semantics而言，其对象的copy不需要以一个函数调用的方式来完成，所需要的
 * 只是底层内存的copy！
 *
 * 那么什么时候编译器认为可以通过bitwise copy semantics来copy呢？ 那就是当该类的全部成员
 * 均是内置类型的时候（整数，指针，等类型）。
 *
 * 当存在类成员，并且类成员有自己的默认构造函数的时候，编译器要想构造该成员，就必须通过调用该类的默认构造
 * 函数来完成该类的构造。
 * 那么这个时候，系统就不可以单纯的从bitwise的角度对代码进行copy了，这时候需要构造一个copy 构造函数
 * 通过函数调用的方式来对对象进行构造！
 *
 * 当然，如果类存在虚函数，主要分成两种情况
 * 1. 当类型一致的时候：
 *  此时也可以对对象进行bitwise的copy，因为对于同类型的vptr的copy而言，是安全的！因为同类型的vptr一定指向
 *  同一个vtable！
 *
 * 2. 如果用不子类来构造父类的情况下（对象类型不一致），
 *  此时就需要对vptr和vtable进行差异化构造了，这时候编译器也会合成一个默认copy构造函数用来正确的初始化vptr和vtable！
 *  因为比如： Base b = d; // d是derived类型的
 *  这里要求b的vptr必须指向Base的vtable，但是d中的vptr指向的Derived类型的vtable。 因此不可以将d成员内的
 *  vptr直接copy到b类型中。
 *
 *
 *
 *
 */



/*
 * **************** 函数成员指针  ****************
 */
class Point3d {
public:
    virtual ~Point3d() = default;
public:
    static Point3d origin;
    float x;
    float y;
    float z;
    float getX() {
        return x;
    }
    virtual float getZ() {
        return z;
    }
};

/*
 * 成员函数指针本质上是offset, 无法单独使用，必须绑定在obj上来使用
 */
void test_members_data_ptr () {
    std::cout << sizeof(float) << std::endl;
    printf("%u \n",& Point3d::x); // 必须用printf来打印！不能用std::cout
    printf("%u \n",& Point3d::y);
    printf("%u \n",& Point3d::z);

    // 成员指针的使用
    Point3d p;
    p.x = 1; p.y = 10; p.z = 100;
    // 声明
    float (Point3d::*coord) = &Point3d::x; // member 声明
    float (Point3d::*getCoord)() = &Point3d::getZ; // member function 声明
    // 使用
    std::cout << p.*coord << std::endl; // 必须绑定在obj上，用来初始化this指针！
    std::cout << (p.*getCoord)() << std::endl; // member function 调用

    //concrete member function pointer 与 virtual member function pointer
    printf("concrete member function place = %u\n", &Point3d::getX);
    printf("virtual member function place = %u\n", &Point3d::getZ);
}


/*
 * 纯虚函数
 */
class Base1 {
public:
    virtual void Interface () = 0;
};

class Derived1 : public Base1 {
public:
    void Interface() override {
        Base1::Interface(); // 编译竟然可以通过，但是link的时候会报错！
        std::cout << "Pure virtual function has been called" << std::endl;
    }
};

void test_constructor_destructor_copy() {
//    Derived1 d1;
//    d1.Interface();
}




int main ()
{
    int a = 10;
    std::cout << a << std::endl;

}
