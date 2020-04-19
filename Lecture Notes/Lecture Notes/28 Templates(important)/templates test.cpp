#include <iostream>
#include <string>
using namespace std;



/*template是一种让编译器在call的时候，先帮你写一个函数或者class的一个方法。在写之前，你可以给编译器几个参数，然后编译器会把对应的参数
 换成你想要的样子。
 这就是模版。这个模版是这对编译器而言的。
 */



/*使用方法1: 用于type变量
 template 在c++ 中， 和java中的generic 很像，可以自己定义一种type，从而让type变成一个变量。
 这样做的好处在于可以大量重复的去适用一个function来适应多种type，从而达到同一个功能使用，适用多种type。
 
 但是template在定义的时候是不存在的，只要在call的时候，template会根据type，马上新建一个新的funciton来使用。
 <>的用途是给模版传入信息
 
 */
template <typename T> // typename指的是，模版变量类型是type。
void Print(T message){
    cout << message << endl;
}


/*
 使用方法二：作为class的传入参数
 用在class上，让class的某些参数有巨大的灵活性。
 template 用来传递不确定的数或者变量。 这是因为template只有在call的时候才编译，我想让我的参数根据结果的不同，
 在每一次call的时候调整参数的值，重新写一个参数不同的class。
 比如我想根据之间计算的结果来决定创建的array的size的大小， 那你用int array[9]就不行。（这里的array是原生array）
 可以我可以用template <int size>来作为参数 int array[size], 这就是个变量了，只有call的时候才确定下来size是多少
 
 template使用的方法和function的传入参数是一样的，只不过把()换成<>
 */

template <typename T1, int size> // 模版变量类型是typename和int

class Array{
private:
    T1 m_Array[size];
public:
    int GetSize() const{
        return size;
    }
};



void TemplatesTst(){
    Print(1);
    Print("Allen");
    Print(4.6);
    
    Print<string>("HELLO"); //这就是上面的功能，string会传给T。其实我们不用给出，c++compile会认识hello是个string
    
    // <int>
    
    Array<int, 6> array;                     //
    cout << array.GetSize() << endl;
}
