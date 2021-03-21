#include <iostream>
#include <memory>
/*
 * ***************  动态数组  *********************
 *
 * 动态数组指的是：通过new和delete，一次性在动态内存（heap）中分配和释放多很多元素的内存所获得的
 * 数据类型。
 * 我们初始化动态数组有两种方式
 * 1. 用new和delete + [] 的形式获得
 * 2. 通过allocator来获得
 * 其两种方式最大的不同在于是否捆绑分配内存与构造操作，以及销毁操作和释放内存操作
 *
 * ****************** new和数组 *******************
 * 使用方法：
 * int *pArray = new int[10]; // 未初始化
 * int *pArray = new int[10](); // 值初始化
 * Foo *pf = new Foo[10]; // 默认初始化，自定义类，一定会调用默认构造函数，且调用10次！
 * string *pst = new string[10]{"a", "b", "cddg"}; // 列表初始化
 *
 * 分析：
 * 1. new + []的形式获得数组，返回的是元素类型指针，而不是数组！！
 *      a).与静态数组不同的是，静态数组你得到就是数组，而不是首元素，更不是首元素指针
 *      ie. int intArray[10]; // intArray就是个实实在在的数组
 *          intArray[0] = 5; // 因此你可以使用数组的下标操作符
 *
 *      b).动态数组你获得就是首元素的元素指针，而不是数组
 *      ie. int *pArray = new int[10]; // pArray真的就是非常存粹的int指针！！
 *          pArray[3]; // 虽然你也可以这么用，但是这是因为c++指针操控和数组操控是一样的
 *                      // 但这并不意味着pArray的类型和intArray的类型一致。
 * 2. 分配一个空的动态数组是合法的！
 *      即： int *pi = new int[0]; // 动态数组可以分配一个空的数组。但不能解引用
 *     
 *
 * *****************  delete 和数组 ********************
 * delete [] p; 
 *  // pointer前面要加上[]，让编译器知道被删除的是个数组！因为p的类型是元素类型指针！编译器无法区分
 *
 *
 * *****************  智能指针和动态数组  ************
 * unique_ptr给我们提供了存放动态数组的接口。被unique_ptr托管的数组，可以直接使用下标操作符，
 * 并在release()的时候，自动调用delete[] 来销毁数组。
 * 
 * shared_ptr 与 unique_ptr不同！shared_ptr 不接受数组类型，不提供下标操作符，
 * 也不会自动调用delete[]来删除动态数组。
 * 因此我们只能传入元素指针类型，并自定义deleter，且用get()获取原始指针，并用对原始指针偏移的
 * 方式操作数组。
 */

int main ()
{
    // ************ new 与 delete的动态数组 ************
    int n = 0;
    int *pArray = new int[n];
    // 这么用是合法的！且可以把其当成end() 指针，用p是否等于end来判定是否继续循环是安全的
    for (int *p = pArray; p != pArray + n; p++) {
        // TODO something
    }

    // ****** 动态数组和unique_ptr *******
    std::unique_ptr<int[]> uIntPtr (new int[10]);
    uIntPtr[4] = 5; // 直接使用下标操作符
    uIntPtr.release(); // unique_ptr被释放的时候，会调用delete[]， 而不是delete

    // ***** 动态数组与shared_ptr *******
    std::shared_ptr<int> spIntPtr(new int[10], [](int *p){delete[] p;});
    // 类型是int，而不是int[], 自定义deleter！
    *(spIntPtr.get() + 5) = 10; // 用get()获取原始指针，指针偏移获得对应元素

}