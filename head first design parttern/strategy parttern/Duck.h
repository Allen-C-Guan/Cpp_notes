//
// Created by Allen on 2021/4/14.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_DUCK_H
#define HEAD_FIRST_DESIGN_PARTTERN_DUCK_H

#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "FlyWithWings.h"
#include "Quack.h"
#include "memory"
/* ******************** 对于pointer的选择 **********************
 * 这里为什么采用unique_ptr 而不用指针呢？ 首先对于new出来的指针的弊端就不多少了，但是貌似stack上的指针也可以实现完全相同的功能啊
 * 为何我们要采用unique_ptr 而不是 stack上的指针呢？ 
 * 这是因为，如果我们采用unique_ptr或者shared_ptr 我们可以保证，只要duck的实体类存在，则这两个指针成员变量对应的内存就一定不会被
 * 释放，但是如果你采用stack上的pointer，则会存在你pointer指向的内存已经释放了，但是你还在去调用，肯定会有问题。
 * 
 * 这时候，你又要说，那我手动保证这些实例都有一个stack上的声明周期不就行了！
 * 那么如果你的Duck的实体类需要动态分配内存呢？你无论如何也无法保证pFly和pQuack的生存周期一致啊。
 *
 * 这时候，你又有个点子，你说那我可以把pfly和pQuack new出来，然后在Duck的destructor里释放掉，就可以和unique_ptr一样了啊，
 * 但是Duck的copy， move，赋值等，你要不要管，你图啥呢，直接弄个智能指针他不香么
 *
 * 综上所述，对于指针成员变量，除非你可以保证，成员的声明周期和本实体的声明周期是完全一致的（可以使用stack上指针），或者你对于成员变量的指针有所处理
 * 比如成员指针所指的对象一旦销毁，则成员变量指针也销毁，否则你就一定有使用已经销毁的内存的风险。
 */
class Duck {
private:
    std::unique_ptr<FlyBehavior> pFly;
    std::unique_ptr<QuackBehavior> pQuack;
public:
    Duck(std::unique_ptr<FlyBehavior> flyBehavior = std::make_unique<FlyWithWings>(),
         std::unique_ptr<QuackBehavior> quackBehavior = std::make_unique<Quack>());
    virtual ~Duck() = default;
    Duck(const Duck&) = delete;
    Duck& operator= (const Duck&) = delete;

    void swim() const;
    void performQuack() const;
    void performFly() const;
    void setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior);
    void setQuackBehavior(std::unique_ptr<QuackBehavior> quackBehavior);
    virtual void display() const = 0;
};
#endif //HEAD_FIRST_DESIGN_PARTTERN_DUCK_H
