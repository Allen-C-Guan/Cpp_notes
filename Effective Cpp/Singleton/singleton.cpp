#include <iostream>
#include <vector>
/*
 * 实现方法（这是用new的时候这么用）：
 * 1. 构造器私有化
 * 2. 创建类变量
 * 3. 自己创建一个obj，并把指针给这个类变量
 * 4. 给其他对象提供一个实例
 *
 *
 */
using namespace std;

//这个例子是是用non-local static（类变量）的指针来实现的单例模式
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

/*
 *       ****** static成员变量的singleton实现方法 的instance（不是ptr）
 * 1. 构造器私有化
 * 2。一个私有的自己类的实例，不能是其他类，并记得全局scope里进行实例化
 * 3。有个get函数，返回这类实例，返回的一定要是reference。（也只能返回reference，返回obj的过程中就会发生copy的）
 * 4。copy和=都要被删除（因为你返回的是obj）
 * 5. getInstance返回的必须是自己的类，
 */

class SingleTonWithStatic {
public:
    static SingleTonWithStatic& getInstance() { // 这里必须是reference，因为不让copy，你return的不是reference就会产生copy
        return s_Instance;
    }
    SingleTonWithStatic (const SingleTonWithStatic&) = delete;
    SingleTonWithStatic& operator = (const SingleTonWithStatic&) = delete;
private:
    static SingleTonWithStatic s_Instance;  //唯一一个初始化
    SingleTonWithStatic() {}  //不允许初始化
};
SingleTonWithStatic SingleTonWithStatic::s_Instance; //初始化这个类变量




                    //  ******** local static 代替 non-local static ******
// 但是我们亦可以用更加高端的形式来实现上述的目的，并且不用关心内存的问题，那就是用local static（函数中的静态变量）来代替 non-local static
//不但安全，而且简单
/*
 * 这里多了两个要求，
 * 1。 就是copy函数和operator要被删除，因为你创建的是个类，那么就有被copy的缝线
 * 2。getobj返回的必须是reference
 * 3. 构造器私有化
 * 4。一个getter返回一个local static变量
 * 5. getter必须是一个static函数
 */
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


/*     ************* 真是的singleton的例子 **********
 * 设计单例模式的思想应该是：
 * 1. 你需要一个class，而你希望这个class的obj全局只有一个。
 * 2. 你尽量不要给private外部接口。否则可以被复制。
 * 3. 设计思想，除了用单例模式必须的，其他的一样，该提供什么提供什么，该有什么成员变量，你就有什么成员变量就行了。
 *  但是这里单例模式需要注意，你的目标是本类型单例！而不是其他什么成员变量是单例。
 */
class ToDoList {
public:
    void initList(vector<string> inputsVec) { //因为没有constructor，所以需要一个init来初始化这个singleton instance
        size = inputsVec.size();
        m_v = inputsVec;
    }
    static ToDoList& getList() {  // 必有的，而且接口必须是static的，return的值也必须是本类型，但local static不是线程安全的
        static ToDoList m_vectorManager;
        return m_vectorManager;
    }
    ToDoList(const ToDoList& ) = delete;  // 这两个一定要删除咯
    ToDoList& operator =(const ToDoList&) = delete;

    string getEvent(int index) {
        return m_v[index];
    }

    size_t getToDoNum() {
        return size;
    }
    int addNewEvent(string input) {
        m_v.push_back(input);
        size++;
    }
    int finishedEvent() {
        m_v.pop_back();
        size--;
    }
private:
    ToDoList() : size(0) {};
    ~ToDoList(){};
private:
    // 由于singleton的设计模式，必须要返回本类型的东西，那么所有非本类型的东西，都必须要作为成员变量放在类里面。
    // 但需要注意，如果给这些私有变量提供了外部获取的接口，那这些私有变量也可以被复制了，这就违反了单例模式的设计思想了。
    // 因为你只限制了当前类的复制，并没限制这些内部参数的复制行为。
    size_t size;
    vector<string> m_v;
};


int main () {
    {
        singleTonLazy* obj = singleTonLazy::getSingleTonInst();
        singleTonLazy* obj2 = singleTonLazy::getSingleTonInst();  //只会被实例化一次。
        singleTonLocalStatic& objStatic = singleTonLocalStatic::getInstance(); //static 变量会在 main函数结束以后才会释放，因此detory会在打印end之后。
    }
    cout << "end" << endl;

}