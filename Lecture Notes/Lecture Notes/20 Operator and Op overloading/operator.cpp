# include <iostream>
using namespace std;



/*
 operator就是overloading:
 功能：即通过对operator进行overloading的方式的，重新定义operator的作用。
 
 什么是overloading： overloading与override最大的区别在于：
    1. overloading 要求 signature必须不完全相同!!!!
    2. overriding 要求 signature必须完全相同!!!!
 
 常用operator的overloading： +, -, *, /, ==, !=， 等
 
 重载运算符的限制：
     1、!!!重载操作符不能改变他们的操作符优先级!!!
     2、重载操作符不能改变操作数的个数；
     3、只有C++预定义的操作符才可以被重载；
     4、对于内置类型的操作符，它的预定义不能改变，即不能改变操作符原来的功能；
     5、除了对（）操作符外，对其他重载操作符提供缺省实参都是非法的；
 
 */
struct Vector{
    float X, Y;
    
    Vector(float x, float y)
    : X(x), Y(y){}
    
    Vector Add(const Vector& other) const{  // 第一个const，因为是引用，要保证第一个引用过来的obj的安全，第二个const是保证自己的安全
        return Vector(X + other.X, Y + other.Y);
    }
    Vector Multiply(const Vector& other) const{
           return Vector(X * other.X, Y * other.Y);
    }
    
    //operator overloading
    Vector operator + (const Vector& other) const{
    return Add(other);
    }
     
    Vector operator * (const Vector& other) const{
    return Multiply(other);
    }
    
    // equals
    bool operator == (const Vector& other) const{
        return X == other.X && Y == other.Y;
    }
    // not equals
    bool operator != (const Vector& other) const{
        return !(*this == other);
    }
    
    
    
};



/*                  ****  overload<<  ****

 该方法通过对 << 的overloading，让自己定义的instance也可以根据自己的需求，打印出来！这是作为print输出的重点！！ 非常重要！！建议直接背下来。
 
 什么是stream: 在c++中， stream是一种输出方式，即将待输出信息存在buffer中，待需要输出的时候，以流（挤牙膏）的方式，
    把buffer中的内容，挤出到console中输出出来。
 
 理解要点：
    1). 传入参数 std::ostream& stream: 其作用是将 std::cout 赋值给stream 这个obj。
    2). stream << vector.X << " ," << vector.Y; 是将待输入内容，全部缓存在当前的stream的buffer里面。
    3). return stream。 即以流的形式，返回存储了待输出数据的buffer，当调用的时候就会输出在concole里。
*/
std::ostream& operator<< (std::ostream& stream, const Vector& vector){ //overloading
    stream << vector.X << " ," << vector.Y;  //设置stream
    return stream;                           //返回stream
}



void Operater_tst(){
    Vector position(4.0, 4.0);
    Vector speed(0.5, 0.5);
    Vector powerup(1.1, 1.1);
    
    Vector result = position.Add(speed.Multiply(powerup));  // position + (speed + powerup)
    //这种写法就很难懂，但是在java和python里，这是唯一的选择，你只能这么写，虽然注释里的方法看起来更好
    
    Vector result2 = position + speed * powerup;
    /*
     *** 这里调用的时候等效于 speed.*(powerup)  *是个speed的函数，*后面自动作为传入参数了  ** 省略了. 和（）
     */
    //这个方法就很牛逼了
    //overloading 的同时， c保留了原来operater的优先级顺序。 这让operator使用的更加合理和方便。
    
    
    // 对<<的overloading     toString()
    /*
     这里，因为std::ostream 没有overload如何去输出你自己定义的东西，那怎么办呢？ 我就要复写这个函数，和java复写toString 一样，
     套路就是上面固定的套路。
     */
    cout << result2 << endl;
    
    // overloading ==     equals()
    
    bool isEqual = result == result2;
    cout << isEqual  << endl;
    
    
}
