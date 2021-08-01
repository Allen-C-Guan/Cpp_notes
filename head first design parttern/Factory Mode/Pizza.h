//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
#include <string>
class Dough { };

class Sauce { };

class Veggies {};

class Cheese {};

class Pepperoni {};

class Clams {};

enum PizzaType
{
    CHEESE = 0,
    VEGGIE,
    CLAM,
    PEPPERONI
};
/*
 * ************* 抽象层 ****************
 * pizza所代表的抽象层级，是工厂模式的核心，高级模块和低级模块均依赖中间的这个抽象层的实现。
 */

class Pizza {
public:
    // 纯虚接口供给子类自己实现
    virtual void prepare () = 0;
    void bake();
    void cut ();
    void box ();
    void setName();
    std::string getName();
private:
    std::string name;
    Dough dough;
    Sauce sauce;
    Veggies veggies[5];
    Cheese cheese;
    Pepperoni pepperoni;
    Clams clams;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
