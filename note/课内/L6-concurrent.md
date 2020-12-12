# Lecture 6 Concurrent Programming

并发

* [Lecture 6 Concurrent Programming](#lecture-6-concurrent-programming)
  * [Recap](#recap)
  * [Concurrency](#concurrency)
  * [并发vs并行：Concurrency vs Parallelism](#并发vs并行concurrency-vs-parallelism)
  * [进程-线程：Processes vs Threads](#进程-线程processes-vs-threads)
  * [线程实现：Thread implementations](#线程实现thread-implementations)
  * [POSIX Threads](#posix-threads)
  * [pthread_create](#pthread_create)
  * [pthread_join: wait another threads to terminate](#pthread_join-wait-another-threads-to-terminate)
  * [互斥：Introducing Mutual Exclusion](#互斥introducing-mutual-exclusion)
  * [临界区 & 条件竞争：Critical Region & Race Conditions](#临界区--条件竞争critical-region--race-conditions)
  * [锁保护临界区：Locks Protect Critical Regions](#锁保护临界区locks-protect-critical-regions)
  * [简单锁例子：Simple Lock Example](#简单锁例子simple-lock-example)
  * [有限缓冲区（生产者消费者问题）：Bounded Buffer](#有限缓冲区生产者消费者问题bounded-buffer)
    * [不安全的有限缓冲 & 死锁：Unsafe & DeadLock](#不安全的有限缓冲--死锁unsafe--deadlock)
    * [死锁解决方法-Busy Waiting：Deadlock Solution](#死锁解决方法-busy-waitingdeadlock-solution)
    * [死锁解决方法-Condition Variable](#死锁解决方法-condition-variable)
  * [带条件变量的有限缓冲区：Bounded Buffer with Condition Variables](#带条件变量的有限缓冲区bounded-buffer-with-condition-variables)
  * [Bounded Buffer Monitor例子](#bounded-buffer-monitor例子)
  * [单 vs 多condition队列](#单-vs-多condition队列)
  * [并发编程困难: Concurrent Programming is Hard](#并发编程困难-concurrent-programming-is-hard)
  * [并发设计要点: Some Important Coordination Aspects](#并发设计要点-some-important-coordination-aspects)
  * [协作(同步)抽象级别:Coordination Abstraction Levels](#协作同步抽象级别coordination-abstraction-levels)
    * [不同语言的同步机制选择:Concurrent Coordination Options for languages](#不同语言的同步机制选择concurrent-coordination-options-for-languages)
  * [信号量: Semaphores](#信号量-semaphores)
    * [有限缓冲区-信号量实现: Bounded Buffer - Semaphore Implementation](#有限缓冲区-信号量实现-bounded-buffer---semaphore-implementation)
  * [Concurrency Reflection](#concurrency-reflection)

## Recap

![](/static/2020-11-17-17-45-54.png)

* 管理资源&内存 - 所有权ownership
  * 在 c + + 中所有权是通过将**资源管理绑定到堆栈变量的生存期**来实现的
* 智能指针&容器使内存管理更容易
  * 避免内存泄漏

## Concurrency

什么是并发性?

![](/static/2020-11-17-20-25-10.png)

* 同时运行，多线程
* 不同方法实现并发
  * 并发物之间**共享内存shared memory**资源，读写，通信（可见性）
  * **消息传递message passing**（比共享内存并发简单）通常被认为是一种更健壮的并发编程形式。消息传递系统的例子有在 Erlang 实现的 actor 模型或者Go中的 csp-style通信（分布并行式课里涉及）

## 并发vs并行：Concurrency vs Parallelism

![](/static/2020-11-17-20-39-36.png)

区分并发&并行

* 并发是编程术语，使用**threads技术异步处理多事件**，or**用于将程序结构化为交互代理的集**
* 并行，**使程序执行更快**
  * 不需要threads实现并行，因为**没有需要响应的异步事件**
  * 并行-使在多**处理器上并行运行一个并发程序**成为可能，但这只是一个额外的好处
* <font color="red>编程中，并发是独立执行的进程组合，并行是真正同时执行计算的能力（待执行程序可能非独立）</font>
  * Concurrency is about dealing with lots of things at onece【一次性处理（看起来像同时）相关计算】
  * Parallelism is about doing lots of things at once【同时计算，可独立，可不独立】

🍊 如果只是追求程序运行速度，应该考虑并行

* 并发需要处理，不然很难运行正确

## 进程-线程：Processes vs Threads

![](/static/2020-11-17-20-48-58.png)

* 进程
  * 每个执行的C程序
  * 多进程可同时执行
  * **每个进程内存空间独立**
* 线程
  * 执行线程是一个独立的程序指令序列（子程序）
  * 多线程可同时执行
  * 一个进程可以有多个线程，**共享同一进程内存空间**
* 使用threads实现并发

## 线程实现：Thread implementations

![](/static/2020-11-17-20-57-28.png)

* C `pthread`库 & C++ threads

不同语言的threads实现类似，周期为

* 创建thread
  * 开始执行任务
  * 参数
  * 标识符
* 等待其他thread结束
* 终断其他thread
* thread结束
* thread间通信（可见性）
  * 共享变量状态修改

## POSIX Threads

![](/static/2020-11-20-19-20-46.png)

c中最常用的并发实现库

* `#include<pthread.h>`
* 编译参数`-lpthread`
  * `clang -Wall -Werror program.c -lpthread -o program`

## pthread_create

`int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void*),void *arg);`

* `thread`
  * thread identifier
  * `pthread_t *`指针
* `attr`
  * 线程属性，调度策略or栈大小
  * **传`NULL`，默认属性**
* `(*start_routine)(void*)`
  * 函数指针
  * 参数`void*`
  * 返回`void*
* `*arg`
  * 传入函数指针`start_routine`

🍊 返回

* `0`
  * 线程成功创建or
* 非`0`
  * 错误码

## pthread_join: wait another threads to terminate

`int pthread_join(pthread_t thread, void **value_ptr);`

* 等待其他线程结束
* `thread`
  * 线程标识符
* `void** value_ptr`
  * 二级指针指向void*的内存地址

🍊 传给`pthread_create`的`start_routine`(函数指针)返回值，会在`value_ptr`中拷贝

* 返回`0`，成功
* 或其他非`0`，错误码

🍊 例子

```c
int* return_value; //接收返回值
int error = pthread_join(thread, (void**)&return_value); //error为等待结果，return_value为thread执行任务结果
assert(error == 0);
if (return_value) { printf("return_value: \n", *return_value); }
// maybe: free(return_value);
```

## 互斥：Introducing Mutual Exclusion

![](/static/2020-11-22-18-11-34.png)
![](/static/2020-11-22-18-14-53.png)

## 临界区 & 条件竞争：Critical Region & Race Conditions

![](/static/2020-11-22-18-37-19.png)

* 临界区
  * 用于更新共享变量/数据结构，如`count`
* **必须保护临界区，使得并发线程不会互相干扰**
* **互斥**
  * 意味着每次只有1个线程操作临界区
* **条件竞争**
  * 当程序执行结果依赖于其他的线程时，出现

## 锁保护临界区：Locks Protect Critical Regions

![](/static/2020-11-22-19-18-32.png)

* 每个临界区关联一个lock，mutex（互斥锁）
* 操作前必须获得lock
* 离开临界区，释放lock
* “获取lock”语义
  * 如果其他线程拥有锁，请求线程**阻塞**，直到其他线程释放锁
  * 如果锁未被持有，请求线程被赋予锁（或需要抢占）
* 释放锁时，如有阻塞线程在等待锁，会立即被赋予所有权，并且开始执行

## 简单锁例子：Simple Lock Example

![](/static/2020-11-22-19-21-42.png)

## 有限缓冲区（生产者消费者问题）：Bounded Buffer

![](/static/2020-11-22-19-27-47.png)

* 有限缓冲区
  * 固定大小的缓冲
* 生产者
  * 生产，插入元素
* 消费者
  * 消费，取出元素

🍊 需要保证

* buffer满时
  * 生产者等待
* buffer空时
  * 消费者等待
* 其他情况，恢复工作

### 不安全的有限缓冲 & 死锁：Unsafe & DeadLock

![](/static/2020-11-22-19-31-42.png)

* 不能决定生产者消费者的交互顺序

![](/static/2020-11-22-19-44-08.png)
![](/static/2020-11-22-19-47-25.png)

* 不恰当的锁位置，造成**死锁**
  * 假设生产者二次抢到锁，缓冲区满了，不释放锁直接等消费者，消费者拿不到锁也会阻塞
  * 反之，消费者卡在count==0，不释放锁，等待生产者生产，但是生产者无法获取锁进行生成，两个线程都阻塞

### 死锁解决方法-Busy Waiting：Deadlock Solution

![](/static/2020-11-22-19-57-00.png)

* 通过某些条件，强制thread等待&释放锁
  * busy waiting解决死锁问题
* **浪费CPU周期？&重量锁**
  * 因为有thread可能**需要不停while loop拿锁释放锁（不属于有效工作）**

🍊 Busy Waiting方式 - tea maker例子

![](/static/2020-11-22-20-03-41.png)

### 死锁解决方法-Condition Variable

死锁解决方式2 - 条件变量

![](/static/2020-11-22-20-04-54.png)

* Busy Waiting方式浪费CPU执行周期&费力
  * 因为有thread可能**需要不停while loop拿锁释放锁（不属于有效工作）**
* 更好的解决方式<font color="red">阻塞获取锁的线程，【需要时再唤醒，取锁】</font>
  * 通过**CONDITION变量`cv`实现**

`pthread_cond_wait(&cv, &m)`

* 调用时需要包括一个lock/mutex `&m`
  * **类似将当前线程t移入condition队列`&cv`，并释放lock `&m`**

`pthread_cond_signal(&cv)`

* 类似，java唤醒condition队列`&cv`中的一个节点（1.将其移入AQS队列（唤醒），并选一个ready线程执行（获得锁））
* **唤醒&赋予`cv`队列中一个阻塞的线程`mutex`的所有权**

![](/static/2020-11-22-20-46-56.png)

* 条件变量类似于硬件信号/中断

---

🍊 Condition Variable方式 - tea maker例子

![](/static/2020-11-22-20-57-40.png)

## 带条件变量的有限缓冲区：Bounded Buffer with Condition Variables

![](/static/2020-11-22-21-27-02.png)

* 需要两个条件队列（变量）控制 - 以便可以分组控制唤醒的线程
  * 生产者condition
    * add
    * 阻塞直到buffer为空
  * 消费者condition
    * 阻塞直到buffer不为空
* 有限缓冲区是一个**monitor**
  * 为线程**提供**共享资源（buffer）的**安全访问**的类
  * 类中所有public函数，`addItem`，`removeItem`都支持互斥
* java，重量级同步机制`synchronised` - monitor

## Bounded Buffer Monitor例子

同步机制，有限缓冲区封装成struct

```c
struct BoundedBuffer {
  int start; int end; int size;
  int* buffer;
  pthread_mutex_t m;//互斥锁
  pthread_cond_t add; //condition队列1 - 生产者队列
  pthread_cond_t remove; //condition队列2 - 消费者队列
};
typedef struct BoundedBuffer BoundedBuffer;

// 生产者
void * producer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;
  for (int i = 0; i < 10; i++) {
     int item = randInt();
     printf("produced item %d\n", item);
     addItem(bb, item);//生产任务
     usleep(randInt());
  }  
  return NULL;
}

// 生产fun
void addItem(BoundedBuffer * bb, int item) {
  If (!bb) return;
  pthread_mutex_lock(&bb->m); //获取锁
  while (bb->start == bb->end) { // buffer is full
     printf("== Buffer is full ==\n");
     pthread_cond_wait(&bb->add, &bb->m); // 阻塞等待,移入add生产者队列,释放锁m
  }
  // buffer is no longer full
  bb->buffer[bb->start] = item;
  bb->start = (bb->start + 1) % bb->size; // move start one forward,移动当前start指针,数值循环
  pthread_mutex_unlock(&bb->m);
  pthread_cond_signal(&bb->remove); //唤醒remove消费者队列 的一个消费者线程
}

// 消费者
void * consumer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;
  for (int i = 0; i < 10; i++) {
    int item = removeItem(bb);
    printf(" consumed item %d\n", item);
    usleep(randInt());
  }
  return NULL;
}

// 消费fun
int removeItem(BoundedBuffer * bb) {
  if (!bb) assert(0);
  pthread_mutex_lock(&bb->m);
  while ( ((bb->end + 1) % bb->size) == bb->start ) { // buffer is  empty
    printf("== Buffer is empty ==\n");
    pthread_cond_wait(&bb->remove, &bb->m);
  }
  // buffer is no longer empty
  bb->end = (bb->end + 1) % bb->size; // move end one forward
  int item = bb->buffer[bb->end];
  pthread_mutex_unlock(&bb->m);
  pthread_cond_signal(&bb->add);
  return item;
}

int main() {
  pthread_t t1;
  pthread_t t2;
  int err;
  BoundedBuffer * bb = createBoundedBuffer(4);
  //创建线程
  err = pthread_create(&t1, NULL, consumer, bb); assert(err == 0);
  err = pthread_create(&t2, NULL, producer, bb); assert(err == 0);
  //等待线程执行结果
  err = pthread_join(t1, NULL); assert(err == 0);
  err = pthread_join(t2, NULL); assert(err == 0);
}

```

## 单 vs 多condition队列

![](/static/2020-11-22-21-42-20.png)

* 单个condition队列,即不加区分唤醒一个队列中所有阻塞线程
  * 可能造成CPU周期浪费
  * 或多个生产者消费者,buffer满之后又唤醒多个生产者

## 并发编程困难: Concurrent Programming is Hard

![](/static/2020-11-22-21-50-14.png)

* 并发提出了顺序计算的所有挑战: 即计算什么。一个正确和有效的算法，使用适当的数据结构，必须构建
* 并发程序还必须指定正确有效的协调策略: 即线程应该如何协作

## 并发设计要点: Some Important Coordination Aspects

![](/static/2020-11-22-21-51-57.png)

* partitioning - 分区
  * 决定计算的哪些部分可以分开执行
  * 例如,执行任务的线程,渲染帧的线程
* Placement - 位置
  * 决定线程执行的位置
  * 例如,将线程分配到最少繁忙的核心
* Communication - 通信(可见性)
  * 什么时候通信,传递什么data
  * 如,film渲染线程具有2个帧(正处理的, 即将被处理的)
* Synchronisation - 同步性
  * 保证线程可以无干扰情况下协作
  * 如,如果代表两个玩家的线程竞争获得一个资源，那么只有一个成功

## 协作(同步)抽象级别:Coordination Abstraction Levels

![](/static/2020-11-22-21-56-40.png)

* 计算可以用不同抽象级别的语言来编写
  * 低级
    * 汇编
    * C
  * 中级
    * java
    * python
  * 高级
    * SQL, haskell
    * prolog
* 协作也可以用不同抽象级别的语言编写
  * 低级
    * locks
    * semaphores信号量
  * 中级
    * GO
    * Monitors(JAVA synchronized机制)
    * c++ Threads Erlang
  * 高级
    * OpenMP

### 不同语言的同步机制选择:Concurrent Coordination Options for languages

![](/static/2020-11-22-21-59-50.png)

* java
  * POSIX, synchronized底层(monitor)
  * Atomic, JUC
  * Executors框架,线程池

## 信号量: Semaphores

**信号量是用来调度线程，可以控制顺序**。锁大多是直接靠抢占，抢占策略决定

* 也可以通过信号量为`1`,实现互斥锁效果.但不是其本身设计目的

---

![](/static/2020-11-22-22-05-31.png)

* 信号量,作为int计数器
* 提供2个操作
  * `wait` - counter--,如计数器`<0`时,阻塞
  * `signal` - counter++, 唤醒waiting线程

🍊 通过信号量

* 可以知道使用了多少个资源(信号量counter数)
* 无资源(`<0`)时阻塞

---

![](/static/2020-11-22-22-52-53.png)

* 二进制信号量(count 1)
  * 结合 mutex互斥锁 & condition变量
  * 允许单个线程操作临界区(wait & signal)

🍊 可以使用,一对信号量,确保正确使用一个unsafe的优先缓冲区

### 有限缓冲区-信号量实现: Bounded Buffer - Semaphore Implementation

![](/static/2020-11-22-22-55-29.png)
![](/static/2020-11-22-23-06-14.png)

```c
struct BoundedBuffer {
  int start;
  int end;
  int size;
  int* buffer;
};
typedef struct BoundedBuffer BoundedBuffer;

sem_t fillCount; // data in the buffer, 信号量 - buffer中元素数量
sem_t emptyCount; // free space in the buffer, 信号量 - buffer中空位数量

// 生产者
void * producer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;

  for (int i = 0; i < 10; i++) {
    sem_wait(emptyCount);// 信号量-空位数, emptycount--
    int item = randInt();
    printf("produced item %d\n", item);
    addItem(bb, item);
    sem_signal(fillCount); // 信号量-元素数, fillcount++
    usleep(randInt());
  }
  return NULL;
};

int removeItem(BoundedBuffer * bb) {
  if (!bb) assert(0);
  pthread_mutex_lock(&bb->m);
  
  sem_wait(emptyCount);
  // buffer is no longer empty
  bb->end = (bb->end + 1) % bb->size; // move end one forward
  int item = bb->buffer[bb->end];
  sem_signal(fillCount);

  return item;
}

// 消费
void * consumer(void * arg) {
  BoundedBuffer * bb = (BoundedBuffer*)arg;
  for (int i = 0; i < 10; i++) {
    sem_wait(fillCount);//元素数--
    int item = removeItem(bb);
    printf(" consumed item %d\n", item);
    sem_signal(emptyCount);//空位数++
    usleep(randInt());
  }
  return NULL;
}

int main() {
  pthread_t t1; pthread_t t2; int err;
  BoundedBuffer * bb = createBoundedBuffer(4);
  fillCount = sem_create(0, 4); // no data in the buffer yet
  emptyCount = sem_create(4, 4); // all spaces in the buffer are free
  err = pthread_create(&t1, NULL, consumer, bb); assert(err == 0);
  err = pthread_create(&t2, NULL, producer, bb); assert(err == 0);
  err = pthread_join(t1, NULL); assert(err == 0);}


```

## Concurrency Reflection

![](/static/2020-11-22-23-18-10.png)