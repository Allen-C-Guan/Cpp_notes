#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 function pointer是一种把function变成variable的方法。
 其对应的功能和python中分别使用 function(); 和function；一样。function()是call， function；是function的变量传递。
 
 通常情况下，我们只是把function当成一个可以被call的功能，当然在call的时候也可以传入参数。
 但实际上，function还可以作为变量，传入给其他function中，这就是通过function pointer做到的
 
 这里最重要的点在于：
 function pointer的定义，是由输入和返回的种类和数量来唯一确定的！  即signature来决定的！ 一个signature对应唯一一个function pointer
 */




void HelloWorld(){
    cout << "Hello World!" << endl;
}

void TestFunction(){
    cout << "this is test function" << endl;
}


void FunctionWithParam(int val){
    cout << "this is val function with val: " << val << endl;
}


/*工厂级函数
 工厂级函数适用于，signature相同，但功能不同函数模块的复用。
 
 工厂级别的函数的作用可以是可以让函数模块化，只要函数的输入输出的类型是确定的，含内部是什么功能我们不管。
 */
void PrintInt(int val){
    cout << val << endl;
}
void PrintAdd(int val){
    cout << val+1 << endl;
}


//主要功能
typedef void(*PrintVector)(int); //定义一个function type(由return void和 input int唯一确定)
void ForEach(const vector<int>& values, PrintVector printfunction){
                    //所有符合return void和 input int 的函数都可以输入，函数的ptr会给printfunction函数
                    //然后就可以直接调用这个函数了
    for (int value: values){
        printfunction(value);
    }
}


void FunctionPtrTst(){
    void HelloWorld(); //这里这个是调用的
    //第一种定义法
    auto function = HelloWorld;
            //这个就是函数指针了，这里他并没有call，因此也不会输出helloworld,只是把指针给放到function中了。
            //这里之后function就和Helloworld funciton 起到的作用是一样的了，调用function等于调用helloword,而且还不用声明返回类型。
    
    //第二种定义法
    void(*function2)() = HelloWorld;  //这才是上面定义的时候的真实的样子，这两个定义的方法是完全一样的。
    
    function();
    
    //第三种定义法
    //上面两种定义方法，第二种比较不好理解，第一种相对好理解一些，但是还可以让可读性更好一点
    typedef void(*ReturnVoidNoParameterFunction)();
    ReturnVoidNoParameterFunction function3 = HelloWorld;
    
    /*
     通过方法2 和方法3我们可以发现，这个function pointer定义的是一套function，这些function具有相同类型的输入和输出的type和数量。
     因此可以得出结论， function pointer的定义，是由输入和返回来唯一确定的！
     */
    ReturnVoidNoParameterFunction tst = TestFunction;
    tst();
    
    
    //有传递参数的
    
    typedef void (*ReturnVoidWithParam)(int);
    
    ReturnVoidWithParam functionInt = FunctionWithParam;
    
    functionInt(5);
    
    //这看起来就和python一样了诶！！ 因为所有的return type，传入函数的type，都已经被封装在了pointer里。
    
    /*
     这里注意下区分  typedef void (*Function)(int) 和 void(*functionptr)(int) = function；的区别
     在typedef里面，你获得是一个type， 就和int一样，并不是一个ptr。如果你要使用，你还要实例化：
        Function function = HelloFunction;
        function(5); 才能用
     在第二种方法中直接就获得了functionptr，这里得到的functionptr就可以直接用了
     functionptr(6);
     */
    
    
    //何时使用function pointer？
    //当我们要建工厂级函数的时候。
    cout << "\n\n this is factory function test" << endl;
    vector<int> values = {1, 2, 3, 4, 5};
    ForEach(values, PrintInt);
    
    cout << "\n" << endl;
    ForEach(values, PrintAdd);
    
    /*
     你看这里 PrintAdd和PrintInt就是两个不同的函数，但是因为有相同的signature，就可以让ForEach发挥不同的作用。
     */
    
    
    
    
    
}
