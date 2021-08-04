//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
#include <string>
#include <memory>
class Dough { };

class Sauce { };

class Veggies {};

class Cheese {};

class Pepperoni {};

class Clams {};

class FreshClams : public Clams {};

class FrozenClams : public Clams {};

class MozzarellaCheese : public Cheese {};

class ReggianoCheese : public Cheese {};

class PlumTomatoSauce : public Sauce {};

class MarinaraSauce : public Sauce {};

class ThinkCrustDough : public Dough {};

class ThinCrustDough : public Dough {};

enum PizzaType
{
    CHEESE = 0,
    VEGGIE,
    CLAM,
    PEPPERONI
};


class PizzaIngredientFactory {
public:
    virtual std::unique_ptr<Dough> createDough() = 0;
    virtual std::unique_ptr<Sauce> createSauce() = 0;
    virtual std::unique_ptr<Cheese> createCheese() = 0;
    virtual std::unique_ptr<Veggies> createVeggies() = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::unique_ptr<Clams> createClam() = 0;
    virtual ~PizzaIngredientFactory() = default;
};

/*
 * ************* 抽象层 ****************
 * pizza所代表的抽象层级，是工厂模式的核心，高级模块和低级模块均依赖中间的这个抽象层的实现。
 */


class Pizza {
public:
    Pizza(std::unique_ptr<PizzaIngredientFactory> ingreFactory)
        : ingreFactory_(std::move(ingreFactory)) {}
    virtual ~Pizza() = default;
    // 纯虚接口供给子类自己实现
    void prepare ();
    void bake();
    void cut ();
    void box ();
    void setName();
    std::string getName();
protected:
    std::string name;
    std::unique_ptr<Dough> dough;
    std::unique_ptr<Sauce> sauce;
    std::unique_ptr<Veggies> veggies[5];
    std::unique_ptr<Cheese> cheese;
    std::unique_ptr<Pepperoni> pepperoni;
    std::unique_ptr<Clams> clams;
private:

    std::unique_ptr<PizzaIngredientFactory> ingreFactory_;
};



#endif //HEAD_FIRST_DESIGN_PARTTERN_PIZZA_H
