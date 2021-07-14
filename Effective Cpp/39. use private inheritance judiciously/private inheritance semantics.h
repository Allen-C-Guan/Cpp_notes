//
// Created by Allen on 2021/7/11.
//

#ifndef EFFECTIVE_CPP_PRIVATE_INHERITANCE_SEMANTICS_H
#define EFFECTIVE_CPP_PRIVATE_INHERITANCE_SEMANTICS_H
#include <iostream>
/*
 * ************************** using private inheritance judiciously ***********************
 * private 继承的语义学：
 * private继承，从语义上来讲和复合的第二个语义是完全相同，既 is implemented in terms of (依靠某物而实现）
 *
 * 因此private继承其实只是*一种实现技术*！，和现实世界的继承毫无关系！换句话说，不要把private继承看成继承，
 * 而是要看成一种为了实现某一目的的"设计模式"
 *
 * 那么这个目的是什么呢？
 * 1. 希望访问某个类的protected base class的成员或者需要重新定义继承而来的virtual函数
 *      的时候，才需要使用private inheritance！
 *
 * 2. 需要让empty base内存最优化，因此empty class以组合的形式出现的时候，是占内存的，但是以继承的出现的时候，是不
 * 占内存的！
 *
 * 除了以上两个目的，其他的需要表达is implemented in terms of 的概念的时候，一律用组合！
 *
 * 这里其实很奇怪，你首先是继承，其次是private，咋就变成依靠某物而实现的语义了呢？为什么不是继承的语义呢？
 *
 * 举个例子：
 * class Person
 * {
 *  void eat();
 * }
 * class Student : private Person {}
 *
 * Student s1;
 * s1.eat();    // 这里会编译器报错！这是因为eat对于Student而言是private的无法接触的
 *
 * 从语义的角度来讲，Student不能eat？？？ WTF？？
 *
 * 这是因为private inheritance本身就不是is-a 含义！
 *
 * 那么我们说一下为什么private是 is implemented in terms of 的含义吧！
 *
 * 当Derived 以private继承了Base的时候，虽然Derived对Base的访问权限和public没有任何区别，但是Derived中的Base
 * 部分对外的呈现均为private，也就是Base部分在Derived的外部是不可见的，即使是Base中的public！！
 * 因此对于Derived而言，他只是继承了父类的实现，却没有继承父类的接口！（因为父类的接口，你一个也暴露不出去！）。
 * 因此，子类中的父类是无法对外呈现的，因此只是用父类，却不让父类对外见光，因此我们说，private继承表示
 * is implemented in terms of的含义！！我们只是用父类，却不想让人看见
 * 的含义！
 *
 * 比如：
 *
 * 我有一个类widget，那么我想让这个类呢，有一个计时的功能，因为我想统计代码运行时长，因此可以说widget依靠timer来实现，
 * 但是为了代码复用，我发现我已经写了一个timer了
 *
 * class Timer
 * {
 * public:
 *      virtual void onTick() const;
 * }
 *
 * 但是我发现，这个timer的onTick()并不是我想要的，我需要override他。既然是override，那么只能来继承
 *
 * 首先我们想到public 继承
 * class Widget : public Timer {};
 *
 * 可是这意味着两点：
 * 1. Widget是一个timer，但是其实widget并不想对外呈现timer的属性，因为timer只是我为了统计运行时长的一个手段而以，
 *  我的目的并不是为了让widget变成一个timer，因此语义上就过不去
 *
 * 2. Widget一旦public了timer，这意味着widget也继承了public的onTick()的接口，这会导致widget的用户有能力调用
 * onTick()接口，这是非常让用户迷惑的行为！
 *
 * 因此，我们需要使用private 继承
 *
 * 那么我们说了，我们的目的是widget的实现需要依赖Timer，这和private继承的语义完美契合，其次，private让onTick()
 * 函数在widget中变成了private，即使你有override的能力。
 *
 * class Widget : private Timer
 * {
 * private: // 这里onTick就不是public接口了
 *      void onTick() override const {...} // 重新写这个实现
 * }
 *
 * 我们发现，上述的例子就是 "根据某物而实现出" + "需要override virtual function"来使用private继承的例子
 *
 *
 * 然而其实我们还有更容易理解的设计 —— 复合（组合）+ public继承
 * 既然widget的目的是将timer当黑盒来使用，从而实现自己的目的，而我们又需要override virtual function，那么我们
 * 可以新增一个类，继承timer，然后将新增类和widget组合！
 *
 * class WidgetTimer : public Timer
 * {
 * public:
 *      void onTick() const override {...} // 重写这个实现
 * }
 *
 *  class Widget
 *  {
 *   private:
 *      class WidgetTimer : public Timer
 *      {
 *      public:
 *          void onTick() const override {...} // 重写这个实现
 *       }
 *
 *   private:
 *      WidgetTimer mTimer;
 *  }
 *
 *  如上设计通过
 *  1. 新增一个类
 *  2. public继承
 *  3. 组合设计
 *  的方式，实现了完全相同的设计！！这个设计更容易让人理解！
 *
 */
int main ()
{

}
#endif //EFFECTIVE_CPP_PRIVATE_INHERITANCE_SEMANTICS_H
