//
// Created by Allen on 24/1/21.
//

#ifndef EFFECTIVE_CPP_HARD_TO_INCORRECTLY_H
#define EFFECTIVE_CPP_HARD_TO_INCORRECTLY_H
struct Month {
public:
    Month(int m) :m_m(m){

    }
    int m_m;
};

struct Year {
public:
    Year(int y) :m_y(y){

    }
    int m_y;
};

struct Day{
public:
    Day(int d): m_d(d){

    }
    int m_d;
};

struct Date {
public:
    Date(Year y, Month m, Day d) : m_y(y), m_m(m), m_d(d){

    }
    Year m_y;
    Month m_m;
    Day m_d;
};
/*
 * 我们提供的接口一定不要让外界容易犯错，如果用户用错了就一定不要让他通过编译，那么我们自己定义类可以防范这样的问题，
 * 类可以帮我们检查用户用的是否正确，如果用错了，编译的时候就不能通过，这才是我们的目的！！
 *
 * 通过对year， month， day的封装，让用户没法写错，同时我们还可以在其内部作出约束，防止2月30日之类的产生！！
 * 如果使用Date(1994, 8, 9) 的方式，保不齐用户会怎么用！！
 */
int test() {
    Date(Year(1994), Month(8), Day(9));

    cout << "main ending" << endl;
}
#endif //EFFECTIVE_CPP_HARD_TO_INCORRECTLY_H
