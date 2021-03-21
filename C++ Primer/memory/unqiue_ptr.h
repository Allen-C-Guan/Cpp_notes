
#include <iostream>
#include <memory>

/*
 * ********************   unique_ptr   ******************
 * unique_ptr与shared_ptr的不同在于：
 * 1. unique_ptr拥有指向的对象，shared_ptr只是可以使用而已
 * 2. unique_ptr没有拷贝和赋值
 * 3. unique_ptr只能直接初始化 #cpp 11 从c++14开始有make_unqiue了
 *
 * 具体使用方法：
 * unique_ptr<T> p (new T()); // 直接初始化
 * unique_ptr<T, D> p; // 类型为D的可调用对象来释放指针
 * unique_ptr<T, D> p(d); // 类型为D的对象d代替deleter，这里和shard_ptr不同，需要类型，shared_ptr只需要可调用对象即可
 * p = nullptr; // 将p指向的对象释放，并将p置为空
 * p.release(); // 将p释放对当前的内存的拥有权，返回row ptr，并将p置空，注意只是放弃了拥有权，没有释放内存！！
 *              // 如果不对返回的row ptr进行存储并在合适的地方释放，会导致内存泄漏
 *              // 该函数通常是为了转移所有权
 * p.reset(); // 释放p所拥有的内存
 * p.reset(q); // 释放旧内存，拥有q（row ptr）的新内存
 *
 * 可以拷贝即将被销毁的unique_ptr
 *
 * 对于即将要销毁的unique_ptr，是可以被"特殊的拷贝"（move）的。这为函数返回局部unique_ptr提供了条件
 * 比如 return unique_ptr<T> up(new T());
 *
 * 这里up其实是函数内部的局部变量，本质上不可以return回到调用点的。因为return就意味着copy。
 * 但这种情况编译器可以识别出来，通过move（所有权转让）的方式将不可以拷贝的局部对象 move到调用点去。
 *
 */

std::unique_ptr<int> GetUniquePtr()
{
    return std::unique_ptr<int>(new int(10));
}

class Connect{
public:
    int a = 10;
    Connect ()
    {
        std::cout << "Connecting" << std::endl;
    }

    ~Connect() // 如果指定了deleter，则destructor不会被执行！因为你压根没delete啊！没delete就不会调用destructor
    {
        std::cout << "Connected has been destroyed" << std::endl;
    }
};

void Disconnected (Connect *c) {
    std::cout << "Disconnected" << std::endl;
}

int main ()
{
    // unique_ptr的直接初始化
    std::unique_ptr<int> up(new int(6));

    // 使用make_unique
    std::unique_ptr<int> up0 = std::make_unique<int>(6);

    // unique_ptr所有权转移
    std::unique_ptr<int> up1(new int(10));
    up1.reset(up.release()); // up将所有权让出（并没有释放内存），返回row ptr，并将自己置为nullptr。
    // up1释放了原内存，并接管了被up释放的内存。
    // release的错误使用
    up1.release(); // 一旦这么用了，up1的内存永远不会被释放了。release并不释放内存，而返回的指针你还扔了。

    // 使用即将被销毁的unique_ptr
    std::unique_ptr<int> pVal = GetUniquePtr(); // 如果真的不允许copy或者move，unique_ptr是没有办法返回的

    // 自定义deleter
    Connect *pc = new Connect();
    std::unique_ptr<Connect, decltype(Disconnected)*>(pc, Disconnected);
    // 不但要有可调用对象Disconnected，还要有可调用对象的类型！！

}

