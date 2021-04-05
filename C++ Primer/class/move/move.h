#include <iostream>
/*
 * **********************  右值引用  *****************************
 * 右值引用和左值引用的区别
 * 内容上的区别：
 * 左值：对象的身份（地址）
 *  我们关注的是内存地址，内存里存放什么我们不在乎。
 *  1. int a; // a表示一个有名的内存，该内存中存放的可以是5，也可以是0，但a这块内存地址不能变
 *  2. arr[3]; // 下标，也是一个地址
 *  3. *pInt; // 解引用
 *  4. ++i; // 前置也是左值
 * 右值：对象的值（内容）
 *  我们关注内存中的内容，内容变了不行
 *  1. 5; // 字面值常量，你变成6了肯定就不是5了嘛
 *  2. 9 + 6; // 临时对象（运算结果，函数返回值等） 类似字面值常量，他就必须是15，是别的就不行
 *  3. 位
 *  4. i++; // 后置是右值
 *
 * 特征不同：
 * 左值持久：比如int a; 由于a是一个已名地址，并可以长时间存在于内存中，
 *
 * 右值短暂：9+6; 这结果你要不赋值给一个左值，这结果就没了，因为这个结果没有放到已名的内存中，这行执行完这个临时的变量就扔了
 *
 * 因此右值通常有如下性质：
 * 1. 对象将要被销毁
 * 2. 对象没有其他用户。
 *
 * 如何理解上面的性质：
 * 这里比如i = 9+6; 其实i并没有用9+6，因为i有自己的地址（家），而15其实没有存放在i家里，i只是在他家里
 * 复制了一个一样的15，放在自己家中，然后9+6的值，其实就被扔了。
 *
 * 而因为右值如上的两条性质让右值引用可以 *自由的接管所引用的对象的资源*！！！ 反正没人用，反正也要扔了，不用白不用！
 *
 * tips：变量是左值！
 * 变量是左值，右值引用类型的变量仍然是左值。因此右值引用不可以绑定到变量上，即使变量是右值引用类型。
 *
 * 其实这并不奇怪，一个字面常量（右值），一旦被右值引用以后，就有了生命周期，是个可以长时间存在的变量！因此也变成了左值。
 * 换句话来说，右值引用类型仍然是左值，因此我们可以得出结论，一切变量，都是左值！
 * 例如：
 * int &&a = 10; // 正确， a有自己的声明周期，可以持久存在，因此是左值。
 * int &&b = a;  // 错误，10是右值，但a是左值（右值引用也是左值）
 *
 *
 * *************** move ************************
 * 我们可以现实的将一个左值转移为对应的右值引用类型。
 * int &&a = 10;
 * int &&b = std::move(a); // 正确！
 * move的调用相当于告诉编译器，我们有一个左值，但我们希望可以像右值一样处理他。
 * 但是，move就意味着承诺：除了对a赋值或者销毁外，我们将不再使用他。在move之后，我们不能对移后源（move from)对象的值做任何假设！
 *
 * 什么是对move from对象的*值*不做任何假设？
 *
 * 前提：move from对象要保证可析构安全和安全使用：
 * 1. 析构安全
 * 我们对任何移动操作必须要保证，move from的对象在被抽离了内容以后（内容转移了出去）要保证析构安全！换句话，在你卸磨杀驴的时候，
 * 不要给程序带来麻烦！
 * 比如在StrVec类中，我们将move from 类型的指针都置成nullptr，这样在析构的时候，既不会把新内容错误的释放掉，也不会因为野指针
 * 而释放了不属于自己的内存。这就是析构安全。
 *
 * 2. 安全使用
 * 安全使用指的是，在move from的对象被抽离以后，你仍然可给他赋值，让他变回一个有内容，有内涵的对象！卸磨以后，驴一样可以被使用。
 * 但是使用move from 对象可能会改变新内存中存放的内容！。展现引用的特征。
 *
 * 比如在strVec里面，我们把move from对象打回默认初始化的状态了！， 你要真是给他赋个新值，这个对象一样可以像新对象一样正常使用
 *
 * 3. move from 对象的*值*不做任何假设
 * 说的是，move from的对象内容被抽离以后，他被抽离后，当前内容（值）是什么状态你不要做任何假设。他只需要保证能析构，能安全使用即可，
 * 他被抽离以后，值是什么不重要。
 * 比如string 在被move以后，其内容可能是空，所有size()返回的可能是0， empty()返回的可能是true，但这不一定，你不要去依赖，也
 * 不要去用move from之后对象的内容（值）
 * 因此，对于move from 对象而言，最好就是不要再用了！！
 *
 *
*/

int main ()
{
    int &&a = 10;
    int &&b = std::move(a);
    b++;
    std::cout << a << std::endl;

    std::string s1("allen");
    std::string &&s2 = std::move(s1);
    // s1已经是移后态了，不要再使用移后态的值了！
    std::cout << s1.size() << std::endl;
    std::cout << s1.empty() << std::endl;
    std::cout << s1<< std::endl;
    s1 = "dfadfa";
    std::cout << s2 << std::endl; // s2也会被修改，这是为啥？？为啥s1和s2不互相独立，难道右值引用和引用呈现效果没差？
}



/*
     * ********************  一个operator= 两用 *****************
     * 通过将operator=的入参变成值传递，就可以一个函数既可以当做move，也可以当做copy
     * 而一个函数两用就是通过值传递完成的。
     * 我们把值传递过程拆开，other要么是由move构造而来，要么是copy而来。
     *
     * Foo other(outsideFoo); // outsideFoo是函数外部实参
     * 如上形式，可以看出other的构造可能是move构造而来，也可能是copy而来， 这取决于outsideFoo的类型。
     * 当outSideFoo时右值的时候，会调用move，而不是copy，而当其实左值的时候，调用copy而不是move
    */
class Foo {
public:
    int a;
    std::string *ps;

    Foo():a(0), ps(nullptr){}
    ~Foo(){
        delete ps;
    }

    Foo (const Foo &other) : a(other.a), ps(new std::string(*(other.ps))){
        std::cout << "this copy constructor" << std::endl;
    }

    Foo (Foo &&other):a(other.a), ps(other.ps){ // 接管内存
        // move from 对象 安全析构 并正常使用
        other.a = 0;
        other.ps = nullptr;
        std::cout << "this is move constructor" << std::endl;
    }

    Foo& operator= (Foo other) {
        Foo temp = other; // 这里other就已经是左值了，所以temp的一定是copy来的
        a = temp.a;
        ps = temp.ps;
        return *this;
    }
};

int main2 ()
{
    Foo f1;
    f1.ps = new std::string("allen");
    std::cout << *f1.ps << std::endl;
    Foo f2;
    f2 = f1; // 赋值入参other是copy而来
    f2 = std::move(f1); // 入参是move而来的
}