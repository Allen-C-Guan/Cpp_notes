#include <iostream>

/*
 * *************************************   嵌套类   *******************************************
 * 嵌套类指的是：一个类定义在另一个类内部，既为嵌套类。
 * 嵌套类的作用：
 * 对于有些只在类内有用的类，没必要放到类外作为一个全局的类，别人也不用，还污染全局空间。
 * 比如：你抽象出来一个数据结构，用来作为类的各个成员函数中间传递的变量，由于是中间变量，对外暴露没有任何意义。这时候你就
 * 可以定义一个私有嵌套类！
 *
 * 注意：
 * 1. 内层和外层的成员之间没有任何关系！
 * 2. 没有任何特殊访问权利！并不会因为嵌套，访问权限就会有特殊性，并没有
 * 3. 内层类只在外层作用域中可见！出了类外就再也看不到了
 *      注意：对于OutsideClass::InsideClass这种，貌似在外部也看到了InsideClass 但实际上，你是在外部打开了OutsideClass作用域
 *          因此::后面的位置就是OutsideClass作用域内部了。
 *          因此并不是你在外面看到了InsideClass，是你在外面打开了OutsideClass的作用域！
 *
 */





class OutsideClass {
public:
    class InsideClass; // class内嵌，仍然遵守访问符的限制，如果在public里面则外面也能看见，private在外面就看不见了
                        // 这里对InsideClass进行声明，但不定义，因此这时候InsideClass还不是完整的
    int a;
    long l;
    InsideClass FooFunc(); // 不能在这里定义这个函数，必须在外面定义！因为这时候InsideClass还不是完整的呢

private:
    class PrivateInsideClass { // 这个类在外面就看不到了！！无法再类外实例化，也无法调用其成员函数
        int a; // 内外两层class之间也没啥关系，命名也不冲突！
    };

};

class OutsideClass::InsideClass { // 这里也必须写OutsideClass::
public:
    InsideClass(int a, double d) : a(a), d(d) {}
    int a;
    double d;
    void print () {
        std::cout << "this is InsideClass" << std::endl;
    }
};
// 通过以上的定义，代码编译到这里的时候，InsideClass终于算是完整了，这时候就可以写含有insideClass的函数了。
// 在这之前，是不可以写的。

OutsideClass::InsideClass OutsideClass::FooFunc() { // return 的值必须要写outsideClass
    return InsideClass(1, 3.14);
}


int main ()
{
    OutsideClass::InsideClass i = OutsideClass::InsideClass(1,3.14);
    i.print();

//    OutsideClass::PrivateInsideClass p;
}
