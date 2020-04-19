#include <iostream>
#include <array>
#include <string>

using namespace std;

/*
 在c里面， 2D array是 一个array里面存放的是下一维度的array的地址。
 */
void twoDArrayTst(){
    //1D array
    int* array = new int[50];  //这里我们实际上分配了50个int的大小的连续内存
    
    //2D array
    int** array2D = new int*[50];
        /*拆开看， int*  *array2D， 其中 *array2D是个pointer， int* 表示你要返回的也是pointer，
         这个pointer是指向array2D的pointer。
         即 pointer -> pointer of int array
         
        这里我们只是分配了50个pointer的内存的大小而已,int指的是pointer指向的是int type的数据。因此array的第一维度就是50.
        第二维度的内存还没有分配呢。
         
        下面的例子能很好的证明
         */
    
    array[1] = 0; //这里说的是int
    array2D[1] = nullptr; //这里说的是ptr
      
    /*
     这里还有一个new的关键点，new的时候，只是分配内存而已，至于你之后用这个内存存什么，其实并不重要。type的用途也仅限于计算所需内存而已。
     */
    
    
    
    
    //2Darray第二维度的赋值
    for (int i = 0; i < 50 ; i++) {
        array2D[i] = new int[20];   //ptr 配 new 一定要记住这个
    }
        
    
    
    //3Darray的赋值
    int*** array3D = new int** [50];   //第一维度  int** 得到的是指针的指针array
        
    for (int i = 0; i < 30 ; i++){      //第二维度
        array3D[i] = new int* [30];      //每一个array的成员都是ptr，都可以直接匹配new。 int*得到的是指针array
        for (int j = 0; j < 20; j++) {   //第三维度
            array3D[i][j] = new int[20];
        }
    }
        
    array3D[0][1][2] = 100;
    
        
    
    
    /*delete array
     delete array的顺序一定是从内向外delete的，因为是pointer的关系，（链表），如果把最外环删除了，内环就再也找不到了
        */
        
    for (int i = 0 ; i < 50; i++) {  //先删除内环
        delete[] array2D[i];
    }
    delete[] array2D;               //在删除外环
    
    
    
    
    /*
     通过array的工作原理我们可以发现，获取array中的某个元素，并不可以通过O(1)的时间复杂度来完成，因为你先要找x，在再x里找y。
     这就很慢啊。
     而且这样memo变得碎片化。
     
     因此我们可以把高维度array存在一维度array里面，然后给弄一个虚拟维度，通过虚拟维度来计算array的实际index。
     */
    
    
    
    
}
