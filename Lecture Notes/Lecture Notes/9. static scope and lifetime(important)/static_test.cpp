# include <iostream>
# define Print(message)  cout << message << endl
using namespace std;


/*
 static的作用
 1. static在class或者structure中
 当static在类或class内部的时候，就是类变量！ 即所有以该class实例化的instance，都将会share这个variable。
 
 2. static在class外部 （静态全局变量）
 表示这个变量的作用范围就在当前file里面，不会出去。你用extern也不会找到。
 而不用static的变量，外部file却可以通过一些方法获取这个file下的变量。因此就要求变量定义不得重复了。
 
 3. local static
 在function 内部定义的static，会在第一次运行函数的时候被初始化，之后就不会在被初始化了，而且这个变量会一直存在到程序结束。不会被抹掉
 但是却只在函数内部可见。
 
 这里就又回到scope的概念了，scope是linking建立了，linking的作用就是在编译的时候，把相同的东西，都和定义的语句连接起来。而变量能被连接的区域就是一个scope了，只要在scope之内，linking才能把scope之内的所有对应变量连接起来，而如果不在scope里面，那么就连接不起来。
 而在一个scope里面，我们不可以有两个相同的定义变量，否则linking就很疑惑，我应该怎么连接。
 
 而static的用法就是改变scope，或者叫linking的作用范围。
 
 
 ********************************************************************************
                            scope和lifetime的区别和联系
 *******************************************************************************
 
 scope指的是变量可作用的范围，lifetime指的是变量从创建到被删除的时间。
 
 C++ 变量根据定义的位置的不同的生命周期，具有不同的作用域，作用域可分为6种：全局作用域，局部作用域，语句作用域，类作用域，
 命名空间作用域和文件作用域。
 
 全局变量  int num;
 全局变量定义于所有函数之外。全局变量具有全局作用域。全局变量只需在一个源文件中定义，就可以作用于所有的源文件。当然，
 其他不包含全局变量定义的源文件需要用extern 关键字再次声明这个全局变量。
 
 静态局部变量   function() { static int num }
 静态变量定义于函数之内，静态局部变量具有局部作用域。它 ***只被初始化一次***， 自从第一次被初始化  ***直到程序运行结束***   都一直存在，
 它和全局变量的区别在于全局变量对所有的函数都是可见的，而静态局部变量只对定义自己的函数体始终可见。
 */

/*
                            *** 1.类中的静态变量 ***

对于类中的static的作用完全和java中的类变量相同
1. 类中的全局变量
2. 不实例化也可以用。

因此类变量 本质上来讲并不属于instance，只是instance可以用而已
*/



/*
                            *** 2. 类外的静态变量  ***
 */
int num = 7;
/*
 这里我在其他文件里面就定义了一个名叫num的变量，虽然不在一个文件下，但是仍然是全局变量。可是如果我在前面加一个static，就让作用范围变成了文件内部，就不冲突了。
 */

extern int num2;
/*
 extern的作用是把其他file中的非static变量给直接引入过来。
 这个工作原理就是， linking会自动的去在外部file中寻找定义过的int，然后拿过来
 */


// 这个方法同样也适用于function，
void function_test(){}

/*
 第二种方法的总结
 对于第二种用法，我们可以简单的理解为static让变量私有化！！ 外面看不到，功能和private相同
 因此使用原则和private相同。 *只要不是非要被其他函数调用，就要用static，无论是函数还是变量*，
 */

/*          *** local static
 
 静态局部变量   function() { static int num }
 关键点就三个
 1. 只初始化一次。
 2. 一直存在到程序结束
 3. 只在local内可以看到。
 */




struct Entity{
    int x, y;
    static int z;
    void print(){
        cout << x << ", " << y << ", " << z << endl;
    }
    
    /*
     static function   --> 只能使用static变量
     static function 无法link到instance var 因为instance var并不属于class
     
     static function 因为static 表达的是一种静态的状态，在class中，所有static的东西都是静止的躺在一个存储空间中不动了，
     而且只要类出现了， 这些变量就一直躺在那里。
     对应其他实例变量而言，实例变量一会有了，一会没了，一会又多一个实例出来，这就是相对的动态
     
     那么既然都是躺尸的状态，那么static函数就必须要只能包含static变量，道理很简单啊， 你class一出现，static function就准备好躺在
     那里了，结果躺下的时候才发现，还有个instance变量没出现，因为没有被实例化，那我怎么躺下？？？
     */
    
    static void method(){
        cout << z << endl;
    }
};

/*
 在class外面的static和class里面的static不同， 只要调用了该函数，那么e一定是已经被实例化过了，那么对于该函数而言，e一定产生了。
 */
static void print(Entity e){
    cout<< e.x << endl;
};


void static_local_var(){
    static int i = 5;   //这里i并不会被重置，因为i一直存在，但是只有函数内部才能看到而已
    i++;
    cout << i << endl;
}


int gVar = 0; //全局变量

void global_var(){
    gVar++;   //函数内也可见
    cout << gVar << endl;
}

int Entity :: z; //类变量不属于instance， 因此要先声明，后用。 ::表示作用域的符号。表示z是Entity的z，此做法是为了保证class有相同属性的时候能不混淆。

void static_test(){
    Print(num2);
    Entity e1 = {3,4};
    Entity e2 = {6,7};
    e2.z = 100000;
    e1.print();
    e2.print();

    //直接使用类来赋值，效果是一样的。
    Entity::z = 0;
    e1.print();
    
    //测试local var
    for (int i = 0; i < 5; i++){
    static_local_var();
    }
    
    
    //global var test
    for(int i =0; i < 5; i++){
        global_var();      //任何函数都可见
        
    }
}
