# include <iostream>
# define LOG(x) cout << x << endl
using namespace std;

/*
 enum的主要作用和java相同，其主要是为了利用可读性比较强的名字，来代替magic number！
 
 
 默认的情况下enum会给予32位，我这里可以明确他的类型，这里我明确了A，B，C的类型都是unsigned char
 但是这个种类，必须都是整数类型的，整型数据主要有char  int, long 等 还可以被unsigned修饰。
 */
enum WeekDay : unsigned char{
    Sunday = 0, Monday, Tusday, Wednsday, Thursday, Firday, Saturday,
    /*
     默认的情况下， A, B, C 的值从0开始，根据定义的顺序，里面存放的是int的值，默认从0开始，后面依次加1，
     如果你定义了A = 5， 那么B和C就都默认是6 和 7
     
     */
};


void Enum_test(){
    WeekDay today = Tusday;
    cout << today << endl;
    
}

