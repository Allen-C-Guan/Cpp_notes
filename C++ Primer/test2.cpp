#include <iostream>
#include <string>

int func1 (int){
    std::cout << "func \n";
}
int func2 (int){
    std::cout << "func2 \n";
}

int func3 (int){
    std::cout << "func3 \n";
}
int a;
int b;
void foo(int(*func)()) {
    func();
}
void test ()
{
    using FuncType = int(*)(int);
    FuncType funArr[3] = {func1, func2, func3};
    for (int i = 0; i < 3; i++) {
        funArr[i](i);
    }
}



int val;


class Foo {
public:
    int val;
    Foo(int val) : val(val) {}
    void print() const {
        float f;
        int val;
        std::cout << val << std::endl;
    }
};


void test_class () {
    Foo f(10);
    f.print();

}


int main ()
{
    test_class();
}

