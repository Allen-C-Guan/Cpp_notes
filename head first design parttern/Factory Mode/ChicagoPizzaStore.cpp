//
// Created by Allen on 2021/8/2.
//
#include "ChicagoPizzaStore.h"
#include "ChicagoStyleCheesePizza.h"
#include "ChicagoStylePepperoniPizza.h"
#include "ChicagoPizzaIngredientFactory.h"
std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(PizzaType pizzaType) {
    switch (pizzaType) {
        case CHEESE:
            return std::make_unique<ChicagoStyleCheesePizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
        case PEPPERONI:
            return std::make_unique<ChicagoStylePepperoniPizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
        default:
            return nullptr;
    }

}
