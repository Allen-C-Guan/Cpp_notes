#include <iostream>

using namespace std;

/*
 union 的功能是，对同一块内存区域，进行不同type的解释，可以解释为int，也可以解释为float等。但是同一块内存单元。
 这就是punning的功能啊， punning多蠢啊看起来，可是这种方法可读性就大大提高了。
 
 实际应用当中有什么作用呢？
     在实际的使用中，我们通常是为了让某个struct可以既以typeA输出，又可以以typeB输出。
     即同一个内容，只是输出形式不同而已的，这时候union可以就牛逼plus了
 
 但是在使用的时候就需要特别了解内存空间的分布，不然输出的肯定不对。
 */


struct Vector2D{
    float x, y;
};

struct Vector4D{          //采用匿名结构就可以不用分等级了去call了
    union{               //在union括号内部的第一层的所有元素，共享内存空间。因此两个struct的就共享内存。
        struct {             //因此这也是为什么float x, y, z, w.要在括号内部，不然就共享内存了
            float x, y, z, w;
        };
        struct{
            Vector2D a, b;    //这里 vector4D 就可以两个2D的方式输出了
        };
    };
};

void print2DVector(const Vector2D& vector){
    cout << vector.x << ", " << vector.y << endl;
}





void unionTst(){
    //简单的例子
    struct Union{
        union{
            int a;
            float b;
        };
    };
    
    Union u;
    u.a = 40;
    cout << "interpret as int: " << u.a << endl;
    cout << "interpret as float: " << u.b << endl;
    
    //结果虽然不同，却是同一块内存区域
    
    
    
    /*
     实际应用test
     */
    
    Vector4D vector4D = {1.0, 2.0, 3.0, 4.0};
    // 你看这就能用出来了。这样就不用写特殊的getter和print了。
    print2DVector(vector4D.a);
    
    
    
    
}
