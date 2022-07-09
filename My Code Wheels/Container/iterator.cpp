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
template <typename ValueType, uint32_t ArraySize> class FilterListIterator;
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

// 正向，带有筛选功能的迭代器
template <typename ValueType, uint32_t ArraySize>
class FilterListIterator : public ForwardListIterator<ValueType, ArraySize> {
public:
    FilterListIterator(List<ValueType, ArraySize> &aList) : ForwardListIterator<ValueType, ArraySize>(aList){}
    bool isLegalValue() override {
        uint32_t &currentCursor = ForwardListIterator<ValueType, ArraySize>::cursor_;
        if(ForwardListIterator<ValueType, ArraySize>::list_[currentCursor].val == 2) {
            return true;
        } else {
            return false;
        }
    }
};
constexpr uint32_t arraySize = 5;
void PrintList(Iterator<Foo, arraySize> &iterator) {
    for (iterator.begin(); !iterator.isOutOfRange(); iterator.next()) {
        if (iterator.isLegalValue()) {
            iterator.CurrentItem().Print();
        }
    }
}
int main ()
{
    List<Foo,arraySize> fList;
    fList[0].val = 0; fList[1].val = 1; fList[2].val = 2; fList[3].val = 3; fList[4].val = 4;

    // 正向打印
    auto forwardIterator = fList.CreateIterator();
    PrintList(forwardIterator);
    std::cout << "_______________" << std::endl;

    // 反向打印
    auto backwardIterator = fList.CreateBackwardListIterator();
    PrintList(backwardIterator);
    std::cout << "_______________" << std::endl;

    // filter迭代器
    auto filterIterator = fList.CreateFilterIterator();
    PrintList(filterIterator);
}
