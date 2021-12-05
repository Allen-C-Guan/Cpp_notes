//
// Created by Allen on 5/12/21.
//
#include <iostream>

class CaffeineBeverageWithHook {
public:
    // 这里是算法框架。算法也只有这一个算法入口。实现接口都不对外开放，因此都是private的
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        // 这个customerWantsCondiments就是个钩子函数，子类可以通过覆盖这个钩子，来实现控制算法流程的方法
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }
private:
    // 这里是子类可以决定的实现细节
    virtual void brew() = 0;
    virtual void addCondiments() = 0;// 因此默认什么也不加

    void boilWater() {
        std::cout << "boiling water" << std::endl;
    }
    void pourInCup() {
        std::cout << "Pouring int cup" << std::endl;
    }

    // 这就是钩子！
    virtual bool customerWantsCondiments() { // 默认不询问客户加什么东西，也可以是纯虚的
        return false;
    }
};

class CoffeeWithHook : public CaffeineBeverageWithHook {
private:
    void brew() override {
        std::cout << "Dripping Coffee through filter" << std::endl;
    }
    void addCondiments() override {
        std::cout << "Add Suger" << std::endl;
    }
    // 我们认为coffee的客人总有特殊需求，这个需求就是加糖。
    bool customerWantsCondiments() override {
        return true;
    }
};

class TeaWithHook : public CaffeineBeverageWithHook {
private:
    void brew() override {
        std::cout << "Dripping Tea by Cup" << std::endl;
    }
    // 默认茶就是什么都不能加
    void addCondiments() override { }
    // 我们认为tea的客人总有没有特殊需求。
    bool customerWantsCondiments() override {
        return false;
    }
};

int main ()
{
    TeaWithHook teaWithHook = TeaWithHook();
    CoffeeWithHook coffeeWithHook = CoffeeWithHook();

    teaWithHook.prepareRecipe();
    coffeeWithHook.prepareRecipe();

}
