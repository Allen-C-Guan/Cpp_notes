#include <iostream>
#include <string>
#define Print(x) cout<< x << endl
/*                           ***** macro *****
定义：
    Macors的所有工作都是在编译之前完成的，而他所做的工作，就是文本层面的替换，这种替换还是在compile之前完成的，和template不一样，
    template的工作是在编译进行时，和call之前完成的。是一种编译器帮你写代码的感觉。

 
使用方法：
 define name(传参） 包含传参的语句或者结构体。
 
 
注意：
 1. 我们不可以以牺牲可读性为代价来写macors。
 2. 通常macro中不写";"。
 3. 在define中，不写等号，用 define A B 来实现 A = B，因为本来define就不是等于，是替代，因此写 “=” 不是很准确。

使用范围：
 1. 通常macors用在的debug上比较多
 2. 一些简单的语句替换。


tips:
其实# 就是一个标志，标志是个内容是preprocess的而已， 就这么简单。里面一样可以有 if else等。但都没有;
可以通过切换debug的值来选择性的去定义一个macors！

*/



//        ***** 例一 ****
#define ISDEBUG 0  // 当值==0 时候，DEBUG啥也输出， 当1的时候 DEBUG才有输出。
#if ISDEBUG == 1
#define DEBUG(x) cout << x << endl
#else
#define DEBUG(x)   //这就相当于一个空语句而已
#endif    //已经记得，有endif


//          ***** 例二  *****
# define Print(x) cout << x << endl;

# define IsDebug 1
# if IsDebug == 1
# define State "Debugging"
# else
# define state "Release"
# endif


using namespace std;

void MacorsTst(){
    Print("Hello");
//    DEBUG("This is debug");
}
