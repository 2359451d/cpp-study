# Basics

cpp basics part

* [Basics](#basics)
  * [Constant](#constant)
  * [keyword](#keyword)
  * [data types](#data-types)
  * [goto](#goto)
  * [array](#array)
    * [multidimensional array](#multidimensional-array)
  * [passing addr vs value](#passing-addr-vs-value)
  * [func](#func)
    * [分文件编写](#分文件编写)
  * [pointer](#pointer)
    * [null & wild pointer](#null--wild-pointer)
    * [const pointer](#const-pointer)
    * [pointer access array](#pointer-access-array)
    * [pointer & func args](#pointer--func-args)
  * [struct](#struct)
    * [struct array](#struct-array)
    * [struct pointer](#struct-pointer)
    * [nested struct](#nested-struct)
    * [passing struct into func](#passing-struct-into-func)
    * [struct const](#struct-const)
  * [momery model](#momery-model)
    * [before program running](#before-program-running)
    * [after execution](#after-execution)
    * [keyword: new & delete](#keyword-new--delete)
  * [Reference](#reference)
    * [Precaution： some tips](#precaution-some-tips)
    * [passing reference as func args](#passing-reference-as-func-args)
    * [reference as the return value](#reference-as-the-return-value)
    * [引用本质](#引用本质)
    * [常量引用](#常量引用)
  * [function：advance](#functionadvance)
    * [default args](#default-args)
    * [placeholder args](#placeholder-args)
    * [Overloads](#overloads)

## Constant

两种定义常量方式

```cpp
// 1. 定义宏常量
#define macros_name value

// 2. const修饰变量
const float PI = 3.14s
```

## keyword

cpp关键字：预先保留的标识符

![](/static/2020-10-12-16-29-39.png)

* 定义变量/常量时不要使用关键字

## data types

数据类型

整型

![](/static/2020-10-12-16-30-58.png)

实型（浮点型）

![](/static/2020-10-12-16-31-40.png)

```cpp
//科学计数法
float f2 = 3e2; // 3 * 10 ^ 2 
cout << "f2 = " << f2 << endl;

float f3 = 3e-2;  // 3 * 0.1 ^ 2
cout << "f3 = " << f3 << endl;
```

字符型

![](/static/2020-10-12-16-33-37.png)
![](/static/2020-10-12-16-34-32.png)

```cpp
cout << (int)ch << endl;  //查看字符a对应的ASCII码
ch = 97; //可以直接用ASCII给字符型变量赋值
cout << ch << endl;
```

转义字符（escape char）

![](/static/2020-10-12-16-35-23.png)

字符串型（str）

```c
// c风格字符串
char str1[] = "hello world";
```

```cpp
// c++风格字符串
#include <string>
string str = "hello world";
```

布尔类型bool

![](/static/2020-10-12-16-37-26.png)

* 注意c没有定义

```cpp
int main() {

  bool flag = true;
  cout << flag << endl; // 1

  flag = false;
  cout << flag << endl; // 0

  cout << "size of bool = " << sizeof(bool) << endl; //1

  system("pause");

  return 0;
}

```

## goto

在程序中不建议使用goto语句，以免造成程序流程混乱

`goto`

![](/static/2020-10-12-16-39-44.png)

* 如果标记的名称存在，执行到goto语句时，会跳转到标记的位置

## array

the usage of array var name

![](/static/2020-10-12-16-42-33.png)

* count the memory which is taken up by the entire array
* fecth the array's **initial address** in the memory

🍊 example

reverse the array

```cpp
int start = 0;
int end = sizeof(arr)/sizeof(arr[0]) -1;//end index of the array

while(start < end){
    int temp = arr[start];
    arrp[start++] = arr[end];
    arr[end] = temp;
}

for (int i =0;i<5;i++){
  cout << arr[i] <<endl;
}
```

### multidimensional array

![](/static/2020-10-12-16-50-05.png)

```cpp
int main() {

  //方式1  
  //数组类型 数组名 [行数][列数]
  int arr[2][3];
  arr[0][0] = 1;
  arr[0][1] = 2;
  arr[0][2] = 3;
  arr[1][0] = 4;
  arr[1][1] = 5;
  arr[1][2] = 6;

  for (int i = 0; i < 2; i++)
  {
  for (int j = 0; j < 3; j++)
  {
  	cout << arr[i][j] << " ";
  }
  cout << endl;
  }

  //方式2 【直观】
  //数据类型 数组名[行数][列数] = { {数据1，数据2 } ，{数据3，数据4 } };
  int arr2[2][3] =
  {
  {1,2,3},
  {4,5,6}
  };

  //方式3
  //数据类型 数组名[行数][列数] = { 数据1，数据2 ,数据3，数据4  };
  int arr3[2][3] = { 1,2,3,4,5,6 }; 

  //方式4 
  //数据类型 数组名[][列数] = { 数据1，数据2 ,数据3，数据4  };
  int arr4[][3] = { 1,2,3,4,5,6 };

  system("pause");

  return 0;
}

```

## passing addr vs value

传值 vs 传址

* 传值
  * 函数调用时实参数值传入形参
  * **形参发生任何改变，不会影响实参**

## func

函数声明 = 函数原型

* **声明可以有多次**

### 分文件编写

分开编写可以使**代码结构更加清晰**，步骤

![](/static/2020-10-12-17-06-05.png)

1. 创建后缀名为.h的头文件  
2. 创建后缀名为.cpp的源文件
3. 在头文件中写函数的声明
4. 在源文件中写函数的定义

## pointer

定义

* `type * pName`
* 指针占`4B/8B`（32bit-compiler/64bit）

### null & wild pointer

空指针

* 指向内存编号为`0`的空间
* **一般用于初始化指针变量**
* <font color="red">注意空指针指向的内存不能访问</font>

```cpp
int main() {
  //指针变量p指向内存地址编号为0的空间
  int * p = NULL;

  //访问空指针报错
  //内存编号0 ~255为系统占用内存，不允许用户访问
  cout << *p << endl;

  system("pause");

  return 0;
}
```

---

野指针

![](/static/2020-10-13-09-51-34.png)

* **指针指向非法内存空间**
  * 没有对内存进行访问权限的申请

### const pointer

const修饰指针有三种情况

1. const**修饰指针**   --- **常量指针**
   1. `const int *p`
   2. 指针指向可以修改，但指针指向的值不可以改
2. const**修饰常量**   --- **指针常量**
   1. `int* const p`
   2. 指针指向不可以改，但指针指向的值可以改
3. **const即修饰指针，又修饰常量**
   1. `const int * const p`
   2. 指针指向不能改，指针指向的值不能改

### pointer access array

指针访问数组元素

```cpp
int main() {

    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };

    int * p = arr;  //指向数组的指针

    cout << "第一个元素： " << arr[0] << endl;
    cout << "指针访问第一个元素： " << *p << endl;

    for (int i = 0; i < 10; i++)
    {
        //利用指针遍历数组
        cout << *p << endl;
        p++;
    }

    system("pause");

    return 0;
}
```

### pointer & func args

（形参）传址的一种，会在函数内部改变外部实参

```cpp
//值传递
void swap1(int a ,int b)
{
    int temp = a;
    a = b; 
    b = temp;
    }
    //地址传递
    void swap2(int * p1, int *p2)
    {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    }

    int main() {

    int a = 10;
    int b = 20;
    swap1(a, b); // 值传递不会改变实参

    swap2(&a, &b); //地址传递会改变实参

    cout << "a = " << a << endl;

    cout << "b = " << b << endl;

    system("pause");

  return 0;
}
```

## struct

结构体属于用户==自定义的数据类型==，允许用户存储不同的数据类型

定义

```cpp
struct 结构体名 { 结构体成员列表 }；`
struct name {

} varname; // var 就是struct name 类型的数据
struct {

} varname; // var是无名struct类型
```

初始化方法

```cpp
//结构体变量创建方式1
struct student stu1; //struct 关键字可以省略

stu1.name = "张三";
stu1.age = 18;
stu1.score = 100;

//结构体变量创建方式2
struct student stu2 = { "李四",19,60 };
```

### struct array

结构体数组

![](/static/2020-10-13-10-49-43.png)
![](/static/2020-10-13-10-45-41.png)
![](/static/2020-10-13-10-46-24.png)

* **自定义结构体放入数组维护**

步骤

1. 定义结构体
2. 创建结构体数组
   1. `struct struct_name arrayname[size]{}`
3. 给结构体数组中元素赋值

```cpp
//结构体定义
struct student
{
  //成员列表
  string name;  //姓名
  int age;      //年龄
  int score;    //分数
}

int main() {
  //结构体数组
  struct student arr[3]=
  {
    {"张三",18,80 },
    {"李四",19,60 },
    {"王五",20,70 }
  };

  for (int i = 0; i < 3; i++)
  {
    cout << "姓名：" << arr[i].name << " 年龄：" << arr[i].age << " 分数：" << arr[i].score << endl;
  }

  system("pause");

  return 0;
}

```

### struct pointer

通过指针访问结构体中成员

![](/static/2020-10-13-10-37-28.png)

* 使用`->`

```cpp
struct student * p = &stu;
p->score=80;
```

### nested struct

![](/static/2020-10-13-10-38-22.png)
![](/static/2020-10-13-10-38-28.png)

### passing struct into func

传值 vs 传址

* struct本身不是地址

![](/static/2020-10-13-10-39-51.png)

### struct const

`const`防止误操作

![](/static/2020-10-13-10-42-01.png)

* **使struct只读**

## momery model

CPP内存分区模型

- **代码区**
  - 存放函数体二进制代码，由os管理
- **全局区**
  - 存放全局变量&静态变量&常量
- **栈**
  - 由编译器自动分配释放，存放函数参数值&局部变量
- **堆**
  - 开发人员分配&释放
  - **若不释放，程序结束时由os回收**

🍊 内存分区意义

- **不同区域存放数据，生命周期不同**，更灵活编程&管理数据

### before program running

程序运行前

![](/static/2020-10-13-15-58-21.png)

* 编译后生成exe可执行程序，**未执行该程序前内存分为两个区**
* **代码区**
  * 存放CPU执行的机器码
  * 代码区**共享**，对于频繁被执行的程序，在内存中有一份代码即可
  * 代码区**只读**,<font color="red">防止程序意外修改其指令</font>
* **全局区**
  * 存放全局&静态变量
  * **还包括常量区，存放字符常量&其他常量**
  * <font color="red">该区域数据在程序结束后由os释放</font>

### after execution

程序运行后

* **栈**
  * 存放函数参数值，局部变量等(栈帧信息)
  * **栈区数据由编译器自动分配释放**
  * ![](/static/2020-10-13-16-08-53.png)
* **堆**
  * **由开发者分配释放，若不手动释放，结束时由os回收**
  * `new`开辟堆区数据

```cpp
int* func(){
  int* a = new int(10);//直接返回地址值
  return a;
}
```

### keyword: new & delete

C++中利用`new`操作符在堆区开辟数据

![](/static/2020-10-13-17-03-36.png)
![](/static/2020-10-13-17-05-05.png)

- **需要手动释放**
  - `delete`关键字

## Reference

引用

- **给变量起别名**
- `type &other_name = original_name`

```cpp
int main() {
  int a = 10;
  int &b = a;

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  b = 100;

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  system("pause");

  return 0;
}
```

### Precaution： some tips

引用

![](/static/2020-10-13-17-21-22.png)

- **引用必须初始化**
- 引用在**初始化后，不可以改变**
  - `=`做赋值操作，而不是更改引用

### passing reference as func args

引用做函数参数（形参）

- **可以利用引用让形参修饰实参**
  - <font color="red">简化指针修改实参</font>
  - <font color="blue">通过**引用参数产生的效果同按地址传递是一样**的。引用的语法更清楚简单</font>

```cpp
// 值传递
void swap1(int a,int b){
  ...
}

// 传址
void swap2(int* a, int* b){
  ...
}

// 引用传递
void swap3(int& a, int& b){
  ...
}
// 简化传址
int a= 10;
int b= 20;
swap3(a,b);//运行结束，ab交换
//传入时，自动转换为 int* const a = &a, int* const b = &b;
```

### reference as the return value

引用作为函数返回值

* **如果函数返回值是引用，则这个函数调用可以作为左值**
* 注意<font color="red">不要返回局部变量引用</font>

```cpp
//返回局部变量引用【不要这么返回】
int& test01() {
  int a = 10; //局部变量
  return a;
}

//返回静态变量引用
int& test02() {
  static int a = 20;//存放在全局区
  return a;
}

int main() {

  //不能返回局部变量的引用
  int& ref = test01();
  cout << "ref = " << ref << endl;
  cout << "ref = " << ref << endl;

  //如果函数做左值，那么必须返回引用
  int& ref2 = test02();//接收静态变量a，作为其引用ref2
  cout << "ref2 = " << ref2 << endl;
  cout << "ref2 = " << ref2 << endl;

  test02() = 1000;//修改静态变量a的原值

  cout << "ref2 = " << ref2 << endl;
  cout << "ref2 = " << ref2 << endl;

  system("pause");

  return 0;
}

```

### 引用本质

🍊 引用本质

![](/static/2020-10-13-18-12-05.png)
![](/static/2020-10-13-18-14-45.png)

- **指针常量**
- `void* const p`
- 指针指向不能变
  - 指向的值可以变

### 常量引用

常量引用

- **修饰（函数）形参**，防止误操作
  - 在函数形参列表中添加`const`
- <font color="blue">`const`修饰引用后，为只读状态，不能修改值</font>

```cpp

// int a = 10;
// int& ref = 10;//不可以这么写，因为引用需要合法空间

/*
 引用本质：int* const ref, 指向不能变，值可以变
 编译器优化代码
 int temp = 10;
 const int& ref = temp;
 */
const int& ref = 10;//此时找不到原名，编译器取原名

// ref = 100; // const引用为只读状态，不能修改值
```

```cpp
//只读
//引用使用的场景，通常用来修饰形参
void showValue(const int& v) {
	//v += 10;
	cout << v << endl;
}

int a= 10;
showValue(a);//传原名，转换为只读引用 const int* const v = &a
```

## function：advance

### default args

c++中，函数形参列表中形参可以有默认值

- `type func_name(arg=default_value){}`
- 必须在形参列表的末尾
- <font color="red">如果函数声明有默认值，函数实现的时候不能有默认参数</font>

```cpp
int func2(int a = 10, int b = 10);//原型
int func2(int a, int b) {//实现的时候不能有默认参数
	return a + b;
}
```

### placeholder args

函数占位参数

![](/static/2020-10-14-00-07-31.png)

- **用于占位，调用时必须填补该位置**
- <font color="red">现阶段用途不大，但后面可能用到</font>
- <font color="blue">占位参数也可以有默认参数</font>

### Overloads

函数重载

- 函数名可以相同，提高复用性

🍊 满足条件

![](/static/2020-10-14-00-14-18.png)

- 同个作用域
- 函数名相同
- 函数参数类型不同（签名）

---

🍬 注意事项

- 引用作为重载条件
- 函数重载&函数默认参数

```cpp
//1、引用作为重载条件

void func(int &a)
{
	cout << "func (int &a) 调用 " << endl;
}

void func(const int &a)
{
	cout << "func (const int &a) 调用 " << endl;
}

int a= 10;
func(a);//a可读可写，所以调的func(int& a)
func(10);//调的func(const int& a),因为该例编译器才会优化代码 int temp = 10; const int& a =temp;
```

```cpp
//2、函数重载碰到函数默认参数

void func2(int a, int b = 10)
{
	cout << "func2(int a, int b = 10) 调用" << endl;
}

void func2(int a)
{
	cout << "func2(int a) 调用" << endl;
}

//func2(10); //碰到默认参数产生歧义，需要避免

```
