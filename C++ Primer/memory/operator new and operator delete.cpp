#include <iostream>
#include <string>
#include <cstdlib>
/*
 * *********************** new 和 delete的工作原理  **************************
 * new的工作流程
 * 1. 调用名为operator new（或者operator new[]）的标准库函数
 *      该函数分配 足够大，原始的， 未命名的内存！
 * 2. 编译器运行相应的构造函数，在原始内存中构造对象，传入初值。
 * 3. 对象被分配了空间并构造完成，返回一个指向该对象的指针
 *
 * delete的工作流程
 * 1. 对指针指向的对象或者数组中的元素执行析构函数
 * 2. 编译器调用operator delete（operator delete[])的库函数释放内存
 *
 * 我们可以自定义new和delete的操作，这时候，编译器会采用我们自定义的版本，而不是编译器的版本。
 * new和delete可以是成员函数！因此我们可以指定某个类的分配和释放内存的方法。
 *
 * new和delete的匹配机制和一般重载函数的匹配机制差不多。
 * 优先使用当前类内（父类）内的delete或new操作，而后全局搜索，最后才选择标准库的版本的。
 * 当然我们也可以指定版本
 *
 */

/*
 * ******************** operator new 和 operator delete 接口  ***************
 * operator new 和 new 表达式的区别：
 * operator new接口只是new表达式所实现的流程中的一环而已，operator new做的只是分配内存，而new所做的是
 * 1. 分配内存，
 * 2. 在分配的原始内存中构造对象，
 * 3. 返回内存地址。
 * 的一整套流程。
 * 而operator new做的只是步骤1.
 *
 * 我们能重载的只是operator new，而不能重载new表达式，也就是说，我们只能自定义分配内存的方法，却不可以改变
 * new的整改流程。
 * 同理，operator delete 和 delete表达式也是这个道理。
 *
 *
 * *********************** operator new 和 operator delete的重载  *****************************
 * // 可能会抛出异常
 * void *operator new (size_t);
 * void *operator new[] (size_t);
 * void *operator delete(void*) noexcept;
 * void *operator delete[](void*) noexcept;
 * // 不会抛出异常
 * void *operator new (size_t, nothrow_t&) noexcept;
 * void *operator new[] (size_t, nothrow_t&) noexcept;
 * void *operator delete (void*, nothrow_t&) noexcept;
 * void *operator delete[] (void*, nothrow_t&) noexcept;
 *
 * operator new使用注意事项：
 * 1. 自定义版本必须位于*全局作用域*中或者*类作用域*中
 * 2. 隐式的就是static的，无需声明（但是声明了也不会有错）。
 *      因为operator new 和 operator delete的调用，在obj构造前和销毁后，因此必须是static（否则对象不存在的时候是没法调用成员函数的）
 *      但也因为是static的，operator new和operator delete的也不可以操控任何数据成员（其调用的时候，一定是任何成员变量都不存在的时候）
 * 3. operator new（[]）的返回类型必须是void*，第一个形参必须是size_t，且该形参不得有默认实参，size_t表示所需开辟的内存的大小！
 *      如果是对象，则是对象所需字节数，如果是对象数组，则是数组所需字节数。
 * 4. operator new 可以提供所需的额外的形参，此时用到这些自定义函数的new表达式必须使用new的定位形式。
 * 5. 永远不可以重载 void *operator new (size_t, void*); 这个形式是专门给标准库来使用的。
 *
 * operator delete 使用注意事项：
 * 1. 返回类型必须是void， 第一个形参必须是void* 。 形参void*用来传递待释放内存的指针
 * 2. 当operator delete（[]）是成员变量的时候，需要包含另外一个形参，size_t, 该形参的初始值是第一个形参所指对象的字节数。
 * 3. 继承体系中，如果基类有个虚析构函数，则传递给operator delete的字节数将因待删除指针所指对象的动态类型不同而有所区别。
 *      实际运行的operator delete函数版本也会由于对象的动态类型决定。
 *
 */


/*
 * *********************  malloc函数与free函数  *******************************
 * 从c继承过来的分配和释放内存的较为底层的函数，在 cstdlib 中
 * void *malloc(size_t size);
 * void free(void *ptr);
 *
 * malloc 接受一个待分配字节数的size_t， 返回指向分配空间的指针，或者0（nullptr)表示分配失败。
 * free 接收一个void*， 他一定是malloc返回的指针的副本！这意味着free只能free malloc所分配的内存，对于stack上的内存是不可以被free释放掉的、
 *      free(0) 没有任何意义
 *
 */
