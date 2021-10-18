#include <iostream>
#include <string.h>
#include <vector>
#include <functional>

/*
 * 这是一个简易版本的String。
 * 该string的基本思想为：”reference counting“ 和 "修改时copy“
 * 实现方法为：
 *
 * reference counting
 * 1. 将数据与引用绑定作为内嵌类。 该内嵌类只负责保存，不负责管理
 * 2. string的copy， 赋值， 构造， 析构，移动，都需要维护计数器和data的释放
 *
 * 修改时copy
 * 1. 对非const版本的[]的调用操作的同时，进行copy操作，并维护计数器
 */

class String {
public:
    String(const char *data);
    ~String();

    String (const String &other);
    String &operator= (const String &other);
    const char &operator[] (size_t index) const; // 这个必须加上const，否则和下面的signature是一样的
    char &operator[] (size_t index);

private:
    struct StringValue {
        int refCount;
        char *data;
        StringValue(const char *data);
        ~StringValue();
    };

    StringValue *value;
};

String::StringValue::StringValue(const char *initValue) : refCount(1)
{
    // 开内存，存数据
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}

String::StringValue::~StringValue()
{
    delete [] data; // 这里delete必须要删除数组！！！！
}

// 首次创建，要分配内存
String::String(const char *data) : value(new StringValue(data)) { }

// obj的复制需要更改索引
String::String (const String &other) : value(other.value)
{
    value->refCount++;
}

String& String::operator= (const String &other)
{
    // 自赋值的问题一定要考虑
    if (value == other.value) { // 这里必须是StringValue层面的判等！！！，不是String层面的，你这里解决的内存自赋值的问题，而不是管理类自赋值的问题
//    if(this == &other) { // 这样写也行，但是效率不高，因为不会存在两个string不同，但是value确实相同的（这时候refCount至少为2），且refCount==1的情况
        return *this;
    }
    // 无脑减refcount
    if((--value->refCount) == 0) {
        delete value;
    }
    // 完成指针的转换
    value = other.value;
    value->refCount++;
    return *this;
}

const char &String::operator[] (size_t index) const
{
    return value->data[index];
}

// 我们和编译器均没法区分在调用非const版本的[]的时候是否修改data的内部值，我们需要悲观的认为所有调用非const版本的，都会修改内部数据
char &String::operator[] (size_t index)
{
    // 只有当大于1份的时候，才说明有人share 内存，这时候要新开辟内存，并且对当前引用--
    if (value->refCount > 1) {
        StringValue *newValue = new StringValue(value->data);
        value->refCount--;
        value = newValue;
        std::cout << "copy string" << std::endl;
    }
    return value->data[index];
}

String::~String()
{
    if (--(value->refCount) == 0) {
        delete value;
    }
}


int main() {
    {
        String s0 = "Allen";
        {
            String s1 = s0;
            s1 = s0;
            std::cout << s0[0] << std::endl; // 这里会调用非const版本的，会发生copy
            const char c = s0[0]; // 而这里会调用const版本的，因此不会发送copy
            std::cout << c << std::endl;
        }
    }

}
