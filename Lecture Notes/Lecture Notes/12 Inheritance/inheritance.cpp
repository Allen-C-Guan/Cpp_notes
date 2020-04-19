# include <iostream>
using namespace std;

class Entity{
public:
    float X, Y;
    void Move(float xa, float ya){
        X += xa;
        Y += ya;
    };
};

class Player : public Entity{
public:
    const char* name;
    void print(){
        cout << name << endl;
    };
};


void inheritance_test(){
    Player player;
    player.name = "Allen";
    player.print();
    player.Move(5,10);
    cout << player.X << ", " << player.Y << endl;;
    
    
    //继承的用途
    /*
     父类能用的东西，子类都能用。甚至可以直接赋值使用。
     */
    Entity e;
    cout << e.X << ", " << e.Y << endl;
    e = player;
    cout << e.X << ", " << e.Y << endl;

    
    
}
