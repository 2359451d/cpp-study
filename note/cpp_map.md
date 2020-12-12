# C++ Map & Unordered_Map

`#include<map>` & `#include<unordered_map>`



# Map

> Map内部实现红黑树（非严格平衡二叉搜索树），自动排序
>
> * Map内所有元素有序（遍历，得到有序序列）
> * Map所有操作相当于对红黑树进行的操作

**优点**

* 有序
* 红黑树操作多能在`O(logn)`时间下实现

**缺点**

* 空间占用高，每个节点都需要额外保存父节点/孩子节点/红黑性质

**应用**

* 适用有序场景





# Unordered_map

> 内部实现哈希表，查找高效（O(1)）, 元素无序

**优点**

* 哈希表实现，查找效率高

**缺点**

* 建表时间慢

**应用**

* 适用查找问题



# Map常用操作

```c++
#include <map>
#include <unordered_map>
using namespace std;

int main(){
    //initialise (C++11 FEATURE )
    unordered_map<int, string> map1 = {{5, "a"}, {6, "b"}};
    //insert
    map1[2] = "c"; // insert pair {2,"c"}, if 2 exists, update the value
    map1.insert(pair<int, string>(3, "d"));
    
    //iterator utilisation
    auto iter = map1.begin(); // automatic type infer
    while(iter!=map1.end()){
        cout << iter->first << "," << iter->second << endl;
        ++iter;
    }
    
    auto iter = map1.find(2); // return the iterator pointer at 2 pos
    if (iter!=map1.end())
        cout <<endl<<iter->first<<","<<iter->second<<endl;
    
    system("pause");
    return 0;
}
```

