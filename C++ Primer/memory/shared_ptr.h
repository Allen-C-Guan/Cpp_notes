//
// Created by Allen on 2021/3/14.
//

#ifndef C___PRIMER_SHARED_PTR_H
#define C___PRIMER_SHARED_PTR_H
#include <iostream>
#include <memory>
#include <vector>
#include <string>

/* ****************** 动态内存 ********************
 * 变量存放的位置可以分成三种
 * 1。stack上：局部变量，块中被初始化，块结束的时候被自动销毁
 * 2。静态内存中：global 和 static变量。程序开始的时候被初始化或者分配内存，程序结束的时候自动被销毁
 * 3。动态内存中：在heap中，需要手动显示初始化，并手动显示的删除，和声明周期与作用域无关。
 *
 * 使用动态内存的原因：
 * 使用动态内存的原因必须为一下三种之一，否则请不要用动态内存
 * 1。程序不知道自己需要使用多少对象。需要动态分配内存，vector
 * 2。程序不知道所需对象的准确类型
 * 3。程序需要在多个对象间共享数据！因为对象的生命期与资源有效期的不一致！！
 *
 * 我们要知道，动态内存和stack最大的区别在于两点，
 * 1。动态！可以随时分配和扩大内存空间
 * 2。资源的有效期，资源有效期由程序员来管理，与对象的声明周期无关！
 *
 * 这里我们需要分开看对象和资源！对象拥有或者使用了资源，但并不意味着对象和资源是永远绑定，同生共死的。
 * 对于stack上而言，对象被销毁，资源也被销毁，但对于heap上而言，对象被销毁，但资源并不一定被销毁。
 *
 * 当我们需要多个对象之间共享底层数据的时候，就不允许某一个对象被销毁，底层数据就被释放，因为底层数据还被其他
 * 对象所引用并使用着。
 *
 *
 */

/*
 * ***************** shared_ptr **************
 * shared_ptr<T> sp = make_shared<T>();
 *
 * shared_ptr的默认初始化是个nullptr；
 * ie. shared_ptr<T> sp; 这里sp内存放的是nullptr
 *
 * make_shared<T>();如果没参数，则是类T的值初始化，如果有参数，则会调用T的对应构造函数。
 *
 * shared_ptr的计数器
 * 计数器的增加：拷贝，初始化，入参，return
 * 计数的减少：被赋新值，被销毁。
 *
 * shared_ptr的作用：
 * 我们可以在大部分情况下，用shared_ptr来代替row ptr管理ptr，包括ptr类型的成员变量。
 * 其最大的好处在于，我们不用再考虑该类的copy，赋值和销毁的时候，如何释放内存的问题。
 * shared_ptr**依赖**默认**的拷贝，赋值和析构函数**！！就能正确的对heap上的内存进行管理和释放。
 *
 * 具体使用方法：
 * 我们需要在构造函数中，分配一块内存，并用make_shared返回一个shared_ptr，存在obj中即可
 *
 */


/*
 * 例子：
 * 构建一个共享vector<string>的类！
 */

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    ~StrBlob() = default;
    bool Empty(){return data->empty();}
    void push_back(std::string s){ data->push_back(s);}
    size_type size(){ return data->size(); }
    void pop_back();

private:
    // 由于该ptr用shared_ptr来管理，因此我们不用考虑该ptr的拷贝，析构和赋值。
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string msg);
};

// 在构造函数中，要对shared_ptr成员变量用make_shared进行初始化，该过程包括在heap上开辟内存，并进行值初始化。
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}

void StrBlob::check(StrBlob::size_type i, const std::string msg) {
    if(i >= data->size()) {
        throw std::out_of_range(msg);
    }
}
void StrBlob::pop_back() {
    check(0, "front on empty StrBlob");
    data->pop_back();
}



int main()
{

}
#endif //C___PRIMER_SHARED_PTR_H
