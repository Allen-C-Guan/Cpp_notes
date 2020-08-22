# include <iostream>
# define Print(message)  cout << message << endl
using namespace std;


/*


                        1. static在class或者structure中
 定义：
 当static在类或class内部的时候，就是类变量或类函数！ 即所有以该class实例化的instance，都将会share这个staticvariable
 或者method。
 
 使用方法：

 1. 类中的全局变量（改一个instance的类变量，所有的都发生了更改）
 2. 不实例化也可以用 但是要用"::"， 而不是“.”。（即： “类::类变量” 或者 “类::类方法” 都是合法的）
 3. ！！！！！static method只能manipulate static variable！！！！！
    我们要记住， static method和static variable 均不属于某一个instance，因此static method没有办法获取instance variable， 他们根本不是一家人，信息也不可以互通。

 综上所述：
 instance是属于类的，但类变量或者类函数却并不属于instance的。因此instance可以share 类函数或者类变量，
 但是类函数无法获取 instance variable。 因此static method中只能有static variable，不可以出现 instance variable。
 
 
 
                                ***  例子 ***
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
      
      那么既然都是躺尸的状态，那么static函数就必须要只能包含static变量，道理很简单啊， 你class一出现，static
      function就准备好躺在那里了，结果躺下的时候才发现，还有个instance变量没出现，因为没有被实例化，那我怎么躺下？？？
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



int Entity :: z; //类变量不属于instance， 因此要先声明，后用。 ::表示作用域的符号。表示z是Entity的z，此做法是为了保证class有相同属性的时候能不混淆。

 









 /*
  ————————————————————————————————————————————————————————————————————————————————————————
  
                        2. static在class外部 （静态全局变量）
  
 其功能为，将 *变量* 或者 *function* 对当前cpp文件的私有化。让其他cpp file无法获取到该文件中的static变量和函数。
 而不用static的变量，外部file却可以通过一些方法（extern type name;）获取这个file下的变量。因此就要求变量定义不得重复了
  
  使用方法总结
  对于static在class外部的情况，使用原则为：对于variable和function， 能用static，就用static
  即*只要不是非要被其他cpp文件调用，就要用static，无论是函数还是变量。
 

                                *** 例子 ***
  */
 int num = 7;
 /*
  全局变量可以与static变量重名。
  这里我在其他文件里面就定义了一个名叫num的变量，虽然不在一个文件下，但是仍然是全局变量。可是如果我在前面加一个static，就让作用范围变成了文件内部，就不冲突了。
  */


 //如何使用其他cpp file中定义的全局变量（注意：function不需要extern来linking）：
 extern int num2;
 /*
  获取其他cpp file的全局变量。
  extern的作用是把其他file中的非static变量给直接引入过来。
  这个工作原理就是， linking会自动的去在外部file中寻找定义过的int，然后拿过来
  */

 // 这个方法同样也适用于function，即 static void function(){}则表示的是该function实际上只在当前cpp中有效。
 void function_test(){}









 /*
  ————————————————————————————————————————————————————————————————————————————————————————
  
                                3. local static
  静态变量定义于函数之内，静态局部变量具有局部作用域。它 ***只被初始化一次***， 自从第一次被初始化  ***直到程序运行结束***
  都一直存在，它和全局变量的区别在于全局变量对所有的函数都是可见的，而静态局部变量只对定义自己的函数体始终可见。
  
  这里就又回到scope的概念了，scope是linking建立了，指的是能被linking连接起来的的区域为一个scope。
  而在一个scope里面，我们不可以有两个相同的定义变量，否则linking就很疑惑，我应该怎么连接。
  而static的用法就是改变scope，或者叫linking的作用范围。
 
  
 静态局部变量   function() { static int num }
 关键点就三个
 1. 只初始化一次。
 2. 一直存在到程序结束
 3. 只在local内可以看到。
 */




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



/*
 ————————————————————————————————————————————————————————————————————————————————————————
 
                        ！！！！！因此什么是static？！！！！！！！！
 
static指的是相对于不加static而言的变量而言是 相对静止的，不消失，不出格的。

对于class之外的static而言，是对应全局变量的静态的 *不出格*，指的是变量会*静静地*躺在当前cpp file中，不会跑到别的cpp file中。
对于class内部的static而言，是对instance variable而言的的 *相对静止的*，指的是只要类出现了，类变量就会一直静静在那里，
    并被所有instance共享。不会随着instance的出现或者消亡而消失。
对于local static而言（在function 或者for循环中的），static是对local variable而言的 *不消失的*， local variable
    在scope结束就消失了，但是static local 并不会消失，他还在内存中，当你再次进入到local的时候， 他还是原来的那个变量。
    但却只初始化一次。

*/


// —————————————————————————————— test ————————————————————————————————————————————
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
