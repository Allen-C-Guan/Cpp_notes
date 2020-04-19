# include <iostream>
using namespace std;

/*
 * 这就是C with class，和java是相同的
 */
class Student {

    /*
     * 和java相同，private和public用来表示可视范围的，private只在class里面才会看到，并被该改变
     */
    private:
        double GPA;

    public:
        string name;
        string major;

        // constructor
        // constructor要和外界接触，自然也就必须要在public里面了
        //没有传参的constructor，通常作为默认的constructor
        Student(){
            name = "no name";
            major = "no major";
            GPA = 0;
        }
        //有传参的constructor
        Student(string aName, string aMajor, double aGPA){
            name = aName;
            major = aMajor;
            GPA = aGPA;
        }

        bool isHonors(){
            return GPA > 3.5;
        }

        /*
         * setter and getter
         * 当我们使用private的时候，外界函数就不可以直接改变当前函数的属性，这时候就需要setter和getter
         * 他们可以帮我们接触到private的内容，因为setter和getter是class里的，他们可以肆意修改class里的任何内容，包括private
         * 而setter和getter又是public的，他们又可以基础到外面的世界
         *
         * 这样做的意义在于： 我们既然可以把setter和getter当成这个class的出入口，那么我们只要在setter或者getter的内部设置好防火墙，
         * 就可以防止外界肆意修改class里面的内容了
         */
        void setGPA(double aGPA){
            // 防火墙
            if (0 <= aGPA and aGPA <= 4){
                GPA = aGPA;
            }else{
                cout << "not a valid GPA" << endl;
            }
        }
        double getGPA(){
            return GPA;
        }
};

int class_and_obj(){
    Student student1("allen","EE", 3.7);
    cout << student1.isHonors() << endl;
    student1.setGPA(4.6);
    cout << student1.getGPA() << endl;
    return 0;
}

