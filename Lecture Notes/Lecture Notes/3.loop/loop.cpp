#include <iostream>
using namespace std;
void loop(){
    
    
    /*
     for loop 的用法
     
     这里就很好的展示了for循环后面的括号的作用，不过就是按着固定顺序执行的语句而已，有还是没有，在哪其实都不重要
     如果连中间的condition都不要了，就成了无限循环了，就相当于把 true写在那个位置上。
     
     */
    
    int condition = true;
    int i = 0;
    for (;condition;){
        cout << i << endl;
        if (i >= 5)
            condition = false;
        i++;
    }
}



