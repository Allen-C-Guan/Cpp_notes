#include <iostream>
#include <string>
/*
 * ************************ 在constructors内阻止资源的泄露 ********************
 * 原则：
 * constructor内尽量不要抛出异常。
 * 当必须constructor必须抛出异常的时候，这时候必须要保证部分构造的对象被正常清理！
 *
 * 原因：
 * 我们要记得两个原则：
 * 1. 未被构造完全的对象不会被编译器调用destructor！！！
 * 2. new失败的动作，会导致赋值语句（不会返回pointer）不会被执行！！
 *
 * 第一条则意味着你在destructor中完成的清理动作在未构造完成的对象中，是不会被执行的！
 * 第二条意味着，如new失败了，已经被构造的部分将会导致永久性内存泄露！！
 *
 * 因此，当我们constructor一定要抛出异常的时候，已经要做好清理工作！
 */
class Image {
public:
    Image() {
        std::cout << "create an image" << std::endl;
    }
    ~Image() {
        std::cout << "image has been destroyed" << std::endl;
    }
};

/*
 * 这个例子让constructor抛出了exception，这实际上导致，image从没有被delete掉，
 * destructor也因为constructor没有执行完毕而不会被调用，从而导致image的永久内存泄露！
 * 因此我们不能让constructor只抛出异常，而不处理异常！
 */
class FooWithException {
public:
    FooWithException(std::string name, int age) :name_(name), age_(age){
        std::cout << "Foo has been created" << std::endl;
        picture_ = new Image();
        throw std::bad_alloc();
    }
    ~FooWithException() {
        delete picture_;
        std::cout << "Foo has been destroyed" << std::endl;
    }
private:
    std::string name_;
    int age_;
    Image *picture_ = nullptr;
};

/*
 * 这个例子就是当constructor抛出异常的时候，在constructor里手动去清理现场！用catch取代destructor的
 * 作用！这里需要注意两个问题！
 * 1. catch需要完成所有清理工作，在外界看来，该实例貌似已经被自动清理过了
 * 2. catch清理完毕后依然要继续throw，一方面你想让外界看到你construct失败了，另一方面如果constructor自己吞下了
 *  execption，这在编译器看来你的constructor是成功，因此也会调用destructor来销毁这个对象，但是由于
 *  catch中的工作和destructor中的工作完全一致，均是内存清理，这会导致内存被重复清理从而导致错误！！
 */

class FooWithOutException {
public:
    FooWithOutException(std::string name, int age) :name_(name), age_(age){
        try {
            std::cout << "Foo has been created" << std::endl;
            picture_ = new Image();
            throw std::bad_alloc();
        } catch (...){
            clearUp();
            throw;
        }
    }
    ~FooWithOutException() {
        clearUp();
        std::cout << "Foo has been destroyed" << std::endl;
    }
    void clearUp() {
        delete picture_;
    }
private:
    std::string name_;
    int age_;
    Image *picture_ = nullptr;
};

/*
 * 还有一种方式，是将内存托管给smart_ptr来管理，smart_ptr在异常抛出的时候，仍然可以调用自身的destructor来保证
 * 被初始化出来的内存被正常的释放！
 */

class FooWithSmrtPtr{
public:
    FooWithSmrtPtr(std::string name, int age) :name_(name), age_(age){
        try {
            std::cout << "Foo has been created" << std::endl;
            picture_ = new Image();
            throw std::bad_alloc();
        } catch (...){
            clearUp();
            throw;
        }
    }
    ~FooWithSmrtPtr() {
        clearUp();
        std::cout << "Foo has been destroyed" << std::endl;
    }
    void clearUp() {
        delete picture_;
    }
private:
    std::string name_;
    int age_;
    Image *picture_ = nullptr;
};

int main ()
{
    std::cout << "\"test FooWithException\"\n" << std::endl;
    {
        try {
            FooWithException f("allen", 10);
        } catch (...) {
            std::cout << "catch the exception" << std::endl;
        }
    }

    std::cout << "\n\n\"test FooWithOutException\"\n" << std::endl;
    {
        try {
            FooWithOutException f("allen", 10);
        } catch (...) {
            std::cout << "catch the exception" << std::endl;
        }
    }

    std::cout << "\n\n\"test FooWithSmrtPtr\"\n" << std::endl;
    {
        try {
            FooWithSmrtPtr f("allen", 10);
        } catch (...) {
            std::cout << "catch the exception" << std::endl;
        }
    }


}
