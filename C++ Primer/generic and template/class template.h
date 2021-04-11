#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <initializer_list>

/*
 * ************************************   类模板   *******************************************
 * 类模板指的是类本事就是个模板类，类模板需要注意的如下
 * 1. 类模板（与模板函数不同）不可以推断类型，使用者必须提供信息
 *
 * 2. 不同模板实例之间不存在任何关系，既不是同类，也不是继承关系
 *
 * 3. 类外定义成员函数需要带上template<T> 和 className<T>::，但类内不需要，类内默认当前类型与初始化类型相同
 *      template<T>
 *      return_type ClassName<T>::funcName(){};
 *
 *      这是因为，模板实例之间是没有关系的，且对于模板类而言，模板参数是参数类型的一部分，因此 className<int> 和
 *      className<double> 之间是没有任何关系，但是如果你不告诉编译器当前当前成员函数属于哪个类，编译器没法实例化
 *      因此就通过 template<T>来告诉编译器T的值，然后编译器用T的值初始化类型className<T>，找到对应类，然后初始化
 *      模板类型实例
 * 4. 模板类的成员和成员函数，只有在使用的时候才会被实例化！也就是说模板类在实例化的时候，并不像非模板类一样，将所有成员
 * 都加载到内存中，而是用多少实例化多少！！
 *
 * 5. 模板声明，template<typename> class class_name;
 *      模板参数也是参数，参数只有在实例化的时候才有意义，声明的时候我们不在意参数是什么，因此typename后面啥也不用写
 *
 */

template<typename> class BlobPtr; // 模板声明

template<typename T> class Blob
{
public:
    friend BlobPtr<T>; // 这里声明了一对一的友元
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(std::initializer_list<value_type> il);
    template<typename It> Blob(It, It);

    size_type size() const {
        return data->size();
    }

    bool empty() {
        return data->empty();
    }

    void push_back(const value_type &val) {
        data->push_back(val);
    }

    void push_back(value_type &&val) {
        data->push_back(std::move(val)); // 这个地方必须是move，因为右值引用本事也是个左值。
    }
    void pop_back();
    T& back();  // 你要是想在class外定义，这tmd还不能写type_value， 因为函数外，类内的typedef是不可见的
    T& operator[] (size_type i);


private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template<typename T>  // 类型外定义函数必须带着template，和Blob<T>，否则编译器是在实例化不同模板参数对应的类时候，没法找到正确的函数
void Blob<T>::check(size_type i, const std::string &msg) const {
    if(i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

template<typename T>
T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];  // 还是要解引用啊，毕竟是shared_ptr
}

template<typename T>
void Blob<T>::pop_back() {
    check(0, "pop from empty Blob");
    data->pop_back();
}

template<typename T>
Blob<T>::Blob()
        :data(std::make_shared<std::vector<T>>()){  };

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il)
        :data(std::make_shared<std::vector<T>>(il)) {  };

// 模板类的模板成员
template<typename T>
template<typename It> // 两个模板都要写，先声明类的模板，然后再声明成员模板
Blob<T>::Blob(It b, It e):data(std::make_shared<std::vector<T>>(b, e)) {}


/*
 * *************************   BlobPtr   **************************
 *
 *
 *
 */


template<typename T> class BlobPtr {
public:
    BlobPtr():curr(0){ }
    BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data), curr(sz) {  }
    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++(); // 前置必须要return 左值
    BlobPtr& operator--(); // 在类内定义，就不用写<T>, 编译器默认类型与初始化模板类型是一样的。
    BlobPtr<T> operator++ (int);
    BlobPtr<T> operator-- (int);

private:
    std::shared_ptr<std::vector<T>> check(size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};
template<typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_t sz, const std::string &s) const {
    auto ret = wptr.lock();
    if(!ret) {
        throw std::runtime_error(s);
    }
    if(sz >= ret->size()) {
        throw std::out_of_range(s);
    }
    return ret;
}


