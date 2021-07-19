#include <iostream>
#include <string>
#include <vector>
#include <map>
/*
 * ****************************** 考虑使用lazy evaluation **********************
 * 当我们用以某种方式撰写你的classes的时候，使他们延缓运算，知道哪些运算结果刻不容缓的被迫需要为止。如果其运算结果一直不被需要
 * 运算也就一直不执行！
 *
 * 1. reference counting
 * 该策略认为，在你真正需要之前，不要急着为某物一个副本。取而代之的是以拖延战术应付，只要能够拖延，就使用其引用，而不是copy一份。

 * 比如：
 * String s1 = "hello";
 * String s2 = s1;
 * 那么通常情况下，我们在执行s2 = s1的时候，s2就会对s1进行内存copy，因此当前内存中存在两份hello！
 * 但是我们也可以在这时，不进行copy，而是选择reference！
 *
 * std::cout << s1 + s2;
 * 我完全不需要s2有自己的一份copy，我们只要将两个“hello”拼在一起就行了，这样就避免了一次copy！
 *
 * 但是当我们需要copy的时候，就需要进行copy了，比如
 * s1.convertTOupperCase();
 * 此时我们发现s1已经发生了变化，按理说s2不应该发生变化，因此这时候，就需要s2拥有自己的一套副本，而不是继续取共享s1的内存
 * 这时候我们就不能在拖延了！
 *
 * 2. lazy fetching
 * 这个策略讲的是，我们只有在需要的时候才fetch出来需要fetch的那部分，否则就只保留一个空壳子，什么也不fetch！
 *
 * 比如我们有一个数据为：
 * class LargeObj
 * {
 *  public:
 *      mutable string *field1Value;
 *      mutable double *field2Value;
 *      mutable int *field3Value;
 *  public：
 *      const string& filed1() const;
 * }
 *
 * 我们需要用这个LargeObj来获取数据， 但是如果我每次都无脑的全量去获取，获取完成以后可能只用其中一小部分就显得很浪费！
 * 所以我们怎么做的呢？
 *
 * 我们每次只是新建一个空的壳子
 * LargeObj object(id); // 其实这里什么也没做，所有field都是nullptr
 *
 * 如果用户需要field1的时候，会调用field1的接口，我们这时候只要获取field1的信息就行了，如果用户没有获取field2，field3，那么
 * 这里两个field则永远不会被get到！！
 *
 * 3. Lazy Expression evaluation
 * 将一个完整的计算过程，拆成一些小的相互不耦合的中间过程，对中间过程进行lazy 方式的计算，也就是说，你用哪步，我算到哪步多了不算
 * 
 * 
 * 
 */

int main() {

    std::cout << "ENDING" << std::endl;
}
