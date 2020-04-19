//
# include <iostream>
using namespace std;

int two_D_array(){
    int numberGrade[][3] =
        {  //2D array中我们必须要给出对应的第二维度，第一维度可以不给
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };

    cout << numberGrade[0][1] << endl;

    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << numberGrade[i][j] << endl;
        }
    }


    return 0;
}
