# C++ vector, list, deque

c++（动态）容器包括 “顺序存储结构”：`vector, list, deque`。“关联存储结构”：`set,map, multiset, multimap`



# vector

> (类似普通数组)，
>
> 连续存储结构，每个元素在内存上连续，
>
> * 支持高效随机访问 
> * ==尾==插/删除（高效）
>   * 其他位置插入，删除效率低

**应用**

* 高效随机访问，存取
* 不关心插入，删除

==vector存储自定义类对象时，自定义类需要满足==

* 有无参构造函数（默认or 自定义）
* 有拷贝函数（默认 or 自定义）

# deque

> 连续存储结构，每个元素在内存上连续 【双端队列，功能合并了vector & list】
>
> * 随机访问方便， 支持索引[]， & vector.at()
> * 方便插入 & 删除
> * ==两端==支持push，pop

**缺点**

* 占用内存大

**应用**

* 高效随机访问，存取
* 关心插入&删除

# list

> 非连续存储结构， 双端链表
>
> * 每个元素维护 头尾指针
>   * 支持头尾遍历
>   * `info`
>   * `pre`
>   * `post`
> * 高效插入删除
> * 随机访问效率低

**应用**

* 高效插入删除
* 不关心随机访问，存取



# 常量容器：*const*



`const vector<int> vec(10)`

* vector容器只读，capacity & size无法修改
* 相当于 `const int a[10]`，不能再扩展，元素也只读

`const vector<int>::const_iterator ite`

* 常量迭代器



# iterator

1. `vector` & `deque`的迭代器都支持算术运算，

2. `list`的迭代器只支持 ++/--
3. `vector`迭代器使用完后释放，链表`list`迭代器使用完后还可以复用



