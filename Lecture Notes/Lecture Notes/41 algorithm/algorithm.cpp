#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>
#include <array>
using namespace std;

//array输出的函数 Allen版本
template <typename Array>
void printArray(const Array& vec){
    for(auto val: vec){
        cout << val << ", ";
    };
    cout << "\n";
}



void algorithemTst(){
    vector<int> arr = {1,2,3,4,5,6,7};
    
    /*count_if
     这个返回的是一个总数，即所有符合条件的总数。lambda方程若是true，则cnt ++；
     */
    auto count_if_result = count_if(arr.begin(), arr.end(), [](int key){return key%3;});
    cout << count_if_result <<endl;
    
    
    
    
    /*
     for_each (it.begin(), it.end(), function)
     利用的是function pointer实现的。 无非就是用for循环+it来实现迭代， funciton来实现功能
     */
    
    
    //实现python中 [list key = lambda x: f(x)]
    vector<int> new_arr;
    for_each(arr.begin(), arr.end(), [&](int val){if (val%3) { new_arr.push_back(val); }});
    
    //用for ( : )来输出
    for(auto val:arr){cout << val << ",";};
    
    
    
    
    
    
    
    /*
    find(it.begin(), it.end(), target)
    find的返回的是第一个被找到的it，如果没找到就返回it.end(),要想获取内容，就要用*it
     */
    auto res1 = find(arr.begin(), arr.end(), 7);
    if (res1 != arr.end()){   // iterator.end()是最后一个有效元素后的一个空，用于截止。
        cout << "\ncontain the: " << *res1 << endl;
    }
    
    //find_if
    // 返回第一个让return 为true的， 不过就是把find中的 val == target 换成你自己定义的lambda，
    auto res2 = find_if(arr.begin(), arr.end(), [](const int& val){return !(val%2);});
    cout << *res2 << endl;
    
    //find_if_not
    // 返回第一个让条件变成 return false的
    auto res3 = find_if_not(arr.begin(), arr.end(), [](const int& val){return val%3; });
    cout << *res3 << endl;
    
    
    
    
    
    /*
     all_of(it.cbegin(), it.cend, f); //因为这函数是const的函数,当然，用begin()也行。
     如果所有成员都让f返回true，就返回true。
     实现的方法是通过find_if_not 来实现的。
     如果没有不符合条件的，就说all_of了。
     */
    auto res4 = all_of(arr.cbegin(), arr.cend(), [](const int& val){return val < 1000;});
    cout << res4 << endl;
    
    //any_of 只要有一个可以就行
    auto res5 = any_of(arr.cbegin(), arr.cend(), [](const int& val){return val < 2;});
    cout << res5 << endl;
    
    //not_of 需要全都返回false。
    auto res6 = none_of(arr.begin(), arr.end(), [](const int& val){return val < 0;});
    cout << res6 << endl;
    
    
    
    
    /*adjacent_find(it.begin(), it.end(), f)
     
     return的是第一个符合条件的it。 没找到就返回 end()。
     
     tip
     1. 要用distance来计算两个it之间的距离
     2. 若f返回true，认为两个值一样大。 默认的是 ==, 只要你需要的目标会产生true就行了
     */
    cout << "\nadj_find test" << endl;
    vector<int> arr2 = {1,2,3,4,4,1};
    
    // 寻找相邻相同
    int index = distance(arr2.begin(), adjacent_find(arr2.begin(), arr2.end()));
    cout << index << endl;
    
    // 自定义寻找
    int index_increase = distance(arr2.begin(), adjacent_find(arr2.begin(), arr2.end(), [](int forword, int behind ){return forword > behind;}));
    cout << index_increase << endl;
    
    
    
    
    /*
     search(it_text.begin(), it_text.end(), parttern.begin(), parttern.end(), f);
     
     复杂度是 T*P  这完全就是个暴力搜索法，返回的是it。没找到就返回end()
     该函数是寻找parttern的函数,因此特别适合用在string上
     */
    
    cout << "search test" << endl;
    string text = "Hello this is Allen";
    string name = "Allen";
    auto index_search = distance(text.begin(), search(text.begin(), text.end(), name.begin(), name.end()));
    cout << index_search << endl;
    
    
    
    /*
     sort
     
     is_sorted(ForwardIt first, ForwardIt last, Compare comp);
     只要comp返回的是true就算sorted，我们可以自定义对比的方法
     */
    vector<int> arr_sorted = {1,2,3,4,5,6,7};
    cout << boolalpha << is_sorted(arr_sorted.begin(), arr_sorted.end(), less<int>())<< endl;
    
    
    
    
    /*
     accumulate
     
     accumulate(InputIt first, InputIt last, T init， BinaryOperation op)
     在<numeric>中
     
     init决定了返回值的type和offset， op决定了如何累计
     */
    
    vector<int> arr_acc = {1,2,3,4,5,6,7};
    auto res_add = accumulate(arr_acc.begin(), arr_acc.end(),0);
    auto res_multp = accumulate(arr_acc.begin(), arr_acc.end(), 1, multiplies<int>());
    cout << "the add accumulate result is: " << res_add << endl;
    cout << "the multiplies result is: " << res_multp << endl;
    
    
    
    /*
     max_element
     
     max_element(ForwardIt first, ForwardIt last, Compare comp);
     comp(max, cur) 中 return true 表示 前面(max)的比后面的小(cur)，因此 comp中大的要返回false
     实现方法就是暴力比较。
     */
    vector<int> arr_max = {1,2,3,5,5,6,7,32,1};
    auto maxptr = max_element(arr_max.begin(), arr_max.end(), less<int>());
    cout << "the max element is: " << *maxptr << endl;
    
    
    
    
    /*
     replace
     
     replace
     void replace( ForwardIt first, ForwardIt last,const T& old_value, const T& new_value );
     
     replace_if
     void replace_if( ForwardIt first, ForwardIt last,UnaryPredicate p, const T& new_value );
     */
    vector<int> arr_replace = {1,2,3,4,5,6,7};
    replace(arr_replace.begin(), arr_replace.end(), 1, 1000);
    for(auto val: arr_replace){cout << val << ", ";};
    cout << "\n";
    
    //replace_if 如果f是true，就会执行replace
    replace_if(arr_replace.begin(), arr_replace.end(), [](int val){return val%2;}, 0);
    
    printArray(arr_replace);
    
    
    
    /*
     swap_range
     ForwardIt2 swap_ranges( ForwardIt1 first1, ForwardIt1 last1,ForwardIt2 first2 );
     从it1.begin()开始，一直到it1.end(), 这期间的所有element都和 it2逐个互换
     */
    vector<int> arr_swap1 = {1,2,3,4,5,6,7,8,9};
    vector<int> arr_swap2 = {10, 20, 30, 40, 50, 60};
    swap_ranges(arr_swap1.begin(), arr_swap1.begin()+4, arr_swap2.begin()+1);
    printArray(arr_swap1);
    printArray(arr_swap2);
    
    
    /*
     reverse
     void reverse( BidirIt first, BidirIt last );
     将这个区间的element reverse，其余部分不动
     */
    vector<int> arr_rev = {1,2,3,4,5,6};
    reverse(arr_rev.begin(), arr_rev.begin()+4);
    printArray(arr_rev);
    
    
    /*
     unique
     unique( ForwardIt first, ForwardIt last, BinaryPredicate p );
     这个去重复只能去掉相邻的重复的内容，返回的是新的end。 因此需要erase来配合使用。
     而如果配合sort使用就可达到完全去重的效果
     */
    vector<int> arr_unique = {1,1,3,3,4,4,5,6,7,8,4,3};
    auto end = std::unique(arr_unique.begin(), arr_unique.end());
    arr_unique.erase(end,arr_unique.end());
    printArray(arr_unique);

    /*
     nth_element
     void nth_element( RandomIt first, RandomIt nth, RandomIt last, Compare comp );
     利用comp的规则来筛选出来， 从小到大的 nth element
     comp中，若first 小，返回的true，默认的是 return first < second
     
     注意，这个方法用的是partial sorting，因此并不返回val，并且还改变了原来是数组
     */
    vector<int> arr_nth = {4, 5, -4, 3,2,1,10,-1};
    nth_element(arr_nth.begin(), arr_nth.begin()+3, arr_nth.end());
    cout << arr_nth[3] << endl;   //+3找的是 4th个元素。
    
    printArray(arr_nth);
    
    
    /*
     fill
     void fill( ForwardIt first, ForwardIt last, const T& value );
     */
    vector<int> arr_fill (10);
    fill(arr_fill.begin(), arr_fill.begin()+5, 66);
    printArray(arr_fill);
    
    /*back_inserter
     不过就是用了push_back(array)来实现的。可以产生一个在结尾处的iterator。
     但是back_inserter(array) 和 arry.end()的区别是，back_inserter可以延长原来的array，
     但是，end()不可以延长原来的array。
     
     因此如果你的目的是在后面进行延长操作，那么一定要用这个，end()不能延长。
     */
    fill_n(back_inserter(arr_fill), 3, -1);
    printArray(arr_fill);
    

    
    /*
     copy
     copy(InputIt first, InputIt last, OutputIt d_first );
     */
    vector<int> arr_from = {0,1,2,3,4,5};
    vector<int> arr_to = {10,12,14};
    copy(arr_from.begin()+2, arr_from.begin()+4, arr_to.begin());
    printArray(arr_to);
    
    copy(arr_from.begin(), arr_from.end(), back_inserter(arr_to));
    printArray(arr_to);
    
    /*
     copy_if
     copy_if( InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred )
     这函数不就是python中用list去初始化另一个list的方式么！！！new_list = [val for val in list if...]
     */
    vector<int> old_array = {1,2,3,4,5,6,7,8};
    vector<int> new_array;
    copy_if(old_array.begin(), old_array.end(), back_inserter(new_array), [](int a ){return a%2;});
    printArray(new_array);
    
    /*
     copy_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );
     右对齐的copy方式
     */
    vector<int> short_arr = {1,2,3};
    vector<int> long_arr = {10,11,12,13,14,15,16,17,18};
    copy_backward(short_arr.begin(), short_arr.end(), long_arr.end());
    printArray(long_arr);
    
    
    
    /*equal
     在c++中，array是以pointer存在的，那么如何才能知道两个array的内容是否相同呢？
     
     bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p );
     
     非常简陋的对比。。。这里对比的是从 it1和it2的两个范围内的值是否一一相等，相等的方式还可以通过p 函数自己设定。
     for(it1++, it2++)
        if(!p(*it1, *it2))
            return false;
     return true;
     */
    vector<pair<int, int>> arr1 = {{2,3}, {1,4}, {4,0},{100, -4}};
    vector<pair<int, int>> arr22 = {{5,3}, {6,4}, {9,0},{10, -4}};
    auto iseq = equal(arr1.begin(), arr1.end(), arr22.begin(), arr22.end(), [](pair<int, int> a, pair<int, int> b) {return a.second == b.second;});
    cout << iseq << endl;
    
    
  
        
    
       
}
