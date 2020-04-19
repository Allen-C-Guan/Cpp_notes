# include <iostream>
using namespace std;
int while_loop(){

    int index = 1;
    while (index < 10){
        index ++;
        cout << index << endl;
    }

    // do while loop 至少执行一次
    index = 1000;
    do {
        cout << index << endl;
        index ++;
    }while(index <= 5);


    return 0;
}
