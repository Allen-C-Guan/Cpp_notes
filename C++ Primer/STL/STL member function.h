//
// Created by Allen on 2021/3/6.
//

#ifndef C___PRIMER_STL_MEMBER_FUNCTION_H
#define C___PRIMER_STL_MEMBER_FUNCTION_H
#include <iostream>
#include <vector>
#include <string>
#include <list>


int main()
{
    /*
     ******************** assign函数（仅顺序容器可用）*******************************
     *
     * assign就是为了解决类型不匹配（但可转换）和子序列的赋值问题而来的函数。
     * 其方法就是先清除自己本身，然后在copy insert来赋值自己。
     * 因此会造成两个问题
     * 1。不可自赋值，且对容器内部的引用，指针和it均失效，失效指的是内容变化了.
     * 2。速度比较慢，比如比swap慢
     * 这里解释一下失效；失效指的是内容不在绑定了，我们指针，reference和it绑定的是内存，
     * 而assign改变的是内存的内容。自然就会发生引用的变化
     */
    std::vector<int> v = {0,1,2,3,4};
    std::list<int> l = {4,3,2,1,0};
    v.assign(l.begin(), l.end());
    v.assign(++l.begin(), --l.end());
    v.assign(v.begin(),v.end());

    /*
     * constructor可以用迭代器来解决子序列和类型不匹配（但可转换）的问题，但相同的赋值问题还是要通过assign
     * 函数来完成
     */
    std::vector<int> v1(l.begin(), l.end());
    std::vector<int> v2(v1);
    std::list<int> l2(v1.begin(), v1.end());

    /*
     ******************** swap ***************************
     * swap不会导致引用和指针的失效，因为swap没有改变内存，只是交换了顶层指针, 因此引用不会导致引用失效。
     * 当然swap的速度也会特别快，因为assign需要清除，在逐个插入。
     */
    std::vector<int> v5 = {0,1};
    std::vector<int> v6 = {10,20};
    int &ip = v5[0];
    std::cout << ip << std::endl;
    std::cout << &v5[0] << std::endl;
    std::swap(v5, v6);
    std::cout << ip << std::endl;
    std::cout << v5[0] << std::endl;
    std::cout << &v5[0] << std::endl;

    /***************** insert ************************/
    /* insert可以返回新插入的内容中的第一个对应的it。如果是0，则返回it_pos;
     * insert(it_pos, val);
     * insert(it_pos, other.it_start, other.it_last);
     * insert(it_pos, num, val);
     * insert(it_pos, {val1, val2, val3...};
     */
    std::vector<int> v7 = {0,1,2,3};
    auto it = v7.insert(v7.begin()+1, 9); // insert是可以返回新插入的内容的第一个的
    std::cout << *it << std::endl;

    /***************** erase() ************************/
    /*
     * erase可以返回被删除的元素后面的第一个
     * erase(it_pos);
     * erase(it_start, it_last);
     */





}
#endif //C___PRIMER_STL_MEMBER_FUNCTION_H