template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++ () {
    check(curr);
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator-- () {
    --curr;
    check(curr);
    return *this;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator++ (int) { // 返回的是局部变量，因此就一定不能是引用
    BlobPtr ret = *this;  // return不动
    ++(*this); // this要动
    return ret; // 返回不动的，但实际已经动了。
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) { // 这里要<T>，这是因为只有域名符号::结束以后才进入到class作用域内，进入以后就不用写<T>了
    BlobPtr ret = *this; // 这里不用<T>
    --(*this);
    return ret;
}

/*
 * *******************   友元    *******************
 * 模板类友元的关系分成三种
 * 1. 一对一的对应关系：
 *          例如 Foo<int> 都是Goo<int>的友元，但是不是Goo<double>的友元，他的友元是Foo<int>
 * 2. 唯一类型的友好关系（特定类型） ：
 *          例如：Foo<int> 是 Goo的友元（Goo是不是模板不重要），只有int才是Goo的友元，其他类型都不是
 * 3. 通用友好关系：任何类型都是其友元
 *          1. 非模板类如果声明是某个模板类的友元，则该非模板类是所有类型的友元
 *          2. template< typename X> friend class className; 由于x可以是任何类型，所以任何类型都是该类的友元
 *
 * 如何记忆这些规定呢？
 * 原则：模板参数是完整类型的一部分！只有当模板参数+class的名字相同的时候才唯一确定*一个*类型
 * 因此我们得出如下结论
 * 1. 如果模板参数存在一一对应关系，则表示一对一关系
 * 2. 如果模板参数不存在一对一关系，则表示通用类型，因为X总可以取到合适的值来与类型T进行匹配
 * 3. 如果模板参数是个常量类型，则表示特性类型。
 *
 *
 */

class Foo1;
template<typename> class Foo2;

// 非模板函数的友元
class Goo1 {
    friend class Foo2<int>; // 只有int类型的Foo2才是Goo1的友元，其他类型都不是其友元，这句不是声明，需要前置声明
    template<typename T> friend class Foo3 ; // 所有Foo3类型都是Goo1的友元，不需要提前声明，因为这句本身就是个声明了
    // 是不是声明只要看类型参数是否齐全，如果类型参数齐全了，就是声明了。否则就不是声明，需要前置声明
};

// 模板函数的友元
template<typename T>
class Goo2 {
    friend class Foo2<T>; // 一对一，同类型的才是友元
    friend class Foo2<int>; // 特定类型的友元，只有int才是Goo2全部类型的友元
    // 以上两个都不是声明，需要前置声明

    template <typename X> friend class Foo4; // 任意类型的Foo4，都是全类型Goo2的友元，因为X和T不一样，
    // X可以是T，也可以不是，因此对Foo4的类型没有任何约束
    friend class Foo5; // Foo5是Goo2的任意类型的友元
};

/*
 * *********************  using 而不是 typedef ************************
 * 新标准下提出了using来代替typedef，using与typedef相比不同在于
 * using 是一种语法糖，其使用范围更广，更随意，其对象可以是任何类型，甚至是模板。
 * typedef是一种类型的定义，其使用的前提在于该变量是个类型！
 *
 * typedef Blob<string> strBlob; //正确
 * typedef Blob<T> Blobs; // 错误，Blob<T>不是类型，只有当T是确定参数之后，其才是类型
 *
 * 但using 可以随便用，因为只是语法糖，所以可以非常灵活的去使用。
 */

template<typename T> using twin = std::pair<T, T>;
template<typename T> using twin2 = std::pair<T, int>;


/*
 * ***********************   模板函数的 static 的成员   *****************************
 * 定义：
 * static成员的定义就是在一般成员前加上static即可
 * 使用：
 * static成员的共享原则仍然是同类型内共享，换句话说，模板参数相同的obj之间共享static成员
 * 注意：
 * 1. 初始化
 * static成员变量的初始化，和类外初始化成员的方法一样。
 *      template<T> int Foo<T>::curr = 0;
 * 2. 静态成员函数也是只有使用时候才会被实例化！
 */
template<typename T>
class Foo {
public:
    static int i;
};
template<typename T> int Foo<T>::i = 0; // 静态成员变量也要带着template参数变量。

int main () {
    Blob<int> iB = {1,3,4,56,7};
    Blob<std::string> sB = {"allen", "cecilia"};
    BlobPtr<int> pb(iB);

}

