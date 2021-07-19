/*
 * ******************************** 了解virtual functions, typeId的成本 **********************************
 * virtual function是通过vptr（每个obj都有自己的vptr，在constructor中构造），和vtable（一个class只有一个vtable）来
 * 实现的
 *
 * 都说virtual function的代价，那其代价到底是哪里来的
 * 1. virtual function的调用：
 *      vtable成本：一个指针间接动作（obj中的vptr索引到vtbl) + 一个偏移调整(vtbl中索引到那个virtual function）
 *      但其成本比较低，通常请款下任务，虚函数的成本约等于函数指针的调用！
 * 2. virtual function意味着放弃inline！
 *      该成本是比较大的，virtual function通常意味着“等待”， 而inline意味着“编译期确定”，因此c++编译器通常会拒绝
 *      virtual function的inline请求
 *      那么这个代价有的时候其实还是比较大的！
 *
 * 但毕竟C++给你提供了这个机制，你可以不用，但如果你需要这个机制，那么编译器实现的通常比自己实现的效率更高，而且更加robust！
 *
 * typeId的实现：
 * 在vtbl中再安插一个ptr，用于指向type-info。 因此，typeId的实现依赖vtable，因此就会要求class至少有一个virtual function
 * 否则无法实现typeId的功能
 *
 */
