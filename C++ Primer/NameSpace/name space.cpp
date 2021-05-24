#include <iostream>
#include <string>
#include <unordered_set>
#include "Sale_data.h"
/*
 * *****************************   namespace   *****************************
 * namespace 的作用是为了避免全局量的冲突而设定的，如果没有namespace，那么你只能通过CEUSML_XXX来避免命名冲突。
 * 但这种方法非常的愚蠢，而且长得也很丑，极其恶心且不优雅，而namespace就给我们提供了一个优雅的方法！
 *
 * namespace的本质就是将当前命名空间继续拆分成有名的命名子区间，而各个区间之间命名不干扰，也不冲突。
 * 使用方法：
 * 1. 只要是能放在全局作用域中的，就可以放在namespace中。
 * 2. namespace既可以放在全局作用域中，也可以放在其他命名空间中。但是不能定义在函数或者类内。
 * 3. namespace就是一个作用域
 *
 * *** 每个命名空间都是一个作用域 ******
 * 作用域的可见性：
 * 原因：命名空间向内层可见，可以直接使用，命名空间向外是不可见的，如果需要使用内层的变量，需要指明作用域。
 * 原理：这主要和c++编译器索引名字的原理有关，对于c++编译器的名字索引，是当前作用域内开始，逐渐向作用域外寻找
 * 直到找到位置，因此，如果不指明作用域，变量名称匹配是不会去内层作用域去寻找的，因此，如果要用内层变量，就
 * 必须要指明作用域。
 *
 * *** 命名空间可以是不连续的 *****
 * 命名空间可以是不连续的，这意味着，一个namespace的作用域可能代表两种功能
 * 1. 新建一个命名空间
 * 2. 打开一个已有的命名空间，然后往里面添加点内容
 *
 * 因此对于命名空间中的类的定义而言，仍然要保证在head中打开命名空间进行声明，在cpp file中打开命名空间进行定义！
 *
 * *** 定义本书的命名空间 ****
 * 根据命名空间的使用，我们可以发现，通过命名空间的不连续，我们可以做到对用户隐藏细节，我们只要include一个"Sale_data.h“ 就可以
 * 去随心所欲的使用所有关于sale_data有关的东西了，而不用关心sale_data是不是依赖某些其他的库啊什么的。
 *
 * **** 定义命名空间成员  *****
 * 要想使用或者定义命名空间内的变量或者函数，需要保证当前所在命名空间和你将要使用或者定义的命名空间之间有嵌套或者被嵌套关系。
 * 既要么你想用外层的变量，要么你想用内层的变量，你不能用一个毫不相干的命名空间的变量。
 * 比如A和B是并列关系，那么你在A中是无法使用B的变量的
 *
 *
 */

namespace outSideSpace {
    int a;
    int c = a; // 同级可以直接使用
    namespace insideSpace {
        int b = a; // 内嵌也可以直接使用
    }
    namespace insideSpace2 {
//        insideSpace::b;   // 必须是互相嵌套关系才可以用，要么在内层（指明作用域后使用），要么在内层（不用指明作用域），对于不互相嵌套的命名空间是不可以使用的
    }
    int d = insideSpace::b; // 外层用内层的必须要指出作用域
}

/*
 * *****************  匿名命名空间  *********************
 * 匿名命名空间中定义的变量拥有静态周期，在第一次使用的时候被创建，在程序结束的时候才会被销毁。
 * 匿名空间可以在一个文件中不连续，但是无法跨越多个文件中。
 * 如果头文件中有匿名的空间，则被include到不同的文件中的匿名空间相互独立。（把include替换成copy，很简单的理解了）
 *
 * 匿名namespce中，定义的名字的作用域与该namespace中所在的作用域相同！这里和命名的空间完全不同。也就是说匿名namespace
 * 并没有缩小namespace，其匿名命名空间与外层的命名空间是一致的！
 *
 * 当匿名空间在全局作用域的时候，还要注意匿名空间内的变量不能与全局作用域相同。
 *
 * *********** 匿名命名空间与静态声明  ************
 * 匿名命名空间在c++中可以完全取代静态声明，其起到的作用是完全一样的，
 * 1. 全局变量的访问权限
 * 2. 只在当前文件中可见！
 */

int a;
namespace {
    int a; 
    namespace {
        int a;
    }
}
// 这里定义的时候不会有问题，但是你使用的时候就会报错，比如a = 10， 编译器就会报错二义性，不知道你说的是哪个a。

namespace {
    void func() {
    }
}

/*
 * ************** using 指示  ***************
 * using指示 具有将命名空间成员提升到包含命名空间本身和using指示的最近作用域的能力
 * 这里“包含命名空间本身” 和 “using指示的最近作用域” 指的是，using所在的作用域的外层，和namespace的外层。
 * using声明指示简单的另名字在局部作用域内有效（类似于重命名），但是using的指示是将该命名空间的
 * 所有内容变得有效。
 *
 * 在理解和使用上，我们可以简单的将using指示看做出现在using所在的最近的外层作用域中。
 * 
 */
namespace outside  {
    int a = 10;
    namespace inside {
        int a = 100;
    }
}

int a = 10;
void func () {
    using namespace outside::inside; // 将outside::inside::a 的作用域提升到了func的作用域的外层，也就是全局作用域！ 
                                     // 这时候，就会造成全局作用域的a和outside::inside::a的命名冲突！
//     a++;
//     std::cout << a << std::endl;

}

namespace outSideTest {
    namespace inSideTest {
        int c;
    }
}
/*
 * ****************  实参相关的查找与类类型形参  ******************
 * 对于函数具有类类型的实参，这里有个例外，就是当实参是类类型的函数时候，此时函数的命名匹配不但会匹配
 * 搜索当前作用域，外层作用域，全局作用域，还会搜索实参所属的命名空间（对类所在的命名空间内搜索!），包括
 * 基类的所属的命名空间！
 *
 * 因为 s1 和 s2 是类类型，且该类属于cpp_primer的命名空间，因此在实参是Sale_data的时候，也会对
 * cpp_primer内进行命名搜索！
 * 因此我们可以直接使用 s1 + s2, 而不需要显示的调用 cpp_primer::operator+(s1, s2)
 *
 * NS中的display也是一个道理，
 *
 * ************* 使用std::move 而不是 move  **********
 * 否则有可能std::move永远都不会被调用到，因为可能会被覆盖或者重载。
 *
 *
 */

namespace NS {
    class A {

    };
    void display(A) {
        std::cout << "NS display" << std::endl;
    }
}

class B : public NS::A {
};
/*
 * 这里display的入参是B类型，因此display的搜索域还包括B类和A类所在的命名域中寻找！
 */
void testNs () {
    B b;
    display(b);
}


int main ()
{
    cpp_primer::Sale_data s1 = cpp_primer::Sale_data();
    cpp_primer::Sale_data s2 = cpp_primer::Sale_data();

    s1 + s2;
    cpp_primer::operator+(s1, s2);

    func(); // 匿名namespace的作用域与namespace所在位置相同

    using namespace UsingTest;
//    t1; // 用了using指示的话， 这时候UsingTest::t1 和 t1 均在main函数的外层这个层级上，因此就会出现命名冲突的问题了。
    ::t1;
    UsingTest::t1;

    using namespace outSideTest::inSideTest;

    testNs();



}
