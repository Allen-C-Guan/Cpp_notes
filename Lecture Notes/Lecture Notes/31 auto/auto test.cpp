#include <iostream>
#include <string>
using namespace std;

/*
 auto 指的是，在编译器知道类型的前提下，他会自动的帮你给出类型，这里有个前提在于，编译器必须要知道这个类型才可以。
 因此初始化的时候不一定能用。
 
 这个工作原理和template 差不多，都是编译器在帮你写代码的情况
 
 何时知道类型呢
 1. 赋值的时候
 2. 接收return的时候
 
 什么时候要用这个auto呢？
 1. 我们不在乎他是什么类型
 2. 如果一个变量接受的数据类型不确定的时候。ie 时而是 a = 7; 时而是 a = "Allen";
 3. 当函数返回的接受值的类型可能会发生改变的时候，auto方便维护。 这带来另一问题是如果我们要用特定type的函数的时候，auto不能保证这个变量
        就是那个类型。
 4. 当type很长的时候， 但这个时候， 用typedef,或者 using 比较好一点
 */

string GetName(){
    return "Allen";
}

void AutoTst(){
    int a = 6;
    auto b = a;
    
    auto c = 8; //他也会自动通过8，来给c一个int的类型，因为他觉的你是int。
    auto str = "ALLen";
    
    auto name = GetName();//这里如果我的函数发生了改变，那么我的主函数，或者应用端不需要任何改变。
    
    
    
}

