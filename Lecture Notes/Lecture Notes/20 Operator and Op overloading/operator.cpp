# include <iostream>
using namespace std;

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

//overload <<
ostream& operator<< (std::ostream& stream, const Vector& vector){ //overloading
    stream << vector.X << " ," << vector.Y;  //设置stream
    return stream;                           //返回stream
}

/**
 *************************************************************************
operator overloading 的精髓就在于 符号前省略了. 符号后省略了括号
  a * b = a.*(b)
  a -> b = a.->()   ->b
 */

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
