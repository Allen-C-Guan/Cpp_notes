#include <iostream>
#include <string>
#define Print(x) cout<< x << endl

//其实# 就是一个标志，标志是个内容是preprocess的而已， 就这么简单。里面一样可以有 if else等。但都没有;
//可以通过切换debug的值来选择性的去定义一个macors！
#define ISDEBUG 0  // 当值==0 时候，DEBUG啥也输出， 当1的时候 DEBUG才有输出。
#if ISDEBUG == 1
#define DEBUG(x) cout << x << endl
#else
#define DEBUG(x)   //这就相当于一个空语句而已
#endif    //已经记得，有endif



using namespace std;


/*
 Macors的所有工作都是在编译之前完成的，而他所做的工作，就是文本层面的替换，这种替换还是在compile之前完成的，和template不一样，
 template的工作是在编译的时候，和call之前完成的。是一种编译器帮你写代码的感觉。
 
 我们不可以以牺牲可读性为代价来写macors。
 
 通常macors用在的debug上比较多
 
 
 */
void MacorsTst(){
    Print("Hello");
//    DEBUG("This is debug");
}
