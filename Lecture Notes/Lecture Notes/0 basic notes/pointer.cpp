# include <iostream>
using namespace std;

//pointer只是另一种data形式而已，和int char 一样，其存放的是地址。


int pointer(){
    int age = 18;
    /*
     * 重点在这里，指针变量的命名必须以*开始，而声明的变量类型，必须是指针所指向的变量的类型。例如这里 age是int，那么指针的类型就必须是int
     * 命名的方式通常是 *p+变量名, 而这里p+变量名就是这个地址变量的变量名，并不包含*，只有初始化的时候才有变量名。
     */
    int *pAge = &age;

    string name = "Allen";
    string *pname = &name;

    double GPA = 3.2;
    double *pGPA = &GPA;

    // 获取memory address 的方法
    // address就是pointer

    cout << "age: " << & age << endl ;
    cout << "name: " << & name << endl;
    cout << "GPA" << & GPA << endl;

    cout << "\npointer test" << endl;
    cout << pAge << endl;

    /*
     * dereference
     * 将地址对应的内容拿出来
     * 对*的理解， *是一个运算符，表示将address转换为内存中的内容，*pname 表示的是，把pname对应的地址转换成里面存储的内容，然后把该内容
     * 变成int类的数据  就是那么就得到了数据
     *
     * 因此可以简单的理解为 *是&的逆运算
     */
    cout << "\ntest dereference " << endl;
    cout << *pAge << endl;

    cout << *&age << endl;


    // 我们还可以定义一个没有null pointer
    void *nullPointer = NULL;






    return 0;
}
