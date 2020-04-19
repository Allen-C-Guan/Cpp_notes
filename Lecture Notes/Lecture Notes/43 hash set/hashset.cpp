#include <iostream>
#include <unordered_set>
#include <set>
#include <iterator>

using namespace std;

template <typename Set>
void printSet(const Set& s){
    for(auto e: s){
        cout << e << ", ";
    }
    cout << "\n" ;
}



void hashsetTst(){
    
    /*
     unordered_set
     unordered_set和set比，由于不需要排序，因此插入，删除的速度会非常的快。
     */
    unordered_set<int> sets = {1,2,3,4,5,6,7};
    bool res = sets.find(5) != sets.end();
    cout << boolalpha << res << endl;
    
    //count 好像比find好用啊！！，count得到的直接就是true or false.
    cout << sets.count(9) << endl;
    
    /*
     set
     set每次的插入，删除的复杂度都是log级别的，
     */
    set<int> s;
    s.insert(4);
    s.insert(3);
    s.insert(2);
    s.insert(1);
    printSet(s);
    
    //自定义set的对比方法和map一样，都需要一个const的class compare
    struct Vector{
        float x, y;
    };
    class cmpSet{
    public:
        bool operator() (const Vector& a, const Vector& b) const{
            return a.y > b.y;
        }
    };
    
    set<Vector, cmpSet> custom_set;
    custom_set.insert({4, 1});
    custom_set.insert({6, 2});
    custom_set.insert({7, 4});
    custom_set.insert({8, 10});
    
    //获取set和map中某一个index的值
    
    //方法1
    set<Vector>:: iterator it = custom_set.begin();
    auto next = *(++it);
    
    
    //使用advance来让获取iterator的内容， advance是在操作it variable！ 并没有return！，其原理就是用next和for来实现的而已，我们不能直接在某些函数外使用+和-的overloading的
    auto it2 = custom_set.end();
    advance(it2, -1);
    auto res1 = *it2;
    
    
    
    
    
}
