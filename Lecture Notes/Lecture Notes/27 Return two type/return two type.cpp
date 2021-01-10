# include <stdio.h>
# include<iostream>
# include <string>
# include <functional>
# include <utility>
using namespace std;
/*
 在C中，我们是没有办法直接return两个不同类型的数据的。这在python里面是很容易的事情
 在C了里面，想要return多个。如果type相同的话，我们可以return一个array<type,size>，或者vector，
    (但是一定要用new来init，不然return以后就没了）
 如果type不同的话，我们不可以直接return string, int, float
 
 有几个比较简单的方法：
 1. 在函数外面init，函数中采用reference的方式传入参数， 这样就不用return了，
    优点：不需要copy，性能很好。
    缺点：看起来很蠢，要在外面先实例化好。可读性差。
 
 2. tuple
    这个算是最经常用的，他不在乎里面放的是什么，放的都是什么种类
    tuple通常要配合auto来使用，auto可以自动返回一个type。
 
 3. 自己写一个struct
    这个好处在于极大的增强可读性
 
 4. pair
 
 */

tuple<int, string, float> GetLable(){
    tuple<int, string, float> tstTuple(1, "Allen", 4.5);
    
    return tstTuple;
}


void ReturnTwoType(){
    
    //                       **** tuple test ****
    
    //传统使用tuple的构造函数。
    tuple <int, string, float> tup1(1,"allen", 9.6);
    //使用make_tuple 函数 和auto key words，auto会自动推测type
    auto tup2 = make_tuple("String", 3, 4.6);
    //获取tuple的元素。 auto element_name = get<index>(tuple_name) auto可以自动获取type类型
    auto tup_element = get<2> (tup2);
    //函数的返回
    tuple<int, string, float> tup3 = GetLable();
    auto tup4 = GetLable();
    
    //也可以用其他方法 using 或者typedef 来增强可读性。
    
    //using
    using label = tuple<int, string, float>;
    label tup5 = GetLable();
    
    //typedef
    typedef tuple<int, string, float> newLabel;
    
    newLabel tup6 = GetLable();

    
    
    //                      **** pair test ****
    pair<string, int> p1("Allen", 27);
    auto p2 = make_pair("Allen", 27);
    string name = p2.first;
    int age = p2.second;
    
    
    
}


