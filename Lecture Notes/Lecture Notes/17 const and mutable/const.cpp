# include <iostream>
#include <vector>
# define Print(x) cout << x << endl;
using namespace std;


class Entity{
private:
    int X, Y;
    int *PX, *PY;
    mutable int var; //这种可变变量在const里面也能用，这b就像一个const的漏网之鱼一样。
    
public:
    Entity(){}
    
    void SetX(int x){
        X = x;
    }
    
    int GetX() const{  //这是一个只读function，这这个function里，你不可以更改任何class里的内容,这个功能有什么用呢？看函数PrintEntity()
        return X;
    }
    int GetX(){   //通常情况有两个getter 进行overloading。
        return X;
    }
    
    const int* const GetPX() const{
        //*之前的const限制了内容，*之后的const限制了pointer， 最后的const限制了函数只读（不能更改class里的内容）。****
        var ++;  //mutable var 即使const，也阻止不了你的改变
        return PX;
    }
    
};

/*
 这就是const的作用。这里我们在函数printentity里面，我们想把entity当成一个const，不要去改变，而且我还是利用的reference，这种情况下，
 我就在该函数中，只能调用具有const的函数来保证不变性。非const函数都不能用
 */
void PrintEntity(const Entity e){
    Print(e.GetX());
    //e.SetX(6); 这个函数就不能在当前函数中使用。
    Print(e.GetPX()); //有mutable在函数中改变也没事。
}



void const_tst(){
    
    //1. 当成constant来用
    const int maxSize = 1000;
    
    //2. pointer of constant
    /*
     const只是限制了content，而没有限制pointer，pointer依然可以改变，例如 */
    const int* p1 = new int;
    int const* p_foo = new int;  //这两个是一个意思，主要取决于*在const之前还是之后，之前是pointer，之后是content。
    
    
    p1 = &maxSize;
    Print(*p1)
    
    //3.constant pointer
    //这里我们限制的和2正好相反，我们限制了pointer不能变，但是content可以变
    int* const p2 = new int;
    *p2 = 66666;
    Print(*p2);
    
    //2 3 点汇总得到， const作用域在右边，如果*被包含了const右边，那就是const pointer 否则就是const content
    
    
    
    //4. const在class中的作用
    /*
     int GetX() const{}    //这是一个只读function，在这个function里，你不可以更改任何class里的内容
     */
    const Entity e;
    e.GetX(); //这就行
    //e.SetX();  这就不行
    
    
    
    //mutable 在lambda function的作用   这方法也不咋用
    
    int x = 8;
    auto f = [=]() mutable{   // =表示赋值，&表示引用， 因此等号表示把传入的内容复制过来,这里的x就变成了local var了，然后作为x，x++，
                              //如果没有mutable，那就是外面的x了
        x ++ ;
        Print(x);
    };
    
    //上式等于
    auto f2 = [=](){
        int y = x;
        y++;
        Print(y);
    };
    
    
    
    
    /*使用const需要注意的地方
     const是可以直接通过赋值来copy给非const变量的，而新的变量并不因为是从const copy过来的就变成const了，它仍然可以自由移动
    */
    const vector<int> v1 = {1,2,3,4,5,65};   //v1是const
    vector<int> v2;                          //v2不是const
    v2 = v1;                                 //通过复制copy
    v2[0] = 9809245;                          //copy后的v2还是可以改变，他只是copy了内容，并没有copy权限啊
    
     //这是一个方法，直接引用
    const vector<int>& v3 = v1;
     //把copy过来的新的vector也变成const
    const vector<int> v4 = v1;
    
    
    //由于const的值必须在声明的时候就确定下来，因此我们并不能像v2一样，先声明，后赋值。
 
  
}
