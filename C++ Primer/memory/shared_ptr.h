#include <sstream>
#include <map>
#include <sstream>
#include <stack>
#include <numeric>
#include <algorithm>
#include <set>
#include <iostream>
#include <vector>
#include <memory>
/* ******************************  heap内存的使用原则 ******************************
 * 变量存放的位置可以分成三种
 * 1。stack上：局部变量，块中被初始化，块结束的时候被自动销毁
 * 2。静态内存中：global 和 static变量。程序开始的时候被初始化或者分配内存，程序结束的时候自动被销毁
 * 3。动态内存中：在heap中，需要手动显示初始化，并手动显示的删除，和声明周期与作用域无关。
 *
 * 使用动态内存的原因：
 * 使用动态内存的原因必须为一下三种之一，否则请不要用动态内存
 * 1。程序不知道自己需要使用多少对象。需要动态分配内存，vector
 * 2。程序不知道所需对象的准确类型
 * 3。程序需要在多个对象间共享数据（内存）
 *
 * 我们要知道，动态内存和stack最大的区别在于两点，
 * 1。动态！可以随时分配和扩大内存空间
 * 2。资源的有效期，资源有效期由程序员来管理，与对象的声明周期无关！
 *
 * tips:
 * 这里我们需要分开看对象和资源！对象拥有或者使用了资源，但并不意味着对象和资源是永远绑定，同生共死的。
 * 对于stack上而言，对象被销毁，资源也被销毁，但对于heap上而言，对象被销毁，但资源并不一定被销毁。
 *
 * 当我们需要多个对象之间共享底层数据的时候，就不允许某一个对象被销毁，底层数据就被释放，因为底层数据还被其他
 * 对象所引用并使用着。
 *
 * heap内存带来的麻烦直接根因可以归结为如下几点：
 * 1. 对象生存周期（或指针生存周期）与内存生存周期的不一致性。
 *      a) 对象销毁了（指针被销毁了）但是内存依然存在，没被释放。内存泄露（内存用于得不到释放）
 *      b) 内存被销毁了，但是对象（指针）依然存在，指针悬空（指针指向一个已经还给系统的自由内存）
 * 2. 对象与内存之间可以是多对一的关系，不知道哪个对象是最后使用该内存的。
 * 3. heap的内存是匿名的，new返回的指针是唯一可以找到和释放该内存的方法！！！
 *
 * ********************************  shared_ptr  ****************************************
 * shared_ptr是通过内存引用计数的方式来管理内存的。make_shared的时候分配内存，引用计数为0的时候自动释放内存
 * share_ptr 必须显示初始化，因为是explicit的.
 *
 * shared_ptr的计数器
 * 计数器的增加：拷贝，初始化，入参，return
 * 计数的减少：被赋新值，被销毁。
 *
 * shared_ptr的作用：
 * 我们可以在大部分情况下，用shared_ptr来代替row ptr管理ptr，包括ptr类型的成员变量。
 * 其最大的好处在于，我们不用再考虑该类的copy，赋值和销毁的时候，如何释放内存的问题。
 * shared_ptr**依赖**默认**的拷贝，赋值和析构函数**！！就能正确的对heap上的内存进行管理和释放。
 *
 * 具体使用方法：
 * 我们需要在构造函数中，分配一块内存，并用make_shared返回一个shared_ptr，存在obj中即可
 *
 * 既：
 * shared_ptr<T> p(new int(4)); // OKK
 * shared_ptr<T> p = new int(4); // 这个可不行！！这使用的隐式转换
 *
 * return shared_ptr<T> p;
 * return new int(); // 这也是隐式转换；
 *
 *
 * std::shared_ptr<T> pObj = std::make_shared<T>(constructor的入参);
 * std::shared_ptr<T> pObj(row_q); // q是内置指针
 * std::shared_ptr<T> pObj(unique_ptr); // 接管unique_ptr， unique_ptr内置空
 * std::shared_ptr<T> pObj(row_q, Deleter); // 我们可以指定Deleter的行为
 *
 * p.reset(); // 如果p是最后一个对该内存的引用，则释放内存
 * p.reset(q); // 会将p的原来的计数器减1， 然后指向q
 * p.reset(q, Deleter); // 还指定了deleter的操作
 *
 * shared_ptr的异常处理
 * shared_ptr因为是利用默认的析构函数就可以完成内存释放，而c++中异常处理，一定会执行析构函数的，因此shared_ptr会保证异常处理中，内存
 * 的正常释放。
 *
 *
 * ******************* make_shared ****************
 * make_shared<T>(constructor入参);
 * make_shared<T>();如果没参数，则是类T的值初始化，如果有参数，则会调用T的对应构造函数。
 *
 * 作用：
 * 分配动态内存，返回指针，指向此对象的shared_ptr
 * 因此make_shared可保证**总是开辟一个新的内存**，返回一个新的指针。
 *
 * 优点：
 * 直接调用shared_ptr的构造函数却不能保证。总会开辟一块新内存。这就有一个内存绑定两个计数器的风险。
 *
 * ******************************  new ******************************
 * new：会返回一个ptr，该ptr指向分配的内存地址，这个ptr是唯一一种可以接触到内存的方法！！
 *
 * new的初始化：
 * 1。 new会在heap上分配一块内存，但该内存是无名的，因此new只会返回ptr，因此我们只能操作ptr来对heap上的内存
 * 进行操控
 * 2。 new在默认情况下是默认初始化，这就意味着内置类型和组合类型有可能未被初始化
 *      ie。int *p = new int; //(*p)的值未定义
 * 3。 new也可以调用构造函数，包括默认构造函数和自定义构造函数来初始化
 *      ie。int *p = new int(); // 默认构造函数
 *          int *pf = new Foo("allen", 10); // 自定义构造函数。
 * 4。 列表初始化
 *      ie. vector<int> *pv = new vector<int>{1,2,3,4};
 *
 *
 *
 * ***************************  delete  *******************************
 * delete也会执行两个步骤，销毁对象（析构函数），释放内存
 *
 * 使用delete需要注意如下几点
 * 1. delete局部变量和delete已经被释放的内存的行为是未定义的。
 *  ps. 未定义的行为通常是因为编译器无法识别区别，这里编译器无法识别ptr是不是指向局部变量，也无法识别该是否已经还给系统了。
 * 2. delete以后要把ptr置成nullptr，不要让指针悬空（但对于copy而来的其他ptr也是没用的）
 *
 *
 *
 * ********************* 使用注意事项 ******************************
 * 使用智能指针的原则是： 我们要让唯一一个计数器对应一块内存
 * 更具体一点：
 * 1. 如果内存让shared_ptr托管了，就不要在使用原始指针了。
 * 2. 不能让两个独立的share_ptr绑定一块内存上（这等于两个计时器计数一块内存）
 *      只有使用了shared_ptr的copy构造函数来复制的才可以共用计数器，用shared_ptr<T> p(row_ptr);出来的不是一个计数器的
 *
 *
 * ******************** 自定义deleter ************************
 * 自定义deleter的目的是为了*代替*delete操作。
 * 这个代替要注意了，这意味着destructor在计数器为0的时候，可能不会被执行了
 * 如果你给smart_ptr一个动态内存，则该ptr的类不会执行destructor！！
 * 但如果你给了smart_ptr一个局部变量指针，则该ptr的类会执行destructor！
 *
 * 道理很简单：
 * 你用deleter来代替了delete，因此此动态内存压根就不可能被自动释放掉了，因为计数为1的时候，执行的是deleter
 * 而不是delete来释放内存。
 *
 * 但如果你用的是局部指针，计数为0的时候，会执行deleter，当对象被销毁的时候，会执行destructor
 *
 */


