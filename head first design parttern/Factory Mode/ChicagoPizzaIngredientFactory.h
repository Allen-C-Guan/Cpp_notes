//
// Created by Allen on 2021/8/2.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZAINGREDIENTFACTORY_H
#define HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZAINGREDIENTFACTORY_H

#include "Pizza.h"

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory{
public:
    std::unique_ptr<Dough> createDough() override ;
    std::unique_ptr<Sauce> createSauce() override ;
    std::unique_ptr<Cheese> createCheese() override ;
    std::unique_ptr<Veggies> createVeggies() override ;
    std::unique_ptr<Pepperoni> createPepperoni() override ;
    std::unique_ptr<Clams> createClam() override;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZAINGREDIENTFACTORY_H
