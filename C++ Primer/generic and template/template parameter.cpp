#include <iostream>
#include <string>
#include <unordered_set>
/*
 * ****************************  重载与模板  *******************************
 * 模板重载的目的：
 * 和普通函数重载的目的相同，有时候一个模板的形式并不能适配所有的类型，因此需要对模板进行重载来适配多种类型的实参
 * 比如：
 * template<typename T> void print(const T& t){std::cout << t << std::endl;};
 * 对于这个模板而言，只能打印那些可以被std::cout 打印的类型，那如果有些类型不支持这种打印方式，或者说
 * 即使打印出来，也不是你想要的内容，比如入参是指针，你肯定不想打印指针地址，而是打印指针内容，这时候就需要
 * 重载模板了
 * template<typename T> void print(const T* t){std::cout << *t << std::endl;};
 *
 * 对模板函数的重载和普通的函数匹配规则是有不一样的，其目的是为了能让用户用到最合适的那个函数。因此其原则如下
 * 精准匹配 > 非模板函数 > 模板特殊化
 * 1. 精准匹配：精准匹配的原则和普通函数的类型匹配原则相同，既最小限度的对函数类型进行转换
 * 2. 非模板函数：指的是如果匹配质量相同，则非模板函数优先非模板函数（非模板函数更特殊一点，否则非模板函数用于不会被调用到！）
 * 3. 模板特殊化： 如果有两个模板函数的匹配结果相同，则适用范围更窄的那个模板会被选中。
 *
 * 根据模板的重载的原则，我们可以反推我们写模板的逻辑和顺序：
 * 一定是先写最通用的模板函数，对于特殊情况，比如某个特定的类型的特殊处理，我们在对函数重载，然后再对那些特殊的类型写模板函数。
 *
 * *******************************   可变参数模板   ************************************
 * 可变参数模板的目的是为了解决在函数调用的时候，参数类型和参数个数都不确定的问题的。
 * 存在两种参数包：模板参数包和函数参数包。模板参数包用来表示模板类型的参数的，函数参数包是用来传递函数值的。
 * 注意：
 *  如果一个参数的类型是模板参数包，则参数一定是函数参数包
 *  template<typename... Args> 表示typename是个包，表示很多个类型的类型，因此Args一定表示一组类型。
 *  void func(Args... &inputs); 则表示Args是个类型包，则inputs一定也是一个参数包，有很多个实参
 *
 * 可变参数模板不但可以推断实参类型，还可以推断实参的个数。
 *
 * *****************************  包扩展  ************************************
 * 对于参数包而言，，除了获取大小之外，我们唯一能做的事情就是扩展！
 * 扩展指的是：将包分解为构成的元素，而这个操作要通过省略号“...”， 来触发。
 * 可被扩展的对象：
 *    // 将参数包（一组参数都拆成参数列表， res1, res2, res3,....的形式）
 * 1. 参数包的扩展：print(i, res...);
 *
 *    // 将类型参数包扩展（Args1 &res1, Args2 &res2, Args3 &res3...)
 * 2. 类型扩展： template<typename...Args> void func(Args&... res)
 *
 *    // 这表示callableObj被拆开了，既callableObj(input1), callableObj(input2), callableObj(input3).....
 * 3. 可调用对象的扩展， func(callableObj(input)...);
 *
 * ***************************    转发参数包    *************************************
 * 转发参数包简单来说就是 转发 + 参数包 的配合，既有些场景，我们既需要完美转发，对于实参的个数又不是特别确定的是，就需要
 * 转发参数包来实现。
 *
 * 比如：在vector中的emplace_back( )中，其函数想要实现的是，直接将入参放到对应的class的constructor里，从而实现直接
 * 在vector的未初始化的内存中构造对象。（与之对应的，push_back()会构造一个临时的obj，然后copy到未初始化的内存中，再把临时
 * obj丢掉）
 *
 * 通过上面的分析，我们发现，emplace_back()的目的就是提高性能，如果没有了完美转发，其一可能会造成不必要的copy，其二，无法
 * 让使用emplace_back()和行为和使用constructor的行为保持一致。
 * 又因为obj 有很多种constructor， copy, move, 构造等，因此参数数量也不确定，这就需要参数包来实现了。
 *
 * 综上所述，当参数个数不确定，且需要参数类型保持一致的时候，需要转发参数包
 *
 * template<typename...Args>
 * void StrVec::emplace_back (Args&&...args) { // 这里必须是万能引用
 *      chk_n_alloc();
 *      data.construct(first_free++, std::forward<Args>(args)...); // 这里可调用对象，模板类型参数包，实参包均得到扩展了。
 * }
 *
 * ****************************   函数模板特例化   **************************************
 * 模板特例化的目的在于，有时候，我们想对特定类型的实现进行特例化处理，这时候就需要模板特例化来实现。
 * 实现方法：
 * template<> void func(int a, int b)
 * 1. 声明这是个模板函数，因此要template来声明
 * 2. <> 空的尖括号表明我们会指定该模板函数的全部参数类型（必须是全部，不允许一部分）
 * 3. 在类型处，指定全部的类型。
 *
 * 注意：
 * 1. 特例化模板不会影响函数的匹配机制
 *  模板特例化不是模板的重载，而是模板实例化的一种而已！！因此模板的特例化并不会影响模板函数的匹配机制，
 *  但是当匹配程度相同的时候，依然会选择更特殊的来调用，因此
 *  非模板函数 > 特例化模板函数 > 普通模板函数
 * 2. 特例化模板需要永远和普通模板绑定在一起，从而让两者可见性完全一致
 *  这是因为如果两者可见性不一致的时候，会导致编译器会用普通模板实例化一个函数，而不是采用特例化的模板
 *  因此需要声明在一个头文件中。
 *
 *
 * ****************************   类模板的特例化    ******************************
 * 类的模板特例化的意义和函数模板的特例化一样，都是为了特殊类型特殊处理而产生的一种功能。
 * 类模板的特例化和函数模板差不多，唯一区别是需要在类名后面加上指定的模板类型
 * template<>
 * class Foo<int> { // 这里需要指定特殊的类型
 * }
 *
 * 重点讲解一下STL里面自定义hash的实现：
 * 前提：key值必须重载==运算符，因为标准库会组合使用==和hash值来判定两个key值是否一致。（因为hash值一致，也可能是不同的key值，和桶管理
 * 方式有关）
 * 特例化hash模板的时候，需要实现：
 * 1. 重载调用运算符，接收一个key类型的对象，return一个size_t的类型，作为hash值
 * 2. typedef两个类型成员，result_type和argment_type，分别表示调用运算符的返回类型和入参类型，将类型通用化，方便调用
 * 3. 默认构造函数和拷贝赋值运算符（可以采用合成的，隐式定义），因为要实例化hash，必须有这些。
 * 4. hash函数，一个好的hash函数要保证，一个hash对应一个key值，要一一对应，才能提高效率。
 *
 * 我们可以调用std内的hash模板，对成员变量分别hash后，在与或起来合成一个总的hash值后再返回。
 *
 *
 * ***************************   类模板的部分特例化   *********************************
 * 对于类模板而言，我们可以指定一部分的模板参数，这里一部分模板参数不是指的数量上的一部分，指的是类型上的一部分
 * 比如 是T 还是 const T&。
 * 功能：这个功能可以对不同子集内的类型分类来处理。比如我们的remove_reference，就希望对于不同的类型采用不同的
 * 处理方法。而这里的不同的处理方法就可以将reference去掉！
 *
 * 注意类模板的特例化的本质也是模板，并不是实例，而是通用模板的一个子集。
 *
 * **************************   特例化类的成员  ***************************
 * 我们也可以只特例化类的一部分成员而不是全部类，这样做的好处在于，当模板实例化为特定类型的时候，只有一个成员是特例的
 * 而其他成员都是正常实例化的。使用起来会更加灵活。
 * template<typename T>
 * class Foo {
 *      void Bar();
 * }
 * template<>
 * void Foo<int>::Bar() {      // 这里只有当Foo初始化为int的时候，其Bar成员函数才执行这个，而其余的正常初始化
 *
 * }
 */

