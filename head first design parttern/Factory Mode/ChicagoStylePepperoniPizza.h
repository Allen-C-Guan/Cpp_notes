//
// Created by Allen on 2021/8/2.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLEPEPPERONIPIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLEPEPPERONIPIZZA_H
#include "Pizza.h"

class ChicagoStylePepperoniPizza : public Pizza {
public:
    ChicagoStylePepperoniPizza(std::unique_ptr<PizzaIngredientFactory> ingreFactory)
            :Pizza(std::move(ingreFactory)) {}

};


#endif //HEAD_FIRST_DESIGN_PARTTERN_CHICAGOSTYLEPEPPERONIPIZZA_H
