#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;
class Base {
public:
    int a;
    int b;
    virtual void PrintA();
    void Print() {
        this->PrintA();
    }
};

void Base::PrintA() {
    cout << "this is Base" << endl;
}

class Derived : public Base{
public:
    void PrintA() {
        cout << "this is Derived" << endl;
    }
};

void Print(int a){
    cout << a << endl;
}
int main() {
    Derived d;
    d.Print();
    Base pb = d;
    pb.PrintA();
}