template<typename T>
void print(const T& o) {
    std::cout << o << std::endl;
}

template<typename T>
void print(T* const p) {
    // 这里不能写顶层const，这主要和模板函数和普通函数的匹配机制有关，顶层const意味着pointer是const的，这时候匹配优先级就比前面的低了
    // 因为类型不匹配
    std::cout << *p << std::endl;
}



//  转发参数包的例子
void work(double, std::string&&, std::string&);
template<typename...Args>
void func(Args&&...args) {
    work(std::forward<Args>(args)...);
}


// 函数模板的特例化
template<typename T>
void specTemplateFunc(T a, T b) {
    std::cout << "this is generic template function" << std::endl;
}

template<>
void specTemplateFunc(int a, int b) {
    std::cout << "this is special int template function" << std::endl;
}


// 类模板的特例化
class Student {
public:
    int age;
    std::string name;
    Student(int age, std::string name) : age(age), name(name) {}
    bool operator== (const Student &other) const {
        return (this->name == other.name) && (this->age == other.age);
    }
};
namespace std {
    template<>
    struct hash<Student> { // 指示列模板的模板类型（函数模板不用指示这个地方）
        typedef size_t result_type; // 必须要在类内定义result_type 和 argument_type类型，分别表示"()"的返回类型和如参类型
        typedef Student argument_type; // 其这样做的目的可以不关心你的实际类型，调用result_type和argument_type即可
        result_type operator() (const argument_type &s) const; // 必须是const 的函数，调用点有要求
        // 使用合成构造和copy，赋值控制函数
    };

