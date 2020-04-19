# include <iostream>
# include <cmath>
using namespace std;
int array() {

// 初始化array的方法
    // 方法一，声明的时候就直接花括号赋值
    int luckyNum[] = {4,5,6,7,8,57,34};
    cout << luckyNum[4] << endl;
        // 更改内容
    luckyNum[4] = 10000;
    cout << luckyNum[4] << endl;
        //如果你超过index的最高限度，仍然可以输出，并不会像java或者python报错。输出的是内存里的内容。就不知道是啥了。
    cout << luckyNum[10] << endl;

    //方法二，声明的时候，给出size的大小，这时候，这20个连续内存空间里面，被赋值的有值，没被赋值的就是0
    int unLuckyNum[20] = {0,1,2,3,4,5,6,7,8,9};  //这里 前10个cell里面就有值，后面的就都是default number 为0。
    cout << unLuckyNum[15] << endl;  // 15没被赋值，就是0
    cout << unLuckyNum[5] << endl;

    return 0;
}
