#include <iostream>

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
        otherObject.Collide(*this); // 这里让又实现了多态。
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

