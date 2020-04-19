# include <iostream>
# include <memory>
# include <string>
using namespace std;




class Entity2 {
public:
    Entity2(){
        cout << "create an entity" << endl;
    }
    
    void Print(){}
    
    
    ~Entity2(){
        cout << "destory an entity" << endl;
    }
};





void SmartPtrTst(){
    /*
     unique pointer
     使用原则： 能用则用。除非一定要share
     使用方法：
     1. 需要显示调用 explicit
     2. 返回的是pointer， 也就是说 unique_ptr<Entity> e (new Entity) 中的e是个pointer。
     3. 不可以复制，因此也不可以赋值，在函数传递的时候，会有很多问题。这是因为unique pointer每个obj只能有一个，多余没有任何意义。一个删除了，
                其他的还有什么用？？unique pointer也不可以被复制，unique pointer会在out of scope 的时候就删除了。
     */
    {
        unique_ptr<Entity2> entity(new Entity2);
        entity -> Print();
        
        //更加安全的做法是
        unique_ptr<Entity2> e_safe = make_unique<Entity2>();
    }
    // 当运行到括号结束的时候， 这个pointer就自动删除了，这个内存就free了
    
    
    
    /*
     share pointer
     share pointer的方法就是最简单的JAVA GC， 该pointer会记录有多少个引用，多一个引用+1， 少一个引用减1，都没了，就free这个memory。
     share pointer可以替代绝大部分的new的情况。这是一种最接近new的方式的smart pointer。
     
     share pointer是用一个ptr存放obj的ptr的方法。 在shared_ptr的复制的过程中，只是复制了obj的ptr。
     因此所有shared_ptr存放的都是同一个指针，而这个指针指向同一个物理地址上的obj。
     
     但是要注意，所有share pointer的copy，都只是share ptr本身的copy， 既不是原来obj的ptr的copy，也不是obj的copy
     
     
     
     其所实现的功能是： 总能在所有引用该obj的scope里存在。 但不能超过最外层引用的scope。
     { shared_ptr<type> ptr_outside;
        {
            {
                share_ptr<type> ptr_inside = make_shared... ;
                ptr_outside = ptr_inside;
            }
        }
            只要在outside对应的scope之内，就还没有被删除。
     }
     
     */
    shared_ptr<Entity2> sharedEntity = make_shared<Entity2>();
    
    
    /*这个方法一定不能用在share上面
    这一位置你先初始化了一个Entity， 而后你再连接给share pointer，这时候这个这个obj就有两个链接了！！ 实际上你指想要一个pointer。
     这么一搞数就查不明白了。
     
     而计数的次数是通过shared_ptr 被*复制*的次数来决定的。
    */
    shared_ptr<Entity2> sharedEntityWrong(new Entity2);
    
    //这个方法就可以copy， （这是obj(shared_ptr<Entity2>)，而c中obj的赋值默认的是 copy， 在java和python中 obj的赋值默认是link）
    shared_ptr<Entity2> copyShare = sharedEntity;
    
    /*
     shared_ptr的工作方式演示
     */
    
    cout << "\n\nshared ptr demo\n" << endl;
    {shared_ptr<Entity2> foo ;
        {
            shared_ptr<Entity2> orignSharedPtr = make_shared<Entity2>();    //创建instance。引用 = 1
            foo = orignSharedPtr;                                           //引用加一 引用 = 2
        }                                                                   //引用-1  引用 = 1
    }                                                                       //引用-1。 引用 = 0. 销毁instance
    
    /*
     weak_ptr
     weak_ptr 的作用是，用weak ptr来获取sharepointer 的时候，并不会增加sharepointer 的计数器，
     因为他没有copy，只是用来引用而已。
     */
    {
        shared_ptr<Entity2> sharedptr = make_shared<Entity2>();      //创建shared pointer cnt = 1
        weak_ptr <Entity2> weakPtr = sharedptr;                      // 引用shared pinter cnt += 0   cnt = 1
    }                                                                // cnt -= 1, cnt = 0 销毁
    
};
