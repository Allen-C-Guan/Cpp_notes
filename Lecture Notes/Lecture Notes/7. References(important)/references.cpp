# include <iostream>
using namespace std;
# define LOG(x) cout << x << endl;
/*
 reference本身并不占内存，也不能凭空创造，你只能去引用已经存在的变量。因此在compile之后，并不存在reference的痕迹， reference只会存在于source code上面。
 因此我们用reference，就和用这个变量是一样的。可以简单的理解为重命名。
 
 
 在c中， 不管是obj还是int，只要是 用了 a = b; 那么 就是copy.
 reference的本质就是，所有以&方式赋值的变量，均是同一个内容，不同的名称都不过是影子名字而已，他们本该一个名字的。
 
 
 那么reference有什么用呢？
 
 */

void increament(int val){
    val ++ ;
}


void increamentWithPassAddress(int* address){
    (*address)++;   //++运算优先级高，因此要加上括号
}


void increamentWithRef(int& val){
    val++;
}

void reference(){
    int a = 5;
    int& ref = a;
    ref = 2;
    cout << "before the calling function "<< endl;
    LOG(a);
    //这时 a = 2 我们调用函数 increament
    increament(a);
    cout << "after calling increament function" << endl;
    LOG(a);
    /*结果显示没什么卵用！！！！ 这是因为，这里我们并没有把a传递进去，而是把val复制为和a相同的值而已，然后去改变val，而没有改变a
    由于我们没有对a的内存的值进行改动，那么自然a就还是原来的值， 有什么办法让a传递进去，而不是把a的值传递进去呢？
    这就是pointer的作用了
    
    解决办法1：以地址为传参。  --> void increamentWithPassAddress(int* val)
    如果我们设置的函数，接受的参数就是地址，那么是不是就可以直接对地址进行操作了？ 这是不是就完成了上面没有完成的任务。这就和python里面obj参数的引用传递参数的作用是一样的了。
    
    解决办法2:用reference
    这个方法解决很多不必要的麻烦，在方法1中，address并不是a，你要时时刻刻留心着，他是pointer，用他的值的时候要加上*。但是在方法2中，val，他就是a，这样大大的增大了代码的可读性。
     
     
     那么什么时候用pointer，什么时候用reference呢
     reference只是一个语法糖，reference对于实际的编译没有任何影响，他就不会出现在编译之后的文件里。
     而pointer是真实存在的。 因此pointer比reference更加的powerful。 所有用reference完成的，你都可以用pointer完成。
     
     但是reference增强了可读性，并让编程的逻辑变得非常的简单。
     
     
     总结如下：
     1. 如果你想用 *引用的方式来传递参数* 而不是复制，那么就用reference。
     2. 而其他的所有和地址有关的事情，就都交给指针来完成吧。
     
     
     注意：
     1. reference一旦建立了，就不可以反悔了，也不可以更改被引用的对象了。
     2. reference必须在创建之时就被赋值，并跟随一辈子。
     
     但是上面两条不能的事情，pointer都可以，还是那句话，因为reference是假的变量，pointer是真的变量。
    */
    
    
    increamentWithPassAddress(&a);
    cout << "after calling increament passsing address"<<endl;
    LOG(a)
    
    increamentWithRef(ref);
    cout << "after call increament reference" << endl;
    LOG(a)
    
    
    
}
