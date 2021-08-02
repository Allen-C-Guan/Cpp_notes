//
// Created by Allen on 2021/8/1.
//

#include "Pizza.h"
#include "PizzaIngredientFactory.h"
void Pizza::bake() {

}

void Pizza::cut() {

}

void Pizza::box() {

}

void Pizza::setName() {

}

std::string Pizza::getName() {
    return std::string();
}

void Pizza::prepare() {
    clams = std::move(ingreFactory_->createClam());
    dough = std::move(ingreFactory_->createDough());
    sauce = std::move(ingreFactory_->createSauce());
    cheese = std::move(ingreFactory_->createCheese());
    pepperoni = std::move(ingreFactory_->createPepperoni());
    clams = std::move(ingreFactory_->createClam());
}
