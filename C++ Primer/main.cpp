#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <set>
#include <vector>
#include <map>
class Foo{
public:
    int a;
    std::string b;
};

class FooWithEmbrace{
public:
    int a;
    std::string s;

//    bool operator< (const Foo &lhs, const Foo &rhs) { // TODO
//        return lhs.a != rhs.a ? lhs.a > rhs.a : lhs.b > rhs.b;
//    }
};
bool isFooLarger(const Foo &lhs, const Foo &rhs) {
    return lhs.a != rhs.a ? lhs.a > rhs.a : lhs.b > rhs.b;
}

int main() {
    // 关联容器的初始化
    std::vector<double> vDouble = {1.1, 2.2};
    std::set<int> sInt(vDouble.begin(), vDouble.end());

    /* 关联容器中关键字类型的比较函数
     * 在关联容器中，我们要求key的值必须可以用 "<"来比较大小，其中"<"的操作必须是逻辑"严格小于等于"的。
     * 但是我认为叫严格小于才合理。
     * 之所以这么规定是因为我们要通过 a不小于b，且b不小于a来判定 a == b
     *
     * 但是我们也可以自定义我们自己的"操作类型"，操作类型指的就是我们比大小的操作。
     * 在关联容器中，操作类型必须是一个类型，要么是函数类型，要么是类类型。
     *
     * 当操作类型是函数类型的时候，我们就要如下定义
     */
    std::set<Foo, bool (*)(const Foo&, const Foo&)> s(isFooLarger);
    /*
     * 这里在set的内部实现的是 将isFooLarger传入作为类型T，然后调用T(f1,f2)来实现对比的。
     */

    /*
     * ************************   map的返回值  ***************************
     * map返回的是一个pair，该pair的first是个迭代器，该迭代器指向已经存在map中的pair（当然pair的key值要
     * 与插入的相同，pair的second是bool值，表示新插入是否成功
     *
     * 当插入成功时，return的first就是新插入的这对pair，bool值为true
     * 当插入失败时，return的first是map中已有的pair（该pair和新插入的pair的key相同），bool值为false。
     */
    std::map<int, std::string> m;
    auto map_ret = m.insert({1, "allen"});
    std::cout << (map_ret.first->first) << ", " << (map_ret.first->second)<< ", " << (map_ret.second) << std::endl;
    auto map_ret2 = m.insert({1, "c"});
    std::cout << (map_ret2.first->first) << ", " << (map_ret2.first->second) << ", " << (map_ret2.second) << std::endl;


}