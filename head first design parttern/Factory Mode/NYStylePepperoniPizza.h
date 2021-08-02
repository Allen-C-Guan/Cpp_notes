//
// Created by Allen on 2021/8/1.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_NYSTYLEPEPPERONIPIZZA_H
#define HEAD_FIRST_DESIGN_PARTTERN_NYSTYLEPEPPERONIPIZZA_H

#include "Pizza.h"
#include "NYPizzaIngredientFactory.h"
class NYStylePepperoniPizza : public Pizza {
public:
    // ingredientFactory 为何要在具体Pizza层级进行组合？不在抽象层级进行组合呢，如果抽象
    // 层级的组合的好处在于prepare的流程也可以在父类中被控制，子类甚至不需要override prepare
    // 只要更换Factory即可，factory的行为来控制即可，不需要子类的实现，只需要factory的实现即可

    NYStylePepperoniPizza(std::unique_ptr<PizzaIngredientFactory> ingreFactory)
        :Pizza(std::move(ingreFactory)) {}
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_NYSTYLEPEPPERONIPIZZA_H
