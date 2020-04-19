# include<iostream>
# include<string>
# include<vector>
using namespace std;


struct Vertex{
    float x, y, z;
};

ostream& operator << (ostream& stream, Vertex& vertex){
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}


void function(const vector<Vertex>& vertices) {} // 这里一定要用reference，这样就不用copy array了。const是为了保证array不被改变


/*
 vector的功能是：一个可以自动增长的array。
 实现的原理： 一旦到达最初分配的memo的space，就会自动新开辟一个更大的地方，把所有东西复制过去，然后删除原来的地方
 */
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
    
    for(Vertex& v: vertices){
        cout << v << endl;
        

    //.erase()
    //这个函数中，需要获取的变量是iterator， 你传入int是不行的， 所以不能写 erase(3), 而vertice.begin()是一个iterator表示第一个元素。
    vertices.erase(vertices.begin()+1);
       
        
        
    //.clear()
    vertices.clear();
        
    }
    //insert
    vertices.insert(vertices.begin(), {4,5,6});
    
    
    //iterator
    /*
     collection <type>:: iterator  it;   初始化
     advance(it, n);  把it移动n个距离
     distance(left, right);  left必须小于right，测量之间的距离
     iter_swap(it1, it2);
     
     */
    
    
    
    
    
}
