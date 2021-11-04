#include <iostream>
#include <string.h>
#include <vector>
#include <functional>
/*
 * 这个类的目的是将计数数据的维护与真正的数据解耦开来，从而实现计数数据的可重用。 这里注意RCObject一定是要分配在heap上的，否则计数没有任何意义
 * 由于计数器需要提供如下接口：
 * 1. 生成与销毁
 * 2. 引用次数的更新
 * 3. 共享状态可查询
 * 因此需要用继承来保证接口的统一！
 *
 * 纯数据容器类，只提供操作接口，不提供除了自我毁灭以外的控制，控制数据（比如：计数的++和--）由使用者来操作。
 * 但是删除是RCObject说了算的！当RCObject自减到0的时候，就会自我删除，删除的是父类指针，但由于多态，子类也会被删除
 */
class RCObject {
public:
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;

protected:
    RCObject();
    virtual ~RCObject() = 0; // 这个函数必须是纯虚的！！
    RCObject(const RCObject &other);
    RCObject& operator= (const RCObject &other);
private:
    int refCount;
    bool shareable;
};

RCObject::RCObject() : refCount(0), shareable(true) { }
RCObject::~RCObject() {

}

// RCObject 的 copy和赋值比较奇怪！！
// RCObject的copy构造意味着这个RCObject是一个新的，因此就应该无脑初始为0，至于应该是多少，是由初始化RCObject的人来完成的
RCObject::RCObject(const RCObject &other) : refCount(0), shareable(true) { }

// RCObject的赋值也不会造成计数的任何变化！因为你计数的目的是为了记录通过String引用底层的信息Data的个数，那么RC的引用并不会对string的引用造成任何影响
RCObject& RCObject::operator= (const RCObject &other)
{
    return *this;
}


void RCObject::addReference()
{
    refCount++;
}

void RCObject::removeReference()
{
    if(--refCount <= 0) {
        delete this; // 别忘了，真正的数据类是其子类，这里父类delete this，其实就会delete掉子类，这也是为什么其析构函数必须是纯虚的！！强迫子类继承，并支持多态
    }
}

void RCObject::markUnshareable()
{
    shareable = false;
}

bool RCObject::isShareable() const
{
    return shareable;
}

bool RCObject::isShared() const
{
    return refCount > 1;
}


/*
 * 这个接口是为了把计数的琐碎的工作从String里面抽出来。因此该智能指针类型负责管理计数
 *
 * 我们之前是让String持有StringValue的指针，而指针是不可能在析构和构造的时候做事的能力，因此使用对象来持有指针的方式，来管理计数
 * 因为我们的目的只是希望RCPtr可以在String消亡，赋值，copy等时候对计数进行修改，对接口没有约束，因此要采用组合的方式与String来组合！
 */

// 类型T必须是RCObject类型的
template <class T>
class RCPtr {
public:
    RCPtr(T *realPtr);
    ~RCPtr();
    RCPtr(const RCPtr &other);
    RCPtr& operator= (const RCPtr &other);
    void init();
    RCPtr* operator*();
    RCPtr& operator->();
private:
    T *pointee;
};
template<class T>
void RCPtr<T>::init()
{
    if (pointee == nullptr) return;
    pointee->addReference();
}

// 构造函数需要对所持有物初始值进行初始化,并负责维护counter的数
template<class T>
RCPtr<T>::RCPtr(T *realPtr): pointee(realPtr)
{
    init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr<T> &other) : pointee(other.pointee)
{
    init();
}

template<class T>
RCPtr<T>::~RCPtr()
{
    if (pointee == nullptr) return; // 对于nullptr的异常保护要注意！！
    pointee->removeReference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator= (const RCPtr &other)
{
    if (other.pointee != this->pointee) {
        if (pointee != nullptr) {
            this->pointee->removeReference();
        }
        this->pointee = other.pointee;
        init();
    }
    return *this;
}

template<class T>
RCPtr<T>* RCPtr<T>::operator* ()
{
    return this;
}

template<class T>
RCPtr<T>& RCPtr<T>::operator-> ()
{
    return *this;
}


class String {
public:
    String(const char *realData);
    ~String();
private:
    class StringVal : public RCObject {
    public:
        StringVal(const char *data);
        StringVal(const StringVal& other); // copy的时候，自己的指针成员变量的诉求在这里是deep copy！！！
        void init(const char *realData);
        virtual ~StringVal();
    private:
        char *data;
    };

    RCPtr<StringVal> data;
};

void String::StringVal::init(const char *realData)
{
    data = new char[(strlen(realData) + 1)];
    strcpy(data, realData);
}
String::StringVal::StringVal(const char *initValue)
{
    init(initValue);
}

// 含有指针成员变量的copy，通常情况下都需要深度copy！！
String::StringVal::StringVal(const StringVal& other) {
    init(other.data);
}

// 其父类RCObject在refCount到0的时候，会自我毁灭，RCObject会先调用StringVal的析构来自我毁灭，这时候就会销毁data，随后RCObject自我销毁自己维护的内容
String::StringVal::~StringVal()
{
    delete [] data;
}

String::String(const char *realData) : data(new StringVal(realData)) { }

String::~String() {}

int main() {
    {
        String s1("allen");
        {
            String s2 = s1;
        }
        std::cout << "end" << std::endl;
    }
    std::cout << "end" << std::endl;
}
