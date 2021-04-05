#include <memory>
#include <iostream>
#include <string>

class StrVec{
public:
    StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
    StrVec(std::initializer_list<std::string> &);
    ~StrVec() {
        free();
    };
    StrVec(const StrVec&);
    StrVec& operator= (const StrVec&);
    StrVec(StrVec &&) noexcept;
    StrVec& operator=(StrVec &&) noexcept;

    // 两个版本的push_back
    void push_back(const std::string&);
    void push_back(std::string &&s);

    size_t size() const{
        return first_free - elements;
    }
    size_t capacity() const{
        return cap - elements;
    }
    std::string *begin() const{
        return elements;
    }
    std::string *end() const{
        return first_free;
    }
private:

    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void chk_n_alloc(){ // 检查内存是否够了，如果不够的话，要自动分配新内存
        if(cap == first_free) {
            reallocate();
        }
    };
    void free();
    void reallocate();
private:
    // why alloc should be static
    static std::allocator<std::string> alloc; // 隐式初始化
    std::string *elements;
    std::string *first_free;
    std::string *cap; // 开辟的内存的尾*后*指针
};


// 接收初始化列表的构造函数
StrVec::StrVec(std::initializer_list<std::string> &l) {
    auto newData = alloc_n_copy(l.begin(), l.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();
    alloc.construct(first_free++, s); // 因为获得是原始内存，因此用之前必须先构造， 这里因为s是左值，constructor调用string的左值构造。
}
// move 版本的pushback
void StrVec::push_back(std::string &&s) {
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s)); // constructor函数会调用string的move版本的构造器来构造！
}



// 重点函数！ 开辟新内存，并把旧的东西copy（构造）到原始内存中。可以给copy来用
std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* oldBegin, const std::string* oldEnd){
    auto newPos = alloc.allocate(oldEnd - oldBegin);
    // 这里要使用memory中函数，将通过头指针和尾指针选择的连续的内存中，直接成片的构造在有allocator分配的未构造的内存上。返回尾*后*指针
    return {newPos, std::uninitialized_copy(oldBegin, oldEnd, newPos)};
}

// 逆向destory已经构造的内容，然后释放内存，注意释放内存前要判被释放的指针是否为空
void StrVec::free() {
    if (elements) { // deallocate的起始地址不能是nullptr！！！
        // destory要一个一个destory，不能批量destory!
        for(auto p = first_free; p != elements;) {
            alloc.destroy(--p); // 这里会调用string的析构函数，string的析构函数会释放自己分配的内存
        }
        alloc.deallocate(elements, cap - elements);
    }
}

// copy 函数只拷贝了被构造部分的内容，因此capacity应该是恰好装下。
StrVec::StrVec(const StrVec &other) {
    auto newStrVec = alloc_n_copy(other.begin(), other.end());
    elements = newStrVec.first;
    first_free = cap = newStrVec.second;
}

StrVec& StrVec::operator=(const StrVec &other) {
    // 处理自我赋值问题，入参先copy成局部变量，然后在自毁
    auto newStrVec = alloc_n_copy(other.begin(), other.end());
    free();
    elements = newStrVec.first;
    first_free = cap = newStrVec.second;
    return *this; // operator= 的return *this; 别总忘了
}

void StrVec::reallocate() {
    size_t newCapacity = size() ? size() * 2 : 1; // 注意当内存是0的时候
    auto newElements = alloc.allocate(newCapacity); // 新开辟一个2倍的内存
//    auto dest = newElements;
//    auto elem = elements;
//    逐个调用string的move函数来构造，而不是copy，uninitialized_copy调用的copy而不是move
//    for(size_t i = 0; i < size(); i++) {
//        alloc.construct(dest++, std::move(*elem));
//    }
    // *********  make_move_iterator **************
    // 如上所说 uninitialized_copy是通过copy完成的constructor的，但我们有函数 make_move_iterator 让其变成"uninitialized_move"
    // make_move_iterator可以把普通迭代器，变成move迭代器，该迭代器返回右值引用！
    // 因此这里实际上调用的是string的move函数来完成逐一copy的！！ 如下一行，就等于上面的for循环！！
    auto dest = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newElements);

    free();
    elements = newElements;
    first_free = dest;
    cap = newElements + newCapacity;
}


/*
 * *******************  move构造函数  **********************
 * 1. 入参必须是右值引用
 * 2. 接管内存。
 * 3. 保证move from 对象的析构安全性，将Move from 对象的指针置成空，否则会导致在other被析构的时候，把新内存释放掉了。
 *
 * 这是因为move的本质是接管内存，并不分配新的内存，既然内存是被接管过来的。就需要考虑将move from 的对象
 * 在析构的时候不要让其释放刚被接管过来的内存。
 */
StrVec::StrVec(StrVec &&other) noexcept
        : elements(other.elements), first_free(other.first_free), cap(other.cap){
    other.elements = other.first_free = other.cap = nullptr;
}

/*
 * *******************  移动赋值运算符  ******************
 * move的赋值也要考虑自我移动问题。
 * 常理来讲，既然用到移动，rhs一定是个右值啊，右值一定是没人用才对，为啥自己会用自己呢？
 * 但一种情况可能触发自己移动自己，既如果这个入参是move的return值。
 * f = std::move(f); // 这也是可能的！
 */
StrVec& StrVec::operator= (StrVec &&rhs) noexcept {
    if(&rhs != this) { // 避免自我移动
        free(); // operator= 需要释放内存！ 赋值意味着自己已经有了内存！复制构造被调用的时候，还没有属于自己的内存！
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.first_free = rhs.cap = rhs.elements = nullptr;
    }
}


/*
 * ***************** noexcept ********************
 * noexcept是在告诉标准库，当前函数一定不会抛出异常(一定是安全的)。为什么需要这么做？
 * 首先明确一点move与copy不同的地方既：
 * move对于容器而言是有风险的，而copy是没有风险的。
 *
 * 原因：move是会改变旧内存的！！
 * 试想如下情景，当vector调用move构造函数的时候，移动到一半的时候（还没有全部从旧内存中移动到新内存中），如果抛出了异常，这时候
 * 旧内存只剩下一半，另一半被移动到了新内存中，此时不管是新内存还是旧内存都没法用！！
 *
 * 但是copy不一样啊，旧内存没动啊！新分配的内存直接扔了（free掉）就行了。
 *
 * 因此，如果你没有标记你的move构造函数是noexcept， STL为了安全，只会调用copy，而不会去使用你的move函数！
 *
 */

std::allocator<std::string> StrVec::alloc;
int main ()
{
    std::initializer_list<std::string> input = {"allen", "ceclia"};
    StrVec s(input);
    std::string ss("kaka");
    s.push_back(ss); // 调用的左值引用版本
    auto size = s.size();
    auto cap = s.capacity();
    s.push_back("c"); // 这里调用的右值引用版本
    size = s.size();
    cap = s.capacity();
    s.push_back("d");
    size = s.size();
    cap = s.capacity();
    s.push_back("f");
    size = s.size();
    cap = s.capacity();
    s.push_back("w");
    size = s.size();
    cap = s.capacity();
}