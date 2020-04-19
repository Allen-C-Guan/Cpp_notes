# include <iostream>
# include <string>
# include <stdlib.h>
# define Print(x) cout <<  x << endl;
using namespace std;

void PrintString(const string& str){
    cout << str << "   this is PrintString funciton " << endl;
}


void StringTst(){
    //方法一： 最原始的方法
    const char* name = "Allen";
    /*这里 const 是一种习惯，我们通常认为string并不可更改。所以加上const。  这种方法本质上和array一样,
    name 只是开头字母"A"的地址而已！！！
     
    那么计算机如何才能知道这个string到什么时候为止呢？
    在这个array里面， string 要以一个字节00， 作为截止，这样string在输出的时候，就会停在正确的位置上了。
    */
    Print(name);
    
    //如果我们真的用array来写string，也不是不行，但是一定要在最后加个0，
    char nameArray[5] = {'A','l','l','e','n'};
    Print(nameArray);
    
    
    char nameArray2[6] = {'A','l','l','e','n',0};
    Print(nameArray2);
    
    /*
     标准库
     标准库中，也是string函数也是有个constructor的， 传入参数是 const char* 和我上面定义的一样。
     */
    string standardName = "Allen";
    standardName.size();
    
    
    //字符串的相加
    //string foo = "Allen" + "Cecilia";  直接对字符串相加是不正确的， 因为字符串本身不过是两个const char的指针而已，指针怎么相加？？？
    string foo = string("Allen") + "Cecilia";
    Print(foo);
    //这是因为stringfunciton本身对+ 进行了overloading，可以把constr char pointer加在string后面，但是const char并没有这个功能
    //简而言之 constr char* + const char* 无效， string + const char* 有效。
    
    // finds
    bool contains = foo.find("len") != string::npos;  //这就是一个类，表示不合法的find结果。
    Print(contains);
    
    
    
    
    //string的传递
    /*
     如果我们对class进行传递，如果我们采用的方式为 type function(class obj){}，编译器将默认的给我复制一个obj,然后放到function 内部
     然而对于java或者python，默认的却是reference 因此在我们传递obj的时候要习惯的使用 reference避免copy，即
     type function(class& obj) {}
     
     而对于string，string也是obj，但是特殊的点在于string我们一般不允许更改，因此我么要写成
     type function(const string& message){}的形式
     */
    
    PrintString("ALLEN");
    
    
    
    
    
    
    
    //string literal（字符串字面量）
    
    
    
    Print("\nstring literal test")
    const char names[7] = "Al\0len"; //6个char + 一个结尾的0 7个字符
    Print(strlen(names));  //strlen是一个查看const char的长度的函数， 查看原理就是到零为止。
    Print(names);
    
    /*const的作用
     我们一定要加const，因为char array 一般被存放在只读存储区，最好不要改动。
     
     这是因为 如果我们采用pointer来定义char array，那么当我们操控这个string的时候，我们通过的是指针，这个指针在只读区，
     内容却受到了威胁，因此这在c中是没有定义的，就会报错。
    
    char* name_a = "ALlen";
    name_a[2] = 'K';  一运行到这里，就炸了，我们无法更改这个值，事情就进行不下去了。
    Print(*name_a);
     
    如果我们非要更改，那么我们只能通过使用char array而不是 string
    */
    char name_foo[6] = "Allen"; // 还是要多定义一个才行。
    Print(name_foo);
    
    /*
     其实所有的string都会被存在只读存储区域，但是不同的是，如果你定义为array，会把string copy下来然后操作，这就是不同。
     */
    
}
