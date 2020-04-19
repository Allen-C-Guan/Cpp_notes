# include <iostream>
# include <string>
using namespace std;


/*
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
