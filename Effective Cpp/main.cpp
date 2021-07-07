#include <iostream>
#include <string>
#include <memory>
#include <vector>

/*
 * ******************** public -> "is a"  *******************
 * 在继承中我们涉及到三个作用域标志：public， protect，和 private。
 * 我们讨论一下public的语义学！
 * 在继承中，public表示is-a的概念，若Derived public Base，则相当于告诉编译器，Derived is a Base
 * 换句话说，既Derived 是一个Base， 但是Base并不是一个Derived。既Base是一个更一般的概念，而D比B表现
 * 出更特殊的概念， 你主张"B对象可用的任何地方，D对象一定可以派上用场！"
 *
 * 比如student 和 person. 既 student是一个person，且我们认为，只要是对person成立的事情，对student
 * 也一定可以成立！ 没有例外！ 反之则不行。
 * 因此我们编译器允许 所有可以接受person的地方，也都愿意接受student！
 *
 * 但注意，以上论点只对public生效！
 *
 *
 * 但是在我们抽象的过程当中，总会遇到问题，比如：
 * 我们认为鸟都可以飞，于是我们：
 * class Bird {
 *     void fly();
 * }
 *
 * 但是当企鹅出现的时候，如果我们认为企鹅也是一种鸟，于是就有了
 * class Penguin : public Bird {  // Penguin is a Bird!
 *
 * }
 *
 * 但是问题来了，企鹅他不会飞啊！但是他确实又拥有鸟的很多共性，单写一个类也不合适啊，怎么办
 *
 * 一般有四种情况
 * 1. 细化分类：
 *      也就是说并不是鸟类都会飞，这是一个事实，那么鸟这里类里，就不应该有fly这个动作。我们可以细化一下分类
 *
 *      class Bird {};
 *      class FlyingBird : public Bird {  // 飞鸟是一种鸟
 *          virtual void fly();
 *      };
 *      class Penguin : public Bird {}; // 企鹅是一种鸟
 *
 *      从语义的角度来讲，更加的合理，也更好理解了，但是使用起来却不方便了！因为可能有些用户在
 *      使用的时候，并不在乎鸟是否会飞，对于这种用户，原来的"粗略的分类"就已经足够了！为什么要多搞这么多
 *      优点：问题在编译期就会暴露！
 *
 * 2. 使用的异常来阻止！
 *      class Bird {
 *          virtual void fly();
 *      }
 *      class Penguin: public Bird {
 *          void fly () override {
 *              // 抛出异常
 *          }
 *      }
 *
 *      这种思路呢就是，我鸟可以会飞，但是如果你让企鹅飞，那就是不对的！
 *
 *      这种做法是比较有问题的，因为该错误要在运行期发现，这就会给定位错误增加成本
 *
 * 3. 抽出一个接口 （自己新增的）
 *      class Bird {};
 *      class Fly
 *      {
 *          virtual void Fly() = 0;
 *      }
 *      class Penguin : public Bird {}
 *      class OtherBird : public Bird, Fly // OtherBird是一种Bird，也可以飞
 *      {
 *          void Fly() override;
 *      }
 *
 *      这种思想就是面向接口，我们认为一个功能也可以抽象成为一个抽象类，那么我们将Fly这个功能抽象出一个
 *      接口来，从而把fly从bird中拿出来！
 *
 * 4. 将功能上升 （more effective c++）
 *      因为dynamic cast的运行成本比较高，但是呢，我们又想只分两个类，接口也要新增一个类啊，怎么办。
 *      就可以使用功能上升，既某些子类独有的功能，我给他提到父类中去，但是父类什么也不做，子类按需override！
 *
 *      class Bird
 *      {
 *          virtual void fly() {}; // 什么都不做
 *      }
 *
 *      class Penguin : public Bird {};
 *
 *      class OtherBird : public Bird
 *      {
 *          void fly () override
 *          {
 *             do something
 *          }
 *      }
 *
 *      这样，即使我们用父类调用了penguin，也没关系啊，反正啥也不做，但是这就要求子类反复的重复override
 *      fly函数，即使这个fly'函数是一样的。
 *
 * 综上所述，我认为面向接口编程更加的友好，当然如果性能要求较高，功能上升也是可以的
 *
 *
 *
 *
 * 我们分析完了 public的"is - a" 我们不得不说一些反直观的例外！并不是说is a 就一定是 public
 *
 * 比如：square和rectangle。
 * 我们说square is a rectangle没什么问题吧，于是我们就 square public rectangle
 *
 * 但是呢，rectangle有一个成员函数（功能）叫做 double_wide() 既将rectangle的短边double一下
 * 但是你认为square应该如何做呢？ square是没有办法单独double某一个维度的，否则就不在是square了！
 *
 * 因此有些时候，我们直觉认为的"is a" 并不完全等于public
 *
 * 这主要是因为代码中的语义中的public强调的Derived总可以在任何地方替代Base，但是我们生活中的分类标准
 * 并不总是这个标准的！
 *
 */
int main()
{

}