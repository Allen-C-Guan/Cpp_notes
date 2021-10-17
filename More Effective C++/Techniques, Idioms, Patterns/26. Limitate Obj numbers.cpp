#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

/*
 * Counted作为接口的实现是：利用自身具有自我计数的特性，将自我以private继承的形式组合给其他类，来让其他类来使用其自我计数的特性。
 * 而counted通过继承，成为子类中的一部分，寄生在子类中，通过与子类保持构造和析构的一致，来检测和控制子类的构造和析构，当子类在发生copy，
 * 构造的时候，counted也在自我增加，当超过阈值的时候，通过counted的构造函数产生异常来触发构造失败！
 *
 * 注意：这里，必须要通过抛出异常来阻止构造，这是因为该机制之所以能进行，是通过子类构造函数中调用父类构造函数，而父类构造函数进行计数和检测的方式
 * 来进行的，因此要想在这条逻辑线上中断，只能通过异常的构造，因为构造函数不能提前打断，也不能有返回值返回错误码，因此要想打断，也只能通过抛出异常了！！
 *
 */
template<class BeingCounted>
class Counted {
public:
    static size_t objectCount()
    {
        return objNums;
    }

protected:
    Counted(); // 子类需要使用构造和析构的，所以只能用protected
    ~Counted(); // 这里可以不是虚函数，其实虚析构函数只有在用父类指针释放子类的时候才有用，但是如果是private继承的话，永远不会存在用父类指针来操作子类的情况。TODO
                // 而且counted类中也不存在任何私有成员，也不分配内存。
    Counted(const Counted &other);
private:
    const static size_t maxObjectes;
    static size_t objNums;
    void init(); // 这里必须要使用exception来打断用户实例的创建！！
    bool isTooManyObj();

};

template<class BeingCounted>
Counted<BeingCounted>::Counted()
{
    init();
}

template<class BeingCounted>
Counted<BeingCounted>::~Counted()
{
    objNums++;
}

template <class BeingCounted>
Counted<BeingCounted>::Counted(const Counted &other)
{
    init();
}

template <class BeingCounted>
void Counted <BeingCounted>::init()
{
    if (isTooManyObj()) {
        throw std::exception();
    }
    objNums++;
}

template <class BeingCounted>
bool Counted <BeingCounted>::isTooManyObj()
{
    if (objNums >= maxObjectes) {
        std::cout << "too much objs" << std::endl;
        return true;
    }
    return false;
}

class Printer : private Counted<Printer>
{
public:
    static Printer *MakePrinter();
    static Printer *MakePrinter(const Printer &p);
private:
    Printer() = default;
    Printer(const Printer &other) = default;
    ~Printer() = default;
};

Printer *Printer::MakePrinter()
{
    std::cout << objectCount() << std::endl;
    return new Printer;
}
Printer *Printer::MakePrinter(const Printer &p)
{
    std::cout << objectCount() << std::endl;
    return new Printer(p);
}

template<> const size_t Counted<Printer>::maxObjectes = 2;
template <> size_t Counted<Printer>::objNums = 0;

int main() {
    Printer* p1 = Printer::MakePrinter();
    Printer* p2 = Printer::MakePrinter(*p1);
    Printer* p3 = Printer::MakePrinter();
}
