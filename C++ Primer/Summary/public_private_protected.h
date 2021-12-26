//
// Created by Allen on 26/12/21.
//

#ifndef SUMMARY_PUBLIC_PRIVATE_PROTECTED_H
#define SUMMARY_PUBLIC_PRIVATE_PROTECTED_H

namespace public_private_protected {
    class Base {
    public:
        void PublicFunc() { }
        int publicVal;

    private:
        void PrivateFunc() { }
        int privateVal;

    protected:
        void ProtectedFunc() {}
        int protectedVal;
    };

    class PublicDerived : public Base {
    public:
        void ShowAuthorityInDerivedSpace() {
            // 可以访问父类的public和private成员。
            this->publicVal;
            this->protectedVal;
            this->PublicFunc();
            this->ProtectedFunc();

            // 父类的私有的成员无法访问到
//            this->privateVal;
//            this->PrivateFunc();
        }
    };

    class PrivateDerived : private Base {
    public:
        void ShowAuthorityInDerivedSpace() {
            // 子类依然可以访问父类的public和private成员！！
            // 这是因为这个private继承，限制的不是子类访问父类的权限。因此不会影响子类作用域的访问权限！
            // 而限制的是子类对象，在子类作用域外部，是否可以将其父类暴露给外部！！
            this->publicVal;
            this->protectedVal;
            this->PublicFunc();
            this->ProtectedFunc();

            // 父类的私有的成员仍然无法访问到
//            this->privateVal;
//            this->PrivateFunc();
        }
    };
}


void TestPublicPrivateProtected()
{
    using namespace public_private_protected;
    // 以公有方式继承父类的子类实例
    PublicDerived pd;
    pd.publicVal; // 子类外部可以使用父类的public成员
    pd.PublicFunc(); // 在子类外部可以使用父类的public 方法
    pd.ShowAuthorityInDerivedSpace(); // 子类外部可以使用子类自己的public 方法
//  pd.ProtectedFunc(); // 子类的外部，不可以使用父类的protected成员
//  pd.PrivateFunc();  // 子类的外部，不可以使用父类的private成员

    // 以私有方式继承父类的子类实例
    PrivateDerived prd;
    prd.ShowAuthorityInDerivedSpace(); // 子类可以使用自己的public成员
//  prd.PublicFunc(); // 但是在子类的外部，子类不可以使用其父类的成员！！！
//  prd.publicVal;

}
#endif //SUMMARY_PUBLIC_PRIVATE_PROTECTED_H
