#include <iostream>

/*
 * 实现方法：
 * 1. 构造器私有化
 * 2. 类变量指向这个唯一的obj
 * 3. 自己创建一个obj，并把指针给这个类变量
 * 4. 给其他对象提供一个实例
 */
using namespace std;

//这个例子是是用non-local static（类变量）来实现的单例模式
class singleTonLazy {
public:

    static singleTonLazy* getSingleTonInst() {
        if (s == nullptr) {  //检测是否是第一次新建这个类变量
            s = new singleTonLazy();    //这里可能会有内存泄漏的问题，
            cout << "singleTonLazy has been created" << endl;
        }
        return s;
    }

    ~singleTonLazy(){
        cout << "singleTonLazy has been destoryed" << endl;
    }

private:
    static singleTonLazy* s; //这个唯一的instance必须是类变量。即类静态指针指向这个instance
    singleTonLazy () {};  //constructor一定是private，不然外部可能会新建一个obj，就无非保证obj是唯一的了

    //这主要是利用c++ RAII机制. 我们知道，在程序结束的时候，系统会自动释放所有的全局变量和静态变量，他们都是存储在内层的静态区域。
    // 利用这个特点我们设计一个资源释放管理的类， 而当gc被释放的时候，s也就被释放了。

    // 但这里还有点小问题，以后改进 TODO
    class GC {
    public:
        ~GC(){
            if (singleTonLazy::s != nullptr) {
                delete singleTonLazy::s;
            }
        }
    };

    static GC gc;
};

singleTonLazy* singleTonLazy::s = nullptr;   //要先给个初值




                    //  ******** local static 代替 non-local static ******
// 但是我们亦可以用更加高端的形式来实现上述的目的，并且不用关心内存的问题，那就是用local static（函数中的静态变量）来代替 non-local static
//不但安全，而且简单

class singleTonLocalStatic {
public:
    singleTonLocalStatic(const singleTonLocalStatic&) = delete;  //把这两个放到private和delete效果是一样的。
    singleTonLocalStatic& operator == (const singleTonLocalStatic&) = delete;

    static singleTonLocalStatic& getInstance() {  //返回方式要用reference，因为是唯一一个obj，没必要用值传递的方式进行赋值操作。
        static singleTonLocalStatic s;  //这里要用static local variable，因为这样这个variable会在第一次遇见的时候被初始化，而后就一定不会被初始化了
        return  s;
    }
    ~singleTonLocalStatic(){
        cout << "local static instance destoryed" << endl;
    }
private:
    singleTonLocalStatic(){cout << "local static instance created" << endl;};
};



/*
 *   *********** static function ********
 *  static function 只要在 函数开头加个static就行了。
 编译器在编译一个普通成员函数时，会隐式地增加一个形参 this，并把当前对象的地址赋值给 this，所以普通成员函数只能在创建对象后通过对象来调用，
 因为它需要当前对象的地址。而静态成员函数可以通过类来直接调用，编译器不会为它增加形参 this，它不需要当前对象的地址，所以不管有没有创建对象，
 都可以调用静态成员函数。

普通成员变量占用对象的内存，静态成员函数没有 this 指针，不知道指向哪个对象，无法访问对象的成员变量，也就是说静态成员函数不能访问普通成员变量，
 只能访问静态成员变量。

普通成员函数必须通过对象才能调用，而静态成员函数没有 this 指针，无法在函数体内部访问某个对象，所以不能调用普通成员函数，只能调用静态成员函数。
 */



int main () {
    {
        singleTonLazy* obj = singleTonLazy::getSingleTonInst();
        singleTonLazy* obj2 = singleTonLazy::getSingleTonInst();  //只会被实例化一次。
        singleTonLocalStatic& objStatic = singleTonLocalStatic::getInstance(); //static 变量会在 main函数结束以后才会释放，因此detory会在打印end之后。

    }
    cout << "end" << endl;

}