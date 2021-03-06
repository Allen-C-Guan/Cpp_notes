# include <iostream>
# include <array>
# define Print(x) cout << x << endl;
using namespace std;

//如果我要把一个standard array传入到一个function里面例如

template <int sizeOfArray>

void PrintStandArr(const array<int, sizeOfArray> array){
    for (int i = 0; i < sizeOfArray; i++){
        cout << array[i] << endl;
    }
}






void array_tst(){
    
    
    /*
                            ******   row array   ******
     
    定义： type name[size];   例如 int A[5];
    性质： array不过就是一个pointer， 指向了array的头部地址， index无非就是偏移地址。 因此如果偏移过头了，c++也不会阻止你。
    注意：
     
     1）c++不会对 out of range 进行限制。由于row array的索引方式是pointer向后偏移index个地址。
     2）array_name 本身是个pointer！！！ 这点很重要。
     3) row array 的初始化必须带着size，由于是静态array，初始化的时候要分配内存的size，因此一定要直接带size的。
     */
    
    int array[5];
    Print(array[0]);
    array[4] = 1000;
    Print(array[100]); //c语言中，由于array不过就是一个head address， 而head address即使超出了你申请的范围，c语言也可以执行，但是这种行为是非常可怕的。这意味着你改动了内存中不是你的内存的内容。
    Print(array); // 可以发现，这就是一个地址而已
    
    
    
    
    /*
     row array与pointer之间的互换使用：
     1) 直接把array赋值给pointer： int* ptr = array_name;
     2) 用pointer来代替array，读取和更改array中的项。   ptr[4] 和 array[4]得到相同的结果。
     3) 用* 来代替[]的作用: *(ptr+4)与 ptr[4] 或者 array[4]相同。
     4) row array是没有办法自动的获得array的size的，除非你自己记录这个信息。
     
     注意：pointer的加减计算，是内存地址的偏移，偏移量取决于type的size。例如 对于 int* ptr;  此时(ptr + 2) 是地址偏移了
        2 * typesize（int) 个 Byte;
     
     例子：
     */
    
    
    //array前面不用加&就可以直接赋值，就已经说明这就是一个地址
    int* ptr = array;
    //利用ptr对array进行输出
    Print(ptr[4]);  //这样用居然也行！！！
    
    //利用指针进行获取和更改
    *(ptr+4) = 88888;   //这里因为ptr的类型是int， 而一个int是4个字节，因此实际上ptr不是增加4，而是增加 4 * 4， 而这就是ptr中类的作用。
    Print(ptr[4]);
    
    Print("\ntest pointer")
    Print(ptr);
    Print(ptr+4);
    Print(*((char*)ptr+16))
    
    
    
    //用new关键词来初始化一个array
    // 上面的方法叫stack定义法， 这个叫做new定义法
    int* anotherArray = new int[5];
    anotherArray[0] = 10000;
    /*
     这种创建的方法和 int another = new int[5]使用起来是完全相同的， 但是生命周期不同，不使用new的关键词的周期只存在于{}之内， {}执行完了以后
     这个变量就被扔了。 但是new不同，new的对象可以一直保存到程序结束才会被释放。
     
     而当一个array想要从function里出来的时候（return array)，就必须要用new了，因为{}执行完了， array也就没了，你还return个屁啊。
     
     因此为了早点释放内存，我们需要使用delete，在不使用的时候就把内存释放出来
     
     */
    delete[] anotherArray;   //要带上[] 因为[]表示的是 array operator
    Print(anotherArray[0]);
    
    
    // size的获取
    //这个方法只适用于stack定义法， 而且不太稳定。
    int size = sizeof(array)/sizeof(int);
    //但是如果你用的new定义法， 那么这个方法不行，因为他返回的一定是pointer的大小，而不是array的大小。
    Print(size);
    
    
   
    
    
    
    
    //                      ********  使用标准库   ***********
    
    /*
     使用方法：
     1）初始化：std ::array <type, size> arrayName;
     2）获取元素： arrayName[index]; 与row array的方法相同。
     3) 获取size: arrayName.size();
     
     
     
     注意：
     1). standard array也不能阻止你out of range。
     2). 这个array仍然是在stack上运行的
     3). standard array的size，是通过template存入的，并不是维护的！
     
     */
    cout << "\n\n Testing standard array" << endl;
    
    ::array<int, 4> standardArray;
//    standardArray[0] = 0;
//    standardArray[1] = 1;
//    standardArray[2] = 2;
//    standardArray[3] = 3;
    // array.size()
    Print(standardArray.size());
    
    /*
     使用row array需要自我维护length，不然你就没法用，也甭想用。传统array不过就是个pointer，天知道你多大
     */
    int arrayOld[30];
    
    
    cout << "\ntest print Array" << endl;
    
    PrintStandArr  <standardArray.size()>  (standardArray); //通过tempale的方式来传递size大小！！
    
    
    
    
    
    
    
}
