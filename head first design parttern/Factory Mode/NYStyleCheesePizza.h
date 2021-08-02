//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_NYSTYLECHEESEPIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_NYSTYLECHEESEPIZZA_H

#include "Pizza.h"
#include "NYPizzaIngredientFactory.h"
class NYStyleCheesePizza : public Pizza {
public:
    NYStyleCheesePizza(std::unique_ptr<PizzaIngredientFactory> ingreFactory)
        : Pizza(std::move(ingreFactory)) {}
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_NYSTYLECHEESEPIZZA_H
