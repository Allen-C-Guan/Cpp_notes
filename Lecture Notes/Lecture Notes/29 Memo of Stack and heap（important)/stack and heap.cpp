# include<iostream>
using namespace std;

/*
 stack和heap都是同一块memory上的两个不同的区域而已
 
                            *****   stack的工作原理   ******
 
 工作原理：
 stack有个指针，从stack的底部(地址高处)逐步向上（地址低处）移动。 当需要开辟一整块stack上的内存单元时，例如需要开辟16个byte的空间时，
 stack 的指针会先向栈顶（地址低处）一次性移动16个byte，这时内存开辟即完成。 如果需要赋值，指针再从栈顶（地址低）到栈底的方向（地址高）
 向下逐一赋值。从而保证数据的分配是以内存地址升序排列的。
 
 简而言之：内存的开辟是从栈底向栈顶开辟的， 数据的赋值却是从栈顶向栈底赋值的。
 
 访问速度：
 通过如上描述，我们可以发现，存储在stack上的数据是按"FIFO"顺序在一段连续的内存空间中“摞”起来。 且相邻数据之间是紧挨着的，
 没有空隙的。这种相邻的，连续的存储方式，让存储在stack上的数据的索引，删除，更改等操作的速度变得非常的迅速。

 Free memory：
 对于stack variable而言， variable一旦变量超出了scope，那么变量就会自动的从stack中pop出去。 而pop不过就是向栈底移动pointer而已。
 因此free的速度非常快。且是自动完成的
 
 
                                ******   heap   ******
 heap和stack最大的不同在于，当你利用new在heap上开辟一段空间时，你要通过操作系统的 "free list" 给你分配一段足够的空闲的空间。
 而后，操作系统会给你返回一个pointer（刚开辟的内存空间的地址）。  因此，当你连续的向heap申请内存的时候，所申请到的内存却并不是连续的。
 因为“free list”所维护的heap的内存空间上，空闲的内存空间并不是连续的。
 另外，存储在heap上的内容，都需要delete来手动的删除。
 
 其具体工作流程为：
 在使用new的时候， c会调用malloc函数， 这个函数会调用操作系统的一些指令， 操作系统的“free list”，专门记着哪些memo上有空位，空位的
 size是多大。因此，系统会给你分配一个大于等于你要的space的连续memory，并把地址给你。 这个地址就成了返回的值。这也就是为什么new
 一定要用ptr来做为函数的原因了。

 这一系列的操作就可以知道，想和操作系统要一个地方是多么的麻烦和复杂，删除的时候也更加麻烦，而且如果操作系统没有那么多地方，你就更麻烦了。
 通过工作原理我们发现，heap上的变量不是相互连接的，每次存储的代价也是非常高的。这就让维护heap的成本大大增加了。
 
 注意：
 1. 即使你使用了smart_pointer，但尽管没有显示的使用 “new” 和 “delete“，但smart_pointer内部仍然是使用“new” 和 “delete"来完成的。
 2. heap和stack上运行速度的差异，主要体现在allocate上！即开辟内存的时候。而对于索引和赋值而言，速度却并没有显著的差异。
 
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
