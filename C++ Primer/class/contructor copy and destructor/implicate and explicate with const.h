#include <iostream>
#include <string>
class Foo
{
public:
    Foo(std::string s):s(s){};
private:
    std::string s;
};

/*
 * *************   implicate的用法！！ ***************
 * 对于隐式转换，我们通常有两种方法
 * 1. 值传递。
 * 2. const + ref的方法
 *
 * 1. 值传递。
 * 值传递中，当入参类型不匹配的时候，函数会调用类的非explicate constructor来构造一个类出来
 * 这个过程就会完成隐式转换
 *
 * 2. const + ref的方法
 * const + ref的方法是一个比较违反逻辑却很实用的c++性质，当const Foo &类型出现类型不匹配的
 * 时候， 编译器依然会调用Foo的构造函数，构造一个Foo的object，绑定在参数上！
 *
 * 这个逻辑其实很不合理，既然是reference，却并没有真的reference了，而是构造了一个新的obj，因此你即使改了被引用的obj，Foo
 * 的内容也会保持原样。这很明显不是真正的reference。
 *
 * 但是这样做的最大好处在于字面值常量可以被直接隐式转换成obj！！
 * 首先字符串常量是可以被绑定在同类型的const class_type& 类型上的，这是c++关于字符串常量的语法定义。
 * 那么如果我们在给这个性质扩展一下，不要求同类型，只要可以隐式转换即可，那么字符串常量的用处就被大大扩展了。这意味着
 * 当函数入参是字面值常量可以被隐式转换成为的类型的时候，同样字面值常量也可以作为入参！！
 *
 * 但是这样做的代价就是，一旦类型不是完全匹配，那么reference的特性丧失了！！既要copy，也并不能实现修改外层变量的功能
 *
 *
 * 同时 ref的入参是绝对不可能完成隐式转换的！！没有const的reference要求类型严格匹配！！
 *
 */



void FuncVal(Foo f) {
}

void FuncConstRef(const Foo &f) {
}

void FuncRef (Foo &f) {
}

int main ()
{
    Foo f("allen");
    std::string str1 = "allen";
    const Foo &f2 = str1; // 用string是因为，入参是string，但是allen是const char*，不能转换
    str1 = "dfadf"; // 这里你更改了str1，其实f2的内部也是不会更改的，本质上没有绑定关系的。



    std::string other = "cecila";
    std::string str;
    FuncConstRef(str);
    FuncVal(str);



}
