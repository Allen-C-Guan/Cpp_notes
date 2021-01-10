#include <iostream>

using namespace std;

class Foo {
public:
    int a;
    Foo () {
        a = 0;
    }

    void PrintFoo () const {
        cout << a << endl;
    }
    void PrintFoo () {
        a ++;
        cout << a << endl;
    }

    void aPlusPlus () {
        a++;
    }

    const int getA() const {
        return a;
    }
    int getA() { //用non-const来调用const的方法
        return static_cast<int> (static_cast<const Foo>(*this).getA());
    }
};

void Print(const Foo& f) {

    cout << f.a << endl;
}


int main() {
    const Foo f1;
    Foo f2;
    cout << f1.getA() << endl;
    cout << f2.getA() << endl;
    std::cout << "ENDING" << std::endl;
    return 0;
}

