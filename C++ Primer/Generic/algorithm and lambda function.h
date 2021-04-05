//
// Created by Allen on 2021/3/6.
//

#ifndef C___PRIMER_ALGORITHM_H
#define C___PRIMER_ALGORITHM_H
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

class Foo {
public:
    Foo(int val, std::string s) : val_(val), s_(s){}
    friend bool isShorter(const Foo&, const Foo&);
private:
    int val_;
    std::string s_;
public:
    bool operator< (const Foo &other) const{
        return this->val_ != other.val_? this->val_ < other.val_ : this->s_ < other.s_;
    }

    bool operator== (const Foo &other) const {
        return (this->val_ == other.val_) && (this->s_ == other.s_);
    }
};

bool isShorter(const Foo &lhs, const Foo &rhs) {
    return lhs.s_.size() < rhs.s_.size();
}

bool isShort(const std::string &lhs, const std::string &rhs) {
    return lhs.size() < rhs.size();
}
int main() {
    // sort
    // sort是利用元素operator< 来实现对比的！
    Foo fList[4] = {{3,"A"}, {2, "B"}, {3, "A"}, {4, "w"}};
    std::sort(std::begin(fList), std::end(fList));

    //unique
    // unique 会把*相邻*的重复的地方，用后面不重复的地方给覆盖掉，数组尾部的位置不管！！其内容也是不确定的，
    // 并返回第一个不重复的位置的迭代器
    // unique 的实现是通过 operator== 来实现的！！
    auto end_unique = std::unique(std::begin(fList), std::end(fList));

    //数组去重
    // sort + unique + erase 来实现, 用erase意味着我们不能用原生数组了。
    std::vector<Foo> vf = {{3,"A"}, {2, "B"}, {3, "A"}, {4, "w"}};
    std::sort(vf.begin(), vf.end());
    vf.erase(std::unique(vf.begin(), vf.end()), vf.end());

    /*
    * find_if(it.start(), it.finish(), 谓语); 返回第一个谓语为true的值
    * 但是这个谓语的要求是：只有一个入参！
    */
    std::vector<std::string> s = {"a", "dddfad", "c","dfa"};
    // 我们想找有多少个string长度小于某个word
    std::string word = "df";
    size_t sz = word.size();
    std::sort(s.begin(), s.end(), isShort); // 按从短到长排序
    auto ret = std::find_if(s.begin(), s.end(),[sz](std::string &s){return s.size() > sz;}); // 返回第一个比sz大的it
    auto size = ret - s.begin();

    // find_each(it.start(), it.finish(), 谓语)
    // 接受一对迭代器表示的范围，并对该范围的每个元素执行谓语操作
    std::for_each(ret, s.end(),[](std::string &s){std::cout << s << ", " << std::endl;});

    /*
     *              谓词
     * 谓词是一个return可以作为条件的可被调用的表达式，即return的值可以被当作bool来使用！
     */
    Foo fList2[4] = {{3,"Aahh"}, {2, "Baf"}, {3, "A"}, {4, "whj"}};
    std::sort(std::begin(fList2), std::end(fList2), isShorter);

    // stable_sort
    // sort不一定保证稳定性，但是stable肯定是稳定的
    std::stable_sort(std::begin(fList2), std::end(fList2), isShorter);

    /* ******************   lambda  ****************************
     * lambda函数是一种匿名内联函数，该函数的特殊之处在于，该函数可以定义在其他函数之内。且return只能用后置类型表示。
     * 而在其他函数只能定义带来的好处是可以捕获外层函数的局部变量给内部使用。
     * lambda可以直接使用定义在该函数之外的名字，例如头文件中的std::cout,vector等
     * return 和 入参列表可以被省略。
     * return被省略，则return靠推断
     * 入参列表被省略，则表示没有入参。
     *
     * [val1, val2, val3]叫做捕获
     * 捕获的意思就是，lambda表达式的body中，也可以捕获外层函数的局部变量，我们那可以指定哪些局部变量可以被捕获。
     * 没指定的则不做捕获处理。
     *
     * lambda的本质是创建了一个类，并在创建类的同时实例化了一个obj。而捕获的内容就是这个类的成员变量。
     * 但成员变量的初始化实在创建时完成的，不是在obj调用的时候完成的。
     *
     */
    bool (*lambda)(int, int) = [](int lhs, int rhs)->bool { return lhs < rhs; };
    bool isSmaller = lambda(1,2);

    // 值传递默认不可修改，如果想改要用mutable，引用传递和其他函数一样，要看变量是否是const
    int val1 = 10;
    [val1]()mutable{val1++;};
    [&val1](){val1++;};

    /*
     * 当lambda的body中不只有一条return的时候，编译器推断的返回类型一定是void，此时如果你不想让他返回void，就需要
     * 指定返回类型
     */
    std::vector<int> vInt = {-1, 1, 3,-5};
    std::transform(vInt.begin(), vInt.end(), vInt.begin(),[](int val)->int // 这里必须写return，否则就是void
    {if(val < 0){return -val;} else {return val;}});

}

/* ***********  lambda的具体实现 ******************
 * lambda函数的实现是编译器将lambda函数翻译成一个**未命名的类*的*未命名对象*！！
 * 该类里只实现了一个重载的函数调用运算符，而该运算符与lambda的函数体内容是完全一样的。
 * 因此该lambda函数被掉翻译后，其实只存在一个未命名obj，而不是真正的函数！
 * 比如这里，如果我们声明lambda如下，则和MyCmp是完全一致的！
 * [](int lhs, int rhs){return lhs < rhs;}
 */
struct MyCmp {
    bool operator() (const int lhs, const int rhs) const { // 入参和this都是const的
        return lhs < rhs;
    }
};


/*
 * lambda函数的捕获与mutable
 * mutable：
 * 如果我们不声明lambda表达式为mutable的时候，编译器给我们翻译的"MyCmp"的版本是 const的函数调用成员函数！
 * 而如果我们声明了mutable，则不会声明为const
 *
 * 捕获行为：
 * 引用捕获：
 * 对于引用捕获而言，编译器不需要初始化未命名类的成员变量来存储数据（注意是编译器层面上的不需要，编译器会直接用）
 *
 * 值捕获：
 * 值捕获的是，编译器会多做两件事
 * 1. 新增private成员变量，与被捕获的值一一对应
 * 2. 新增public构造函数，该构造函数会用值传递的入参一一对应的来初始化所有成员变量。
 *
 * [a](int lhs, int rhs) {};
 * struct MyCmp {
 * public:
 *      MyCmp(int a):a_(a){}; // 值传递的所有内容，都要一一对应的初始化成员变量！
 *      bool operator()(const int lhs, const int rhs) const {}
 * private:
 *      int a_;
 * }
 *
 */



int main2 () {
    std::vector<int> v = {5,3,1,6,2};
    std::vector<int> v2 = v;
    std::stable_sort(v.begin(), v.end(), [](int lhs, int rhs){
        return lhs < rhs;
    });
    std::stable_sort(v2.begin(), v2.end(), MyCmp());
}

#endif //C___PRIMER_ALGORITHM_H
