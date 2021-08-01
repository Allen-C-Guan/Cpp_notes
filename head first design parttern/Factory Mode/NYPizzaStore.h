//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_NYPIZZASTORE_H
#define HEAD_FIRST_DESIGN_PARTTERN_NYPIZZASTORE_H

#include "PizzaStore.h"
class NYPizzaStore : public PizzaStore {
private:
    // 子类自己的实现
    std::unique_ptr<Pizza> createPizza(PizzaType pizzaType) override;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_NYPIZZASTORE_H
