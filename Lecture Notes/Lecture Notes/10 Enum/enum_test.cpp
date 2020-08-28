# include <iostream>
# define LOG(x) cout << x << endl
using namespace std;

/*
 enum的主要作用和java相同。用struct的模式来操控数字。让数字成为一种 *只可以通过选择* 来确定的 *type*。而不是数字！
 
 1.用可读性比较强的type，来代替 **整数***！注意是type，不是数字，也不是变量，是type！
 2.规范户填写的内容，比如星期，你不能随便写啊。没有星期10啊
 
 enum可以放在class里面，成为class中的 *类变量*
 
 
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



class Enum_test{
public:
    enum Grade{  //在class中的enum可以当成。*类变量* 来使用偶
        H1 = 80, H2 = 70, H3 = 60,
    };
};

void Enum_test(){
    WeekDay today = Tusday;
    cout << today << endl;
    
    //enum在class中的使用
    cout << Enum_test::H1 << endl;
    
}

