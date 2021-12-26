//
// Created by Allen on 26/12/21.
//

#ifndef SUMMARY_THE_RULES_OF_THREE_H
#define SUMMARY_THE_RULES_OF_THREE_H
#include <string>
#include <iostream>
/*
 *                          行为像指针的类（智能指针）
 * 因为希望类的行为像指针，即多个类共享同一片内存空间，复制的只是指针，而不是内存，因此内存释放因为内存的共享而变得复杂。
 * 为了能正确的释放内存，我们采用内存引用计数的方式，当指针引用个数为0的时候，释放内存。
 *
 * 因此，我们需要作出如下设计
 * 1。所有的constructor（除了copy），初始化计数器
 * 2。拷贝构造函数：递增计数器
 * 3。析构函数：递减计数器
 * 4。赋值函数：递增右边，递减左边。
 * 5。赋值和析构函数函数中，检查是否计数为0，释放内存。
 *
 * 重点：
 * use记录的是内容（成员变量，也是heap上内存）被引用的次数，而不是实例被引用的次数。因此只要内容（heap上的内存）没有人继续使用了，
 * 就要被释放，而这里释放的也是heap上的内存（内容）而不是实例本身。实例本身还是存在的，只是内容换了一套而已。
 *
 * 这也就解释了为何 赋值也要减少右边的计数器，并且当计数器为0的时候，就要释放。即使该实例的声明周期还存在！因为释放的不是实例
 * 而是实例里的内容，内容已经没人用了。
 *
 * 因此内容被释放的流程有两种，
 * 1。内容是在赋值的时候被释放的
 * 2。内容在实例被销毁的时候被释放的。
 *
 */

namespace the_rules_of_three{
    using namespace std;
    class StudentPtr {
    public:
        // 构造函数中有new，这意味着，我们需要一个析构函数来实现delete，而如果我们需要一个析构函数，意味着我们可能还需要
        // 赋值和拷贝！，因此我们需要设计一下我们的析构，赋值和拷贝
        StudentPtr(string name, int age) : m_name(new string(name)), m_age(age), useCntr(new size_t(1)) {
            std::cout << *m_name << " has been constructed" << std::endl;
        }

        StudentPtr(const StudentPtr &other) : m_name(other.m_name), m_age(other.m_age), useCntr(other.useCntr) {
            ++(*useCntr);
            std::cout << *m_name << " has been copy constructed" << std::endl;
        }

        StudentPtr &operator=(const StudentPtr &rhs) {
            ++(*rhs.useCntr);  // 处理自赋值问题，我们先增加右边的，
            if (--(*useCntr) == 0) { // 即使自我赋值，也不会减到0，而是减回原来的值；
                std::cout << *m_name <<  " has been deleted by assignment" << endl;
                delete useCntr;
                delete m_name;  // delete的是heap上的内存，而不是变量本身，变量本身还是存在的，只是变量内容变了
            }
            m_name = rhs.m_name;
            m_age = rhs.m_age;
            useCntr = rhs.useCntr;
            return *this;
        }

        ~StudentPtr() {
            if (--(*useCntr) == 0) {
                std::cout << *m_name <<  " has been deleted by destructor" << endl;
                delete useCntr;
                delete m_name;
            }
        }

    private:
        string *m_name;
        int m_age;
        size_t *useCntr;
    };

}


void TestTheRulesOfThree() {
    using namespace the_rules_of_three;
    StudentPtr cecilia("cecilia", 8);
    {
        {
            StudentPtr allen("allen", 28);
            StudentPtr bob("Bob", 2);
            cecilia = allen; // 这时候，celica的内容就要被allen的内容替换掉，其原来申请的存放cecilia的内存将没有人在使用，因此需要别释放掉
            cecilia = bob; // 这时候，celica的实际内容变成allen后，又要被bob覆盖掉，其原来存放allen内存将没有人在使用，因此需要别释放掉
        }
    }
}

#endif //SUMMARY_THE_RULES_OF_THREE_H
