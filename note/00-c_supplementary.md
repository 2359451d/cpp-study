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

