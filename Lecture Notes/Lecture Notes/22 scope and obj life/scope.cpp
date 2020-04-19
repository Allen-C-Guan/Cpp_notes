# include <iostream>
using namespace std;

/*
 通常情况下，在stack上的内容都会有一个scope， scope可以是一个{}, if  for function， 这里面的一切，一旦出来了，就全部被清除了。
 */

// stack 中的初始化，没什么卵用，见光死
int* WrongCreateArray(){
    int array[40];  //这其实没有任何意义，因为你在括号里面初始化的，array一旦出了括号，就没了，所以返回的时候就已经没掉了
    array[0] = 6868;
    return array;
}

//heap 初始化，
int* NewCreateArray(){
    int* array2 = new int[40];
    array2[0] == 7777;
    return array2;
}

//引用法 在外面定义
void RefCreatArray(int* array){
    array[0] = 100;
}



void ScopeTst(){
    int* stackArray = WrongCreateArray();
    cout << stackArray[0] << endl;   //你看我在里面明明已经给了array[0] 赋值了6868，出来就没了。

    int* newArray = NewCreateArray();
    cout << newArray[0] << endl;

    int refArray[40];
    RefCreatArray(refArray);
    cout << refArray[0] << endl;
    
}


