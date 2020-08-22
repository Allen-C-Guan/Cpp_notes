# include <iostream>
using namespace std;



/*
 
 head file的作用
 1. 函数的声明
 在linking和include的区别中我们讲到了,由于linking与include的工作特性，以及声明的意义， 因此如果一个函数要想被使用的话，至少
 要两步走，step1 定义 step2 声明。并且保证定义一次，但需要重复的声明。而重复的声明的工作，就交给了头文件来执行了。
 即，函数要在cpp文件中定义，在head文件中声明。 而对于其他cpp文件，只要include一下这个头函数就行了。
 
 
  #pragma once的作用
 在一个cpp文件中，相同的内容，只会出现一次。从而避免多次定义！
 Log.h中定义了一个struct student, common.h 中 include "Log.h". 本文中又同时include了 Log.h和common.h两个内容。
 因此struct student在该cpp中被定义了两次。
 
 而如果在 定义该struct的头文件中，加一个 #pragma once， 该头文件的全部内容都只会在一个cpp file中出现一次。
 
 */

# include "Log.h"
# include "common.h"

/*
 include 为何有时候用<>有时候用“”
 
 这是因为“”表示当前路径下的文件，而<>表示搜索系统+附加包含路径中的文件。简单理解可以为<>范围更大，支持第三方库的搜索。 “”通常是自己的内容。
 */


void head_test(){
    cout << "Hello Word!" << endl;
    Log2("this is a Log function");
}
