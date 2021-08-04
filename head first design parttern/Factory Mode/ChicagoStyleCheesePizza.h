//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLECHEESEPIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLECHEESEPIZZA_H

#include "Pizza.h"
class ChicagoStyleCheesePizza : public Pizza {
public:
    ChicagoStyleCheesePizza(std::unique_ptr<PizzaIngredientFactory> ingreFactory)
            :Pizza(std::move(ingreFactory)) {}
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLECHEESEPIZZA_H
