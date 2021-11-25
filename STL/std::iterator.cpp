#include <iostream>
/*
 * ******************************* 写在前面 *****************************************
 * 本章主要有两个重要的关键机制：
 * 1. 通过模板类和模板的特例化作为类型的适配层，并在类中定义内嵌类型保证类型对外呈现的归一化。注意，只有对象才能帮助推导。
 * 2. 模板类作为基类，约束子类必须定义某些类型。
 */

/*
 * ****************** 特性萃取机 iterator_traits ***********************
 * 需要一个iterator_traits（迭代器的特征）用来萃取所指类型。
 *
 * 通常我们如果想要自定义类的类型，可以单纯的通过在class 内部定义自己的value_type即可。在使用的时候，只要调用MyClass::value_type即可
 * 那么我们为什么需要这样个特性萃取机作为中间转递一下呢？
 *
 * 这是为了解决内置类型不存在class，因此也无从谈起int::value_type的操作了。中间这个特性萃取机就通过模板偏特化来实现内置类型和自定义类型的适配！
 * **而其机制为：模板类用来适配类型外部，特例化模板+内部定义的类型用来*归一化*value_type的类型！**。
 * 从而让任何迭代器的value_type都可以归一化为 iterator_traits<T>::value_type; 类型
 *
 * 总结一句话，特性萃取机就是一个 内置类型和自定义类型的 到value_type的适配层，该适配机制是通过模板特例化完成的。(类型自定义 + 模板 +特例化机制，总是可以成为类型的适配层）
 */

// 这个模板是最general的一个类型，需要迭代器自我定义type_value。
struct input_iterator_tag;
struct output_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator;
struct random_access_iterator_tag;

template<class T>
struct iterator_traits {
    typedef typename T::value_type value_type;
    typedef typename T::difference_type difference_type; // 用户自定义的difference_type
    typedef typename T::reference reference;
    typedef typename T::pointer pointer;
    typedef typename T::iterator_category iterator_category;
};

// 对内置指针类型的偏特化
template<class T>
struct iterator_traits <T*> {
    typedef T value_type;
    typedef ptrdiff_t difference_type; // 原生指针定义的difference_type
    typedef T& reference;
    typedef T* pointer;
    typedef random_access_iterator_tag iterator_category;
};

// 对const内置类型指针的偏特化
template<class T>
struct iterator_traits<const T*> {
    typedef T value_type;
    typedef ptrdiff_t difference_type; // 原生指针定义的difference_type
    typedef T& reference;
    typedef T* pointer;
    typedef random_access_iterator_tag iterator_category;
};


/*
 * 假设我们有这样一个函数，需要返回一个迭代器所指向的类型，这在template中是无法通过模板参数推断来完成的，需要用一个类型定义来完成。
 *
 * 但是我们发现，要想有value_type的前提这个前提是这个参数I必须是个类！ 对于内置类型，你是无法做到给内置类型定义一个value_type的
 * 从属类型的。
 * 因此我们需要特例化模板来解决这个问题
 *
 * 我们还需要解决一个问题，就是当声明为iterator_traits<const int*>::value_type的时候，你的预期是想让value_type是const int，还是
 * int呢？
 * 如果你的目的是希望有个const int类型的I，那么你声明了一个const int类型有啥用呢？你希望的肯定是很“纯粹”的类型，不包含const的。
 * 为了解决这个问题，我们依然要利用模板偏特化来解决这个问题。
 *
 */
template<class I>
typename iterator_traits<I>::value_type func(I ite) {
    return *ite;
}

/*
 * ***************************** iterator_category *******************************************
 * 我们之所以要给iterator_category 进行分类，是因为各种iterator所能实现的功能是不一致的，通常可以分成如下5大类：
 * forward_iterator_tag和bidirectional_iterator只支持顺序搜索，一次只能移动一个位置，random_access_iterator_tag可以支持随机访问。
 *
 * 那么我们为什么要给iterator_category分类呢？
 * 这主要原因就是因为iterator的效率不同，比如你在advance的操作中，如果你的数据结构支持随机搜索，你却用顺序搜索，那你就很蠢，因此我们有诉求
 * 将各个iterator的类型进行区分，希望算法可以用到效率最高的算法上。
 *
 * 那么我们的算法如何识别不同的iterator种类呢？
 * 最先想到的是可以通过提供不同的算法接口来实现：比如：
 * void advance_II(inputIterator& i, Distance n);
 * void advance_BI(inputIterator& i, Distance n);
 * void advance_RAI(inputIterator& i, Distance n);
 * 这样你可以按需调用。 但这样是不是有点丑呢？我们能不能归一化接口呢？
 * 方法1：再封装一层统一接口，动态识别类型。
 * void advance(inputInterator& i, Distance n) {
 *      if (is_random_access_iterator(i)) advance_RAI(i, n);
 *      else if (is_bidrectional_iterator(i)) advance_BI(i, n);
 *      else advance_II(i, n);
 * }
 * 问题：
 * 这个写法需要动态确定类型，效率极低，我们希望可以在编译期就确定类型？
 *
 * 问题解决：统一入口 + 编译期确定类型 = 函数重载！
 *
 * 方法2：函数重载实现统一接口+编译期确定类型
 * void advance(inputIterator& i, Distance n, forward_iterator_tag);
 * void advance(inputIterator& i, Distance n, bidirectional_iterator);
 * void advance(inputIterator& i, Distance n, random_access_iterator_tag);
 * 注意这里最后一个参数只是为了激活函数重载的，没有任何使用的价值
 *
 * 问题：使用者需要关心类型。能不能我不关心类型？
 * 解决问题：多一层包装，将类型识别托管给模板类型推到！
 *
 * 终极解决方案见代码！
 */
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator { };

