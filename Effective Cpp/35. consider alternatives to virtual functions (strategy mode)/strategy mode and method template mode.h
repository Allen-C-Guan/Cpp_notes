//
// Created by Allen on 2021/7/11.
//

#ifndef EFFECTIVE_CPP_STRATEGY_MODE_AND_METHOD_TEMPLATE_MODE_H
#define EFFECTIVE_CPP_STRATEGY_MODE_AND_METHOD_TEMPLATE_MODE_H
#include <iostream>
#include <functional>

/*
 * ************************* 考虑virtual 函数以外的其他选择 ************************
 * 我们通常会使用virtual function的多态来实现统一接口但个性化处理的方法，但是或许有跟多选择
 *
 *
 *
 *
 * *********************** method template **************************
 * 思想：
 * method template 和 模板没有任何关系，他指的是将某个流程抽象为一个固定的流程，从而将流程
 * 变成一个wrapper。但是流程的某些步骤的具体实现确是通过子类override private virtual function的
 * 多态来实现的！
 *
 * 该流派认为 virtual 函数几乎总是private，virtual 是private的意味着该继承体系对外封装
 * 更好。 因为public的接口都是non-virtual的，而non-virtual是一成不变的，因此对外接口就是
 * 一成不变的！
 *
 * 具体方法为：
 * 1. 父类实现一个 public的 non-virtual function 来表示流程；
 *      non-virtual function 在上一节中讲过，表示继承体系中该流程不会更改，既继承了接口，也
 *      继承了实现！
 *      public表示这是所有继承体系的对外接口，既该流程是全继承体系对外的暴露的接口
 *
 * 2. 子类通过override流程中的某些环节，来实现实现的个性化。
 *      注意这些环节都是父类中的private虚函数，这样可以保证个性化信息不对外暴露
 *
 * NVI（non-virtual interface)的优点在于，其总可以在virtual函数被调用前做好准备工作，并在
 * virtual函数被调用后做好善后工作！比如清理现场等。该设计模式更适合流程非常固定，且流程中
 * 只有某些环节需要个性化定制的情况。
 *
 * 这种设计的精髓在于，Base决定了函数何时被调用的权利（流程），但是子类保留了如何实现的权利！（实现）
 *
 * tips：
 * 这里因为父类的virtual是private，但是子类仍然可以override他们！！虚函数的override是不受访问权限控制的
 * 这和vtable的初始化不会看访问权限符号有关。
 *
 * 比如
 */

class GameCharacter
{
public:
    int healthValue() const     // 我们将healthVal抽象成一个流程！从step1到step4四个步骤
    {
        // step1.判定一下当前是否处于流血状态
        // step2.更新血量信息
        int retVal = doHealthVal(); // step3.获取当前血量 这有step3需要个性化定制
        // step4.清理
        return retVal;
    }
private:
    virtual int doHealthVal() const  // 父类给出default virtual 实现
    {
        // default计算血量的算法；
    }
};


class EvilBadGuy : public GameCharacter
{
private:
    // 子类可以override父类的private方法！！
    int doHealthVal() const override {
        std::cout << "EvilBadGuy is Blooding" << std::endl;
        return 10;
    }
};

/*
 * ******************************* strategy 模式 *****************************
 * 说到strategy，其精髓就在于"用组合代替继承"从而提供了"实体维度"的灵活性！
 *
 * 其好处相比继承和virtual member function而言有：
 * 1. 同类型的不同实体之间也是可以有不同的策略的！（实体之间的策略更灵活）
 * 2. 策略可以在运行时变更！（运行时的策略更灵活）
 *
 * 这两个优点，virtual是无法实现的，因为virtual与类型绑定，而成员却是个体维度绑定的！
 *
 * 既然是组合，既为将策略放在实体内作为其成员变量，然后通过父类统一接口来调用策略成员，
 * 那么我们可以根据把什么放到实体里来分类！
 *
 * ********************** Function Pointer 实现 strategy *********************
 * 这个方法就是将function pointer作为策略放到成员中的方法来实现策略！
 *
 * 该方法比较直接且简单，既函数指针作为策略成员，在父类构造函数中被初始化，然后父类接口统一掉调用
 */

class GameCharacterFuncPtr
{
public:
    using HealthCalcFunc = int(*)(const GameCharacterFuncPtr&);

    explicit GameCharacterFuncPtr(HealthCalcFunc hcf) : HealthFunc(hcf) {}
    int healthVal () const // 不需要virtual function，因为你需要子类同时继承接口和实现
    {
        return HealthFunc(*this);
    }
private:
    HealthCalcFunc HealthFunc;
};

