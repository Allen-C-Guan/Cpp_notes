# include <iostream>
# include <string>
using namespace std;


/*
                **** arrow operator ****
 "->"最常见的用途是用作语法糖。既用来代替 "(*obj)" 的一种更加优雅的写法。
 但是利用overloading operator，可以让 "->" 实现更加复杂和更加优雅的目的。
    ie. 对于一个obj你可以这样使用， e->print();
        且有个ptr存放这个e， 你如果不对ptr的“operator->”进行overloading， 你就不能使用 ptr->print();
        但是如果你overloading “operator ->”， 并让其返回e后，则就可以直接使用 ptr->print()了;
 */


class Entity11{
public:
    int x;
    void Print() const {cout << "hello this is arrow test" << endl;}
};

/*
 这是一个自定义的scope pointer，可以在out of scope的时候，自动删除存放在heap上的instance。
 */
class ScopePtr{
private:
    Entity11* m_obj;
public:
    ScopePtr(Entity11* entity)  //传入的应该是一个entity的ptr，new得到的结果就是一个ptr
    : m_obj(entity)
    {}
    
    // 因为m_obj 是个private,所以就要有个getter，可是有个getter就不好看了，你就要写, entity.GetObj()->Print()
    Entity11* GetObj(){
        return m_obj;
        
    }   //返回的是一个entity的ptr
    
    //我如果override一下pointer
    
    Entity11* operator -> (){   // entity->  == m_obj了，就牛逼了，就可以用entity -> Print();了
        return m_obj;
    }
    
    Entity11* operator -> ()const {   // entity->  == m_obj了，就牛逼了，就可以用entity -> Print();了
        return m_obj;
    }
    
    ~ScopePtr(){
        delete m_obj;
    }
};

void ArrowTst(){
    Entity11* ptr2;
    /*
     ->的作用只是一个语法糖而已，没什么卵用，本质上  (*ptr) ==  ptr->
     */
    ptr2-> Print();
    (*ptr2).Print();
    
    
    //ScopePtr
    cout << "\n test ScopePtr" << endl;
    ScopePtr entity = new Entity11;   //这个正好是对的， new返回的是ptr， 而scope接受的就是ptr。
    entity.GetObj()->Print();  //这个写法就有点蠢, 当然你也可以吧getobj函数改一下，改成返回*m_=obj;
    
    entity->Print(); // entity-> == entity.->() == m_obj 
    
    const ScopePtr constEntity = new Entity11;
    /*
     const obj要求的是所有的函数必须是const的。函数const指的是函数后面的const，即函数内部不能改变这个obj的内容。这个逻辑才是完整的。
     const obj指的是这个obj不能动，那么如果你把这个obj给放到非const的函数里，那这obj出来的时候，不就有可能不是那个obj了。
     */
    constEntity -> Print();
    

}
