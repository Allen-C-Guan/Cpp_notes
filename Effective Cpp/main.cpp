#include <iostream>
#include <string>
using namespace std;

class Foo {
public:
    int val;
    string name;
    Foo () {
        cout << "created" << endl;}
    ~Foo () {
        cout << "destoryed" << endl;}

    Foo (const Foo& f){
        val = f.val;
        name = f.name;
        cout << "copy " << endl;
    }

};

Foo Func() {
    Foo f;
    return f;
}


int main() {
    Func();

    std::cout << "ENDING" << std::endl;
    return 0;
}
