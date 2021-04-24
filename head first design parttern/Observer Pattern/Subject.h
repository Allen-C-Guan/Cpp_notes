//
// Created by Allen on 2021/4/22.
//

#ifndef HEAD_FIRST_DESIGN_PARTTERN_SUBJECT_H
#define HEAD_FIRST_DESIGN_PARTTERN_SUBJECT_H
#include <unordered_set>
#include <memory>
#include "Observer.h"

/* ******************************** 观察者模式 *********************************
 * 观察者模式的精髓在于巧妙利用*通知*的方法来实现一对多的数据传输和管理！
 *
 * 具体实现既：
 * subject应该提供"注册"，"移除"和"通知" 三个接口，其作用分别是，让observer在constructor中
 * 将自己注册进来，允许运行的时候移除某一个观察者，以及通知，既如果subject自身出现更新，则需要
 * 广播出去。
 *
 * observer只需要实现两件事，
 * 1。将自己在constructor的时候注册到subject中
 * 2. 实现一个update的接口，供给subject广播的时候来调用。
 *
 * 其工作的原理不过就是：
 * 1. observer将自己注册在subject中。
 * 2. subject在发生变化的时候逐一通知所有已经注册的observer。
 *
 * 通过上面的介绍我们发现，通知者模式不但很好的实现了1对多的关系，也很好的松了耦合，subject和object之间唯一
 * 的强耦合就在于subject要求object一定要实现update接口，除此之外没有其他要求。
 *
 * 观察者模式不能依赖update的顺序！
 *
 * ********************************   关于抽象类的介绍  ***********************************
 * 我们需要让subject和observer是纯虚类，因为不管是subject还是observer，我们描述的都是一个比较
 * 抽象的概念，因此subject和observer应该是个接口，而不是抽象类更合理一点。
 *
 * 虽然按理讲，subject理应具有通知observer的能力，这应该是所有subject 实体化之后都应该使用的功能
 * 但是仍然不能在subject中实现，具体为什么还需要研究！！但是总之，感觉接口就应该虚化，
 *
 * observer就更应该是个纯接口了，observer本就应该多种多样，这就是observer之所以是observer的原因
 * 比如observer并不一定对notify的全部内容都感兴趣，或许他只对其中一小部分感兴趣。
 *
 * 那么我们在面向接口的时候，就更不应该给observer设置更多的限制，而是尽可能的让继承的observer自由的
 * 去发挥
 *
 */
class Subject {
public:
    Subject() = default;
    ~Subject() = default;
    virtual void notifyObject () const = 0;
    virtual void removeObject (Observer* o) = 0;
    virtual void registerObject (Observer* o) = 0;
};


#endif //HEAD_FIRST_DESIGN_PARTTERN_SUBJECT_H
