#include <iostream>
#include <queue>
#include <utility>
using namespace std;

/*
 这就是一个heap而已， 使用方法和queue和stack是 一样的。
 对于再带sort功能的container，其使用cmp的方法都是建立一个带有 对（）overload的 函数的class，并带有3个const key words
 */



void priority_queue_tst(){
    priority_queue<int> pq;
    
    for(int n: {1,2,3,4,5,6}){
        pq.push(n);
    }
    
    
    //在function中定义的类是局部类，局部类只能在当前function之中存在，其实例化的instance也只能在当前function之中存活。
    class myCMP{
    public:
        bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) const{
            return a > b;
        }
    };
    
    // priority_queue < type,   container type,  MyCmp>
    priority_queue <pair<int, int>, std::vector<std::pair<int, int>>,  myCMP> myQueue;
    
    
    
}


