//
// Created by Allen on 2021/8/2.
//

#include "NYPizzaIngredientFactory.h"

std::unique_ptr<Dough> NYPizzaIngredientFactory::createDough() {
    return std::unique_ptr<ThinCrustDough>();
}

std::unique_ptr<Sauce> NYPizzaIngredientFactory::createSauce() {
    return std::unique_ptr<MarinaraSauce>();
}

std::unique_ptr<Cheese> NYPizzaIngredientFactory::createCheese() {
    return std::unique_ptr<ReggianoCheese>();
}

std::unique_ptr<Veggies> NYPizzaIngredientFactory::createVeggies() {
    return std::unique_ptr<Veggies>();
}

std::unique_ptr<Pepperoni> NYPizzaIngredientFactory::createPepperoni() {
    return std::unique_ptr<Pepperoni>();
}

std::unique_ptr<Clams> NYPizzaIngredientFactory::createClam() {
    return std::unique_ptr<FreshClams>();
}
