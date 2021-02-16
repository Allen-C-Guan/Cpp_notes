//
// Created by Allen on 17/1/21.
//

#ifndef EFFECTIVE_CPP_SMARTPTR_H
#define EFFECTIVE_CPP_SMARTPTR_H
class Foo {
public:
    Foo () {
        cout << "Foo constructor" << endl;
    }
    ~Foo () {
        cout << "Foo destructor" << endl;
    }
    void getter() {}

};

template <typename T>
class MySmartPtr {
public:
    MySmartPtr(T *ptr): m_smartPtr(ptr) {};
    ~MySmartPtr(){
        if (cnt == 0) {
            delete m_smartPtr;
        } else {
            cnt--;
            cout << cnt << endl;
        }
    }

    MySmartPtr(const MySmartPtr<T> &others)
            :m_smartPtr(others.m_smartPtr){
        cnt++;
        cout << cnt << endl;
    }
    // 获取原始数据的接口。
    T *get() {
        return m_smartPtr;
    }


private:
    T *m_smartPtr;
    static uint32_t cnt; // 这里用个类计数器技术，实现类似shared_ptr的可以被copy的功能。
};


template<> uint32_t  MySmartPtr<Foo>::cnt = 0;


int testMySmartPointer() {
    {
        MySmartPtr<Foo> ptr1 = new Foo();
        {
            MySmartPtr<Foo> ptr2 = ptr1;
        }
    }
    std::cout << "ENDING" << std::endl;
    return 0;
}



/*
 * *****************   deleter  ***************
 * smartpointer 给我们提供了自定义deleter的功能，让我们在智能delete变量的时候，不只是单纯的delete；也可以做我们想做的事情；
 * 比如delete []; 删除一个array
 * 比如 UnLock;
 * 对于第二种用法，是因为我们的目的有时候并不想用smartptr帮我们管理内存，而是帮我们管理一些事件，这时候，就可以封装一个RAII机制的class，
 * 但与传统的RAII不同的是，该class里没有destructor，取而代之的是个smartptr的私有变量。我们利用的是smartptr的自我销毁机制，
 * 来代替destructor。
 * 这样做的好处是，当使用该RAII的class的时候，即使该class被复制，也只是smartptr的复制（struct的复制本质上是成员变量的复制），并不会产生多次销毁。
 *
 * 这样的RAII class的写法为：
 * 1。 写一个deleter，deleter的要求是，入参是一个**smart_ptr的模板类的指针**，然后body是你想要在smart_ptr被销毁的时候做的事情。
 * 2。 传入一个pointer，并用该ptr和**deleter函数指针**来初始化smart_ptr;
 * 3. 在constructor内写你要在初始化的过程中完成的步骤。
 */

static void LockIt () {cout << "locked" << endl;}
static void UnLockIt (string* s) {cout << "unlocked" << endl;}
// deleter 必须要接受一个 templete的ptr，因为只有ptr进入到函数里，这个指针对应的heap变量才可以被删除。

class Lock {
public:
    Lock (string *s) :s_(s, UnLockIt){
        LockIt();  // body 初始化的时候的事情
    }
private:
    shared_ptr<string> s_;
};


int testDeleter() {
    {
        string s = "allen";
        Lock l1(&s);
        {
            Lock l2 = l1; // 即使发生了复制，也不担心在销毁的时候，二次销毁。（这里不会是unlock两次）
        }
    }
    std::cout << "ENDING" << std::endl;

/*
 * 几乎所有的smart ptr都会对"->" 和 "*" 进行overloading，使-> 可以调用的是原始ptr的函数而是不是smart ptr的函数
 * 这是因为，所有资源管理类必须给外界提供一个可以直接接触到原始类型的接口
 * 同时smart ptr还有get()函数用来获取原始指针的接口。
 */
    shared_ptr<Foo> fPtr(new Foo());
    // 这里是调用原始数据的函数
    fPtr->getter();
    (*fPtr).getter();
    //这是调用shared_ptr的get() 返回的是原始数据
    Foo *f = fPtr.get();


    auto &obj = ToDoList::getList();
    obj.initList(vector<string>({"cook", "sleep", "meeting", "eat"}));
    cout << obj.getToDoNum() << endl;
    cout << obj.getEvent(3) << endl;
    cout << obj.addNewEvent("fixBug");
    cout << obj.finishedEvent() << endl;
    cout << "main ending" << endl;
    return 0;
}
#endif //EFFECTIVE_CPP_SMARTPTR_H