// 实际执行的代码段
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag)
{
    while (n--) ++i;
}

template <class ForwardIterator, class Distance>
inline void __advance(ForwardIterator& i, Distance n, forward_iterator_tag) // 其实这个函数不用写，因为forward_iterator_tag继承自input_iterator_tag，编译器找不到的时候，会找其父类的
{
    __advance(i, n, input_iterator_tag());
}

template <class BidirectionIterator, class Distance>
inline void __advance(BidirectionIterator& i, Distance n, bidirectional_iterator)
{
    if(n >= 0) {
        while (n--) ++i;
    } else {
        while (n++) --i;
    }
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag)
{
    i += n;
}
// 封装一个统一类型识别的接口，该接口即有统一的入口，又避免了用户在调用的时候还要关注其iterator的类型的问题。
template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
    // 我们可以看见，iterator_traits帮我们萃取了iterator的类型，并转交给实际执行的函数手中，
    __advance(i, n, iterator_traits<InputIterator>::iterator_category()); // 这里必须是个对象，不能是个类型，要创建一个临时对象，用于匹配
}

/*
 * ******************************** distance() **********************************
 */

template <class InputIterator, class Distance>
inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        first++;
        ++n;
    }
    return n;
}

template <class RandomAccessIterator, class Distance>
inline typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
    return last - first;
}

template <class InputIterator, class Distance>
inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
{
    return __distance<InputIterator, Distance>(first, last, iterator_traits<InputIterator>::iterator_category());// 这里必须是个对象，不能是个类型，要创建一个临时对象，用于匹配
}


/*
 * ********************** 迭代器 *************************************
 * 如果定义iterator，为了泛型算法的诉求，必须拥有提供5个内嵌相应型别，利于traits萃取，否则该iterator无法与其他STL组件搭配。
 * 为了保证iterator的规范性，因此我们需要提供一个基类保证迭代器遵循法则。
 *
 * 该基类不会包含任何成员变量，因此不会给子类有任何负担。但是却强制约束了迭代器需要定义这五种类型。
 * 注意：模板作为基类能约束基类类型相关的参数！ 因为模板的参数是类型，作为基类就将该类型继承给子类了。
 */

template <class category, class T, class Distance = ptrdiff_t, class Reference = T&, class Pointer = T*>
struct iterator {
    typedef category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

/*
 * 我们自定义这样的一个iterator，iterator 的关键目的问题就在对 operator* 和 operator-> 的重载。
 * 因此
 * 1. 你要给出一个value_type提供给别人使用。
 * 2. 对operator*进行重载，让其行为像个指针
 * 3. 对operator->进行重载，
 * 4. 其他操作符，例如++， --等
 */

template<class T>
struct MyArrIter : public iterator<random_access_iterator_tag, T>{ // 这里等于限制了MyArrIter的内置类型为如下5个组合
public:
//    typedef T value_type;
//    typedef ptrdiff_t difference_type;
//    typedef T& reference;
//    typedef T* pointer;
//    typedef random_access_iterator_tag iterator_category;

    MyArrIter(T *p) : ptr(p) { }
    T& operator* () const {return *ptr;};
    T* operator->() const {return ptr;}; // 先执行return，在进行->的寻址操作。
    void operator++ () {
        ptr += 1; // 数组的索引 +1 等于 地址偏移 sizeof(T) * 1 个单位
    }
    const MyArrIter operator++(int) {
        MyArrIter temp = *this;
        ++(*this);
        return temp;
    }

private:
    T *ptr;
};


int main ()
{
    // 测试MyIter的功能。
    int arr[] = {1, 2, 3, 4};
    MyArrIter<int> it(arr);
    std::cout << *it << std::endl;
    it++;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;

    // 测试iterator_traits
    std::cout << "test iterator_traits" << std::endl;
    std::cout <<  func(it) << std::endl;

    int *i = new int(100);
    std::cout <<  func(i) << std::endl;

    const int *ci = new int(100);
    iterator_traits<const int*>::value_type ci2 = 1; // 这里类型推到为int 而不是const int，因此ci2可以被修改
    ci2++;
}
