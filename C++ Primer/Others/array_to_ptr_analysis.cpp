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
int main() {
    int arr[10];
    ArrWithRef(arr);
    ArrWithoutRef(arr);
    ArrWithPtr(arr);
}
