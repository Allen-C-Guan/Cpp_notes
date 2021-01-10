# include <iostream>
# include <string>
using namespace std;

/*
                                **** c++中的copy  ****
 在我们使用 “=” 和 作为传入参数的过程中，我们always copy！ 在java和python中，primtive和string会copy，obj会自动引用。
 其的copy，主要包括：
     int b = a;
     Play p1 = p2;
     struct vector1 = vector2;
     甚至是：
     int* ptr1 = ptr2;
    以及： void foo(Entity e){}; 中的e，就是copy来的
 
 但是第四个和前三个不同的在于，第四个copy的是pointer，虽然ptr1和ptr2存放在不同的memo中，但内容是相同的。
 因此 *ptr1 和 *ptr2 指向的是同一个地址。
 这只是pointer 的copy，并不是obj的copy。
 
 我们就可以利用第四个方法，来减少obj的copy。因为obj一般要远大于pointer。

 /******* new comments **************
 shadow copy（默认的copy函数）只会存在对成员变量进行比特级别对copy而已，对于static variable或者ptr内的数据，是并没有进行copy的。
 当然这也是合理的，因此instance本身在内存中就是一段连续的内存单元，其中存放的仅仅是instance的成员变量，不包括类变量。那么shadowcopy
 不过就是把这片内存单元进行的copy而已。

 shadow copy的作用范围和const 函数的约束范围是一样大的。
 
 
 /* end new comments
                        **** c++中的deep copy与shadow copy ****
 deep copy与shadow copy最大的不同在于当被copy的instance中存在pointer的时候。
 对于shadow copy而言， 他copy的不过就是pointer。而不是内容。这就会导致2个pointer指向同一个instance。
 而deep copy 就会做到copy内容，

 /* new comments
 deep copy 实现的方法为（当涉及到ptr的时候，ptr指向的为止为new出来的内存空间时 deep copy和shadow不同）：
     1). 用copy constuctor new一个新的空间出来，然后把other的内容，拷贝到这个新的空间内，这时候就会创建出来一个新的位于不同内存空间上
     的但内容相同的instance。 而不是copy pointer！
            Class_name (const Class_name& other){}; // 这里的传入参数必须是const reference！！！！！
 
     2). 新建的方法和constructor中对instance的初始化的方式基本相同。

 /* end new


 deep copy使用注意：
    1). copy（不管是deep还是shadow）会发生在 “=” 和 作为函数的传入参数的时候。
    2). 如果你写了copy constructor，则在使用 “=” 进行赋值和作为函数的传入参数的时候，就会自动的调用deep copy constructor。而不是shadow copy.
    3). 如果你禁止当前instance的复制，需要在class中， 让 copy constructor 的声明 = 0；
    

 deep copy的办法和java中相同。
 
 */


class String{
private:
    char*  m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string){
        m_Size = strlen(string);   // 查string的长度
        m_Buffer = new char[m_Size+1];  //开辟新的空间
        memcpy(m_Buffer, string, m_Size);   // memcpy(des, source, size)。对内容进行复制。
        m_Buffer[m_Size] = 0; //最后一位置0
    }
    
    /*
     copy constructor for deep copy
     copy constructor 会在你使用 “=” 的时候使用
     */
    
//  String (const String& other) = delete;     = delete可以防止copy！！
    String(const String& other)
    : m_Size(other.m_Size)
    {
        m_Buffer = new char[m_Size+1];  //开辟空间
        memcpy(m_Buffer, other.m_Buffer, other.m_Size+1); //copy
        cout << "copy is finished" << endl;
    }
    
    
    
    friend ostream& operator<< (ostream& stream, const String& string);
    //friend 就是说，只有我声明的这个函数，才能看到我的隐私。
    
    
    ~String(){
        delete[] m_Buffer;
    }
};

//overloading 一下，
ostream& operator<< (ostream& stream, const String& string){  //引用ostream， override ostream， return ostream
    stream << string.m_Buffer;
    return stream;
}


// 在作为传递参数的时候， obj仍然会自动运行copy constructor来创建一个新的String instance 叫做string. 因此我们要带上& 来减少copy
void PrintString(const String string){
    cout << string << endl;
}

void RefPrintString(const String& string){
    cout << string << endl;
}



void CopyTst(){
    int a = 4;
    int b = a; //这里b就是一个a的copy， a和b有两个不同的内存地址，这是特点同样适合class和struct。
    
    String string = "Allen";
    cout << string << endl;
//    String s2 = string;
//    cout << s2 << endl;
    /*
    String s2 = string;
    这么用就完了，流程是这样的。
    1. shadow copy
     shadow copy，仅仅是把string这个class中的所有成员变量都copy过来。即： s2 = string  在s2中 char* m_Buffer = string.m_Buffer; 这时候问题就已经暴露了，这意味着两个pointer 指向一个memo address。
    2. 但是一旦该函数运行完毕，这就意味着两个obj都要被销毁，可是在销毁的过程中，先销毁了string，那么对应的buffer就已经被free了
     可在删除s2的时候， s2的指针也要删除s2，可发现这个内存区域已经被释放了。 这就炸了啊。
     */
    
    
    // deep copy 在使用 “=” 的时候, 和传递参数的时候会自动调用
    String s_deepCopy = string; //
    
    cout << "\ntest for parameters with out reference" << endl;
    PrintString(string); //每次传入都copy就很无聊。
    
    cout << "\ntest for parameters with reference" << endl;
    RefPrintString(string); // 这就没有copy了
    
    //ref的普通用法
    String& ref_s = string;

    
}   //程序运行到这里的时候，才暴露出来。
