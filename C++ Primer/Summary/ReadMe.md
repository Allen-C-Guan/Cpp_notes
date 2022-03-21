# C++ 基础知识

## 一. 类：封装，继承与面向对象

### 1. 封装的意义：
封装：封装的意义，在于明确标识出允许外部使用的所有成员函数和数据项，或者叫接口。有了封装，就可以明确区分内外，使得类实现者可以修改封装内的东西而不影响外部调用者；而外部调用者也可以知道自己不可以碰哪里。这就提供一个良好的合作基础——或者说，只要接口这个基础约定不变，则代码改变不足为虑



### 2. 继承的意义：
   继承+多态：继承和多态必须一起说。一旦割裂，就说明理解上已经误入歧途了。先说继承：继承同时具有两种含义：其一是继承基类的方法，并做出自己的改变和/或扩展；其二是声明某个子类兼容于某基类（或者说，接口上完全兼容于基类），外部调用者可无需关注其差别（内部机制会自动把请求派发[dispatch]到合适的逻辑）。再说多态：基于对象所属类的不同，外部对同一个方法的调用，实际执行的逻辑不同。

继承的第二种含义非常重要。它又叫“接口继承”。接口继承实质上是要求“做出一个良好的抽象，这个抽象规定了一个兼容接口，使得外部调用者无需关心具体细节，可一视同仁的处理实现了特定接口的所有对象”——这在程序设计上，叫做归一化。归一化使得高层的外部使用者可以不加区分的处理所有接口兼容的对象集合——就好象linux的泛文件概念一样，所有东西都可以当文件处理，不必关心它是内存、磁盘、网络还是屏幕（当然，对底层设计者，当然也可以区分出“字符设备”和“块设备”，然后做出针对性的设计：细致到什么程度，视需求而定）。


### 3. 什么是真正的封装

真正的封装是，经过深入的思考，做出良好的抽象，给出“完整且最小”的接口，并使得内部细节可以对外透明（注意：对外透明的意思是，外部调用者可以顺利的得到自己想要的任何功能，完全意识不到内部细节的存在；而不是外部调用者为了完成某个功能、却被碍手碍脚的private声明弄得火冒三丈；最终只能通过怪异、复杂甚至奇葩的机制，才能更改他必须关注的细节——而且这种访问往往被实现的如此复杂，以至于稍不注意就会酿成大祸）。一个设计，只有达到了这个高度，才能真正做到所谓的“封装性”，才能真正杜绝对内部细节的访问。否则，生硬放进private里面的东西，最后还得生硬的被拖出来——当然，这种东西经常会被美化成“访问函数”之类渣渣（不是说访问函数是渣渣，而是说因为设计不良、不得不以访问函数之类玩意儿在封装上到处挖洞洞这种行为是渣渣）



## 二. 构造、析构与拷贝 ——"三/五原则"

### 什么是构造函数：

#### 构造函数的定义
每个类都分别定义了它的对象被初始化的方式，类通过一个或几个特殊的成员函数来控制其对象的初始化过程，这些函数叫做构造函数。

构造函数的任务是初始化类对象的数据成员，无论何时，只要类的对象被创建，就会执行构造函数。

#### 构造函数的分类
##### 1. **默认构造函数**： 没有入参的构造函数，就叫默认构造函数

##### 2. **合成默认构造函数**：当你没有提供默认构造函数的时候，编译器会合成一个默认构造函数！

#### **合成默认构造函数的语义学**：
1. 为什么编译器会给你合成默认构造函数？

    当编译器需要的时候，而不是程序员需要的时候！ 

    编译器需要指的是，如果编译器在实例化该对象的时候，除了分配内存以外，还需要额外做一些事情的时候，就需要合成默认构造函数。


2. 什么是构造函数的扩张？
   
    构造函数会做一些我们没写的东西，这就叫编译器对构造函数的扩张！