    size_t hash<Student>::operator()(const argument_type &s) const {
        return hash<int>()(s.age) ^ hash<std::string>()(s.name);
    }
}

// 部分实例化
template<typename T>
class SpecialPartialTemplate {
public:
    SpecialPartialTemplate(){
        std::cout << "general" << std::endl;
    }
};
template<typename T>
class SpecialPartialTemplate<T&> { // 这表示入参类型的整体表示T&，模板需要反推T
public:
    SpecialPartialTemplate(){
        std::cout << "left value reference" << std::endl;
    }
};

template<typename T>
class SpecialPartialTemplate<T&&> {
public:
    SpecialPartialTemplate(){
        std::cout << "right value reference" << std::endl;
    }
};

// 部分特例化的实用的例子
template<typename T> struct remove_reference {
    typedef T type;
};

template<typename T> struct remove_reference<T&> {
    typedef T type;
};

template<typename T> struct remove_reference<T&&> {
    typedef T type;
};

// 特例化成员
template<typename T>
class Foo {
public:
    void Bar() {
        std::cout << "this is general bar func" << std::endl;
    }
};

template<>
void Foo<int>::Bar() {
    std::cout << "this is int bar func" << std::endl;
}


int main ()
{
    int a = 10;
    int* pa = &a;
    // 模板重载
    print(a);
    print(pa);
    // 函数模板特例化
    specTemplateFunc(1, 2); // 这里会调用特例的int的function
    specTemplateFunc("allen", "1"); // 这里会调用普通的模板函数

    // 类模板特例化
    std::unordered_set<Student> studentSet;
    studentSet.insert(Student(10, "allen"));
    studentSet.insert(Student(20, "cecilia"));

    // 类的部分模板特例化
    SpecialPartialTemplate<int> s1; // 调用general版本的
    SpecialPartialTemplate<int&> s2; // 调用左值引用版本的
    SpecialPartialTemplate<int&&> s3; // 调用的右值引用版本的


    // 去掉remove_reference的实现 得到的类型都是int类型！
    remove_reference<int>::type t1;
    remove_reference<decltype(10)>::type t2; //
    int val = 10;
    int &rVal = val;
    remove_reference<decltype(rVal)>::type t3;

    // 测试特例化一个成员
    Foo<std::string> f;
    Foo<int> f2;
    f.Bar();
    f2.Bar();

}
