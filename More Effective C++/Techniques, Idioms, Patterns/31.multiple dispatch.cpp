#include <iostream>
/*
 * ******************************** multiple dispatch ********************************
 * C++语言中并不支持对一个以上的对象类型而实现函数的虚化。 
 * 虚函数只能对某一个特定的类型来实现虚化。 但是比如，你想实现 当A和B类型遇见的时候，执行A1函数，当A和C遇见的时候，执行A2函数是不可以的。
 * 
 * 那么我们该这么做呢？我们可以用两个虚函数来凑一个double dispatch。
 * 
 * 具体实现方法如下：
 * 1. 父类中提供一个父类入参的引用来作为批量处理的纯虚函数入口，其可以不感知兄弟类型之间的差异
 * 2. 父类中再提供两两一组的具体实现的虚函数入口。
 * 3. 让批量处理的虚函数入口，去调用入参的虚函数，并将this作为类型传入
 * 
 * 这样就可以实现
 * 1. 父类入口屏蔽类型
 * 2. this所对应的具体类型，实现特性的细节和功能。
 */

class SpaceShipe;
class SpaceStation;
class Asteroid;

class GameObject {
public:
    // 若想让这个函数入口，前提是：静态类型必须是GameObject，但其实如果这个函数不是入口，也没关系，也永远不会出现循环调用的情况，因为其他入口均不存在调用。
    virtual void Collide(GameObject& otherObject) = 0;

    // 这三者之前一定有个出口
    virtual void Collide(SpaceShipe& otherObject) = 0;
    virtual void Collide(SpaceStation& otherObject) = 0;
    virtual void Collide(Asteroid& otherObject) = 0;
};

class SpaceShipe : public GameObject {
public:
    virtual void Collide(GameObject& otherObject) override { //我们通过两个多态，来实现double dispatch，这个入参实现了批量处理。
        otherObject.Collide(*this); // 这里让又实现了多态。 因为*this一定是个确定的具体类型，不是父类型
    }

    virtual void Collide(SpaceShipe& otherObject) override {
        std::cout << "SpaceShipe collide with SpaceShipe" << std::endl;
    }

    virtual void Collide(SpaceStation& otherObject) override {
        std::cout << "SpaceShipe collide with SpaceStation" << std::endl;
    };

    virtual void Collide(Asteroid& otherObject) override {
        std::cout << "SpaceShipe collide with Asteroid" << std::endl;
    }
};


class SpaceStation : public GameObject {
public:
    virtual void Collide(GameObject& otherObject) override {
        otherObject.Collide(*this);
    }

    virtual void Collide(SpaceShipe& otherObject) override {
        std::cout << "SpaceStation collide with SpaceShipe" << std::endl;
    }

    virtual void Collide(SpaceStation& otherObject) override {
        std::cout << "SpaceStation collide with SpaceStation" << std::endl;
    };

    virtual void Collide(Asteroid& otherObject) override {
        std::cout << "SpaceStation collide with Asteroid" << std::endl;
    }
};

class Asteroid : public GameObject {
public:
    virtual void Collide(GameObject& otherObject) override {
        otherObject.Collide(*this);
    }

    virtual void Collide(SpaceShipe& otherObject) override {
        std::cout << "Asteroid collide with SpaceShipe" << std::endl;
    }

    virtual void Collide(SpaceStation& otherObject) override {
        std::cout << "Asteroid collide with SpaceStation" << std::endl;
    };

    virtual void Collide(Asteroid& otherObject) override {
        std::cout << "Asteroid collide with Asteroid" << std::endl;
    }
};

int main () {
    GameObject *spaceShipe = new SpaceShipe();
    GameObject *spaceStation = new SpaceStation();
    GameObject *asteroid = new Asteroid();

    spaceShipe->Collide(*spaceShipe);
    spaceShipe->Collide(*spaceStation);
    spaceShipe->Collide(*asteroid);

    spaceStation->Collide(*spaceShipe);
    spaceStation->Collide(*spaceStation);
    spaceStation->Collide(*asteroid);
}

