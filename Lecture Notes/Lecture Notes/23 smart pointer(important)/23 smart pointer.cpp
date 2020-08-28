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
                        ***   smart pointer   ***
     smart pointer的作用是： 为了解决自动化的管理创建在heap上的instance的删除问题。
     
     
                    ****  unique pointer  ****
     定义： unique pointer是一个scope pointer，且该pointer不接受复制。
     原理： 当unique pointer被创建的时候，在stack上分配一个地址用来存放该new返回的的pointer，而当scope结束的时候，
            就会call delete来删除这个object。
     注意： instance被建立在了heap上， 只是pointer被存放在了steak上而已！因此要想删除这个instance依然要call delete。
     使用原则： 能用则用。除非一定要share
     使用方法：
     1. 需要显示调用 explicit： 即：instance_name (new Class_name)
     2. 返回的是pointer， 也就是说 unique_ptr<Entity> e (new Entity) 中的e是个pointer。
     3. 不可以复制，因此也不可以赋值，在函数传递的时候，会有很多问题。这是因为unique pointer每个obj只能有一个，多余没有任何意义。
     一个删除了，相应呢内存就会被释放，其他的pointer继续指向一个被释放的内存还有什么意义？
     */
    
    {
        unique_ptr<Entity2> entity(new Entity2);
        entity -> Print();
        
        //更加安全的做法是
        unique_ptr<Entity2> e_safe = make_unique<Entity2>();
    }
    // 当运行到括号结束的时候， 这个pointer就自动删除了，这个内存就free了
    
    
    
    /*
    ——————————————————————————————————————————————————————————————————————————————————————————————————————
     share pointer
     作用：！！！
        若对于一个存放在heap中的instance，有share pointer A，B 和 C都指向了该instance， 那么对A，B和C的scope，取并集，
        就会得到这个instance可以存在的scope的范围了。其中A，B，C的scope的关系可以是嵌套，也可以是相离，（例如B是个被调用的函数）。
        因此该方法可以实现instance被函数调用， 复制，引用等。并在无用的时候被自动delete。
     
     工作原理： 该pointer会记录有多少个引用，多一个引用+1， 少一个引用减1(由于某些pointer的超出了scope而被删除），当cnt ==0 时候，就在heap上delete这个instance。
     
     使用方法：share pointer可以替代绝大部分的new的情况。这是一种最接近new的方式的smart pointer。
     
     注意：
     1). share pointer只是复制pointer，而不是instance。
     2). 所有shared_ptr存放的都是同一个地址，即该instance的heap地址
     3). reference的减法，share_ptr的删除是因为超出了scope而被删除。因此每次跳出一个scope， 就有几个share pointer超出了scope，reference就会相应的减几。
     
     
     
     
     其所实现的功能具体可表现为：
     { shared_ptr<type> ptr_outside;
        {
            {
                share_ptr<type> ptr_inside = make_shared... ;
                ptr_outside = ptr_inside;
            }
        }
            只要在outside对应的scope之内，就还没有被删除。
     }
        到这里的时候就被删除了。
     
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
                                    ****   weak_ptr   *****
     
     功能：只是想查看pointer，并不想更改scope的范围。
     原理：用weak ptr来获取sharepointer 的时候，并不会增加share pointer 的计数器，因为他没有copy，只是用来引用而已。
     
     */
    {
        shared_ptr<Entity2> sharedptr = make_shared<Entity2>();      //创建shared pointer cnt = 1
        weak_ptr <Entity2> weakPtr = sharedptr;                      // 引用shared pinter cnt += 0   cnt = 1
    }                                                                // cnt -= 1, cnt = 0 销毁
    
};
