#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void ForEach1(const vector<int>& values, void (*func)(int)){
    for(int val: values){
        func(val);
    }
}


void LambdaTst(){
    vector<int> values = {1,2,3,4,5,6};
    auto lambda = [](int value){cout << "Value: " << value++ << endl;};
    /*
    1. []中表示captures， ()中表示的input， {}中就是函数的主体了。这就是一个完整的function
    2. auto lambda = function; 这就是function pointer的最常用的使用方法了。lambda就可以想python中一样使用了。
                不需要声明type，功能和后面定义的内容是一样的。
     */
    ForEach1(values, lambda);
    
    
    
    /*[]的作用是决定外部参数以何种方式进入到lambda函数中，因为lambda函数的scope只在内部，外部定义的变量只能通过传参
     的形式进或者出lambda function，但是我们有办法把lambda的scope向外扩大一层。通过对[]内部的定义
     
     []表示啥也不capture  内外互不干扰
     */
    int a = 1000;
//    auto lambda1 = [](){cout << "Value: " << a << endl;}; // 这个方法就不行
//    lambda1();
    
    
    // = 表示capture所有外层变量，并均通过copy的方式
    auto lambda2 = [=](){cout << "Value: " << a << endl;};
    lambda2();
  
    // &表示capture所有外层变量，并通过reference的方式
    auto lambda3 = [&](){cout << "Value: " << a << endl;};
    lambda3();
    
    // [a]表示只有外部的a可以进去的。当然也可以是 &a
    auto lambda4 = [a](){cout << "Value: " << a << endl;};
    lambda4();
    
    // mutable lambda 只有加上mutable， lambda里面才能更改外面的内容。
    auto lambda5 = [&a]() mutable {cout << "Value: " << a++ << endl;};
    lambda5();
    cout << a << endl;
    
    
    
    /*python 中可以iterator的obj中，可以通过lambda进行筛选， list = [.... key = lambda x: x > 5]
     在c中，也可以，就是非常麻烦。
     首先你要有一个迭代器， vector自带迭代器， .begin() , .end(),等 然后才能用lambda来筛选
     
     使用函数find_if,这个函数在algorithm里面
    */
    auto iterator = find_if(values.begin(), values.end(), [](int val){ return val > 4;});
    
    //用return的bool的值，决定是否把这个值加在iterator里面
    cout << *iterator << endl;  //iterator是一个地址，我们要打印的是内容
    
}

