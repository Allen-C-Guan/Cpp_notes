
#include <iostream>
using namespace std;
/*
 对于data type，我们唯一在意的并不是名称，我们在意的不过就是所占内存的大小而已。
 与python不同，c++没有很多的规则必须要遵守，c相对来说还是比较直接的对内存进行操作的。因此即使出现的array的超出范围，也没有关系
 这一方面是c的弊端，因为这让编程要在意的东西很多，因为规则不是很多，编译器并不会报错。
 但是这也是优点，这意味着c语言的使用更加的灵活多变。
 
 例如我们不用在乎变量是char还是int，随便用，只是解释方式不同而已，对应的内存中的二进制是相同的
 
 1 Byte = 8 bits
 
 *整型数据
 int     4 Byte    只能存下正负 2 billion的值  2^31 其中一位用来表示正负号。
 unsigned int   没有正负号， 可以存 2 ^ 32个数， 如果是负数，就会得到补码。
 char    1 Byte
 short   2 Byte
 long    4 Byte  一般是4个 compiler不同可能不同
 long long  8 Byte
 
 *小数数据类型
 float   4 Byte
 double  8 Byte
 
 bool  1 Byte   因为地址只能索引到Byte级别 0表示false， 其他表示true
 
 */
void variable(){
    int variable = 8;
    cout << variable << endl;
    
    unsigned int v2 = 8;
    cout << v2 << endl;
    
    char v3 = 63;
    cout << v3 << endl;
    // 并不像java和Python，我们就是可以把63赋值给v3，并不会报错的。这在python中不存在的
    // 但是不同的是，在调用函数cout的时候， 由于v3是 char形的，所以cout会把63转换成char来输出，因此输出的是 “？”。
    // 这是还是那个问题，不管你v3 = '?'，还是v3 = 63， 本质上存在内存里的内容是一样的，但是函数使用的时候，会分类讨论，导致结果的不同
    
    float v4 = 5.5f;
    double v5 = 5.5;
    cout << v4 << endl;
    
    // sizeof 函数可以查看内存空间
    cout << sizeof(v4) << endl;
    cout << sizeof(v5) << endl;
    
    
    
}


