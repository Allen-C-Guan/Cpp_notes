# include <iostream>
# include <cmath>
using namespace std;

// switch 和 java中的用法几乎完全一样的啊
string getDayOfWeek(int dayNum){
    string dayName;
    switch(dayNum){
        case 0 :
            dayName = "Sunday";
            break;
        case 1 :
            dayName = "Monday";
            break;
        default:
            dayName = "wrong Number";
    }
    return dayName;
}


int switch_case() {
    cout << getDayOfWeek(5) << endl;
    return 0;
}

