#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;


struct students{
    static int a;
};
int students::a;

int main() {
    
    students s1;
    cout << students::a << endl;
    
    cout << "\n\nmain  has finish" << endl;


    
}
