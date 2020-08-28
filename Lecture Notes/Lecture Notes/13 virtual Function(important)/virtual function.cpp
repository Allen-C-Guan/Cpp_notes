# include <iostream>
# include <string> // string不是primitive 因此要include，string
# define Print(x) cout << x << endl;
using namespace std;
/*
————————————————————————————————————————————————————————————————————————————————————————————————————————
            ***************** c++的多态  ************************
 c++的多态主要由两部分组成
 1) 静态多态（编译的时候确定）
    该多态在编译的时候，编译器就给确定下来了， 是一种覆盖性的多态。
 2）动态多态（运行的时候确定）
    代码在运行的时候，会根据实际情况来选择运行哪个。 是一种并存的多态。


 
 *** 静态绑定与动态绑定的区别  ****
 1） 静态多态
   i). overloading：
        例如 void build(int x ){};
            void build(double y){};
        对于同一个名称的函数进行overloading，编译器在编译的时候，会选择恰当的函数放在被调用处。
            例如： cpp中出现 build(0.5); 编译的时候，该部分会自动调用第二个函数，第一个函数就压根不会在obj文件中出现。
    
 2). 动态多态
    动态多态采用v table来记录所有同名的function， 并在运行的时候根据v table，来临时决定该instance该调用哪个的函数。
    即
            v table类似于
 
                /  char function1 (int a ){body1};
    function1() -  char function1 (int a){};
                \  char function1 (int a){body};
    
    当我们调用function1的时候， 我们需要去查看table，来选择我们到底要调用哪个function。因此，这3个function都在obj文档里会
    出现。3个都是备胎。选哪个临时决定。

 
 *** 动态多态与静态多态在继承中的区别 ****
 
 当overriding在继承中出现的时候：
  静态绑定（没有virtual）：  指针绑定function，指针是父类则调用父类function， 指针是子类则调用子类function。
  动态绑定（有virtual）： instance type绑定function。当用父类指针调用子类的时候，function永远是使用该子类自己的function。
 
 因此，区别可以总结为，动态绑定可以将所有子类统一为父类进行处理，但却保留了子类自己的“个性”。而静态多态则会把所有子类的个性全部统一成父类。
 
 
 *** 动态多态的使用 ***：
    父类函数前加上virtual， 子类body前加上override。并保障signature相同。
    class base{
    virtual int function_name (传参1){body_base};
    };
    
    class child : public base{
    int function_name (传参1) override {body_child}
    };
    
 
 
 ** 多态实现的条件
    ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    1）base中的virtual function，并在child functon 中被override了。
    2) 通过base的指针来调用函数，或直接调用或引用virtual function。
        i). base的指针来调用：
                base* base_instance = child_instance;
            此时， base_instance就是一个base指针，而这个base指针指向了一个 child_instance.
        
        ii). 调用virtual function
                void ExampleFunction(base* b){};    所有的instance都会通过base pointer来调用
                ExampleFunction(child_instance);    当传入参数是child instance的时候。
            
    ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
 
 
                    **************** interface *********************
 
    interface 与 virtual function之间最大的不同在于， virtual function如果不被子类重新写，那么子类会继承父类的virtual
    function 的body， 但interface却强制性的要求子类必须要override该virtual function。
 
 
    *** interface的实现 ***：
    在base class中: virtual int function1(传参2) = 0;
    在child class中： int function1(传参2) override { body};
 
 
    *** 使用注意 ***：
       1. 如果一个class 含有pure virtual function, 那这个class就是一个interface， 因此这个class就不能实例化。
       2. 如果子类没有override全部的interface，那么子类也依然是一个interface，直到所有所有virtual function都被override了，这才是一个可实例化的类。
       3. 可以继承很多个类， java只能继承一个类。
 
 
         **** 如何理解继承树 ****
        继承就像一棵树，但是你只需要知道父类们的合集包括什么即可，（父类的父类的内容也是父类中的一部分），则父类中的全部特征的集合，即为子类的通用属性。
        
       
 
 
 
 ————————————————————————————————————————————————————————————————————————————————————————————————————————
 */

class Entity{
public:
    string getName(){
        return "Entity";
    }
};


class Player: public Entity{
private:
    string m_Name;
public:
    Player(const string& name){
        m_Name = name;
    }
    string getName(){
        return m_Name;
    }
};


// virtual function example
class Animal{
public:
    virtual void bark (){
        Print("Not defined yet");
    }
};


// interface example
class pats{
public:
    virtual void eat() = 0;
};


//多继承
class Cat : public Animal, pats{ //可以继承多个
public:
    void bark() override {
        Print("MiaoMiao");
    }
    void eat() override {
        Print("fish")
    }
};



void animalBark(Animal* a){
    a->bark();
}



//——————————————————————————————————- test ————————————————————————————————————————————————
void virtual_function(){
    Entity* e = new Entity();    //这里e只是存储了instance的指针而已
    cout << e -> getName() << endl; // 指针要想使用instance的函数，只能用箭头，而不能用"."
    
    Player* player = new Player("Allen");
    cout << player -> getName() << endl;
    
    // 上面这个例子中说明这是静态绑定 就是子类直接覆盖了父类的函数
    
    /*如果我想采用动态绑定
    什么是动态绑定，那就是即使我把子类，赋值给父类变量，但是自己仍然可以保持个性（保护自己的方法不受干扰） 那就需要动态绑定
    例如 我有个Dog, Cat, 都是Animal, 且dog和cat都已经复写了父类的函数，这时候我们有一组obj，这个obj里既有cat也有dog，
    那么我们想统一处理， 那么函数的传入参数必须且一定是Animal了，可以一旦变成了Animal你的个性都没了，那怎么办呢？
     
     这时候就用virtual function了
     声明 base function 为virtual的，才有可能出现动态绑定，不然就一定是静态绑定, 既子类的特性就没了。
    */
    
    //Entity和player这么写就无法完成动态绑定
    Entity* entity = player;  // 把子类赋值给父类
    cout << entity -> getName() << endl;  //输出的还是父类！！ 这就没有存在动态绑定。
    
    
    //animal and cat
    Animal* a = new Animal();
    Cat* c = new Cat();
    a->bark();
    c->bark();
    
    Animal* b = c;
    b -> bark();  //这里b还是可以喵喵叫即使b被定义成animal
    
    
    //有什么用呢？？用处在这里
    /*这里c是猫， 如果不用动态绑定的话就很麻烦，因为animalBark function接收的是Enitity， 编译器看到是enitity就会去entity里面找，
     然后找到了not define yet, 可是如果我们加了一个virtual，那么就会有一个virtual table被建立起来了，遇见entity之后，会在所有
     entity子类里面去寻找对应的被override的函数，然后予以运行。这就是动态绑定！！！
     
     例如在这里， c被变成了entity，然后去使用函数bark()，在找到bark()之后，就发现他是一个vitural， 那我就在看看这个virtual表，
     表里写着 cat - > bark() {miaomiao} ， 而c就是个喵喵，好了那就输出喵喵了
     
     
     因此我们可以看到，要想实现动态绑定，就必须要用指针来实现，因为实例之间怎么可以赋值呢， 只有指针才可以跳转和赋值。
     */
    animalBark(c);
    c->eat();  //这就吃鱼了
}
