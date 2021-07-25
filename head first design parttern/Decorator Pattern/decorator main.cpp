
#include <iostream>
#include "decrator.h"
#include "drinks.h"

int main ()
{
    std::shared_ptr<Beverage> houseBlend = std::make_shared<HouseBlend>();
    houseBlend = std::make_shared<Milk>(houseBlend);
    houseBlend = std::make_shared<Mocha>(houseBlend);
    houseBlend = std::make_shared<Milk>(houseBlend);
    std::cout << houseBlend->getDescription() << std::endl;
    std::cout << houseBlend->cost() << std::endl;
}