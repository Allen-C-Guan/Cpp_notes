#include <iostream>
using namespace std;
class Transaction {
public:
    Transaction();
//    virtual void logTransaction () const = 0;     //pure virtual function
    virtual void logTransaction () const{           // virtual function
        cout << "this is Transaction logTransaction function" << endl;
    }
};
Transaction::Transaction(){
    logTransaction();
}

class BuyTransaction : public Transaction {

    virtual void logTransaction() const override {
        cout << "this is BuyTransaction logTransaction function" << endl;
    }
};

class SellTransaction : public Transaction {
    virtual void logTransaction() const override {
        cout << "this is SellTransaction logTransaction function" << endl;
    }
};

/*
 * 绝不在constuctor或者destructor里面call任何virtual function（包括pure virtual 和 virtual function）。
 * 对于构造函数而言。
 * 首先因为第一点，构造函数的执行顺序是先base 后 derived。 第二点是在执行base construction的时候，编译器默认derived是根本不存在的。
 * 因此base constructor里调用的任何函数都是base里当前已经存在的函数！
 *
 * 基于以上两点，base中即使调用了virtual function，调用的也是base自己的virtual function，即使子类已经override了这个virtual function，
 * 也并不会被调用（因为子类在当前阶段默认是不存在的）。 可是既然一定是要调用基类的function，那么virtual就没有任何意义了。你virtual的目的
 * 不就是实现多态么，你virtual的目的就是想要调用子类自己的function么，可是这点在base constructor期间是不可能实现的，那你莫不如直接不用
 * virtual，直接调用自己的base类的non-virtual function就完事了。
 *
 * 而当base里的virtual 是个pure virtual的时候，问题就更严重了，此时base的constructor正在试图调用一个pure virtual function。这是违法的。
 *
 * 因此无论是pure virtual function还是virtual function，你都不该让他存在在constructor里，因为有没有virtual的结果是一样的，都无非实现
 * 多态，反而让代码容易被误解。
 *
 *
 * 对于destructor而言也是一样的，destructor的调用顺序和constructor相反，先调用子类，后调用父类，那么当父类的destructor被调用的时候，意味着
 * 子类的destructor早已不存在了（被销毁的），既然子类都被销毁了，还谈何多态，没了多态，你要virtual有何用。
 */
int main () {
    BuyTransaction b;
}
