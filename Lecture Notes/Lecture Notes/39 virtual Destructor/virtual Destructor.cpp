#include <iostream>

using namespace std;

/*
 只要是使用了destructor的继承， 就一定要virtual化。一定！否则可能发生memo leak
 */
class Base {
public:
    Base(){cout << "Base constructor" << endl;}
    virtual ~Base(){cout << "Base destructor" << endl;}
};

class Derived : public Base {
private:
    int* array;
public:
    Derived(){ array = new int [10]; cout << "Derived constructor" << endl;}
    ~Derived(){delete[] array; cout << "Derived destructor" << endl;}
};


void virtualDestructor(){
    Base* b = new Base();
    delete b;
    
    cout << "----------------\n";
    Derived* d = new Derived();   //derived function要先建立一个base，在建立一个derived。destruct的时候顺序相反。
    delete d;
    
    //多态测试
    cout << "------------\n";
    Base* poly = new Derived;
    delete poly;
    /*
     这里如果我们不对base destructor使用virtual， 那么在动态绑定的时候，就不会执行子类的destructor了。而只是执行父类的
     constructor。
     这是因为，编译器自己并不知道，自己在动态绑定中，destructor被override了。因此并不会在执行base destructor的时候，
     会自动的执行子类的destructor。
     
     此种情况只会出现在动态绑定中。
     
     如何解决这个问题呢？
     给base的destructor加一个virtual。这时候，动态绑定的时候，也会执行子类的destructor了。
     还不会影响其他方法使用destructor。
     
     */
    
    
}
