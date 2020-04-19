# include<iostream>
using namespace std;

/*
 stack和heap都是同一块memory上的两个不同的区域而已
 
 stack的工作原理是：
 stack有个指针，stack的底部逐步向上移动，每次移动都会存储一些内容在里面，移动多少取决于存储内容的数量和大小。
 但是是先从下往上移动到对应的位置上，然后才是从上往下存储当前内容。 即内容内部的内存是从低到高，但内容之前是先来后到的关系。
 因此stack的内存空间都是互相连接的。
 
 而且一旦变量超出了scope，那么变量就会从scope中pop出去。 因此stack不但输入的时候是连续的，输出的时候也是连续的。
 
 通过该工作原理我们可以知道，stack的工作原理不过就是上下连续的移动指针而已，根本用不到指针的索引。这就让stack的速度非常的快！
 
 
 heap的工作原理：
 在使用new的时候， c会调用malloc函数， 这个函数会调用操作系统的一些指令， 操作系统有个地方，专门记着哪些memo上有空位，空位的size是多大。
 因此，系统会给你分配一个大于等于你要的space的连续memo，并把地址给你。 这个地址就成了返回的值。
 这也就是为什么new一定要用ptr来做为函数的原因了。

 这一系列的操作就可以知道，想和操作系统要一个地方是多么的麻烦和复杂，删除的时候也更加麻烦，而且如果操作系统没有那么多地方，你就更麻烦了。
 
 
 通过工作原理我们发现，heap上的变量不是相互连接的，每次存储的代价也是非常高的。这就让维护heap的成本大大增加了。
 */

struct Vector{
    float x, y, z;
};

void StackAndHeap(){
    // stack
    int value = 5;
    int array[5];
    Vector vector;
    
    //heap  heap都是用new完成的，即使是smart_pointer 也是用new来实现的。
    int* hvalue = new int;
    int* harray = new int[5];
    Vector* hvector = new Vector;
    
    
    
    
}
