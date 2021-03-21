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


/*
 * 用weak_ptr来实现一个可以访问strBlob的ptr。
 * 要求：我们的目的在于访问，因此不能影响strBlob的声明周期，如果被销毁了，就不要访问，如果没销毁，则需要返回内容！
 * 因此我们就要用weak_ptr来实现这个目的
 */

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){  };
    StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz){  };
    std::string& deRef() const;
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
        throw std::runtime_error("unbound strBlobPtr");
    }
    if(i >= ret->size()) {
        throw std::out_of_range("");
    }
    return ret;
}


std::string& StrBlobPtr::deRef() const
{
    std::shared_ptr<std::vector<std::string>>ret = check(curr); // 使用之前必须check释放已经被释放
    return (*ret)[curr];
}

int main ()
{

}