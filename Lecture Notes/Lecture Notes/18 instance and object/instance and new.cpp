# include <iostream>
# include <string>
using namespace std;

/*
 memory 主要分成stack 和heap
 stack memory主要负责scope， 这也是scope运行的原理， 一个变量在内存中的位置取决于声明的时候，变量会在声明的时候被压入stack，
 然后等用过了之后，就被弹出来
 heap并不是这样的，heap会压入之后进行排序，然后一直存在，直到你让他删除，他才删除
 
 */


class Entity{
private:
    string m_name;
public:
    Entity() :m_name("unknown") {};
    Entity(const string& name): m_name(name){};
    const string& GetName() const{return m_name;};    //返回的string是个const， 函数不可更改类中属性。
};


void instance_tst (){
    /*
     stack类型的实例化
     使用原则， 如果你可以用这种方法创建obj，就用这个方法创建obj，这个方法最快，而且最方便管理！
     这是因为这个变量的建立，和其他变量int, string, 一样，一旦超过了scope，（从if for function 里出来）这个obj就会被自动销毁。不用手动销毁
     */
    
    Entity e;                     // 1. 调用无参构造器。
    Entity e2("Allen");           // 2. 调用有参构造器。
    Entity e3 = Entity("Allen");  // 3. 最常用的方法！！ 也是方法2的另一种写法。
    
    //这里Class_name(val);表示调用构造器实例化。
    
    
    //实验何时销毁
    Entity* ep;
    {
        Entity e_stack = Entity("Allen");
        ep = & e_stack;
    }
    //代码只要执行到这了 *ep就没了内容了，因为被销毁了
    
    
    
    
    
    
    /*
     heap实例化
     使用原则，
     1. 如果你要长时间保存这个实例，因为你要在各种scope下使用。
     2. 这个obj太大了，stack很小的。这时候就要用heap
     
     使用方法：
     1. 对于单个obj：
        Class* c = new Class(传入参数);
        delete c;
     2. 对于array：
        Class* e = new Entity[50];  //size是必须要先给出来的，方便分配内存单元。
        delete[] e;
     
     注意事项：
     1. 使用new keywords
     2. 只能使用指针来初始化 Class* c = new Class(传入参数);  这里c是一个pointer。new只能用pointer来实例化。
     3. 使用delete来销毁， 使用new就一定需要手动管理这个instance，只要你不delete，这个东西就会一直存在，直到程序关闭。
     */
    
    //实验何时销毁
    Entity* ep2;
    {
        Entity* entity_heap = new Entity("Allen");
        ep2 = entity_heap;
    }
    //到这里依然存在
    
    delete ep2;
    
    
    /*
     new的使用和测试：
     注意：new返回的永远是一个pointer，不管你new的是obj，primitive or class or obj你获得永远都是pointer.
     
     new的工作方式分成两部分：
     1. 内存中开辟空间， new int[10] 会开辟40个连续Bytes的空间
     2. 调用constructor 他会调用constructor函数来对其进行实例化。
     
     delete的工作方式也分成两部分
     1. call destuctor
     2. free memory
     
     有new就一定要有delete
     */
    
    int a = 5;
    int* b =new int[4];
    Entity* enitityArray = new Entity[50];
    
    delete[] b;   //如果new的是array，就要用加上[]
    delete[] enitityArray;
    
    
    /*
     new 的高阶用法 replacement
     直接覆盖内存， anotherEArr会直接覆盖entityArray的内存空间，这种直接覆盖内存的方式非常的牛逼。
     */
    Entity* anotherEArr = new(enitityArray) Entity[50];
    
    delete[] anotherEArr;
    
    
    
    
    
}
