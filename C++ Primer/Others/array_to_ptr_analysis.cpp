// 数组不会退化为指针
void ArrWithRef(int(&arr)[10])
{
    std::cout << sizeof(arr) / sizeof(arr[0])<< std::endl;
}
// 数组会退化为指针
void ArrWithoutRef(int arr[])
{
    std::cout << sizeof(arr) / sizeof(arr[0])<< std::endl;
}
// 这个和上面的是等价的！！！
void ArrWithPtr(int *arr)
{
    std::cout << sizeof(arr) / sizeof(arr[0])<< std::endl;
}

class Foo {
public:
    using Arr = int(&)[10];
    // 数组指针的返回
    int* getArrPtr()
    {
        return arr;
    }
    // 数组引用的返回
    auto getArrRef() ->int(&)[10]
    {
        return arr;
    }
    // 使用using返回数组引用
    Arr getArrRef2() {
        return arr;
    }

private:
    int arr[10] = {1,2,3,4};
};
void testReturnArr() {
    int a = 2;
    Foo f;
    auto arr = f.getArrPtr();
    std::cout << arr[1] << std::endl;
    auto arrRef = f.getArrRef();
    std::cout << arrRef[2] << std::endl;
    arrRef[2] = 10;
    std::cout << arrRef[2] << std::endl;

    Foo::Arr arr2 = f.getArrRef2();
    std::cout << arrRef[2] << std::endl;
}


int main() {
    int arr[10];
    ArrWithRef(arr);
    ArrWithoutRef(arr);
    ArrWithPtr(arr);
}
