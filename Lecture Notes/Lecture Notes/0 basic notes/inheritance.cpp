# include <iostream>
using namespace std;
class Chef{
public:
    void makeChicken(){
        cout << "the chief is cooking chicken" << endl;
    }
    void makeSalad(){
        cout << "the chief is cooking salad" << endl;
    }
    void makeSpecialDish(){
        cout << "the chief makes bbq ribs" << endl;
    }

};
/*
 * 继承
 */
class ItalianChef  : public  Chef{
public:

    //自己特有的function
    void makePasta(){
        cout << "the chief makes pasta" << endl;
    }
    // overriding
    void makeChicken(){
        cout << "the italian make chicken" << endl;
    }
    //overloading  即 signature不一样
    void makeChicken(string kind){
        cout << "the italian make " << kind << " chicken";
    }
};


int inheritance(){
    Chef chef;
    chef.makeChicken();

    ItalianChef chef2;
    chef2.makeSalad();

    chef2.makePasta();
    chef2.makeChicken();
    chef2.makeChicken("good");
    return 0;
}
