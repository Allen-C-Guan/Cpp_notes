#include <iostream>
#include <string>
using namespace std;



/*
 该例子为了证明如下几件事
 1. 函数的继承关系。如果继承关系为 A -> B -> C， 则即使C只是继承了B， 但仍然继承了A的全部特征。
        当动态绑定之后， Vtable 选择函数的规矩是根据，继承关系从下往上找，先从辈分最低的中找是否有当前函数，
        如果没有才往上找，直到找到为止。
 2. 虚函数的override。 interface -> virtual function -> concrete function, 即可以分步的实体化。
 3. 动态绑定的实现必须通过*指针或者引用* 而不能通过instance本身来完成。
 4. 静态绑定（base中没有virtual），调用哪个函数依赖指针的类型,在编译的过程中采用覆盖的形式确定函数的调用，而不是v-table。
 */



class Animals{
public:
    //virtual function
    void Eat(){
        cout << "Eat function have not be defined yet" << endl;
    }
    // interface
    virtual string Bark() = 0;
    
    virtual int MaxSize() = 0;
};

// interface 抽象成 虚函数
class CatOrDogClass: public Animals{
public:
    virtual int MaxSize() override {
        return 8;
    }
};


class Dog1 : public CatOrDogClass{
    
public:
    string voice;
    string food;
    Dog1(string default_message):
        voice(default_message), food("meat")
    {
    }
    
    string Bark() override{
        return voice;
    }
    
    void Eat() {
        cout << food << endl;
    }
};



class Cat1: public CatOrDogClass{
public:
    string voice;
    string food;
    
    Cat1(string init_voice,string init_food): voice(init_voice), food(init_food)
    {
    }
    
    string Bark() override{
        return voice;
    }
    
    void Eat() {
        cout << food << endl;
    }
    //虚函数再被重写
    int MaxSize() override {
        cout << "this is cat: ";
        return 10;
    }
    
};






void PrintEat(Animals* a){
    a->Eat();
}

void PrintBark(Animals*  a ){
    cout << a->Bark() << endl;
}

void PrintMaxSize(Animals* a){
    cout << a->MaxSize() << endl;
}



void Inheritant_Test(){
    
    Cat1* c1 =  new Cat1 ("miao", "fish");
    Dog1* d1 = new Dog1("wangwang");
    PrintBark(c1);
    PrintBark(d1);
    
    PrintEat(c1);
    PrintEat(d1);
    c1->Eat();
    d1->Eat();
    
    PrintMaxSize(c1);
    PrintMaxSize(d1);
    
    
    
}
