#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <string>
class Data1{
public:
    Data1() = default;
    Data1(const Data1 &other) {
        std::cout << "data1 is copyed" << std::endl;
    }
};

class Data2{
public:
    Data2() = default;
    Data2(const Data2& others) {
        std::cout << "Data2 is copyed" << std::endl;
    }
};

template<typename... InputArgs> class Interface {

};

template<typename ...InputArgs>
class Counter : public Interface<InputArgs...> {
    virtual void UpdataCounter(InputArgs... data) = 0;
};

class MyCounter1 : public Counter<Data1&> {
public:
    void UpdataCounter(Data1& data) override {
        std::cout << "this is data1 counter" << std::endl;
    }
};

class MyCounter2 : public Counter<Data2&> {
public:
    void UpdataCounter(Data2& data) override {
        std::cout << "this is data2 counter" << std::endl;
    }
};

class MyCounter3 : public Counter<Data1&, Data2&> {
public:
    void UpdataCounter(Data1& data1, Data2& data) override {
        std::cout << "this is data1 and data2 counter" << std::endl;
    }
};
template<typename CounterType, typename ...InputArgs>
void Print(CounterType &counter, InputArgs&&... datas) {
    counter.UpdataCounter(std::forward<InputArgs>(datas)...);
}
int main() {
    MyCounter3 myCounter3;
    MyCounter1 myCounter1;
    MyCounter2 myCounter2;
    Data1 data;
    Data2 data2;
    Print(myCounter3, data, data2);
    Print(myCounter1, data);
    Print(myCounter2, data2);
}
