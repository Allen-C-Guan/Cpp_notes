#include <iostream>

/*
 * 代理的使用
 */
/*
 * C++里面对于2维数组的支持是很不友好的，要想声明一个二维数组，你需要声明一个第一维度是int指针的数组，第二维度才是int类型的数据。
 * 换句话说，就是一个指针数组，每个指针元素指向一个array
 */
int (*arr2D)[4] = new int[2][4];

/*
 * 那么我们有没有什么办法能解决这个问题那
 */
template<class T>
class Array2D {
public:
    Array2D(int d1, int d2): array1DSize_(d2) {
        data = (T*) malloc(sizeof(T) * d1 * d2); // 由于template没有采用参数模板，那么我们就用C方式来直接的分配内存
    }
    /*
     * 这里1D是个代理，目的是为了逐级解决operator[]的问题，2D的operator[]返回一个1D，然后1D的operator[]返回是某一个元素。
     */
    class Array1D {
    public:
        Array1D(T *pd) :data(pd) { }
        // 第二维度的开始位置向后偏移dim2个单位
        T& operator[](int dim2) {
            return *(data + dim2);
        }
    private:
        T* data;
    };

    // 第二维度为1D的长度，那么2D的第一维度表示第几组1D数组的开始位置
    Array1D operator[] (int dim1) {
        return Array1D(data + array1DSize_ * dim1);
    }
    ~Array2D() {
        free(data);
    }

private:
    size_t array1DSize_;
    T* data;
};
int main () {
    Array2D<int> a(2,4);
    std::cout << a[1][3] << std::endl;

}

