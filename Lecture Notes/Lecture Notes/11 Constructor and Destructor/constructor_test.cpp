# include <iostream>
using namespace std;

class ListExample{
public:
    ListExample(){
        cout << "this is default constructor" << endl;
    }
    ListExample(int x){
        cout << "this is constructor with parameter "<< x << endl;
    }
};


class Entity0{
public:
    float X, Y;
    ListExample l;
    
    // constructor
    
    /* 无参constructor
     在c里面，并不是所有的编译器都会给属性一个固定的初始值，因此我们一定要在construtor中，手动的给所有的属性一个初始值。
     而无参变量就可以作为default constructor，完成上面所说的任务，因此，我们的class，一定要有无参的构造器.
     */

    Entity0(){
        X = 0;
        Y = 0;
        l = ListExample(5);    //这里ListExample 会先被无参数构造器实例化，然后扔掉，在用有参构造器在实例化一个。这浪费了内存空间。
        cout << "constructor Entities" << endl;
    };
    
    // 有参 constructor
    
    Entity0(float x, float y){
        X = x;
        Y = y;
        
    };
    
    /* member initialize list
     这个方法的好处在于可以减少一次obj创建的过程。
     list的顺序要和定义的顺序相同
    */
    Entity0(float x)
        : X(x), Y(0), l(ListExample(1000))  //如果用List的话，只会实例化一次。并不会调用无参构造器，因此能用list就用list
    {
    };
    
    

    //Destructor
    /*
     Destructor的作用是当instance被销毁之前，需要做的事情，可以写在Destructor里面。
     
     创建对象时系统会自动调用构造函数进行初始化工作，同样，销毁对象时系统也会自动调用一个函数来进行清理工作，例如释放分配的内存、关闭打开的文件等，这个函数就是析构函数。

     析构函数（Destructor）也是一种特殊的成员函数，没有返回值，*不需要程序员显式调用*，而是在销毁对象时*自动执行*。构造函数的名字和类名相同，而析构函数的名字是在类名前面加一个~符号。

     注意：析构函数没有参数，*不能被重载*，因此一个类只能有一个析构函数。如果用户没有定义，编译器会自动生成一个默认的析构函数
     销毁是在out of scope的时候被销毁，对于这里 function内部是一个scope，那么所有在funcition内部的instance， 在function返回的同时，都会被销毁。
     */
    
    ~Entity0(){
        cout << "Destructor Entities" << endl;
    }
    
    void Print(){
        cout << X << ", " << Y <<endl;
    };
    
};

void Function(){
    Entity0 es;
    es.Print();
};



void constructor_test(){
//    Entity e; //在有些编译器下， 这样的声明是不会给e初始化的，只有在调用e的时候才会初始化。但是mac的编译器里会初始化，并给赋予初值。
//    e.Print();
//
//    Entity e2(10,5);
//    e2.Print();
    
    cout << "test deconstructor\n" << endl;
    Function();
    
    
    cout << "\n test the initialize list" << endl;
    Entity0 e(5);
    
    Entity0 e2;
    
  
    
    
    
    
}
