# include <iostream>
#include <vector>
# define Print(x) cout << x << endl;
using namespace std;


/*
                        *****  const在变量中的作用  ****
 
 1. 定义常量： const int MAX_SIZE = 10;
 2. pointer of constant: 指内容是constant的指针。指针不是constant。指针可以变
    使用方法： const 在 “*” 之前即可, 与type的先后顺序无关。
    i).  const int* ptr;
    ii). int const* ptrl
 3. constant pointer: 指pointer是个constant，但内容不是！
    使用方法： const在 “*” 之后即可。
    例如： int* const ptr
 4. 综合方法2和方法3: const int* const ptr; 内容和pointer都无法更改。
 
 其记忆方法也不难： const int 如果连在一起，表示的是内容的type是const int， 而cont ptr表示ptr这个变量是个constant而已。
 
 
 
 
 
 
                        ***** const在class function 中的作用 ****
 
 1. const在声明之后：
    使用：int GetX() const {body};
    作用：
    i).  该function中不可以改变 *成员变量*， 但是可以改变静态成员变量（static variable) 和 传入的或者引用的变量！！！
    ii). 当传入参数是(const class_name& instance_name)的时候，在该函数中，该instance只能调用该class中的const function。
        ie. void foo (const Student& s){body};
            在这个body中，只能调用s的const function！！！  非const function是不能在body中调用的。
    
    因此 const 是一个标签，表示该函数，或者该instance的instance variable不可以被更改。 因此const instance也只能调用
    const function.
 
 2. return type:
    使用 const int* const GetName(){};
        这里const int* const说的是return type的种类，即， return的内容是：一个pointer，且该pointer内容和自身都不可改变。

 因此综合以上两点，一个函数的声明可以同时包含3个const， 2个是限制return type的， 1个是限制body的
    
    const int* const getPointer() const {return ptr;};
 

 
 
                            *** mutable ****
 mutable的作用
 1. 与const对应的作用
    用法： mutable int var; 该var，即使在const function中，仍然可以被更改。
 2. 在lambda中和[=]的组合应用:(不咋用）
    用法： anto lambda_function [=]() mutable {body};
    作用： [=]表示值引用，即不可以改变外面的var的值，但加了mutable，可以在body中直接对变量进行改变，但不影响外面的值。相当于一个重名的局部变量。
        
   
 
 
 
 
 
 
                    ****  lambda ****
 
 捕获值列表，是允许我们在Lambda表达式的函数体中直接使用这些值，捕获值列表能捕获的值是所有在此作用域可以访问的值，包括这个作用域里面的临时变量，类的可访问成员，全局变量。
 捕获值的方式分两种，一种是按值捕获，一种是按引用捕获。顾名思义，按值捕获是不改变原有变量的值，按引用捕获是可以在Lambda表达式中改变原有变量的值。

 [捕获值列表]:

 1、空。没有使用任何函数对象参数。

 2、=。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是值传递方式（相当于编译器自动为我们按值传递了所有局部变量）。

 3、&。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是引用传递方式（相当于编译器自动为我们按引用传递了所有局部变量）。

 4、this。函数体内可以使用Lambda所在类中的成员变量。

 5、a。将a按值进行传递。按值进行传递时，函数体内不能修改传递进来的a的拷贝，因为默认情况下函数是const的。要修改传递进来的a的拷贝，可以添加mutable修饰符。

 6、&a。将a按引用进行传递。

 7、a, &b。将a按值进行传递，b按引用进行传递。

 8、=，&a, &b。除a和b按引用进行传递外，其他参数都按值进行传递。

 9、&, a, b。除a和b按值进行传递外，其他参数都按引用进行传递。
 
 
 */








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
    
    int GetX() const{  //这是一个只读function，这这个function里，你不可以更改任何成员变量,这个功能有什么用呢？看函数PrintEntity()
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
     int GetX() const{}    //这是一个只读function，在这个function里，你不可以更改任何class里instance variable
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
