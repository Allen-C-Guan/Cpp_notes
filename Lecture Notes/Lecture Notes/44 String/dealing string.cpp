#include<iostream>
#include<cctype>
#include <regex>
#include <sstream>
using namespace std;


/*
 split写成function
 */
vector<string> split(const string& text, const string& split_flag){
    regex flag(split_flag);
    return vector<string>(sregex_token_iterator(text.begin(), text.end(), flag, -1), sregex_token_iterator());
}




void StringTst1(){
    /*
     cctype中包含大量可以处理字符串或者字符的函数
     但是这个库里面都是用int来处理char的， input也是int类型， output也是int类型
     */
    
    /*
     int isalnum (int ch);
     若char是大小写和数字，就返回non-zero int, 否则就返回0
     */
    cout << isalnum('A') << endl;
    //通常输出的时候可以伴随着bool cast
    cout << boolalpha << (bool) isalnum('4') << endl;
    
    //toupper
    //我们需要在重新cast成为char
    cout << (char)toupper('C') << endl;
    
    
    /*
     int stoi(string s)
     作用是把string变成 int，从头开始，贪婪的从头往后截取最长的数字， 并且会包含正负号
     而cast在c中，是ascii码的cast
     */
    
    int num = stoi("-123i3445");  //得到的是-123
    
    /*
     to_string
     这个功能和java中的string差不多，就是输出的时候调用的函数。 把各种类型变成string的类型。
     */
    string s = to_string(4);
    
    
    /*
     split
     
     借助regex完成split的原理在于：
     1. 利用iterator，每次都先调用函数 regex_search， 看看是否match上，而后自增。
     2. 如果匹配上就会包含在match_res中，如果没匹配上，就不包含在match_res中
     3. iterator  ***返回一个it的头***  ，即begin(), 而it的结尾是空it， 既 regex_iterator()。
     4. 从it -> regex_iterator()  表示从begin() -> end()
     
     5. -1表示res里存放没匹配上的内容。
     */
    
    
    /*
     注意！！！
     
     regex_iterator的end是一个空it，既 regex_iterator()
     通常情况，我们用容器的时候，是s.begin(), s.end(), 这因为s是个continer, 而continer.begin()返回的是it_head, s.end() 返回的是空it,既 iterator()
     
     但是在用iterator的时候是：  it_head, iterator()即可
     */
    
    
    cout << "split test" << endl;
    
    string text = "hahaf afads  htgh yuy kluy 63456345  79";
    regex parttern ("\\s+");
    /*
     -1表示，返回的是从上一次matching到下一次matching之间的内容。既两个匹配上的内容中间没匹配上的部分。
     如果没有-1，只返回匹配上的部分。
     */
    
    vector<string> split_res (sregex_token_iterator(text.begin(), text.end(), parttern,-1), sregex_token_iterator());
    
    
    auto res = split(text, "\\s+");

    
    
    
    /*
     一个更简单的split的方法， -> stringstream
     但是这个方法的局限性在于 split是按着 空格，回车， 表格分隔符来拆分字符串的.
     
     stream的使用可以归结如下几个关键点
     1. stream的输出是通过 >> 来输出的
     2. stream的工作方式和it相似，都是可以记录运行到哪了。
     3. stringstream每步的停止点是 空格， 回车和分隔符，且不关心有几个空格，连续的一律抹掉

     */
    cout << "this is sstream test" << endl;
    text = "adfa \n dfadf  78899i 094 ()  $$$"; //空格，\n， 一个或者多个，对于stream而言都是一样的
    //stream的初始化
    //method 1
    stringstream ss;
    ss.str(text);
    
    //method2
    stringstream ss2(text);
    
    string cur_part;
    while (ss >> cur_part){    //这里是stream的特殊工作方式，有点像迭代器的工作方式
        cout << cur_part <<endl;
    }
    
    
    
    /*  截取string中的一部分的方法、
     
    substr(start_index,end_idx)
    其中 start必须在indexRange里， end可以不载indexrange里
     */
    string s_ = "123456789";
    string sub = s_.substr(2,10);
//    cout << sub << endl;
}

