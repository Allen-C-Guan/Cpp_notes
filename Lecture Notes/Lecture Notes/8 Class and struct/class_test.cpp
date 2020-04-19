# include <iostream>
# define LOG(x) cout << x << endl
using namespace std;

class Player{
public: //默认情况下的visability是private
    int X, Y;
    int speed;
    
    void Move(int a, int b){
        X += a;
        Y += b;
    }
};

void Move(Player& player, int a, int b){
    player.X += a;
    player.Y += b;
}



/*      struct
 
 struct从技术上来讲 struct和class只是默认可见度不同而已。
 struct默认的是public， class默认的是private
 
 
 如何区分使用struct和class？
 其实不用区分，但是为了增加代码的可读性，我们可以采用这样的规定
 
 struct只用来存放一堆数据。 比如 坐标， 人的基本信息，或者简单的处理一下信息。例如加减坐标，打印输出等。
 class可以拥有丰富的功能。 比如 闹钟，闹钟有很多的功能，报时，铃声等function。
 
 不使用struct来继承。
 
 
 */

struct MainPlayer{
    
    int X, Y;
    int speed;
    
    void Move(int a, int b){
        X += a;
        Y += b;
    }

};


void class_test(){
    Player player1;
    cout << player1.X << player1.Y << endl;
    Move(player1, 1, -1);
    cout << player1.X << player1.Y << endl;
    
    player1.Move(10, 100);
    cout << player1.X << player1.Y << endl;
    
    MainPlayer mainPlayer;
    mainPlayer.Move(-1000, -49999);
    cout << mainPlayer.X << mainPlayer.Y << endl;
    
    
    
    
    
}
