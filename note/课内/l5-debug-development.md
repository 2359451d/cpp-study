# L5 - Debugging & Development Tools

## Recap: Ownership

![](/static/2020-11-11-19-39-49.png)
![](/static/2020-11-11-23-17-14.png)

C++资源管理（栈中的创建，销毁）由对象，struct data types中的构造&析构函数完成

* constructor - create values
* destructor - when a variable of this type reaches its lifetime's end

C++中，堆分配的内存，创建和销毁，使用`new` & `delete`

* 有时候会忘记，所以引入智能指针的使用,**负责自动释放所指对象**
  * `unique_ptr`
  * `shared_ptr`
  * **C++11标准库还提供`weak_ptr`辅助类**
    * 指向`shared_ptr`所管理的对象
* 智能指针的使用跟指针相同
  * 默认初始化保存一个空指针

## Bugs & Finding Them

![](/static/2020-11-12-02-04-35.png)

* debuggers - 调试器
  * 在一个受控环境中运行一个程序，在那里我们可以调查它的执行情况
* static analysis - 静态分析
  * 不运行程序的情况下，推断其行为
* dynamic analysis - 动态分析
  * 给程序添加instructions，用于检测运行时bug

## Debugger：GDB & LLDB

![](/static/2020-11-12-02-48-03.png)

两种debugger

* DB
* LLDB

🍊 步骤

* 编译时需要包括`-g`参数
  * binary文件中添加调试信息
* 启动调试器模式运行程序
  * `gdb --arg ./program arg1 arg2`
  * `lldb --s ./program arg1 arg2`
* 调试器内部执行`run`命令
  * `(lldb) run`
* 结束调试
  * `quit`

## 段错误：Segmentation Fault

![](/static/2020-11-12-02-55-02.png)

* 最常见的运行时期错误之一
* 由硬件抛出，**访问的内存超过了系统所给这个程序的内存空间**
  * **访问了不可访问的内存**，
    * 这个内存要么是不存在的，要么是受系统保护的

🍊 常见出现segfault的情况

* **解引NULL指针**
* **尝试在只读内存空间上写入**
* **缓冲区溢出**
  * 在分配的缓冲区之外访问内存
* **栈溢出**
  * 通常由没有base case基步的递归引发

## 找出来源：Where segmentation Fault from?

![](/static/2020-11-12-03-00-54.png)

* 找出哪行引发段错误，运行调试器
  * `lldb -- ./program 12345`
  * `(lldb) run`
* 错误出现，调试器会停止执行
  * 使用`bt(backtrace)`命令，找出导致segfault的调用
  * ![](/static/2020-11-12-03-04-05.png)

## 断点&GUI调试：Breakpoints & GUI for debugging

![](/static/2020-11-12-03-05-36.png)

## 静态分析：Static Analysis

![](/static/2020-11-12-03-06-01.png)

* 不运行的情况下找出错误模式
* 每次编译代码时，编译器都会执行一些静态分析，例如类型检查
* 善用`-Wall` & `-Werror`参数
* 一些静态分析开销太大，无法在每个构建中执行，其他静态分析强制执行特定的编码准则
* 可以通过特定参数or工具进行静态分析
  * clang编译器提供的静态分析工具 --- **static analyzer**

`clang --analyze --analyzer-output html program.c`

* 使用参数flag启用静态分析工具，并指定分析report的输出格式

### 静态分析报告：Clang static analyzer report

![](/static/2020-11-12-03-10-37.png)

### 基于AST的静态检查工具：clang-tidy

clang-tidy不仅仅可以做静态检查，还可以做一些修复工作。

![](/static/2020-11-12-03-17-38.png)

Clang-tidy 是一个 linter (这个名字来自于第一个在 c 上执行静态分析的 UNIX 工具)。

* 它像编译器一样被调用，接受与clang相同的参数`--`
  * `clang-tidy - --`
* 可以启用和禁用一系列检查。这里我们**启用可读性检查**:
  * `clang-tidy -checks="readability-*" 6.c -Wall -Werror`
* 建议在 if 语句的分支周围加上大括号，并使用 const
* Clang-tidy 是一个灵活的工具，允许执行编码guidelines
  * 并使源代码现代化。
  * 你可以自定义checks扩展clang-tidy

## 动态分析工具：Dynamic Analysis Tools

![](/static/2020-11-12-03-22-04.png)

* 需要运行程序，只能检测特定输入中的运行时bug
* clang的静态分析工具：**sanitizers**
  * **AddressSanitizer**内存错误检测器
  * **MemorySanitizer**未初始化内存读取的检测器
  * **LeakSanitizer**内存泄漏检测器
  * **UndefinedBehaviorSanitizer**未定义行为检测器
  * **ThreadSanitizer**数据竞争data race探测器

### 内存错误检测工具:AddressSanitizer

![](/static/2020-11-12-03-28-41.png)
![](/static/2020-11-12-03-34-10.png)

* 越界访问
* （堆）释放后使用
* double free

🍊 启用这个工具，clang 将在程序中**插入指令来监视每一个内存访问**

* `clang -fsanitize=address -fno-omit-frame-pointer -O1 -g -Wall -Werror program.c -o program`
  * `-fno-omit-frame-pointer`输出可读调用栈，
  * `-01`启用基本优化
  * **编译过程产生通常的binary file, 可用于执行**
* <font color="red">大规模软件项目(firefox, chromium)中，可找到**hundreds of bugs**</font>
* 降低执行速度（2倍）
* *相似工具valgrind，执行速度降低20-100倍*

### 未初始化内存读取工具: Memory Sanitizer

![](/static/2020-11-12-03-35-56.png)

* 用于检测 读取未初始化内存
* 这个工具正在开发中，目前只能在 linux 上使用

### 内存泄漏检测器：Leak Sanitizer

![](/static/2020-11-12-03-39-40.png)

* 检测内存泄漏
  * 程序结束时还未释放的内存
* 这个工具也在积极开发中，并被标记为实验性的

### 未定义行为检测器：Undefined Behavior

![](/static/2020-11-12-03-51-18.png)
![](/static/2020-11-12-03-55-20.png)

* 什么是未定义行为？
  * 对于某些操作，**c 标准不要求特定的行为**
  * 这些情况通常被认为是 bug，例如**解引空指针**
* **如果有效操作（行为），每次检查指针是否解引代价高**
  * 因为编译器不必确保空指针的特定行为
  * 它可以假设程序员已经确保指针不是空的
* 未定义的行为对于高效代码很重要
  * 但是使得 bug 的检测更加困难，因为不能保证 bug 是否会导致程序崩溃

🍊 未定义行为检测器

* 检测不同类型未定义行为
* integer overflow...