# include <iostream>
using namespace std;


/*
                        **** 继承 ****
 继承的意义： 继承可以实现 将通用功能定义在父类之中，子类无需重复定义通用功能即可拥有，只需要修改细节即可实现子类的全部功能的目的。
 继承的使用方法：*public base*
    例如：
     class child_name : public base_name
     {
        body
     }
 
 更多关于继承的内容，请看章节： *13 virtual function* 
 
 */
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


//———————————————————————————————————— test ————————————————————————-——————————
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
