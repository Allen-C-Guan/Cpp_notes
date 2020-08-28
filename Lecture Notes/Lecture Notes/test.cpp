#include <iostream>
#include <array>
#include <memory>
using namespace std;


class Foo{
public:
    Foo(){
        cout << "Constructed" << endl;
    };
    ~Foo(){
        cout << "Destructed" << endl;
    }
};

void test(){
    weak_ptr<Foo> t;
  
    {
        
        std::shared_ptr<Foo> f = std::make_shared<Foo>();
        t = f;
        
    }
}
