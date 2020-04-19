# include <iostream>
# include <string>
using namespace std;

class Entity{
private:
    string m_Name;
    int m_Age;
public:
    Entity(const string& name)
    : m_Name(name), m_Age(-1) {}
    
    Entity(int age)
    : m_Name("unknown"), m_Age(age) {}
    
    const string GetName() const{
        return m_Name;
    }
    
    
};

void PrintEntity(const Entity& e){
    cout << e.GetName() << endl;
}


void explicit_and_implicit_tst(){
    /*
     一下三种方法是完全相同的
     第一种方法是常用的方法，也和java相似的，
     第二种方法是c特有的， 他会直接调用对应的constructor
     第三种方法只有c有，由于Entity有个constructor可以接受 int， 那么等于就可以直接调用对应的constructor来进行实例化，
            这种方法常见于函数调用的情况！！！
     
     而这第三种，就是我们所说的implicit,这是一种隐式的方法，最好不要用它来init，function的时候可以用，但是init的时候，会让人觉得很奇怪。
     */
    Entity a = Entity(9);
    Entity b("Allen");
    Entity c = 9;
    
    PrintEntity(25);//这里你就发现，竟然可以这么干！打印25也行？？
    PrintEntity(string("Allen"));  // 这是因为”Allen“是const char，不是string，string和其他所有obj一样，不是自动就成为string的。
    
    /*
     explicit
     我们前面看到了 implicit可以用等号，隐式的调用函数，我也可以直接完全禁止这个方法，那就在声明前面加上 explicit
     */
    
}
