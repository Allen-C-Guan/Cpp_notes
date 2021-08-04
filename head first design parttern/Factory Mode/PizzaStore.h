//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_PIZZASTORE_H
#define HEAD_FIRST_DESIGN_PARTTERN_PIZZASTORE_H

#include <memory>
#include "Pizza.h"

class PizzaStore {
public:
    // 父类工厂控制生产流程
    std::unique_ptr<Pizza> order(PizzaType pizzaType);
    virtual ~PizzaStore() = default;
private:
    // 子类工厂负责实现细节
    virtual std::unique_ptr<Pizza> createPizza(PizzaType pizzaType) = 0;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_PIZZASTORE_H
