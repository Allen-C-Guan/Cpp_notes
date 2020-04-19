#include <iostream>
#include <string>
using namespace std;

void castTst(){
    
    // static cast 是在compile的时候完成的
    //这叫隐式cast， a自然而然就可以变成b
    int a = 5;
    float b = a;
    
    //c style cast
    double c = 5.6;
    int d = (int) c;
    
    //c++ style cast
    double e = 4.6;
    int f = static_cast<int>(e);  // cast成为int；
    
    // 这里c++ 和c之间的style上的不同，本质上没有区别， c++style cast只是一个语法糖，看起来更简单，更容易理解而已。

    
    /*
     dynamic cast
     其功能和instanceof()相同。
     dynamic cast是在run的时候才进行的。
     dynamic cast可以用于判定这个类是否继承与另一个类， 如果是的话，会返回一个ptr，如不是的话，会返回一个null。
     我们就可以利用这个返回值，来做条件，产生判定
     
     其工作原理就是RTTI（run time type information)中在运行的过程中，记录了原来的类。保留了之前class的痕迹。这才让dynamic
     cast得以执行。当然这期间就需要额外的开销，比如需要额外的时间来cast，需要额外的空间来存储痕迹。
     
     但是dynamic cast必须要求base class是个抽象的class。即有virtual的function
     */
    
    class Entity{
    public:
        virtual void PrintName(){}
    };
    class Player: public Entity{};
    class Enemy : public Entity{};
    
    Player* player = new Player(); //player 具有两个type entity and player
    Entity* e1 = player;
    //这种自下而上的cast是可以自然而然，implicit就是完成的。
    
    
    //当多态存在的时候，cast就可以进行了。这就增加了危险性
    Entity* enemy = new Enemy();
    
    //强行cast,这种行为很危险。
    //c style
    Player* player1 = (Player*)enemy;
    //c++ style
    Player* player2 = static_cast<Player*>(enemy);
    
    //dynamic cast
    //这里要求base类是一个virtual的类才行。
    Player* playerd = dynamic_cast<Player*>(enemy);  //这个返回的就是null
    
    
    Player* playerp = dynamic_cast<Player*>(e1);  //这个就返回的是地址了。不是null了
    
    /*
     因此我们可以利用其返回值，来作为条件，进行后面的代码执行。
     */
    
    if (playerd){
        
    }else{
        
    }
    
    
    
    
    
    
    
    
    
}
