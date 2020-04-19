# include <iostream>
# include <cmath>
/*
 * include 的作用是把我们指定的内容， 全部的复制粘贴到当前文件下
 *
 * 编译的过程：
 * 是把当前代码变成二进制机器代码，根据机器不同，编译的方法和结果也不同。
 */


using namespace std;
int input_and_output() {
    // variable
    string name = "Allen";
    int age = 28;
    cout << "hello," << name << age << endl;

    //type
    char grade = 'a';   //char必须用单引号！
    string name_ = "Allen";
    int age_ = 34;     //int正数负数均可以
    double GPA = 3.4;  //double 更多一点
    float foo = 6.5;
    bool isMale = true;



    // print
    cout << "Hello, World!" << endl; //这里 <<表示插入， cout 和 endl 表示 concle out 和 end line
    cout << "Allen ";    //如果不写endl的话，就不会换行 那么下面的hello就会继续输出下去

    //print中回车的使用方法
    cout << "hello" << endl;
    cout << "allen\n";    // \n也可以换行
    cout << "this is allen" << endl;

    //string的函数使用
    //length
    string name_tst = "Allen, guan";
    cout << name_tst.length() << endl;
            //这里就和python就本质上的区别，在c中，只有struct才有function，如果你直接用"allen".length()是不行的
            //因为"allen"是个常量！没有function
    // find
    cout << "find function test" << endl;
    cout << name_tst.find("guan",0) << endl; // find 第二个是开始搜索的index
    // substr
    cout << name_tst.substr(8,3) << endl;  // 从4开始，获取3个连续字符串



    //string中 index的使用
    cout << name_tst[1] << endl;  //在c里面，string也可以当list来索引
    name_tst[0] = 'C'; //也可以更改


    //number
    cout << 4 << endl;
    cout << 4 + 5.5 <<endl;
    int cnt = 5;
    cnt ++ ;
    cnt -- ;
    int inum = 3;
    double dnum = 4.5;
    cout << inum + dnum << endl; //整数和小数计算，得到的总是小数
    cout << 10 / inum << endl; //整数和整数计算，得到的总是整数，及时除不开 这里是10/3

    // cmath的使用
    cout << "\ncmath test " << endl;
    cout << pow(3,5) << endl;
    cout << sqrt(4.3) << endl;
    cout << round(8.5) << endl;   // 4舍5入的一种round的方法
    cout << ceil(4.3) << endl;    //向上取整
    cout << floor(4.3) << endl;   //向下取整
    cout << fmax(4, 5) << endl;
    cout << fmin(4,5) << endl;



    // input 的使用
//    //在这里，我们用cin的话，他就像光标一样，cin或一次性获取到全部的信息，用空格隔开，每次获取之后，光标会停留在当前位置，如果还要获取，就继续往后拿
//    //而getline则指的是光标后面的该行内容，我都要了
//    cout << "\ninput test" << endl;
//    int ages;
//    cout << "Enter your age: ";
//    cin >> ages;                //cin可以获取一般的例如char，int
//    cout << "Your age is: " << ages << endl;
//
//    string names;
//    cout << "enter your name: ";
//    getline(cin, names);  // getline通常用来获取string，既输入的一整行
//    cout << "Hello, " << names << endl;


    string this_name, this_age, this_department;
    cout << "enter a name: ";
    getline(cin, this_name );
    cout << "enter a age: ";
    getline(cin, this_age);
    cout << "enter a departement: ";
    getline(cin, this_department);
    cout  << this_name << this_age << this_department << endl;



    return 0;
}
