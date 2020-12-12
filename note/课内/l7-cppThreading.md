# Lecture 7 notes - Cpp Threading

* [Lecture 7 notes - Cpp Threading](#lecture-7-notes---cpp-threading)
  * [Recap: L6](#recap-l6)
  * [C++高级并发：High level concurrency in C++](#c高级并发high-level-concurrency-in-c)
  * [Hello World from C++ thread](#hello-world-from-c-thread)
  * [局部变量类型推断：auto: Local Type Inference](#局部变量类型推断auto-local-type-inference)
  * [Lambda Expression](#lambda-expression)
  * [Lambda语法：C++](#lambda语法c)
  * [lambda共享值：Sharing a value with lambda](#lambda共享值sharing-a-value-with-lambda)
  * [线程&lambda：Threads & Lambdas](#线程lambdathreads--lambdas)
  * [互斥：释放锁-Mutual Exclusion：Unlock](#互斥释放锁-mutual-exclusionunlock)
  * [C++ 互斥：C++ Mutual Exclusion](#c-互斥c-mutual-exclusion)
  * [线程安全的链表C++：Thread Safe Linked List in C++](#线程安全的链表cthread-safe-linked-list-in-c)
  * [C++条件变量：Condition Variables](#c条件变量condition-variables)
  * [C++有限缓冲区：Bounded Buffer in C++](#c有限缓冲区bounded-buffer-in-c)
  * [异步任务：Asynchronous Tasks](#异步任务asynchronous-tasks)
  * [异步启动任务：Launching Tasks with std::async](#异步启动任务launching-tasks-with-stdasync)
  * [Futures std::future](#futures-stdfuture)
    * [Example: Parallel Sum](#example-parallel-sum)
  * [Better Parallel Sum](#better-parallel-sum)
  * [异步任务通信：Communicating with an async task:std::promise](#异步任务通信communicating-with-an-async-taskstdpromise)
  * [使用Promise：Using a Promise](#使用promiseusing-a-promise)
  * [同步：std::promise<void>](#同步stdpromisevoid)
  * [Tasks as First Class Objects](#tasks-as-first-class-objects)
  * [封装任务：Manipulate Tasks with std::packaged_task](#封装任务manipulate-tasks-with-stdpackaged_task)

## Recap: L6

![](/static/2020-11-25-14-21-58.png)
![](/static/2020-11-25-14-26-33.png)

* low level concurrency
  * how to create and wait for a thread using pthreads in C
  * Race conditions - avoid using mutual exclusion which ensure with a mutex/lock
  * Condition Variables - avoid busing waiting for 1 condition to become true
* high level concurrency
  * 区分协作 & 计算。 学习不同抽象级别语言的并发
  * 设计一个数据结构（结构体），类似bounded buffer
    * 内部实现同步机制，保证线程使用安全，Monitors
  * 信号量（计数/二进制）高级，结合了mutex & condition variable & counter

## C++高级并发：High level concurrency in C++

![](/static/2020-11-25-14-29-25.png)

* C++提供低级pthread结构
* 中级thread实现
  * C++ 2011，标准库
* 高级thread结构

## Hello World from C++ thread

![](/static/2020-11-25-14-31-27.png)

* 头文件
  * `#include<thread>`
* 编译指令，指定C++11以上标准
  * `clang++ -std=c++17 -stdlib=libc++ -pthreads -o hello_world hello_world.cpp`
  * c++11/14/17
* `auto` & `lambda`特性

## 局部变量类型推断：auto: Local Type Inference

![](/static/2020-11-25-14-34-58.png)

C++推荐使用`auto`声明变量，自动类型推断

* 编译器推断出声明语句中变量类型
* 便利了长类型名的使用
* `auto v = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9};`
* `for (auto iter = v.begin(); iter != v.end(); iter++) { /*...*/ }`
  * `for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) { /*...*/ }`不使用auto要写全

## Lambda Expression

![](/static/2020-11-25-14-37-37.png)

* 函数指针
  * 将函数作为参数传递
* `int error = pthread_create(&thread, NULL, PrintHelloWorld, NULL);`
  * `PrintHelloWorld`为函数指针

---

使用lambda表达式，简化

* `int main() { auto t = std::thread( [](){ printf("Hello World\n"); } ); t.join(); }`
  * **匿名方法function literal/ anonymous functions**，创建thread时直接定义匿名方法

## Lambda语法：C++

![](/static/2020-11-25-14-43-48.png)

* `[/*captures*/] (/*params*/) {/*body*/}`
  * captures list variables
    * **lambda创建时**，变量从作用域传入
  * params list
    * **lambda调用时（函数）**，参数传入函数
  * body
    * 函数体，lambda调用时执行
* **因为传值，所有传入函数的参数都会拷贝一份**

## lambda共享值：Sharing a value with lambda

![](/static/2020-11-25-14-47-29.png)

```cpp
  int main() {
    auto l = list{};
    l.append_to_list('a');
    l.append_to_list('b');

    //通过指针，在函数体里共享 变量？
    auto t1 = std::thread(      [l_ptr = &l] (){ l_ptr->remove_from_list(1); });
    t1.join();
  }
```

## 线程&lambda：Threads & Lambdas

![](/static/2020-11-25-17-45-56.png)

* lambda在thread中及其有用
* 创建thread
  * `std::thread`对象，传入函数指针或利用lambda写匿名函数
* `pthread`中函数指针参数类型`void*`，后续需要强转

```cpp

  void* remove_second_element_from_list(void* arg) {
    struct list* list = (struct list*)arg; // restore the meaning of the pointer
    // ...
  }
  int main() {
    struct list* list = create_list(create_node('a')); // ...
    pthread_create(&t1, NULL, remove_second_element_from_list, list ); // ...
  }

```

---

lambda保证了函数参数类型？

![](/static/2020-11-25-17-49-24.png)

```cpp

int main() {
    auto l = list{};
    l.append_to_list('a'); // ..
    //l_ptr的类型保证
    auto t1 = std::thread([l_ptr = &l] (){ l_ptr->remove_from_list(1); }); // ...
}
```

## 互斥：释放锁-Mutual Exclusion：Unlock

![](/static/2020-11-25-17-52-30.png)

容易忘记锁&释放锁

## C++ 互斥：C++ Mutual Exclusion

![](/static/2020-11-25-17-53-16.png)

C++避免了忘记释放锁的问题

* C++将锁mutex视为所有权资源
* 应用RAII（(Resource Acquisition Is Initialization)）机制

stack上创建局部变量，锁

* 变量生命周期结束时，锁会自动释放

```cpp
#include <mutex>
std::mutex m; // mutex variable; shared across threads [线程间共享的锁]
void foo() {
    std::unique_lock<std::mutex> lock(m); // acquire the mutex【上锁，所有权，自动释放】
    // ... do some work
} // releases the mutex by calling m.unlock();【自动释放锁】

```

## 线程安全的链表C++：Thread Safe Linked List in C++

![](/static/2020-11-25-18-03-22.png)
![](/static/2020-11-25-18-04-16.png)

## C++条件变量：Condition Variables

![](/static/2020-11-25-18-13-55.png)

避免不停等待busy waiting的，定点唤醒等待机制 - condition variables

```c
// c pthread
pthread_mutex_lock(&m);
while(!cond){
    pthread_cond_wait(&cv, &m);
}
```

```cpp
// c++
//交锁m， 条件队列cv
//线程唤醒时，会检测cond条件是否为true
cv.wait(m, [](){return cond;});
```

![](/static/2020-11-25-18-18-51.png)

要注意这里的 cond 的相反检查。

* 在C语言的pthread中，while检查条件是否为真，可能会重复等待。
* 在C++中，我们反过来写检查，以表达我们等待条件变为真的意思

## C++有限缓冲区：Bounded Buffer in C++

![](/static/2020-11-25-18-23-09.png)

Producer

![](/static/2020-11-25-18-24-34.png)

BoundedBuffer Constructor

![](/static/2020-11-25-18-25-35.png)

* vector 线程安全，自动实现资源管理（初始化，释放）

AddItem

![](/static/2020-11-25-18-33-02.png)

RemoveItem

![](/static/2020-11-25-18-34-59.png)

## 异步任务：Asynchronous Tasks

![](/static/2020-11-25-18-53-59.png)

到目前为止，我们已经明确地创建了线程，并使用了低级的协调方式

* 更高层次的摘要更容易使用，更难出错
* 我们可以不考虑线程，而是考虑应该并发处理的任务。
* 与其说是同步化，不如说我们可以思考这些任务是如何沟通的
* C++提供了一个高级接口来启动一个异步任务：`std::async` ...

## 异步启动任务：Launching Tasks with std::async

![](/static/2020-11-25-19-05-27.png)

## Futures std::future

![](/static/2020-11-25-19-08-47.png)

* `future.get()`获取结果

![](/static/2020-11-25-19-10-43.png)

* 计算任务完成之前都会阻塞

### Example: Parallel Sum

![](/static/2020-11-25-19-12-18.png)
![](/static/2020-11-25-19-14-12.png)

🍊 效率

![](/static/2020-11-25-19-14-51.png)
![](/static/2020-11-25-19-15-12.png)

* 考虑阈值的影响

## Better Parallel Sum

原始的sum并行和创建了太多的线程，

* 管理所有这些线程的时间超过了运行线程所节省的时间。
* 如果我们的（**线程）核心数量较少（比如8个**），我们可以解决这个问题，
  * **只在前几个递归调用中产生线程**

![](/static/2020-11-25-19-18-20.png)

## 异步任务通信：Communicating with an async task:std::promise

![](/static/2020-11-25-19-23-13.png)

* `some_future.get()`
  * 读取通信管道的数据
* `some_promise.set_value(42)`
  * 通信管道尾部写入
* 可以通过promise获取future对象
  * `std::future<int> some_future = some_promise.get_future();`

## 使用Promise：Using a Promise

![](/static/2020-11-25-19-27-37.png)

## 同步：std::promise<void>

![](/static/2020-11-25-19-30-28.png)

## Tasks as First Class Objects

![](/static/2020-11-25-19-31-51.png)

大多数编程语言的目标是将所有类型的值视为第一类，例如，你可以在任何地方使用任何类型的值，

* 例如，将其作为参数传递，将其存储在数据结构中。

问：你所知道的语言的真实性如何？你可以作为参数传递，存储在数据结构中，从函数中返回：整数，字符串，结构/对象，函数？

我们已经看到，在C++中，我们可以把**通信通道（也就是承诺/未来）当作第一类**，但是任务呢？

* 操纵任务是必不可少的，例如，要写一个线程调度器，也许是为一个虚拟机写的

## 封装任务：Manipulate Tasks with std::packaged_task

![](/static/2020-11-25-19-34-52.png)