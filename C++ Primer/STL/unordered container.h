//
// Created by Allen on 2021/3/14.
//

#ifndef C___PRIMER_UNORDERED_CONTAINER_H
#define C___PRIMER_UNORDERED_CONTAINER_H
#include <iostream>
#include <unordered_set>
#define PRINT(X) std::cout << (X) << std::endl;

/*
 * ************ 无序容器  *************
 * 无序容器是通过hash函数和"=="来组织容器结构的
 * hash函数是用来将key值映射到桶内，而==是用来对比两个key值是否相等
 * 当然我们可以将hash函数和自定义的判等函数或者类在初始化的时候放到模板中
 *
 * 而有序容器是通过比较函数或者"<" 来组织容器结构的。
 *
 * 与此同时，无序容器是通过将key值转换成hash值，然后通过hash值找到对应该hash值的桶，然后把该key放到桶内。
 * 也就是说hash值和桶是一一对应关系，但不同的key值可以映射到相同的hash值（桶）内，但相同但key值，必须
 * 映射到相同的hash值（桶内）。
 *
 *
 *
 */

int main() {
    std::unordered_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    PRINT(s.bucket_count());
    PRINT(s.max_bucket_count());
    PRINT(s.bucket_size(0));
    PRINT(s.bucket(10));
}
#endif //C___PRIMER_UNORDERED_CONTAINER_H