class Evil : public GameCharacterFuncPtr
{
public:
    explicit Evil(HealthCalcFunc hcf) : GameCharacterFuncPtr(hcf) {}
};

int loseHealthQuickly(const GameCharacterFuncPtr& character)
{
    return 10;
}

int loseHealthSlowly(const GameCharacterFuncPtr& character)
{
    return 1;
}

/*
 * ************************ 通过std::function 来实现 ***********************
 * 该方法和函数指针对比的有点在于更大的灵活性！
 * 其更大灵活性体现在：
 * 1. 任何callable的对象均可作为策略成员
 * 2. 可以是成员函数
 * 3. 返回值只要能互相转换即可！
 *
 * 而如果将function 和 bind 配合使用，那将是更加的灵活（连调用形式都可以不一样了！）
 * bind的可以作为适配层，更改函数的signature，而function类型可以存储bind返回类型！
 * 一个适配，一个存储！无限的弹性！
 *
 */

class GameCharacterFunctional
{
public:
    using HealthCalcFunc = std::function<int(const GameCharacterFunctional&)>;
    explicit GameCharacterFunctional(HealthCalcFunc hcf) : healthFunc(hcf) {}
    void healthVal ()
    {
        healthFunc(*this);
    }
private:
    HealthCalcFunc healthFunc;
};

// 1. 可调用对象
struct HealthCalculator
{
    int operator() (const GameCharacterFunctional& character)
    {
        std::cout << "this is callable object" << std::endl;
        return 1000;
    }
};

// 2. 外部函数
int loseHealth(const GameCharacterFunctional& character)
{
    std::cout << "this is outside function " << std::endl;
    return 10;
}


// 3. lambda表达式
auto lambdaHealthCalc = [](const GameCharacterFunctional& character)->int {
    std::cout << "this is lambda function" << std::endl;
    return 11;
};

// 4. 成员函数
class GameLevel {
public:
    int health (const GameCharacterFunctional& character) {
        return 10;
    }
};

/*
 * ************************** 古典的strategy模式 ************************
 * 古典strategy模式 是将策略做成一个分离的继承体系中的virtual function，而后将
 * 对象的指针放在成员变量中，通过调用指针成员变量，实现策略
 */

class GameCharactorClassic;
class HealthCalcFunc // 策略父类
{
public:
    virtual int calc(const GameCharactorClassic&)
    {
        return 0; // default计算方法
    }
};

class SlowHealthLoser : public HealthCalcFunc      // 子类的计算方法
{
    int calc (const GameCharactorClassic&) override
    {
        return 1;
    }
};

class QuickHealthLoser : public HealthCalcFunc // 子类特有计算方法
{
    int calc (const GameCharactorClassic&) override
    {
        return 10;
    }
};

class GameCharactorClassic
{
public:
    explicit GameCharactorClassic(HealthCalcFunc *phcf) : pHealthCalc(phcf) {}
    int HealthVal ()
    {
        return pHealthCalc->calc(*this);
    }

private:
    HealthCalcFunc *pHealthCalc;
};

int main ()
{
    // function ptr 版本
    Evil evil1(loseHealthQuickly);
    Evil evil2(loseHealthSlowly);
    std::cout << evil1.healthVal() << std::endl;
    std::cout << evil2.healthVal() << std::endl;

    // std::function版本 （这里就不写子类了）
    HealthCalculator h;
    GameCharacterFunctional g1(h);
    g1.healthVal();
    GameCharacterFunctional g2(loseHealth);
    g2.healthVal();
    GameCharacterFunctional g3(lambdaHealthCalc);
    g3.healthVal();

    // 成员函数版本
    GameLevel currLevel;
    std::function<int(const GameCharacterFunctional&)> d = std::bind(&GameLevel::health, &currLevel, std::placeholders::_1);
    GameCharacterFunctional g4(d);

    // 经典策略模式

    HealthCalcFunc *hcf = new HealthCalcFunc();
    std::cout << sizeof(*hcf) << std::endl; // 虽然没有成员变量，但是依然8字节，这是因为vptr的存在，因此如果该内存被销毁的
                                            // 访问其仍然是个危险的行为，因为vptr可能会被销毁（有待证实！）
    GameCharactorClassic gc(hcf);
    std::cout << gc.HealthVal() << std::endl;




}

#endif //EFFECTIVE_CPP_STRATEGY_MODE_AND_METHOD_TEMPLATE_MODE_H
