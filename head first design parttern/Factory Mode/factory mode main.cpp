//
// Created by Allen on 2021/8/1.
//
#include "NYPizzaStore.h"

int main ()
{
    // 新建一个实体store
    NYPizzaStore *nyPizzaStore = new NYPizzaStore();
    // 实体store调用pizza order接口
    // order接口调用子类自己实现的createpizza接口（这是工厂模式，子类自己实现创建实例）
    // createPizza的时候需要传入指定供货商（抽象工厂以组合的形式让主体持有自己）
    // 实例化属于自己店里的类型的pizza
    // prepare的时候，调用pizza的接口，pizza会调用持有的供货商接口给予特定的供货（抽象工厂供给一个家族的实例）
    nyPizzaStore->order(CHEESE);

}