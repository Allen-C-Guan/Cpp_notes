# include <iostream>
# include <cmath>
using namespace std;


/*
    重点！！！  在我们调用sayhi的时候，如果sayhi没有在前面出现过，就会报错，可是我们又想把sayhi定义在后面，我就可以用这个方法。
    我们只写一个signature， 并不写内容，这样，就如同

    int nums;
    nums = 5;

    一样 先声明 并不赋值，后赋值。
    这样 编译器就会把两个内容给联系起来了。
 */
void sayHi(string name, int age);



//有return的方法
double cube(double num){
    return num * num * num;
}

int function() {
    sayHi("Allen",45);

    cout << cube(4) << endl;
    return 0;
}

// sayHi 一定要写在前面，
void sayHi( string name, int age ){
    cout << "Hello " << name  << endl;
    cout << "you are " << age << endl;
}
