#include <iostream>

using namespace std;
/*
这里我们需要讲解一下struct在内存中的样子， struct在内存中，不过就是两个连续的int单元而已， 并没有一个区域，区域的开头写着
 vector， 后面跟着一些variable。 并没有，只有一些连续存储的变量而已。如果种类相同，你甚至可以把它当成array来对待。
*/
struct Vector{
    int x, y;
};



/*
 punning在做的事情不过就是， 把某一种type的 pointer， cast成另外一种pointer， 这样这个pointer所能控制的范围就变化了。
 然后通过对地址的解析， 我们就可以对那段内存进行操作了。
 
 */




void punningTst(){
    int a = 50;
    double value = a;       //这是个implicit操作，系统把acopy到value内存上，并cast成为一个double
    cout << value << endl;  // 一切都很正常
    
    /*但是我只是单纯的要copy 以a开头的内存地址后的一段内存，到value所属的内存上，我并不想cast， 这时候应该怎么做，借助指针完成
    例如a的地址为从&a开始以后4个byte都是a，可我想取a之后的8个字节，不管是啥，都拿出来。
     */
    
    //方法1:原始法
    double val = *(double*) &a;
    /*讲解一下， a的指针地址 &a 是一个4Byte的指针，我把它cast成8byte的指针，此时该指针的作用范围就成了8个byte。
     然后我在把这8个byte全拿出来。 就完成了任务
     */
    cout << val << endl;
    
    //实际是如何使用的
    Vector v1 = {4, 6};
    int* array = (int*) & v1;   //这里直接把struct给强行变成了int pointer， int pointer就可以当int array来使用了。
    cout << array[0] << endl;
    cout << array[1] << endl;
    
    
    
}
