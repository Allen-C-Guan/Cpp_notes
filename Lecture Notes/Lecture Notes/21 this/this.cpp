# include <iostream>
# include <string>
using namespace std;


/*
 this关键字：
 定义： this，是一个指向当前instance的pointer。
        即： Entity* e = this; 表示一个pointer
 
 用法：
    1). 指向当前的pointer： this->m_X;
    2). 指一个const type* const pointer： 在const function中， this就是一个内容和pointer都不可以改变的pointer。
    3). (*this)，表示当前的instance，而不是一个pointer。 通常用在在class内部， 调用一个当传入参数为 instance的functon的时候。
        例如： 在class内部使用 printVector(this); or printVector(*this);
            当printVector 定义在class外部的时候，并且传入参数分别对应 (const Entity* e) or (const Entity& e)的时候。
 
 this 的用法和self的用法的最大区别就在于this用的是 "->", 而self用的是 ".".
 
 */


class This_tst;
void PrintThis(const This_tst& t);

class This_tst{
public:
    int x, y;
    This_tst(){}
    This_tst(int x, int y){
        this -> x = x;       //this是一个指向当前instance的一个指针，注意他是一个指针不是变量。也不是obj，
        this -> y = y;
    }
    
    void Print() const{
        PrintThis(*this);  //在class内部想要把自己传出去，用this就能把自己给弄出去了， 但还是注意，this是pointer，
                            //如果接受端是obj，或者reference， 那么就可以 就用*this
    }
};

void PrintThis(const This_tst& t){
    cout << t.x << t.y << endl;
}

void this_tst(){
    
    const This_tst t(4,5);
    t.Print();
    
}
