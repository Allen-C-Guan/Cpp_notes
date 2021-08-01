//
// Created by Allen on 2021/8/2.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZASTORE_H
#define HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZASTORE_H

#include "PizzaStore.h"

class ChicagoPizzaStore : public PizzaStore {
private:
    std::unique_ptr<Pizza> createPizza(PizzaType pizzaType) override;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_CHICAGOPIZZASTORE_H
