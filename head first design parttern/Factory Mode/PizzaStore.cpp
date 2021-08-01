//
// Created by Allen on 2021/8/1.
//

#include "PizzaStore.h"

std::shared_ptr<Pizza> PizzaStore::order(PizzaType pizzaType) {
    // 提供工厂模式的接口，由子类自己去实现，生产流程父类来控，子类自己控具体实现。
    auto pizza = createPizza(pizzaType);
    // 工厂的实现还依赖于下层抽象模块pizza的实现。工厂依赖抽象模型pizza，而不是具体模型，这就比较好
    // 而具体产品，比如cheese pizza也依赖抽象模型的实现！
    // 这就是所说的依赖倒置，高低的具体组件均依赖中间层的抽象模块的实现！！
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}
