# include <iostream>
using namespace std;
# define LOG(x) cout << x << endl

/*
 pointer 是什么？
 pointer不过就是一个地址而已，而这个地址不过就是个整型数据而已
 
 pointer和type的关系
 
 pointer本身和type是本质上来讲没有关系的， pointer只是一个内容的首个存放地址而已，无论该地址后面存放的是什么type的变量，
 pointer都只是一个表示内存物理地址的integer而已。
 
 但是pointer和type又是有关系的。因为cpu在读取内存中的数据的时候，首先要根据ptr来找到物理地址，但从该位置开始，获取多长的连续内存
 才能获得完整的数据内容，又是依赖于ptr对应的type的。如果ptr的type是一个int，则cpu会从当前位置获取4个字节。 而如果ptr指向的是个
 double，则cpu会从当前位置开始获取8个字节。
 
 因此，ptr与type之间的关系是，即无关又有关，无关是因为，不管type是什么，ptr永远是一个整数。有关是因为，当cpu获取数据的时候，要
 根据type来决定获取多长的数据才完整。
 
 
 
 常用的pointer的知识：
 1. nullptr: 也可以写做“0”， “NULL”. 当一个ptr是0的时候，表示这个ptr是一个无效的ptr。即这个ptr并没有指向任何东西。
 
 2. “&”：
    1). 与变量一起： &var 得到的是var的地址，
    2). 与type一起： int* ref = var; 表示ref是var的reference，两个变量本质上是一个变量。ref只是var的一个影子而已。
 
 3. "*":  两个作用
    1). int* ptr: 与type在一起，表示该变量是一个int type的ptr
    2). *ptr: 与变量在一起，表示该ptr指向的变量，即内容，而不是地址。
        
        int* ptr = &a;  定义了ptr的类型，并赋值地址。
        *ptr = 10;    更改了内容

 4. new 关键字：new中存放的内容，只能通过ptr来获取和更改。
    new的作用是请求在heap上分配一块内存空间，并且这块空间还不会被消除，除非你主动消除。 而这种存放变量的方式，只能
    通过ptr来记录，存放和更改。
 
        char* buffer = new char[8];
        delete[] buffer;
 
 5. 多指针： ptr -> ptr -> ptr -> content
    ptr本身也是一个integer， 也要存放在memory中，因此也可以用另一个ptr来指向当前的ptr，从而实现多指针。
    char** ptr_2 = &ptr_1;
 
 
 
 */
void pointer_test(){
    int var = 16;
    double* ptr = (double*)&var;
    
    /*
     depoint
     */
    int var2 = 20;
    var2 = 100000;
    int* ptr2 = &var;
    cout << *ptr2 << endl;
    
    
    char* buffer = new char[8];
    /*
     这里表明的是我们在向内存申请8个连续的字节的内存空间， char代表一个字节，我申请了8个。
     而buffer里面存放是这8个字节的开始点的地址。
     memset是一个可以把连续空间的数据都变成一个数。memset（pointer, val, size) 可以把从pointer开始的连续size个内存空间，全部变成val.
     */
    memset(buffer, 1, 8);
    
    /*
     指针的指针，double pointer
     因为指针也是一个变量，因此，指针作为一个整数，也存放在一个内存中，而我们做的只是再用一个指针 用来存放这个指针变量的地址。
     */
    char** ptr_double = &buffer;
    
    
    delete[] buffer;
    
    
}
