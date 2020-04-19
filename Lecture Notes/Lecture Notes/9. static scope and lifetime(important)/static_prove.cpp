# include <iostream>
using namespace std;

static int num = 7;  // 只限于这个file下的
int num2 = 100000;   //全局变量



void static_prove(){
    
}

class extern_class{  // 这class好像不能extern来引用
    float x = 0, y = 100;
    
};

static void function_test(){
    cout << "this is static function" << endl;
}
