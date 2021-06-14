//
// Created by Allen on 2021/6/14.
//

#ifndef MORE_EFFECTIVE_C___INIT_ARR_WITHOUT_DEFAULT_CONSTRUCTOR_H
#define MORE_EFFECTIVE_C___INIT_ARR_WITHOUT_DEFAULT_CONSTRUCTOR_H
#include <iostream>
#include <string>
/*
 * ********************  初始化没有默认构造函数的类的数组 ********************
 * 对于有些类而言，我们不希望其拥有默认构造函数，比如一个类，用来抽象真实人的身份信息，如果没有名字，没有身份证号，那这个对象就毫无意义，
 * 那这个时候，我们就不给其提供默认构造函数。
 * 但没有默认构造函数的类，在初始化array的时候显得格外的费劲！
 *
 *
 */

class People {
public:
    People() = delete;
    People(std::string name): name_(name) {}
    std::string name_;
};

int main() {
    // 方法1：使用non-heap内存 + 初始化列表来初始化
    // non-heap上的内存是可以用初始化列表来初始化array的，同时给每个元素提供初值
    People pArr[3] = {{"allen"}, {"h"}, {"dd"}};


    // 方法2：使用ptr array + 显示初始化， 缺点： 需要手动释放数组中的所有成员
    People **ppArr = new People* [4]; // ppArr有二级指针，说明ppArr寻址再寻址之后，得到的是People obj类型
    //  第一层寻址是因为ppArr是个array，第二次寻址是因为ppArr里放的是pointer而不是obj
    for (int i = 0; i < 4; i++) {
        ppArr[i] = new People("allen"); // []索引本身就包含一次解引用！！所以索引之后的结果就是元素，也就是pointer
    }

    for (int i = 0; i < 4; i++) {
        delete ppArr[i]; // 方法二必须手动释放对象，而不能通过删除array的方式来批量删除对象们
    }


    // 方法2换种写法, 更好理解：
    typedef People* PPeople;
    PPeople *ppArr2 = new PPeople[4];
    for(int i = 0; i < 4; i++) {
        ppArr2[i] = new People("Allen");
    }


    // 方法3：使用operator new 和 operator delete
    // 缺点：不容易维护，不能自动调用constructor和destructor！

    void *arrPtr = operator new(sizeof(People) * 4); // 分配原始内存
    People *arrPeople = static_cast<People*> (arrPtr); // 原始内存cast成实际的类型
    for (int i = 0; i < 4; i++) {
        new (&arrPeople[i]) People("allen");  // 只能使用placement new来构造
    }

    for(int i = 0; i < 4; i++) {
        arrPeople[i].~People();
    }
    operator delete[] (arrPtr);  // operator new出来的只能用operator delete来删除！

    std::cout << "Ending" << std::endl;
    return 0;
}

#endif //MORE_EFFECTIVE_C___INIT_ARR_WITHOUT_DEFAULT_CONSTRUCTOR_H
