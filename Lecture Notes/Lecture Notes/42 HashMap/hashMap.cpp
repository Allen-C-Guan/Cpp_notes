#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
using namespace std;
/*
 std::unordered_map<type_key, type_val> map_name = {{a,b}, {c,d}....};
 map里的key和val之间是利用pair存储的， first = key, second = val
 value_type :std::pair<const Key, val>
 
 */
void hashMapTst(){
    // map的初始化
    unordered_map<string, int> dic = {{"Allen", 100}, {"cecilia", 40}};
    
    //通过key访问val
    //可是这里如果key不存在的话，就返回type的默认值，或者不知道是啥了，如果需要保险需要用find过滤一下
    cout << dic["Allen"] << endl;
    
    
    //添加key-val对儿
    //1.直接添加
    dic["Guan"] = 10000;  //和python一样，就直接赋值就行了
    //如果已经存在了就更改。
    dic["Guan"] = 100;
    /*2. insert({key,value});
     
    这个函数可以自动选择是否插入，如果已经有相同的key，就不插入了，并返回已经存在的pair
    如果没有相同的key，就插入当前pair,
    返回的是一个pair pair的第一个是被插入的元素，或者阻止其插入的元素的it。第二值表示是否成功插入
     */
    auto insert_res = dic.insert({"shuo", 8888});
    cout << insert_res.first -> first << endl;
    cout << insert_res.first -> second << endl;
    
    
    //擦除
    //1. 用key擦除
    dic.erase("Guan");
    
    //2. 用it擦除
    dic.erase(dic.begin());
    
    //3.擦除一个范围 dic.erase( it.begin(), it.end())
    
    
    
    /*find
     find(const key& key)
     如果存在返回的是it，如果不存在，返回的是end();
    */
    
    auto is_exist = dic.find("Allen");
    if (is_exist != dic.end())
        cout << (*is_exist).first << ": "<< (*is_exist).second << endl;
    
    
    //empty
    cout << boolalpha << dic.empty() << endl;
    
    //clear
    dic.clear();
    
    
    /*
     map
     map和unsorted_map 的区别在于有序，但是随之而来的每次插入和删除的代价就是log级别的
     */
    
    map<int, string, greater<int>> hashMap;
    hashMap[100] = "Allen";
    hashMap[90] = "shuo";
    hashMap[80] = "chen";
    
    //自定义排序
    /*
     自定排序的方法竟然是写一个struct_compare，struct中包括一个const 的对 ()的overloading wtf？？？
     */
    struct Vector{
        float x , y;
    };
    struct cmpMap{
        bool operator() (const Vector& v1, const Vector& v2) const { //最后这个const必须有
            return v1.y < v2.y;
        }
    };
    
    map<Vector, int, cmpMap> custom_map;
    custom_map.insert({{1,9}, 9});
    custom_map.insert({{2,8}, 8});
    custom_map.insert({{3,7}, 7});
    custom_map.insert({{4,6}, 6});
    
    
    
    
}
