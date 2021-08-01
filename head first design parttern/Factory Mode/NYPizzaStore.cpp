//
// Created by Allen on 2021/8/1.
//

#include "NYPizzaStore.h"
#include "NYStyleCheesePizza.h"
#include "NYStylePepperoniPizza.h"

std::unique_ptr<Pizza> NYPizzaStore::createPizza(PizzaType pizzaType) {
    switch(pizzaType) {
        case CHEESE:
            return std::make_unique<NYStyleCheesePizza>();
        case PEPPERONI:
            return std::make_unique<NYStylePepperoniPizza>();
        default:
            return nullptr;
    }
}
