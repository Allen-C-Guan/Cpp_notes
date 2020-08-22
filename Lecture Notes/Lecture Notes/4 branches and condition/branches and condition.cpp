# include <iostream>

void branches_test(){
    const char* ptr = "ba";
    /*这是一个非常典型的用于判定当前信息是否是None的方法
     当ptr指向某个变量或者地址的时候，ptr的值就一定不是nullptr(0), 那么ptr 做完bool就是一个true
     */
    if (ptr)  //如果ptr有所指，则执行，
        std::cout << "this is not None, this is "<< *ptr << ", the next one is "<< *(ptr+1) << std::endl;
    else if (*ptr == 'c')
        std::cout << "hello this word" << std::endl;
    else
        std::cout << "this is a None" << std::endl;
    
    
    
    // if else的简短写法
    
    int var = 8;
    int result = var > 5? 10000: 0;  // if result = var, result = 1000  else result = 0
    
    
    int res = var > 5 ? var >10? 100 : 8 : 0;
    /*
     if (var > 5)
        if (var > 10)
            var = 100;
        else
            var = 8;
     else
        0;
     
     */
    
    
    
    
}
