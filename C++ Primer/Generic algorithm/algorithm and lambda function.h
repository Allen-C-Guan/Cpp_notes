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
    /*
     *  ********************  algorithm  *************************
     *  算法，是一种泛型编程，也就是说我不关心你的容器是什么容器，我要做的就是无论什么容器，我都要获得相同的结果
     *  为了实现以上的功能，我们的办法就是，我们使用不直接操作容器，而是用迭代器来操作容器，因为迭代器不同的容器的接口是相似的，
     *  这就给泛型编程提供了条件。 我们利用这些对外呈现相似的迭代器而间接的操作不同的容器，我就不需要关心是什么容器了。
     *
     *  但是因为泛型算法操作的是迭代器，而不是容器本身，而迭代器本身是没有能力直接改变容器大小的，因此泛型算法也没办法直接
     *  改变容器的大小。
     *
     */
    int a[6] = {1,2,3,4,5,6};
    int b[12];

    // find
    auto ret = std::find(std::begin(a), std::end(a), 5);
    std::cout << ret - std::begin(a) << std::endl;

    // accumlate
    // 该算法的功能依赖于容器中存放的类的operator+的定义！， accumulate的本质就是遍历并调用类的“+”来实现的
    auto ret2 = std::accumulate(std::begin(a), std::end(a), 0);
    std::cout << ret2 << std::endl;

    // equal
    // equal的功能依赖于容器中类对operator==的定义。
    // 这种操作两个容器的算法就体现出泛型算法的牛逼之处了，av和equal不管是容器还是内容都是不一样的，但是只要可以存储的类型可以转换
    // 并且两种类型之间可以用 “==” 来比较，就可以了。
    std::vector<long> av = {1,2,3,4,5,6};
    auto ret1 = equal(std::begin(a), std::end(a), av.begin());
    std::cout << ret1 << std::endl;

    // ******************* 写操作 ***************************
    // 关于写操作，我们必须要自己保证有足够内容够写，算法是不关心的。
    // fill  fill_n
    // 这里的fill是覆盖写操作的。
    int i1[10];
    std::fill(std::begin(i1), std::end(i1), 100);
    std::fill_n(std::begin(i1), 10, 1000);


    /*
     * back_inserter(容器）
     * 提供了一种可以忽略内容是否足够写的一个迭代器。而代价是你只能在序列后面插入，所有你当然就不用考虑够不够的问题了
     * 实现： 该函数获取一个容器的引用，然后返回一个与该容器绑定的迭代器，该迭代器的功能是，当调用 = 的时候，会调用push_back();
     */
    std::vector<int> vec = {0, 1, 2, 3, 4};
    std::fill_n(std::back_inserter(vec), 5, 8888);

    // copy 函数
    int array[10] = {1,2,3,4};
    std::vector<int> v1;
    std::copy(std::begin(array), std::end(array), std::back_inserter(v1));
    std::cout << "end";

    // replace replace_copy
    std::replace(std::begin(array), std::end(array), 4, 44444);

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
