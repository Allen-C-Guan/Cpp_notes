# include <iostream>
using namespace std;


//——————————————————————————————————————————————————————————————————————————————————————————————————————
/*
            *********************   constructor   ****************************
 
 定义：constructor指的是class在被实例化的时候，都会运行的一种特殊的method。
 
 使用方法：
 1). 无传递参数的版本：
 简单版本的初始化： class_name(){ 初始化操作 };
 实例化： Class  instance1 ;
 
 2). 有传递参数的版本：
 简单版本的初始化： class_name(传参){ 初始化操作 };
 实例化： Class  instance1 (传参1， 传参2， ... );
 
 
 例子：
 */
class ListExample{
public:
    ListExample(){
        cout << "this is default constructor" << endl;
    }
    ListExample(int x){
        cout << "this is constructor with parameter "<< x << endl;
    }
};



 
 /*          *********************  多个constructor  ************************
  
  功能：多个constructor可以实现实例化的时候，根据传入参数数量，种类的不同 而实现自主匹配constructor的功能。
  
  使用方法：一个class可以有很多个constructor，只要保证signature是不同的。
  
  例子：
  */
class Entity0{
public:
    float X, Y;
    ListExample l;

    //*************************
    /*          *** 无参constructor ***
     在c里面，并不是所有的编译器都会给属性一个固定的初始值，因此我们一定要在construtor中，手动的给所有的属性一个初始值。
     而无参变量就可以作为default constructor，完成上面所说的任务，因此，我们的class，一般要有无参的构造器.
     */
    Entity0(){
        X = 0;
        Y = 0;
        l = ListExample(5);    //这里ListExample 会先被无参数构造器实例化，然后扔掉，在用有参构造器在实例化一个。这浪费了内存空间。
        cout << "constructor Entities" << endl;
    };
    
    
    
    //*************************
    
    //          *** 有参 constructor 与多个 constructor ***
    
    Entity0(float x, float y){
        X = x;
        Y = y;
    };
    
    
    
//——————————————————————————————————————————————————————————————————————————————————————————————————————
    
    //         *** 用list 来初始化instance variable ***
    
    /* member initialize list
     
     方法： constructor(type1 val1,  type2 val2)
            : m_val1(val1), m_val2(val2),
            {
            }
     注意： initialize list 的顺序一定要和 instance variable 的初始化顺序相同。
     
     优点： 这个方法的好处在于可以减少一次obj创建的过程。
        因为在被实例化的时候，会调用constructor， 如果constructor中，把所有instance variable的初始化都放在body中，
        则所有instance var都会被先用无参构造器初始化，如果body中进行了更改，那么就会再将原来通过无参构造的instance或者variable
        的内容进行覆盖或者更改。
        
        但是如果你使用了initialize list的话，再初始化的过程中，就会根据initialize list直接对instance variable进行初始化。
        而不需要先初始化，后覆盖或覆盖。
        
    使用原则： 能用list就用list！
     
     
    */
    
    Entity0(float x)
        : X(x), Y(0), l(ListExample(1000))  //如果用List的话，只会实例化一次。并不会调用无参构造器，因此能用list就用list
    {
    };
    
    

    
    
    
    
//——————————————————————————————————————————————————————————————————————————————————————————————————————
    
    //                               *** Destructor ***
    
    /*
     Destructor的作用：当instance即将被销毁之前，所执行的一个函数。注意，一个类只能有一个destructor.
        如果用户没有定义，编译器会自动生成一个默认的析构函数
     
     instance的销毁：
        1). out of the scope: 当instance不是利用new来实例化的时候，一旦out of scope,所有scope里的instance
            都会自动被销毁。
        2). delete： 当instance用new来实例化的时候，delete instance的时候会触发销毁。
  
     使用方法：
        ～class_name(){body}
     
     例子：
     */
    ~Entity0(){
        cout << "Destructor Entities" << endl;
    }
    
    void Print(){
        cout << X << ", " << Y <<endl;
    };
    
};


//———————————————————————————————————— test ——————————————————————————————————————————————


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
