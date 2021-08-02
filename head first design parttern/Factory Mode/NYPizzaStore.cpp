//
// Created by Allen on 2021/8/1.
//

#include "NYPizzaStore.h"
#include "NYStyleCheesePizza.h"
#include "NYStylePepperoniPizza.h"
#include "ChicagoPizzaIngredientFactory.h"
#include "NYPizzaIngredientFactory.h"
std::unique_ptr<Pizza> NYPizzaStore::createPizza(PizzaType pizzaType) {
    switch(pizzaType) {
        case CHEESE:
            return std::make_unique<NYStyleCheesePizza>(std::make_unique<NYPizzaIngredientFactory>());
        case PEPPERONI:
            return std::make_unique<NYStylePepperoniPizza>(std::make_unique<NYPizzaIngredientFactory>());
        default:
            return nullptr;
    }
}
