# c supplemetary content

自用补充

* [c supplemetary content](#c-supplemetary-content)
  * [存储类](#存储类)
    * [auto](#auto)
    * [register](#register)
    * [static](#static)
    * [extern](#extern)
  * [enumerative](#enumerative)
    * [枚举变量定义](#枚举变量定义)
    * [遍历](#遍历)
  * [函数指针](#函数指针)
    * [回调函数](#回调函数)
  * [struct](#struct)
    * [struct pointer](#struct-pointer)
  * [位域](#位域)
    * [定义](#定义)
    * [无名位域](#无名位域)
    * [为什么使用位域](#为什么使用位域)
  * [共用体：union](#共用体union)
  * [typedef](#typedef)
    * [typedef vs #define](#typedef-vs-define)
  * [输入 & 输出](#输入--输出)
    * [getchar() & putchar()](#getchar--putchar)
    * [gets() & puts()](#gets--puts)
    * [scanf & printf](#scanf--printf)
  * [File I/O](#file-io)
    * [二进制I/O](#二进制io)
  * [C预处理器](#c预处理器)
    * [预定义宏](#预定义宏)
    * [预处理器运算符](#预处理器运算符)
      * [宏延续运算符: \](#宏延续运算符-)
      * [字符串常量化运算符:](#字符串常量化运算符)
      * [标记粘贴运算符:](#标记粘贴运算符)
      * [defined() 运算符](#defined-运算符)
    * [参数化宏](#参数化宏)
  * [头文件](#头文件)
    * [只引用一次头文件](#只引用一次头文件)
    * [有条件引用](#有条件引用)
  * [强制类型转换](#强制类型转换)
    * [整数提升](#整数提升)
    * [常用算术转换](#常用算术转换)
  * [c错误处理](#c错误处理)
    * [程序退出状态](#程序退出状态)
  * [可变参数](#可变参数)
  * [动态内存管理](#动态内存管理)
    * [动态分配内存](#动态分配内存)
    * [重新调整内存大小 & 释放内存](#重新调整内存大小--释放内存)
  * [命令行参数](#命令行参数)

## 存储类

定义c程序中**变量/函数**

* 可见性
* 生命周期

可用存储类

* `auto`
* `register`
* `static`
* `extern`

### auto

`auto`存储类

* 所有局部变量默认存储类

```c
{
    //auto 只能用于函数内，修饰局部变量
    int mount;
    auto int month;
}
```

### register

`resiter`存储类

* 用于定义存储在**寄存器中（而不是ram）的局部变量**
* <font color="red">定义的变量最大大小匹配寄存器大小，不能对其应用`&`运算符</font>

```c
{
    // 用于快速访问的变量，如计数器
    // register并不意味着变量一定存储在寄存器，取决于硬件&实现的限制
    register int miles;
}
```

### static

`static`存储类

* 指示，编译器在程序的生命周期内**保持局部变量的存在，而不需要每次进行创建&销毁**
* **可应用于全局变量**
  * 使其作用域限制在声明他的文件内

```c
#include<stdio.h>

void func1(void);//prototype

static int count=10;//全局变量

int main(){
    while(count--){
        func1();
    }
    return 0;
}

void func1(void){
    static int thingy=5;
    thingy++；
    printf("thingy为%d, count为%d", thingy, count);
}
```

### extern

`extern`存储类

* 提供一个全局变量的引用，**在另一个文件中声明一个全局变量or函数**
  * 对所有程序文件可见
  * **通常用于有两个or多个文件共享相同全局变量or函数时**
* <font color="red">对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置</font>
* <font color="blue">当有多个文件，且定义了一个可以在其他文件中使用的全局变量or函数时</font>
  * 可以在其他文件中使用`extern`来得到已经定义的变量or函数的引用

```c
// main.c
#include<stdio.h>

int count;
extern void write_extern();//引用

int main(){
    count=5;
    write_extern();
}
```

```c
// support.c
#include<stdio.h>

extern int count;//引用全局变量

void write_extern(void)
{
    printf("count is %d", count);
}
```

编译 `gcc main.c support.c -o a.out`

## enumerative

枚举

* `enum type_name{element1, element2,...}`
* c中被当作`int`或`unsigned int`处理

```c
// 不使用枚举,不整洁，代码量多
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define SUN 7

// 改进, 第一个枚举成员默认值为0，可调
enum DAY
{
    MON=1,TUE,WED,THU,FRI,SAT,SUN
};

enum season{
    // spring=0, summer=3, autumn=4,...
    spring, summer=3, autumn, winter
};
```

### 枚举变量定义

```c
// 1. 定义枚举类型，在定义变量
enum DAY{
    MON=1, TUE,WED,THU,FRI,SAT, SUN
}

enum DAY day;

// 2.同时定义
enum DAY{
    MON=1, TUE,WED,THU,FRI,SAT, SUN
} day;

// 3.省略枚举名称(无名枚举)，直接定义枚举变量
enum{
    MON=1, TUE,WED,THU,FRI,SAT, SUN
} day;
```

### 遍历

不连续的枚举类型无法遍历
![](/static/2020-10-23-22-21-05.png)

```c
enum{
    MON=1, TUE,WED,THU,FRI,SAT, SUN
} day;

int main(){
    for(day=MON; day<=SUN; day++){
        print("enum: %d", day);
    }
}
```

## 函数指针

函数指针

* 指向函数
* **可以像一般函数一样，用于调用函数，传递参数**
* `typedef int (*fun_ptr)(int,int);`生成一个指向同样参数，返回值的函数指针类型

```c
int max(int x,int y){
    return x> y?x :y;
}

int main(void){
    int (*p)(int,int) = & max;// &可省略，函数max指针
    int a,b,c,d;
    scanf("%d %d %d", &a,&b,&c);

    // 调用，等同于 d = max(max(a,b), c)
    d = p(p(a,b), c);
    return 0;
}
```

### 回调函数

函数指针作为函数参数

* 回调函数 - 通过函数指针调用的函数
  * **别的函数执行时，通过函数指针，调用你实现的函数**

```c
//回调函数
void populate_array(int* array, size_t arraySize, int(*getValue)(void))
{
    for (size_t i=0; i<arraySize; i++>)
    {
        array[i] = getValue();//函数指针调用函数
    }
}

int getNextRandomValue(void)
{
    return rand();
}

int main(){
    int array[10];
    populate_array(array, 10, getNextRandomValue);// &函数名，&可省
    return 0;
}
```

## struct

互相包含的结构体
![](/static/2020-10-23-23-50-27.png)

### struct pointer

![](/static/2020-10-23-23-51-46.png)

## 位域

> **有些信息存储时，并不需要占用一个完整的字节，而只需占几个或一个二进制位**
>
> 例如在存放一个开关量时，只有 0 和 1 两种状态，用 1 位二进位即可
>
> 为了节省存储空间，并使处理简便，C 语言又提供了一种数据结构，称为"位域"或"位段"。

* "位域"
  * 把一个字节中的二进位划分为几个不同的区域，并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作
  * 这样就可以把几个不同的对象用一个字节的二进制位域来表示
* 实例
  * 用 1 位二进位存放一个开关量时，只有 0 和 1 两种状态。
  * 读取外部文件格式——可以读取非标准的文件格式。例如：9 位的整数
* **位域在本质上就是一种结构体类型，不过其成员是按二进位分配的。**

### 定义

```c
struct 位域结构名{
  // 位域列表: type bit_field_name: length
};
```

🍊 例子

```c
struct bs{
    //共占2B
    int a:8; // 位域a占8bit
    int b:2; // 位域b占2bit
    int c:6;
}data;
```

### 无名位域

![](/static/2020-10-24-00-00-49.png)

### 为什么使用位域

![](/static/2020-10-24-00-17-40.png)

## 共用体：union

共用体

* **允许在相同内存位置存储不同数据类型**
* **支持多成员的共同体**

```c
union [union tag] //tag可选
{
    member definition;
    member definition;
    ...
    member definition;
}[one or more union variables];//共同体变量可选
```

![](/static/2020-10-24-00-14-44.png)

```c
// Data共同体类型的变量(data),可以存储: 1个整数,1个浮点数,1个字符串
// Data占20B(最大)
union Data{
    int i;
    float f;
    char str[20];//20B
} data;
```

## typedef

`typedef`

* 用于为类型取新名字

```c
typedef unsigned char BYTE;

BYTE b1,b2;// BYTE可作为 unsigned char的缩写

typedef struct Books{
    char title[50];
} Book; // Book可作为 struct Books结构体类型的缩写

Book book;
book.title;
```

### typedef vs #define

区别

* `typedef`
  * 用于为**类型定义符号名称**
  * **由编译器执行解释**
* `#define`
  * 可为**类型/数值定义别名**
    * 如`#defin one 1`
  * **由预处理器处理**

![](/static/2020-10-24-00-24-03.png)

## 输入 & 输出

标准输入

* 文件指针`stdin`
* 键盘

标准输出

* 文件指针`stdout`
* 屏幕

标准错误

* 文件指针`stderr`
* 屏幕

### getchar() & putchar()

![](/static/2020-10-24-00-36-14.png)

`int getchar(void)`

* 读取char,返回为int
* 可循环读取多个char

`int putchar(int c)`

* 按char输出到屏幕,返回相同字符
* 可以循环输出多个char

### gets() & puts()

![](/static/2020-10-24-00-39-46.png)

`char* gets(char* s)`

* 从`stdin`读取**一行**,到`s`所指缓冲区
  * **直到终止符 or `EOF`**

`ins puts(const char *s)`

* 把s和其`\n`写入`stdout`

### scanf & printf

![](/static/2020-10-24-00-41-27.png)

## File I/O

打开文件

* `FILE *fopen( const char * filename, const char * mode );`
  * `filename`字符串
  * `mode`可为
    * ![1](/static/2020-10-24-00-55-06.png)

关闭文件

* `int fclose(FILE *fp);`
  * `0` - 成功关闭
  * `EOF` - 关闭异常
* 实质: 清空缓冲区中数据,关闭文件,释放内存

写入文件

* `int fputc(int c,FILE* fp)` 单字符
  * `fputc()`把参数c的字符值写入到fp所指向的输出流(文件)
  * 成功 - 返回写入字符
  * 失败 - `EOF`
* `int fputs(const char *s, FILE* fp);` 字符串(多字符缓冲)
  * 把一个以 null 结尾的**字符串写入到流**中
  * 成功 - 返回非负int
  * 失败 - `EOF`
* `int fprintf(FILE *fp,const char *format, ...)` 字符串输出至文件输出流

读取文件

* `int fgetc(FILE* fp)` 单字符文件输入流
  * 成功 - 返回所读字符
  * 失败 - `EOF`
* `char* fgets(char* buf, int n, FILE *fp)`多字符(字符串)文件缓冲输入流
  * 函数 fgets() 从 fp 所指向的输入流中读取 n - 1 个字符
  * **读取的字符串复制到缓冲区 `buf`**，并在最后追加一个 null 字符来终止字符串
  * **遇到`\n`或`EOF`结束**
* `int fscanf(FILE *fp, const char *format, ...)`
  * 从文件中读取字符串, 多字符文件缓冲输入流(文件->内存)
  * 在遇到**第一个空格和换行符结束**

🍊 例子

```c
int main()
{
    //写
    FILE* fp = NULL;
    fp = fopen("/tmp/test.txt", "w+");
    fprintf(fp, "Testing for fprintf...\n");
    fputs("hahahah", fp);
    fclose(fp);

    // 读
    FILE* fp = NULL;
    char buff[255];
    fp = fopen("...", "r");
    fgetc(fp);
    fgets(buff, 255, fp);
    fscanf(fp, "%s", buff);
}
```

### 二进制I/O

![](/static/2020-10-24-01-15-40.png)

## C预处理器

文本替换工具

![](/static/2020-10-24-15-43-40.png)

* 在实际编译之前完成所需预处理
* C preprocessor - CPP
* 所有预处理命令,以`#`开头

🍊 例子

```c
// 告诉 CPP 把所有的 MAX_ARRAY_LENGTH 替换为 20。使用 #define 定义常量来增强可读性
#defin MAX_ARRAY_LENGTH 20
```

```c
// 这个指令告诉 CPP 取消已定义的 FILE_SIZE，并定义它为 42
#undef  FILE_SIZE
#define FILE_SIZE 42
```

```c
// 这个指令告诉 CPP 只有当 MESSAGE 未定义时，才定义 MESSAGE
#ifndef MESSAGE
   #define MESSAGE "You wish!"
#endif
```

```c
// 这个指令告诉 CPP 如果定义了 DEBUG，则执行处理语句。在编译时，如果您向 gcc 编译器传递了 -DDEBUG 开关量，这个指令就非常有用。它定义了 DEBUG，您可以在编译期间随时开启或关闭调试
#ifdef DEBUG
   /* Your debugging statements here */
#endif
```

### 预定义宏

![](/static/2020-10-24-15-49-07.png)
![](/static/2020-10-24-15-49-37.png)

### 预处理器运算符

#### 宏延续运算符: \

* `\`
* 单行未完成宏定义时使用

```c
#define message_for(a, b) \
    printf(#a "and" #b ": hahh\n")
```

#### 字符串常量化运算符: #

* `#`
* 当需要**把一个宏的参数转换为字符串常量**时
  * 有特定参数/参数列表

```c
#define message_for(a,b) \
    printf(#a "and" #b ": hahh\n")

//会将传入的参数,转入字符串常量
int main(void)
{
    message_for(a, b);
    return 0;
}
```

#### 标记粘贴运算符: ##

* `##`
* 合并两个参数
  * 允许在宏定义中两个独立标记合并为一个

```c
#define tokenpaster(n) printf ("token" #n " = %d", token##n)

//printf ("token34 = %d", token34);
int main(void)
{
   int token34 = 40;

   tokenpaster(34);//token34 = 40
   return 0;
}
```

#### defined() 运算符

`defined`预处理器

* 用于常量表达式,**判断一个标识符是否被`#define`过**
  * 如以定义,值为真(非零)
  * 未定义,值为假(0)

```c
#if !defined (MESSAGE)
   #define MESSAGE "You wish!"
#endif

int main(void)
{
   printf("Here is the message: %s\n", MESSAGE);  
   return 0;
}
```

### 参数化宏

使用参数化的宏, **模拟函数**

* 注意`()`

```c
int square(int x) {
   return x * x;
}

// 可写为宏
#define sqaure(x) ((x) * (x))

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int main(void)
{
   printf("Max between 20 and 10 is %d\n", MAX(10, 20));  
   return 0;
}
```

## 头文件

扩展名为`.h`的文件

* 包含了**c函数声明 & 宏定义**
  * 被多个源文件中引用共享
* 分类
  * **自定义头文件**
  * **编译器自带头文件**
* 使用
  * `#include`预处理指令引用头文件,**相当于复制头文件内容**

### 只引用一次头文件

如果一个头文件被引用两次，编译器会处理两次头文件的内容，这将产生错误

* **使用条件编译语句**
* **包装器 #ifndef**
  * 再次引用头文件,条件为假,因为已定义.此时预处理器会跳过该文件的整个内容,编译器会忽略他

🍊 标识命名

* 应唯一,一般头文件名全大写,前后加下划线,`.`也变为下划线
  * 如`stdio.h` -> `#ifndef _STDIO_H_`

```c
#ifndef HEADER_FILE
#define HEADER_FILE

the entire header file file

#endif
```

### 有条件引用

有时需要从**多个不同的头文件中选择一个引用**到程序中

* 如指定在不同os上使用配置参数
* **但头文件比较多时,不妥当**
  * 往往会用一个`global.h`头文件来**包括所有要引用的`.h`文件**
  * **预处理器使用宏来定义头文件名称 -- 有条件引用**

```c
#ifndef _GLOBAL_H
#define _GLOBAL_H
#include <fstream>
#include <iostream>
#include <math.h>
#include <Config.h>
#endif

//另外文件
#include "global.h"

//2.
#define _GLOBAL_H "global.h"
...
#include _GLOBAL_H
```

```c
#if SYSTEM_1
   # include "system_1.h"
#elif SYSTEM_2
   # include "system_2.h"
#elif SYSTEM_3
   ...
#endif
```

## 强制类型转换

* `(type) expression`

```c
int main()
{
   int sum = 17, count = 5;
   double mean;

   mean = (double) sum / count;//强转优先级大于出发
   printf("Value of mean : %f\n", mean );
}
```

### 整数提升

把小于`int`/`unsigned int`的整型转为`int`/`unsigned int`

```c
int  i = 17;
   char c = 'c'; /* ascii 值是 99 */
   int sum;

   sum = i + c;//116, 'c'的值进行整数提升
   printf("Value of sum : %d\n", sum );
```

### 常用算术转换

![](/static/2020-10-24-17-56-43.png)
![](/static/2020-10-24-18-10-50.png)

```c
#include <stdio.h>
/*
c 首先被转换为整数，但是由于最后的值是 float 型的，所以会应用常用的算术转换，编译器会把 i 和 c 转换为浮点型，并把它们相加得到一个浮点数
 */
int main()
{
   int  i = 17;
   char c = 'c'; /* ascii 值是 99 */
   float sum;

   sum = i + c;
   printf("Value of sum : %f\n", sum );

}
```

## c错误处理

不提供直接的错误处理

* 发生错误时,大多返回`1/NULL`
  * 同时会设置一个**错误代码 errno**，该错误代码是全局变量，表示在函数调用期间发生了错误
  * **可以在 errno.h 头文件中找到各种各样的错误代码**
* 可以通过检查返回值，然后根据返回值决定采取哪种适当的动作
  * 初始化时，把**errno 设置为 0**，这是一种良好的编程习惯。0 值表示程序中没有错误
* <font color="red">应该使用 stderr 文件流来输出所有的错误</font>

![](/static/2020-10-24-18-26-19.png)
![](/static/2020-10-24-18-26-28.png)

### 程序退出状态

![](/static/2020-10-24-18-29-41.png)

## 可变参数

函数可变参数

* 可涉及宏
* `int func(int, ...)`
* **需要使用 stdarg.h 头文件**

🍊 具体实现

* 定义一个函数,参数省略号
* 函数定义内创建`va_list`类型变量
  * 头文件`stdarg.h`中定义了
* 使用`int`& `va_start`宏
  * **初始化`va_list`类型变量**为一个**参数列表**
  * `va_start(valist, num)` num个参数初始化valist
* 使用**`va_arg`宏**&**`va_list`变量**访问参数列表中每个项
  * `va_arg(valist, int)`
* 使用`va_end`宏
  * 清理`va_list`变量内存
  * `va_end(valist)`

```c
#include <stdarg.h>

double average(int num,...)
{

    va_list valist;
    double sum = 0.0;
    int i;
 
    /* 为 num 个参数初始化 valist */
    va_start(valist, num);
 
    /* 访问所有赋给 valist 的参数 */
    for (i = 0; i < num; i++)
    {
       sum += va_arg(valist, int);
    }
    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return sum/num;
}

```

## 动态内存管理

🍬 void * 类型表示未确定类型的指针。C、C++ 规定 void * 类型可以通过类型转换强制转换为任何其它类型的指针

`stdlib.h`头文件

* `void* calloc(int num, int size)`
  * **内存中动态分配num*size个字节长度的内存空间**,且字节值都为`0`
* `void free(void *address);`
  * 数释放 address 所指向的内存块,**释放的是动态分配的内存空间**
* `void *malloc(int num)`
  * **堆区分配一块指定大小的内存空间，用来存放数据**
  * 这块内存空间在函数执行完成后不会被初始化，它们的值是未知的
* `void *realloc(void *address, int newsize);`
  * **重新分配内存，把内存扩展到 newsize**

### 动态分配内存

按需分配

![](/static/2020-10-24-19-25-27.png)

* 也可以使用`calloc(200, sizeof(char))`编写

### 重新调整内存大小 & 释放内存

程序退出时，**os会自动释放所有分配给程序的内存**

* <font color="red">在不需要内存时，都应该调用函数 `free()` 来释放内存</font>
* 您可以通过调用函数**`realloc()`来增加或减少已分配的内存块的大小**

![](/static/2020-10-24-19-35-45.png)

## 命令行参数

执行程序时，可以从命令行传值给 C 程序. 这些值被称为**命令行参数**

* 命令行参数是使用main()函数参数来处理的，其中，**argc**是指传入参数的个数，**argv[]**是一个指针数组，指向传递给程序的每个参数。
* argv[0] 存储程序的名称，argv[1] 是一个指向第一个命令行参数的指针，*argv[n] 是最后一个参数

下面是一个简单的实例，检查命令行是否有提供参数，并根据参数执行相应的动作

```c
#include <stdio.h>

int main( int argc, char *argv[] )  
{
   if( argc == 2 )
   {
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc > 2 )
   {
      printf("Too many arguments supplied.\n");
   }
   else
   {
      printf("One argument expected.\n");
   }
}

$./a.out testing
The argument supplied is testing
```