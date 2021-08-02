//
// Created by Allen on 2021/8/2.
//

#include "ChicagoPizzaStore.h"
#include "ChicagoStyleCheesePizza.h"
#include "ChicagoStylePepperoniPizza.h"
#include "NYPizzaIngredientFactory.h"
std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(PizzaType pizzaType) {
    switch (pizzaType) {
        case CHEESE:
            return std::make_unique<ChicagoStyleCheesePizza>(std::make_unique<NYPizzaIngredientFactory>);
        case PEPPERONI:
            return std::make_unique<ChicagoStylePepperoniPizza>(std::make_unique<NYPizzaIngredientFactory>);
        default:
            return nullptr;
    }

}
