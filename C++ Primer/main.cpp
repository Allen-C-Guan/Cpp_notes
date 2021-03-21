#include <iostream>
#include <memory>
#include <vector>
/*
 * **************** allocator 类 ********************
 * 功能：
 * allocator类，可以将分配内存和构造操作拆开，将析构和释放内存操作分开！
 * 即使类没有默认构造函数，也一样可以动态分配数组
 *
 * 原因：
 * 我们之前采用new和delete来对内存进行操作，new操作将内存分配和对象构造绑定在一起，而delete
 * 把对象析构和内存释放绑定在一起。这种操作对单个对象而言，无疑是方便且安全的。
 * 因为构造意味着你要知道初值是什么，在分配内存的时候，直接给定一个合理值是安全高效的。
 *
 * 但当我们考虑开辟一大片内存的时候，我们通常需要按需构造对象！这意味着在我开辟内存的时候，
 * 1. 我不知道实际需要构造多少对象！（不一定开辟的内存都要用上）
 * 2. 我不知道整个数组中，每个元素应该的初值是多少！
 *
 * 而如果此时采用new来开辟内存，意味着在你不知道各个元素的初值的情况下，所有开辟的内存空间，
 * 都会被**默认构造出来***。这无疑是浪费的。
 * 1. 我在用的时候还要改的，原来默认构造的东西被直接覆盖，从未被用到
 * 2. 我可能开辟了1w个单位的内存，实际上我只用10个，哪后面那么多构造好了有何用？
 * 3. 如果我的自定义的类是没有默认构造函数的咋办？new[]只能默认初始化！
 *
 * allocator的解决方案：
 * allocator可以做到，当开辟一大片内存的时候，只有我需要的时候，我真正构造对象。
 * 而最初开辟的内存是原始的，未构造的。
 *
 * 使用方法：
 * allocator<T> a; // 适用模版初始化一个allocator, 可以为类型为T的对象分配内存。
 *
 * a.allocate(n); // 分配原始，未构造的内存，个数为n，内存大小根据T的大小计算
 * a.deallocate(p, n); // 释放内存，p必须是个T*类型的指针，且用allocator创建而来
 *                     // n表示释放的T的个数，且n的个数和p创建时候的大小！
 *                     // 使用deallocate之前要destroy。
 *
 * a.construct(p, args) // p必须是类型T*的指针，且指向原始内存，args是T的构造函数入参
 * a.destroy(p); // p指向的对象执行析构。
 *
 */
int main ()
{
    // 初始化allocator
    std::allocator<std::string> alloc; // 一个可以分配string array的分配器
    std::allocator<std::basic_string<char>>::pointer pStrArr = alloc.allocate(5); // 用分配器获得一片原始内存

    // 使用allocator生成对象
    std::allocator<std::basic_string<char>>::pointer cur = pStrArr;
    alloc.construct(cur); // 没有arg，调用默认初始化
    cur++;
    alloc.construct(cur, 10, 'A'); // 调用val和char的构造函数
    cur++;
    alloc.construct(cur, "Allen"); // 调用string的拷贝构造函数

    // 销毁对象
    while(cur != pStrArr){
        alloc.destroy(cur--);
    }

    // 释放内存，必须在destory之后
    alloc.deallocate(pStrArr, 5); // n的值必须和分配内存的时候一样大，

    /*
     * 拷贝和填充未初始化的内存算法 在memory中
     * 功能，在荒芜的未初始化过的内存中，直接创建对象，一步到位
     */
    std::vector<int> iArr = {1,2,3,4};
    std::allocator<int> alloc2;
    auto p = alloc2.allocate(iArr.size() * 2);

    // 直接在未构造过的内存中将vector的内容copy过来
    auto curPos = std::uninitialized_copy(iArr.begin(), iArr.end(), p);
    // 将剩余内容全部填充为888。
    std::uninitialized_fill_n(curPos, iArr.size(), 888);

}