/*
 * 例子：
 * 构建一个共享vector<string>的类！
 */

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    ~StrBlob() = default;
    bool Empty(){return data->empty();}
    void push_back(std::string s){ data->push_back(s);}
    size_type size(){ return data->size(); }
    void pop_back();

private:
    // 由于该ptr用shared_ptr来管理，因此我们不用考虑该ptr的拷贝，析构和赋值。
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string msg);
};

// 在构造函数中，要对shared_ptr成员变量用make_shared进行初始化，该过程包括在heap上开辟内存，并进行值初始化。
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}

void StrBlob::check(StrBlob::size_type i, const std::string msg) {
    if(i >= data->size()) {
        throw std::out_of_range(msg);
    }
}
void StrBlob::pop_back() {
    check(0, "front on empty StrBlob");
    data->pop_back();
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
    // 一块内存绑两个内存的例子
    int *pInt = new int(6);
    std::shared_ptr<int> p2(pInt); // 用pInt来，初始一个shared_ptr，p2计数器是1
//    {
//        std::shared_ptr<int> p1(pInt);
//        std::cout << "delete p1" << std::endl;  // 又用pInt来初始化一个shared_ptr 此时一块内存已经绑定了两个独立的ptr，有了两个计数器
//                                                // P1的计数器也是1
//    } // p1的计数器减1，清零了，因此释放了内存，但实际上p2还在继续使用！！

    {
        std::shared_ptr<int> p3 = std::make_shared<int>(8);
    }

    // 自定义Deleter 对动态内存的运用
    {
        Connect *pc = new Connect();
        std::shared_ptr<Connect> pConnect(pc, Disconnected);
    } // 计数器为0，执行deleter，并不执行delete操作，因此内存并不会被释放，destructor也不会被执行！


    // 自定义deleter局部变量的运用
    {
        Connect c = Connect(); // 局部变量
        Connect *cp = &c;
        std::shared_ptr<Connect> pConnect(cp, Disconnected); // 局部变量给smart_ptr托管
    }   // 计数器为0 执行deleter
    // 局部对象被销毁，执行destructor
    std::cout << "end" << std::endl;


}
