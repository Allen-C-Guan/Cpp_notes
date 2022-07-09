#include <iostream>
#include <algorithm>
#include <memory>
class Foo {
public:
    Foo () {}
    void Print() {
        std::cout << val << std::endl;
    }
    int val;
};

template<typename ValueType>
ValueType &GetUnexpectedObj() {
    // 这里一个assert
    static ValueType value;
    return value;
}

// 抽象的iterator
template<typename ValueType, uint32_t ArraySize>
class Iterator {
public:
    virtual void begin() = 0;
    virtual bool isOutOfRange() = 0;
    virtual void next() = 0;
    virtual ValueType &CurrentItem() = 0;
    virtual bool isLegalValue() {
        return true;
    }
protected:
    Iterator() {}
};

template <typename ValueType, uint32_t ArraySize> class ForwardListIterator;
template <typename ValueType, uint32_t ArraySize> class BackwardListIterator;

// 具体的List类
template <typename ValueType, uint32_t ArraySize>
class List {
public:
    friend ForwardListIterator<ValueType, ArraySize>;
    ForwardListIterator<ValueType, ArraySize> CreateIterator()  {
        return ForwardListIterator<ValueType, ArraySize>(*this);
    }
    FilterListIterator<ValueType, ArraySize> CreateFilterIterator()  {
        return FilterListIterator<ValueType, ArraySize>(*this);
    }
    BackwardListIterator<ValueType, ArraySize> CreateBackwardListIterator()  {
        return BackwardListIterator<ValueType, ArraySize>(*this);
    }

    ValueType& operator[](uint32_t i) {
        if (i > ArraySize) {
            return GetUnexpectedObj<ValueType>();
        }
        return list_[i];
    }
private:
    ValueType list_[ArraySize];
};

// 正向迭代器
template <typename ValueType, uint32_t ArraySize>
class ForwardListIterator : public Iterator<ValueType, ArraySize>{
public:
    ForwardListIterator(List<ValueType, ArraySize> &aList) : list_(aList){}
    void begin() override {
        cursor_ = 0;
    }
    bool isOutOfRange() override {
        return cursor_ >= ArraySize;
    }
    void next() override {
        cursor_++;
    }
    ValueType& CurrentItem() override {
        return list_[cursor_];
    }
protected:
    List<ValueType, ArraySize> &list_;
    uint32_t cursor_;
};

// 反向迭代器
template <typename ValueType, uint32_t ArraySize>
class BackwardListIterator : public Iterator<ValueType, ArraySize>{
public:
    BackwardListIterator(List<ValueType, ArraySize> &aList) : list_(aList){}
    void begin() override {
        cursor_ = ArraySize - 1;
    }
    bool isOutOfRange() override {
        return cursor_ < 0;
    }
    void next() override {
        cursor_--;
    }
    ValueType& CurrentItem() override {
        return list_[cursor_];
    }
protected:
    List<ValueType, ArraySize> &list_;
    int cursor_;
};

class FooFilter {
public:
    FooFilter () = default;
    virtual bool operator () (Foo &f) {return true;};
};
class EvenFilter : public FooFilter
{
public:
    EvenFilter() = default;
    bool operator () (Foo &f) override {
        return (f.val % 2 == 0);
    }
};

constexpr uint32_t arraySize = 5;
void PrintList(Iterator<Foo, arraySize> &iterator, FooFilter &filter) {
    for (iterator.begin(); !iterator.isOutOfRange(); iterator.next()) {
        if (filter(iterator.CurrentItem())) {
            iterator.CurrentItem().Print();
        }
    }
}
int main ()
{
    // list初始化
    List<Foo,arraySize> fList;
    fList[0].val = 0; fList[1].val = 1; fList[2].val = 2; fList[3].val = 3; fList[4].val = 4;

    // 迭代器初始
    auto forwardIterator = fList.CreateIterator();
    auto backwardIterator = fList.CreateBackwardListIterator();
    // 过滤器初始
    FooFilter defaultFilter = FooFilter();
    EvenFilter evenFilter = EvenFilter();

    // 正向打印
    PrintList(forwardIterator, defaultFilter);
    std::cout << "_______________" << std::endl;
    // 反向打印
    PrintList(backwardIterator, defaultFilter);
    std::cout << "_______________" << std::endl;
    // 正向只过滤偶数打印
    PrintList(forwardIterator, evenFilter);
    std::cout << "_______________" << std::endl;
    // 反向只过滤偶数打印
    PrintList(backwardIterator, evenFilter);
}
