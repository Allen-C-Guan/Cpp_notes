#include <iostream>
#include <memory>
#include <vector>

using namespace std;

const vector<int> tst(vector<int>& v){
    auto vtst = v;
    return vtst;
}

void StringTst1();
int main() {
    {
        const vector<int> v1 = {1,2,3,4,5,65};
        const vector<int> v2 = v1;
        
        cout << "main has finished" << endl;
    }
    cout << "\n\nmain  has finish" << endl;
}
