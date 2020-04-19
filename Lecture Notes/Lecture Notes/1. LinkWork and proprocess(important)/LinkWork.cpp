#include <iostream>
using namespace std;


/*
 * 声明的作用
 声明的作用主要是通知linking，你要去别的file里面去找这个东西，找到了，我们再来用。
 linking只在compile之后完成的， compile的时候只关心每个独立的文件是否有问题。至于这个文件和其他文件的*互动*是否正确，他并不知道，
 因为compile的过程是在每个文件之间独立运行的。
 
 而linking是在compile之后，要把各个file之间的关系联系起来，比如当前file是有用到其他file的函数或者变量，这是，linking出现把他们联结起来，
 一连接起来，就会发现问题了。比如你在当前文件里声明说有个函数叫LOG 记过linking去别的file里一找，发现并没有，这就叫linking error
 
 
 * 这个叫做声明，只是说声明这里已经有了一个log函数，然后你下面就可以去用这个函数了， 至于这个函数是否真的存在，或者这个函数是否真的合法
 * 在main的时候，并不关心。
 * 比如这里面的trush function， 我们在声明trush function的时候，即使根本没有这个函数存在，我们也不在乎.
 * 只有当真正调用这个函数的时候， linking才会产生连接，这时候我们发现这个函数到底是什么，到底存不存在。
 *
 * 通过以上的内容，我们就可以知道，Link 的作用和工作原理了,
 * Link在你声明的时候，会产生一个link，而这个link里面的内容，如果没有被执行，那就根本不会接触到。如果一但执行了，那么当前函数，就会通过
 * 一个link，接入到log函数的文件中去，这时候，如果发现没有这个文件，那就会产生link error
 *
 * linking 的作用
 * linking的作用就是把多个file编译在一起，从而互相调用。
 *
 * linking和include的区别
 * include是单纯的复制粘贴，并在preprocessing 的时候完成的，而linking并没有复制粘贴，只是编译在一起，从而可以互相调用
 *
 */
void Log(const char* message);
void trush(int num);

/*
 * static的作用
 * 这里，如果我们不再test前面加上static，即使我们用不到test韩遂，那么编译也会出错，因为编译器认为，你的test也有可能被别的file调用，
 * 即使你在main里没有，因此，这时候，编译器要求你的test也必须是合法的。
 *
 * 但是我们一旦加了static， 就说明， test之后存在于当前函数中，其他函数不会存在，那么test就不会被编译，因为没有被用到，编译器压根都没
 * 碰到test。
 *
 *
 *
 * signature 与 linking
 * 再有就是，只要是signature不完全相同，你就会发现一个linking error。
 * 这是因为每个signature对应唯一一个linking， int Log 和 void Log是不同的linking， 而void Log(int nums) 和 void Log( char A)
 * 也并不是一个linking，那么自然就也会发生linking error的问题了。
 *
 *
 * same name same signature
 * 如果发生有两个完全相同的name和signature，即使body不一样，也会发生linking error，那是因为linking是由name + signature共同决定的
 * 如果两者相同，就会产生相同的signature，这就会导致linking error
 *
 * 这个情况经常发生在include的head的时候，如果我们include一个head，这个head中有相同函数，那么就会到这这个问题。
 * 通常这个时候，我们可以采用static的方式把函数的作用域限制在一个file 内
 */
static void test(){
    trush(1);
}


/* pre process
 
 这里我们就利用了proprocess的原理来完成的，我们只是重新定义了一个名字而已，在编译之前，会有一个预先的process，在这个process的时候，会把所有的
 INTEGER都换成int
 
 除此之外，所有的常量，include等，只要能直接带入到，都会被直接带入固定值，然后才进行编译。
*/



# define INTEGER int  //只是单纯的字母替换而已的作用


# if 1    //用于将if 和 endif之间的内容做判定后在决定是否对其进行编译，如果if 1表示这之间进行编译， if 0 表示这之间不进行编译。这段就等于删除了。

int LinkWork_test() {
    Log("Hello world");
    INTEGER a = 4; //这里我们可以看到，我们
    cout << a << endl;
    
    return 0;
# include "EndBrace.h"

# endif
/*
 * 关于include的分析
 * EndBrace在这里就比较牛逼了，你看，我少写了一个 "}", 而我在include "EndBrace.h"里面，只写了一个一个}
 * 我一个include，就把 } 粘贴在后面了。对！ 就是直接的复制粘贴而已！！！然后就不报错了
 *
 * 因此可以证明 include就是复制粘贴而已！！！！ 非常的简单！！！
 */
