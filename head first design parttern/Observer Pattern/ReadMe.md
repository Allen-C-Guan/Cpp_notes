观察者模式 


观察者模式的精髓在于巧妙利用*通知*的方法来实现一对多的数据传输和管理！
 
 
具体实现既：
subject应该提供"注册"，"去注册"和"通知" 三个接口，其作用分别是，让observer在constructor中将自己注册进来，允许运行的时候移除某一个观察者（比如observer被释放的时候），以及通知，
既如果subject自身出现更新，则需要广播出去。

observer需要实现三件事：
1. 将自己在合适的时候注册到subject中，比如constructor
2. 实现一个update的接口，供给subject广播的时候来调用。
3. 析构函数中，要去注册！（很容易被忽略）
 
 其工作的原理不过就是：
 1. observer再初始化的时候，就将自己注册在subject中。
 2. subject在发生变化的时候逐一通知所有已经注册的observer。

因此想要实现观察者模式其实只要满足以上两点即可，不关心你的方法是什么，从实现的角度来说你需要实现几个关键点：
  1. observer必须提供一个类型完全一致的，统一的可调用接口，这个接口可以是多态实现的，也可以是回调函数实现的
  2. observer必须在初始化的时候，将自己的统一接口或者可调用对象注册到subject中
  3. subject 必须提供一个容器用来放observer，且提供notify函数遍历observers容器，逐个调用接口来实现更新。
  4. observer必须在自己销毁的时候，将自己从subject中移除，从而避免内存泄露
 
 
 通过上面的介绍我们发现，通知者模式不但很好的实现了1对多的关系，也很好的松了耦合，subject和object之间唯一
 的强耦合就在于subject要求object一定要实现update接口，除此之外没有其他要求。
 
 观察者模式不能依赖update的顺序！
 
 
 observer注册到subject的途径
 我们观察到，观察者模式的核心就在于注册，注册的方法也决定了通知的方法。
 C++ 中有主要有两类注册方法
 1. 利用接口来注册到subject中，而后利用多态来通知
 2. 利用lambda或者其他可调用对象（函数）来注册，而后通过可调用对象来通知。（不需要observer的接口了就）
 
 方法一：
 
 实现：
 
 首先对于第一种方法实现就是：提供observer和subject两个接口，然后observer中有subject指针成员，在observer的constructor中，observer把自己注册到subject中。
 此时subject的装有observer的容器中就存在了该observer，notify的时候，只要遍历容器，调用update接口，利用多态来实现通知即可。 同时在observer的destructor中，
 要释放subject中的自己。
 
 
 方法二：
 
 不使用object的接口，而是采用共同的可调用对象类型来作为update的接口，首先subject需要有一个容器用于容纳可调用对象，由于可调用对象没有标识，因此容器必须有标识，
 比如map，key是int，val是可调用对象。因此这个key值就是每个observer的标识了，val就是update的接口了。
 
 lambda实现方法：
 
 observer在constructor的时候，将自己的update函数用lambda包装一下塞到subject的容器中，通知的时候，调用一下val，就会调用lambda函数了。 但是这个lambda因为是匿名的
 需要返回一个key值，由observer来保管，在constructor中，可以利用这个key值来释放已经被注册的自己。
 
 
 关于抽象类的介绍 
 
 我们需要让subject和observer是纯虚类，因为不管是subject还是observer，我们描述的都是一个比较抽象的概念，因此subject和observer应该是个接口，而不是抽象类更合理一点。
 
 虽然按理讲，subject理应具有通知observer的能力，这应该是所有subject 实体化之后都应该使用的功能 但是仍然不能在subject中实现，具体为什么还需要研究！！但是总之，感觉接口就应该虚化，
 
 observer就更应该是个纯接口了，observer本就应该多种多样，这就是observer之所以是observer的原因 比如observer并不一定对notify的全部内容都感兴趣，或许他只对其中一小部分感兴趣。
 
 那么我们在面向接口的时候，就更不应该给observer设置更多的限制，而是尽可能的让继承的observer自由的去发挥
 
