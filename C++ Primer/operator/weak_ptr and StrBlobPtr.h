#include <iostream>
#include <memory>
#include <vector>

/*
 * *********************  weak_ptr  *********************************
 * weak_ptr的功能是：不控制所指向对象的生存周期的智能指针，且必须要指向shared_ptr
 *
 * weak_ptr的用法：
 * weak_ptr<T> w; // 空
 * weak_ptr<T> w(sp); // 用shared_ptr来初始化一个weak_ptr。其中T必须是能转换为sp所指向的内容
 * w = p; // p既可以是shared_ptr 也可以是 weak_ptr, 共享底层内存
 * w.reset(); // 将w置空
 * w.use_count(); // 与w共享对象的shared_ptr的个数
 * w.expired(); // 表示底层内存是否被销毁（过期），若w.use_count()为0，则返回true。否则是false；
 * w.lock(); // 若底层内存没被销毁，则返回shared_ptr, 否则返回空的shared_ptr
 *
 * 用法注意：
 * 1. 不能直接使用weak_ptr来访问内容
 * 通过用法与功能我们可以发现，weak_ptr并不像shared_ptr一样，只要使用得当，底层内存总是会存在的。
 * 因此我们必须利用weak_ptr的lock()成员函数来获取share_ptr, 然后利用shared_ptr来访问内存。
 *
 *
 */




class StrBlob {
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string>);
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

StrBlob::StrBlob(std::initializer_list<std::string> ilist)
        :data(std::make_shared<std::vector<std::string>>(ilist)){}

void StrBlob::check(StrBlob::size_type i, const std::string msg) {
    if(i >= data->size()) {
        throw std::out_of_range(msg);
    }
}
void StrBlob::pop_back() {
    check(0, "front on empty StrBlob");
    data->pop_back();
}


/* 实现一个简单的迭代器类
 * 1. 迭代器类要可以访问容器中的内容，支持++，--，解引用，检查所指内容是否有效等功能
 * 2. 在不使用的时候，不要改变源内容的计数器
 *      我们迭代器不能在没有使用原内容的时候，不能增加原内容的计数器，因此要借助weak_ptr来访问源数据！如果还可访问，
 *      则用share_ptr来进行访问，如果不存在了，不要用share_ptr来访问，否则会增加计数器。
 * 3. 迭代器只需要保存源数据的数据成员变量的指针和当前坐标位置即可！其他的不要实现，也不需要包括。
 *      这样解引用的时候，就可以直接通过数据成员变量的指针 + 现在的偏移，获得数据。
 *
 * 用weak_ptr来实现一个可以访问strBlob的ptr。
 * 要求：我们的目的在于访问，因此不能影响strBlob的声明周期，如果被销毁了，就不要访问，如果没销毁，则需要返回内容！
 * 因此我们就要用weak_ptr来实现这个目的
 */

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){  };
    StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz){  };
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    // 迭代器中，解引用与箭头，返回的是所存储的数据成员指针对应的数据的当前位置元素！return的type不是this的type。
    std::string& operator* () const;
    std::string* operator-> () const;
private:
    std::size_t curr;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::shared_ptr<std::vector<std::string>> check(std::size_t i) const;
};

/*
 * 使用lock()的基本流程
 * 1. 检查是否为空
 * 2. 是否合法
 * 3. 返回shared_ptr;
 */
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i) const
{
    std::shared_ptr<std::vector<std::string>> ret = wptr.lock(); // 我们只能通过lock回来的shared_ptr来接触底层内存，否则有风险
    if (!ret) { // 如果return的shared_ptr是空，则说明已经被释放了，就不能用了！
        throw std::runtime_error("destroyed");
    }
    if(i >= ret->size()) {
        throw std::out_of_range("unbound strBlobPtr");
    }
    return ret;
}
/*
 * 前置后置运算符的使用原则：
 * 1. 检查是否越界，--检查在前，++检查在后
 * 2. 前置要返回reference，后置要值传递返回。且后置要把更改前的状态存储在局部变量中。
 * 3. 前置入参是空，后置入参是int，但我们不要用int
 * 4. 我们只要定义4个中的一个，就要全定义四个，且后置要通过调用前置来完成
 *
 * 前置返回的是++或者--之后的内容，后置返回的是操作之前的内容
 * 前置和后置在语法上的区分是通过入参是空还是int来区分的，由于前置后置都叫operator++，那么怎么区分呢？就用入参来区分
 * 而入参的int除了用来区分前置和后置之外没有任何作用！！
 * 后置因为返回的是操作之前的内容，因此不可能返回reference！因为this已经被更改！
 */


StrBlobPtr& StrBlobPtr::operator++() {
    check(curr);
    ++curr; // ++的check要放在后面，这return this的结果最坏也是end！
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
    --curr; // -- 的check要放在后面，保证有效性
    check(curr);
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;
    ++(*this);
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this; // 先把更改前的内容存放局部变量中！
    --(*this); // 调用前置来完成
    return ret; // return更改前的内容！
}


std::string& StrBlobPtr::operator*() const{ // 必须返回reference
    auto p = check(curr); //
    return (*p)[curr];
}

std::string* StrBlobPtr::operator-> () const{ // 必须返回pointer，而不是reference
    return &(this->operator*());
}

int main ()
{
    StrBlob s = {"allen", "cecilia"};
    StrBlobPtr p(s);
    std::string::iterator a = p.operator->()->end();
}