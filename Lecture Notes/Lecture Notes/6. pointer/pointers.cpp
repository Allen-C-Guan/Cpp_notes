# include <iostream>
using namespace std;
# define LOG(x) cout << x << endl

/*
 pointer不过就是一个地址而已，而这个地址不过就是个整型数据而已
 */
void pointer_test(){
    /*pointer的类的作用
    pointer本身和类没有任何关系，而type的作用只是让编译器知道当前地址下存放的是什么类型，我要按着相应类型的数据来解析和提取而已罢了。
    至于类型是double还是int，只要物理地址相同，这都不影响这个pointer的值，
    */
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
