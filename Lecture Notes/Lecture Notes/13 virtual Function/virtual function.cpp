# include <iostream>
# include <string> // string不是primitive 因此要include，string
# define Print(x) cout << x << endl;
using namespace std;
/*
 virtual function指的是 overriding  可以实现抽象方法 抽象类和动态绑定！！！
 虚函数只能借助于指针或者引用来达到多态的效果。
 
 动态绑定的动态指的是运行时才决定的， 静态指的是编译的时候就决定好的 (overloading，overriding）
 
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


class Animal{
public:
    virtual void bark (){
        Print("Not defined yet");
    }
};


class pats{  // 抽象类
public:
    virtual void eat() = 0;
};


class Cat : public Animal, pats{ //可以继承个
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


void virtual_function(){
    Entity* e = new Entity();    //这里e只是存储了instance的指针而已
    cout << e -> getName() << endl; // 指针要想使用instance的函数，只能用箭头，而不能用"."
    
    Player* player = new Player("Allen");
    cout << player -> getName() << endl;
    
    // 上面这个例子中说明这是overriding 就是子类直接覆盖了父类的函数
    
    /*如果我想采用动态绑定
    什么是动态绑定，那就是即使我把子类，赋值给父类变量，但是自己仍然可以保持个性（保护自己的方法不受干扰） 那就需要动态绑定
    例如 我有个Dog, Cat, 都是Animal, 且dog和cat都已经复写了父类的函数，这时候我们有一组obj，这个obj里既有cat也有dog，
    那么我们想统一处理， 那么函数的传入参数必须且一定是Animal了，可以一旦变成了Animal你的个性都没了，那怎么办呢？
     
     这时候就用virtual function了
     在java中，动态绑定不需要把method定义为virtual（abstract），只要你采用了声明父类来赋值子类，动态绑定就会生成
     但是这在c++中并不可以，只有声明为virtual的，才有可能出现这个效果，不然就一定是overloading, 既子类的特性就没了。
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
    
    
    /*
    一句话解释 interface在c中的作用，  abstract method
    注意：
    1. 如果一个class 含有interface， 那么这个class就不能实例化。
    2. 如果子类没有全部的定义所有interface，那么子类也依然是一个抽象类，直到所有所有virtual function都被定义了，这才是一个可实例化的类。
    3. 可以继承很多个类， java只能继承一个类。
    
    */
    
    c->eat();  //这就吃鱼了
}
