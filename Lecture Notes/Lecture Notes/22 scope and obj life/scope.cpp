# include <iostream>
using namespace std;

/*
                                **** scope  ****
 
 通常情况下，在stack上的内容都会有一个scope， scope可以是一个{}, if, for, function
 scope的作用
 1. 内容的自动消除：所有在内部初始化的一切，随着scope的结束，全部被消除.
 2. 对于return而言，如果你instance一个stack的内存空间，并return这个内存空间的pointer，这也是无用的。 但是如果return的是个instance，还是可以的。
 */





//              *****  在scope中分配内存，并以pointer来返回的证明和解决办法  ****

// stack 中的初始化的array，如果以pointer来返回的话，也没什么卵用，见光死
int* WrongCreateArray(){
    int array[40];  //这其实没有任何意义，因为你在括号里面初始化的，array一旦出了括号，就没了，所以返回的时候就已经没掉了
    array[0] = 6868;
    return array;
}



//                              **** 解决方法 *****：
// heap 初始化，
int* NewCreateArray(){
    int* array2 = new int[40];
    array2[0] == 7777;
    return array2;
}

//引用法 在外面定义
void RefCreatArray(int* array){
    array[0] = 100;
}




/*
                            ****  自定义的scope pointer ****
 原理： 利用一个scope下实例化的instance来存放new返回的pointer， 并且该instance会在自我销毁前，先释放pointer对应的instance。
 
 其实现主要依赖两个要素
 1. 在stack上initialize的pointer instance来存放new返回的instance的address。
    ie：
    //constructor来存放
    ScopeInstance(Class_name* ptr) :m_ptr(ptr){};
    
    //initialize
    ScopeInstance i = new Class_name();   // new返回的是class_name类型的pointer。
 
 2. 并且该pointer instance的destructor可以delete该instance。
    ~ScopeInstance(){delete m_ptr;}            //destructor中的delete来删除这个pointer。
 */




class Entitys{
public:
    Entitys(){cout << "Entity is created" << endl;}
    ~Entitys(){cout << "Entity is destoried" << endl;}
};




class ScopeEntity{
private:
    Entitys* m_e;
public:
    ScopeEntity(Entitys* e)
    : m_e(e){
    }
    
    ~ScopeEntity(){
        delete m_e;
    }
};





// ——————————————————————————————————————————  test ——————————————————————————————————————————————————————
void ScopeTst(){
    int* stackArray = WrongCreateArray();
    cout << stackArray[0] << endl;   //你看我在里面明明已经给了array[0] 赋值了6868，出来就没了。

    int* newArray = NewCreateArray();
    cout << newArray[0] << endl;

    int refArray[40];
    RefCreatArray(refArray);
    cout << refArray[0] << endl;
    
    
    {
        ScopeEntity e = new Entitys();
    }
    
}


