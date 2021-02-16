//
// Created by Allen on 31/1/21.
//

#ifndef EFFECTIVE_CPP_NON_MEMBER_FUNC_AND_NAMESPACE_H
#define EFFECTIVE_CPP_NON_MEMBER_FUNC_AND_NAMESPACE_H
using namespace std;
/*         **********  non-member func 替代 member func 并用namespace来增加顶层封装
 *
 * 用 non-member function 来代替 member function 来减少访问private变量的函数。从而增加private variable的封装性。
 * 但缺少的整体性，（因为non-member function和class不在一起啊)，可以用namespace来弥补上。
 * 这样做还有个好处在于扩展性和拆分性，在namespace里面可以随便加各种过程函数，这样过程函数也被封装了起来，而且不需要考虑class内部的事情
 * 换句话说，namespace的扩展性和弹性远大于class
 * 同时这样还可以分开声明，这是class无法做到的！！！！避免不必要的声明！！！
 * 适用范围： 适用一个类和对这个类的功能函数的封装。！！
 */
namespace Print {  // 我们用namespace封装
    class Text{
    public:
        Text(){};
        ~Text(){};
        void PrintText() {
            cout << m_text << endl;
        }
        void PrintSize() {
            cout << m_size << endl;
        }

    private:
        string m_text = "Allen";
        int m_size = m_text.size();
    };
}

namespace Print {  // 用相同的name space 来封装 non-member function 可以做到封装的一体性。
    void PrintTextAndSize (Text &t) {
        t.PrintSize();
        t.PrintText();
    }
}


int test() {
    Print::Text t = Print::Text();
    Print::PrintTextAndSize(t); // 虽然是过程函数，但通过namespace的封装，让class和操纵class的过程函数封装在了一起。

    t.PrintText();
    t.PrintSize();

}
#endif //EFFECTIVE_CPP_NON_MEMBER_FUNC_AND_NAMESPACE_H
