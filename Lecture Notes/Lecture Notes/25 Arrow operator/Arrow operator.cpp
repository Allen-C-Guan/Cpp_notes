# include <iostream>
# include <string>
using namespace std;

class Entity11{
public:
    int x;
    void Print() const {cout << "hello this is arrow test" << endl;}
};


/*
 这个函数的作用在于，我们获取的是利用new 创建的entity。 这个entity自然就是ptr，因此需要在scope之外的时候，删除这个ptr，从而释放内存
 ********************************************************************
 这个原理是因为，你把一个stack变量的声明周期和一个new变量声明周期捆绑在了一起，你用new建立的是entity！ 不是scopePtr啊
 你的scopeprt仍然在stack里面，一旦出了scope，你这ptr就被删除了，而就在你被删除的时候 你也把entity也拉下水了。
 *******************************************************************
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
    Entity11* ptr;
    /*
     ->的作用只是一个语法糖而已，没什么卵用，本质上  (*ptr) ==  ptr->
     */
    ptr -> Print();
    (*ptr).Print();
    
    
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
