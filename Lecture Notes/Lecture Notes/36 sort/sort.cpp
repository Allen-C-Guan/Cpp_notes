#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void sortTst(){
    
    /*vector sort
     vector sort中，利用的是vector自带的迭代器。
     */
    vector<int> values = {4,5,6,1,2,5,8};
    sort(values.begin(), values.end());
    
    
    /*
     lambda函数在sort中的作用。      和python中key的方式完全相同， 和java中的compareTo也相同
     默认的方式是有个cmp的函数，
     默认设置是 cmp 函数input是两个值， a 和 b， 若a < b 则为true， a > b 则为 false
     
     因此规则可以简化为：
     简单来说就是， a 和 b， 如果cmp返回的是ture， a在前， 返回的是false，b在前。
     */
    
    
    //逆向排序
    sort(values.begin(), values.end(), [](int a, int b ){return a > b;});
    
    
    
    /*自定义排序法  这个太牛逼了！！！
     这个思想主要就是通过自定义规则，来控制返回的true or false，从而控制排序的规则
     自定义排序有两种方法
     1. lambda function
     2. compare class  和map中的一样，是通过class中一个 override bool operator()的方式的function 来做到的！！！
     */
    
    sort(values.begin(), values.end(), [](int a, int b)
    {
        if (a == 4)    //这规则就直接让4永远在最后一位上。
            return false;
        else if (b == 4)
            return true;
        else
            return a < b;
    });
    
    //cmpclass
    
    cout << "compare class test" << endl;
    
    struct {
        bool operator ()(const int& a, const int& b) const{
            return a < b;
        }
    }myCmp;

    sort(values.begin(), values.end(), myCmp);

//    struct {
//        bool operator()(int a, int b) const
//        {
//            return a < b;
//        }
//    } customLess;
//    sort(values.begin(), values.end(), customLess);
    
}
