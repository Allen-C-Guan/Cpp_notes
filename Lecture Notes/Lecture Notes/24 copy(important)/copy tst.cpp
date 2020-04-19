# include <iostream>
# include <string>
using namespace std;

/*
 在我们使用 = 的过程中，我们always copy！ 在java和python中，primtive和string会copy，obj会自动引用
 int b = a;
 Play p1 = p2;
 struct vector1 = vector2;
 甚至是：
 int* ptr1 = ptr2;
 
 但是第四个和前三个不同的在于，第四个copy的是pointer，虽然ptr1和ptr2存放在不同的memo中，但内容是相同的。
 因此 *ptr1 和 *ptr2 指向的是同一个地址。
 这只是pointer 的copy，并不是obj的copy。
 
 我们就可以利用第四个方法，来减少obj的copy。因为obj一般要远大于pointer。
 */


class String{
private:
    char*  m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer, string, m_Size);   // memcpy(des, source, size)
        m_Buffer[m_Size] = 0; //最后一位置0
    }
    
    /*
     copy constructor for deep copy
     copy constructor 会在你使用=的时候使用，这是c++自带的一种constructor
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
    1. copy
     copy会把string中的所有成员变量都copy过来。即： s2 = string  在s2中 char* m_Buffer = string.m_Buffer;
     这时候问题就已经暴露了，这意味着两个pointer 指向一个memo address。
    2. 但是一旦该函数运行完毕，这就意味着两个obj都要被销毁，可是在销毁的过程中，先销毁了string，那么对应的buffer就已经被free了
     可在删除s2的时候， s2的指针也要删除s2，可发现这个内存区域已经被释放了。 这就炸了啊。
     */
    
    
    // deep copy 在=的时候, 和传递参数的时候会自动调用
    String s_deepCopy = string; //
    
    cout << "\ntest for parameters with out reference" << endl;
    PrintString(string); //每次传入都copy就很无聊。
    
    cout << "\ntest for parameters with reference" << endl;
    RefPrintString(string); // 这就没有copy了
    
    //ref的普通用法
    String& ref_s = string;

    
}   //程序运行到这里的时候，才暴露出来。
