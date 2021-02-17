#include <iostream>

using namespace std;
/*
 *                          行为像指针的类（智能指针）
 * 因为希望类的行为像指针，即多个类共享同一片内存空间，复制的只是指针，而不是内存，因此内存释放因为内存的共享而变得复杂。
 * 为了能正确的释放内存，我们采用指针引用技术的方式，当指针引用个数为0的时候，释放内存。
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
class StudentPtr{
public:
    StudentPtr(string name, int age):m_name(new string(name)), m_age(age), use(new size_t(1)){
    }

    StudentPtr(const StudentPtr &other):m_name(other.m_name), m_age(other.m_age), use(other.use) {
        ++(*use);
    }

    StudentPtr& operator=(const StudentPtr &rhs){
        ++(*rhs.use);  // 处理自赋值问题，我们先增加右边的，
        if(--(*use) == 0) { // 即使自我赋值，也不会减到0，而是减回原来的值；
            delete use;
            delete m_name;  // delete的是heap上的内存，而不是变量本身，变量本身还是存在的，只是变量内容变了
            cout << "deleting from assignment" << endl;
        }
        m_name = rhs.m_name;
        m_age = rhs.m_age;
        use = rhs.use;
        return *this;
    }

    ~StudentPtr(){
        if(--(*use) == 0) {
            delete use;
            delete m_name;
            cout << "deleting from destructor" << endl;
        }
    }
private:
    string *m_name;
    int m_age;
    size_t *use;
};
int main() {
    StudentPtr s0("cecilia", 8);
    {
        {
            StudentPtr s1("allen", 28);
            StudentPtr s2("mm", 2);
            s0 = s1;
            s0 = s2;
        }

    }

}