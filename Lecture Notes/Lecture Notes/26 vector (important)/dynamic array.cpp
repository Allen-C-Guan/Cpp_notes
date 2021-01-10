# include<iostream>
# include<string>
# include<vector>
using namespace std;

/*
                           **** dynamic array ****
dynamic array与众不同之处在于，array的size动态的，也就是说， 该数据结构，既可以实现常数复杂度的索引，也可以实现list的size自由扩展。

其实现的基本原理为：
   1. 程序会根据初始数据的size，自动分配一段连续的内存空间。
   2. 当空间占满以后，重新开辟一段新的，连续的，更大的，内存空间。
   3. 把当前所有内容，copy到新内存空间，并释放原内存地址。
 
*/


struct Vertex{
    float x, y, z;
    Vertex()
    : x(0), y(0), z(0)
    {
    }
    
    Vertex(float x, float y, float z)
    :x(x), y(y), z(z)
    {
    }

    Vertex(const Vertex& other)
    :x(other.x), y(other.y), z(other.z)
    {
        cout << "copy" << endl;
    }
    
};

ostream& operator << (ostream& stream, const Vertex& vertex){
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}


void function(const vector<Vertex>& vertices) {} // 这里一定要用reference，这样就不用copy array了。const是为了保证array不被改变



void DynamicArrTst(){
    
    //vector的初始化
    //1.空vector
    vector<Vertex> vertices;    // vector <type>  arrayName;
    
    //2.直接赋值法
    vector<Vertex> v1  = {{1,2,4}, {3,54,6}};
    
    //3.拷贝法
    vector<Vertex> v_copy = v1;
    
    //4. iterator 法
    vector <Vertex> v_it (v1.begin()+1, v1.end()-1);
    
    //5.只指定size，使用默认值初始化
    vector <Vertex> v_default (7);
    
    //6.指定size和初始值
    vector <Vertex> v_size_and_val (7, {1,3,43});   // 7是size， 后面是初始值
    
    //7. 2D array的size
    int x_size = 8, y_size = 10, init_val = 50;
    vector<vector<int>> v_2D (x_size, vector<int>(y_size, init_val)); //每个里面都是10的2D矩阵。
    
    
    // function
    // .push_back()     从后面压入array
    vertices.push_back({1,2,3});
    vertices.push_back({4,5,6});
    vertices.push_back({7,8,9});
    
    //.size()           获取size的大小
    cout << vertices.size() << endl;
    
    
    //for(type a: array)的使用方法   和python里面的for in是一样的！！ 不需要index
    //这个功能和python中的for in一样， 1.不需要担心 container是空的，空的for就不执行了，不用检测是否为空 2. 不会超界！
    for(Vertex v: vertices){
        cout << v << endl;
    }
    //这里采用的是copy的方式，因为v其实是在每次循环的时候，都copy过去的。
    //我们之前说过，只要传参不需要变，就一定用reference。
    
    for(const Vertex& v: vertices){
        cout << v << endl;
    }
    
    //可以用index的方式
    for (int i = 0; i < vertices.size() ; i++) {
        cout << vertices[i] << endl;
    }

    
    //.erase()
    //这个函数中，需要获取的变量是iterator， 你传入int是不行的， 所以不能写 erase(3), 而vertice.begin()是一个iterator表示第一个元素。
    vertices.erase(vertices.begin()+1);
       
        
        
    //.clear()
    vertices.clear();
        
    
    //insert
    vertices.insert(vertices.begin(), {4,5,6});
    
    
    //iterator
    /*
     collection <type>:: iterator  it;   初始化
     advance(it, n);  把it移动n个距离
     distance(left, right);  left必须小于right，测量之间的距离
     iter_swap(it1, it2);
     
     */
    
    
    
    
    
    
    /*
                        **** optimization *****
     对于vector而言，主要有两个地方可以进行简单且有效的优化
     1. 用emplace_back(); 来代替 push_back();
     2. 用.reserve(); 来分配内存，从而避免不必要的size扩展。
     
     其原因为：
     1. push_back(); 会首先建立一个instance，而后通过copy instance 的方式来放到vector中。然后再把被建立的instance释放。
     2. size的扩展会导致重新分配内存，而array中的内容就会被复制。
     */
    
    cout << "***** copy test *******" << endl;
    
    
    cout << "***** row test *******" << endl;
    vector <Vertex> v2;
    v2.push_back({1,2,3});
    //这里等效于， Vertex v_temp(1,2,3); v2.push_back(v_temp); //这就是copy了
    v2.push_back({4,5,6});
    v2.push_back({7,8,9});
    
    
    cout << "***** emplace_back test *******" << endl;
    
    vector <Vertex> v3;
    v3.emplace_back(1,2,3);  //这里，我们采用emplace_back()把instance直接放到vector中，不需要先初始化，在复制，在抛弃。但这里仍然有内存满了需要重新分配的问题。
    v3.emplace_back(4,5,6);
    v3.emplace_back(7,8,9);
    
    
    cout << "***** emplace_back + reserve test *******" << endl;
    
    vector <Vertex> v4;
    v4.reserve(3);
    v4.emplace_back(1,2,3);
    v4.emplace_back(4,5,6);
    v4.emplace_back(7,8,9);
    
}