void *operator new (size_t size)
{
    if (void *mem = malloc(size)) { // C++ 中， if中如果使用赋值语句，会将赋值语句的结果作为条件
        return mem;
    } else {
        throw std::bad_alloc();
    }
}

void operator delete(void* mem) noexcept          {
    free(mem);
}

/*
 * *******************************    定位new表达式   *********************************
 * 定位new指的是给new一个地址，让new在该地址上构造对象的方法就是定位new！ 其功能就是在原始内存上构造对象
 * 定位new的方法是极其灵活的，可以在任何地址上构造对象！
 *
 * 定位new的使用方法：
 * new (place_address) type;  // 只有指针实参的时候，是不分配内存的
 * new (place_address) type (initializers);
 * new (place_address) type [size];
 * new (place_address) type [size] {braced initializer list};
 *
 * operator new 与 allocator的allocate成员相似，都是只负责分配或者释放内存，并不会构造和销毁对象！
 * 既只负责和系统要资源，并不会初始化任何东西。
 *
 * 但是与allocator不同的是，
 * allocator::construct(ptr, 构造函数的入参列表) （其中ptr是allocator::allocate(size_t); 返回的ptr）
 * 可以在原始内存上构造构造对象。 但 operator new返回的指针不可以直接调用constructor在其上构造。
 *
 * 我们只能使用定位new表达式来构造对象，因此可以这么说
 * allocator::allocate(size_t) 和 allocator::construct(place_address， initializer); 是一对的
 *
 * operator new(size_t) 和 new (place_address) type (initializer)是一对的
 * 前者负责分配内存，后者负责在分配的内存上构造object。
 *
 * 注意：
 * construct的指针必须指向同一个allocator分配的内存，但是定位new不需要，new甚至无需指向operator new分配的内存
 * new甚至不需要指向动态内存上！
 *
 *
 * **********************  显示调用析构函数  ***********************
 * 不管是operator new 还是 operator delete 只是操控内存，并不销毁对象，因此不会执行构造与析构。
 * 因此如果需要调用operator delete前，需要对对象进行析构，我们可以显示的调用析构函数。
 *
 * 析构函数的显示调用和调用对象的成员函数没有任何区别。
 * 既可以利用对象直接调用，也可以利用指针或者引用，
 *
 * string *sp = new string ("aa");
 * sp->~string();
 *
 * ************************  使用流程汇总  **************************
 * 因此一个完整的使用流程应该是：
 * 1. operator new 来获取一段raw memory
 * 2. placement new 在这个raw memory上构造对象（只有placement new才能咋operator new分配出来的内存中构造对象）
 * 3. 使用完毕后，必须显示调用对象的析构函数，operator new出来的内存是不会自动调用destructor的
 * 4. 调用operator delete 来释放 raw memory
 *
 * ****** 注意 ******
 * 不管是析构还是构造函数，都不会分配内存，同时不管是operator new 还是 operator delete也都不会构造对象，只会和系统要内存空间而已。
 *
 *
 */




int main ()
{
    int arr[2] = {11, 22};
    int *arrPtrForm = arr;
    int **pArr = &arrPtrForm; // 表示指向array的指针，这里array本身就是个int*，那么指向arr的ptr就是int **pArr
    std::cout << pArr << std::endl;
    std::cout << &arrPtrForm << std::endl;
    std::cout << arrPtrForm[1] << std::endl;
    std::cout << (*pArr)[1] << std::endl;

    void *p = operator new(100); // 开辟一个100的内存
    new(p) int (7); // 第一个四字节上初始化7
    new((int*)p+1) int (100); // 第二个四字节上初始化100
    new((int*)p+2) int [3] {1,2,3}; // 第3到5 个四字节上初始化1,2,3

    int *intp = (int*)p;
    for(int i = 0; i < 5; i++) {
        std::cout << *(intp+i) << std::endl; // 打印
    }
    using namespace std;
    std::string *ps = (std::string*)operator new(10); // 向系统要内存
    new(ps) std::string ("allen");                      // 在原始内存上构造对象
    std::cout << *ps << std::endl;                         
    ps->~string();                                         // 析构string
    std::cout << *ps << std::endl;                         // string的析构并没有干什么，只是把内存权限给了系统，内存并没有擦除！
    operator delete(ps);                                   // 将内存还给系统

}
