//
// Created by Allen on 2021/7/11.
//

#ifndef EFFECTIVE_CPP_COMPOSITION_SEMANTICS_H
#define EFFECTIVE_CPP_COMPOSITION_SEMANTICS_H
#include <iostream>

/*
 * ***************************** 复合（组合）语义学 *****************************
 * 我们之前说过，public是is-a的语义，就是说所有Derived对象均是Base，所有Base适用的地方，Derived
 * 一定可以！那么组合的语义学是什么呢？
 *
 * 复合（组合）指的是：一个类中含有其他其他类作为自己的成员，那么该类和这些成员之间的关系就是复合！
 * 比如：
 * class Person
 * {
 * private:
 *      Address address;
 *      PhoneNumber voiceNumber;
 *      PhoneNumber faxNumber;
 * }
 * 我们看，person是由3个类成员复合（组合）而成的，既Person的完整信息是由地址，电话号码，传真号组成
 *
 * 那么组合表示什么语义呢？
 *
 * 复合的语义学有两个：
 * 1. has-a （有一个）
 * 2. is implemented in terms of (根据某物来实现出）
 *
 * has-a：当为应用域的时候，复合的语义为has-a。
 * 应用域表示：当一个类是为了塑造真实世界中的某些事务的时候，我们就说这个类属于应用域中的！
 * 比如上面的例子：Person has a address, person has a voiceNumber...
 *
 *
 * is implemented in terms of （容易和is a 混淆）
 * 当类为实现域的时候，复合的语义为"根据某物来实现出"。
 * 实现域指的是：当一个类存粹是为了实现而抽象出来一个现实中不存在的事务的时候，就说这个类属于实现域中。
 * 比如：互斥器，查找树等抽象概念
 *
 * 举例：
 * 如果我们想用vector来实现set的功能，（vector为底层数据接口，但对外特性为set的数据结构）
 * 于是我们首先想让Set : public std::vector<int>，
 * 但是我们想一下，Set是一个vector，这合理吗？
 * vector可以重复，set可以吗？set不行！也就是说，并不是所有vector都适用的地方，set就可用。
 * 因此绝不可以用 public vector！
 *
 * 但是我们可以说：set可以 "根据vector实现出来" ！！！
 * 因此我们需要把vector作为set的一个成员，而不是一个父类！！
 *
 *
 */



int main ()
{

}
#endif //EFFECTIVE_CPP_COMPOSITION_SEMANTICS_H
