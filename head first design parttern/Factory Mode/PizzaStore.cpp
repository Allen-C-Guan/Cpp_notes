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
    // 当我们一旦确定了这个抽象中间层的时候，我们自上而下实现的时候，就不需要向下继续考虑了。
    // 换句话说，当我们写PizzaStore的时候，就不需要考虑具体的Pizza类，这样就让用户从具体的类中脱离出来
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}
