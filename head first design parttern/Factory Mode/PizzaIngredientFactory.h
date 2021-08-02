//
// Created by Allen on 2021/8/2.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_PIZZAINGREDIENTFACTORY_H
#define HEAD_FIRST_DESIGN_PARTTERN_PIZZAINGREDIENTFACTORY_H
#include "Pizza.h"


class PizzaIngredientFactory {
public:
    virtual std::unique_ptr<Dough> createDough() = 0;
    virtual std::unique_ptr<Sauce> createSauce() = 0;
    virtual std::unique_ptr<Cheese> createCheese() = 0;
    virtual std::unique_ptr<Veggies> createVeggies() = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::unique_ptr<Clams> createClam() = 0;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_PIZZAINGREDIENTFACTORY_H
