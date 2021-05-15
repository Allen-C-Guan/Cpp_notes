#include <iostream>
#include <string>
/*
 * *********************  引用成员变量  ****************************
 */
class Foo {
public:
    // 实参必须是引用类型的，否则你的引用没有任何意义！且很危险
    // 如果实参不是引用类型，你的成员变量引用的将是实参的copy（入参的形参）！！ 而不是真的外部变量
    Foo (int &a, std::string s, double &d) : a(a == 0 ? a : --a), s(s), d(d) {}
    int &a;
    std::string &s;
    double d;
};


int main ()
{
    int a = 1;
    std::string s = "allen";
    double d = 3.14;
    Foo f(a, s, d);
    std::cout << f.a << std::endl;
    std::cout << f.s << std::endl;
    std::cout << f.d << std::endl;

    f.a = 1000;
    f.s = "cecilia";
    std::cout << a << std::endl;
    std::cout << s << std::endl; // 这里虽然你改了f.s 但是你并没有真的引用到s，而是引用到了临时变量形参上！
}
