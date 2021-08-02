//
// Created by Allen on 2021/8/2.
//

#include "ChicagoPizzaIngredientFactory.h"

std::unique_ptr<Dough> ChicagoPizzaIngredientFactory::createDough() {
    return std::unique_ptr<ThinkCrustDough>();
}

std::unique_ptr<Sauce> ChicagoPizzaIngredientFactory::createSauce() {
    return std::unique_ptr<PlumTomatoSauce>();
}

std::unique_ptr<Cheese> ChicagoPizzaIngredientFactory::createCheese() {
    return std::unique_ptr<MozzarellaCheese>();
}

std::unique_ptr<Veggies> ChicagoPizzaIngredientFactory::createVeggies() {
    return std::unique_ptr<Veggies>();
}

std::unique_ptr<Pepperoni> ChicagoPizzaIngredientFactory::createPepperoni() {
    return std::unique_ptr<Pepperoni>();
}

std::unique_ptr<Clams> ChicagoPizzaIngredientFactory::createClam() {
    return std::unique_ptr<FrozenClams>();
}
