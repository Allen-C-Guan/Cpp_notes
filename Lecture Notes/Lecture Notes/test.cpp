#include <iostream>
#include <array>
#include <memory>
using namespace std;

# define Print(x) cout << x << endl;

# define IsDebug 1
# if IsDebug == 1
# define State "Debugging"
# else
# define state "Release"
# endif


void test(){
    Print("ALlen");
    Print(State);
    
    

}