3. 什么场景下编译器会给你合成或者扩张默认构造函数？ 
   1. 子类构造函数：如果子类没有显示的调用父类构造函数，那么子类的构造函数会隐式的调用父类的默认构造函数来构造父类部分
   因此可以看成父类部分也是子类的一个成员，那么当你没有显示初始化父类的时候，编译器会给你默认初始化父类的 
   
   2. 对于有virtual function的情况：如果存在虚函数，那么即使你不给出默认构造函数，成员变量均为内置类型，编译器也一定会生成一个默认构造函数，因为vptr和vtbl无论如何也要被构造出来！ 并且要保证，其中的vtbl中对应的虚函数要换成子类自己的成员函数！

   3. 有virtual base 的情况：对于存在虚继承父类的情况，编译器一定要保证，在编译器，父类的数据在每一个子类中的位置可以安排妥当！
   否则子类无法调用父类的数据！ 
   那么对于多重继承而言，cfront编译器是将父类以指针的形式存放在子类对象中的，当需要父类数据的时候，
子类可以通过指针索取到其父类数据！
   
### 析构：
#### 什么是析构函数
析构函数执行与搞糟函数相反的操作：构造函数初始化对象的非static数据成员，还可能做一些其他工作；析构函数释放对象使用的资源，并销毁对象的非static数据成员。

在析构函数中，首先执行函数体，然后销毁成员。成员按照逆序销毁。

注意：内置类型没有析构函数，因此销毁内置类型成员什么也不需要做，只要将内存还给系统即可。

#### 析构函数的功能：
可以在对象被销毁的时候，自动的做一些事情，用于环境清理，内存释放，解锁等操作。

### 什么是拷贝，赋值，移动构造，移动赋值？
见代码

### 什么是"三五法则"？
三五法则指的是：对于拷贝构造，拷贝赋值，(移动构造，移动赋值)，析构函数这三/五个基本操作中。如果需要实现其中任何一个，则意味着你可能需要实现他们的全部！

这是因为，通常情况下，当你需要其中任何一个的时候，意味着你可能申请了动态内存，或者你持有了某些指针，而拷贝，赋值和移动等行为与所持有的内存的行为密切相关。因此需要对其进行全面的设计

见代码
## 三. 类的访问控制符：public，private， protected
### 在类中的作用：
   控制类外作用域对内类成员的访问权限。

### 在继承中的作用：
   控制类外作用域对其父类部分的成员的访问权限！

*见代码*
### 继承的语义学
#### public继承

在继承中，public表示**is-a**的概念，若Derived 以public的方式继承自 Base，则相当于告诉编译器，Derived is a Base
换句话说，既Derived 是一个Base， 但是Base并不是一个Derived。既Base是一个更一般的概念，而子类比父类表现
出更特殊的概念， 你主张"父类对象可用的任何地方，子类对象一定可以派上用场！"

比如student 和 person. 既 student是一个person，且我们认为，只要是对person成立的事情，对student
也一定可以成立！ 没有例外！ 反之则不行。
因此我们编译器允许 所有可以接受person的地方，也都愿意接受student！

### private继承
复合（组合）指的是：一个类中含有其他其他类作为自己的成员，那么该类和这些成员之间的关系就是复合！
比如：
```
class Person
{
private:
   Address address;
   PhoneNumber voiceNumber;
   PhoneNumber faxNumber;
}
```
我们看，person是由3个类成员复合（组合）而成的，既Person的完整信息是由地址，电话号码，传真号组成

pirvate继承表示一个复合的语义，可以看成两种概念：
1. has-a （有一个）
2. is implemented in terms of (根据某物来实现出）

#### has-a：
当为应用域的时候，复合的语义为has-a。

应用域表示：当一个类是为了塑造真实世界中的某些事务的时候，我们就说这个类属于应用域中的！
比如上面的例子：Person has a address, person has a voiceNumber...

#### is implemented in terms of （容易和is a 混淆）

当类为实现域的时候，复合的语义为"根据某物来实现出"。
实现域指的是：当一个类存粹是为了实现而抽象出来一个现实中不存在的事务的时候，就说这个类属于实现域中。
比如：互斥器，查找树等抽象概念

#### 举例：
如果我们想通过继承，用vector来自己实现一个set的功能，（vector为底层数据接口，但对外特性为set的数据结构）
于是我们首先想让Set : public std::vector<int>，

但是我们想一下，Set是一个vector，这合理吗？
vector可以重复，set可以吗？set不行！也就是说，并不是所有vector适用的地方，set都可以。
因此违反了 **is-a** 中的 "所有父类可用的地方，子类均可用的原则"，
因此绝不可以用 public 的方式继承 vector！

但是我们可以说：set可以 "根据vector实现出来" ！！！
因此我们需要让set以私有的方式继承vector
   


## 四. 继承

1. 继承



## 五. 友元
