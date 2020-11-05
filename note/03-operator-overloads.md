# Operator Overloads

运算符重载

* 对**已有的运算符重新进行定义，赋予其另一种功能**，以适应不同的数据类型
  * 只能是**自定义数据类型**
    * 对于**内置的数据类型**的表达式的的**运算符**是**不可能改变的**
* <font color="red">允许存在,运算符函数重载</font>
* <font color="blue">注意返回引用</font>
  * 有时候是为了**提高效率**,不必在外部再**隐式创建副本**接收(值方式返回)
  * 有时候为了**对一个数据进行连续运算操作**

* [Operator Overloads](#operator-overloads)
  * [+](#ulliliul)
  * [<<](#)
  * [++](#-1)
    * [引用 & 值 & 链式操作](#引用--值--链式操作)

## +

加号运算符重载

* 实现**自定义数据类型**的`+`
* 实现编译器提供的函数名,重载

🍊 实现方式

* **成员函数**实现`+`重载
  * 本质`object.operator+(object2)`
* **全局函数**实现`+`重载
  * 本质`operator+(objece1,object2)`

```cpp
class Person{
    public:
        // 1.成员函数实现+重载
        Person operator+(const Person& p2){
            Person temp;
            temp.a = this->a + p2.a ;
            temp.b = this->b + p2.b ;
            return temp;//值方式返回局部对象,调用拷贝构造,返回的是副本
        }
        int a;
        int b;
}

// 全局函数实现重载+
Person operator+(Person &p1, Person &p2){
    Person temp;
    temp.a = p1.a + p2.a;
    temp.b = p1.b + p2.b;
    return temp;
}

// 全局函数(重载): 实现不同重载+
// 实质 Person temp = operator+(p,num)
//  Person temp = p+num
Person operator+(Person &p, int num){
    Person temp;
    temp.a = p.a +num;
    temp.b = p.b +num;
    return temp;
}

void test1(){
    Person p1;
    p1.a =10;
    p1.b =10;

    Person p2;
    p2.a =10;
    p2.b =10;

    Person p3 = p1+p2;//+重载,成员函数本质相当于p1.operator+(p2)
    //全局函数本质 : Person p3 = operator+(p1,p2)
}
```

## <<

左移运算符重载

* 位移
* **输出**
  * 如重载实现自定义类的输出
  * <font color="red">通常不选择成员函数重载`<<`</font>
  * **只能通过全局函数重载`<<`运算符**
  * <font color="red">可以配合友元</font>

```cpp
class Person{
    public:
    // !!! 通常不使用成员函数重载<<运算符, p<<cout无法实现cout在左边
    //   void operator<<(cout){
    //   }
        int a;
        int b;
}

//利用全局函数实现<<重载
// 本质
// operator<<(cout, p) : cout<<p
//不能值传递创建副本,所以使用引用/指针传参
cout operator<<(osstream &cout, Person &p){
    cout << "a: " << p.a << "b: " << p.b;
    return cout;
};

void test1(){
    Person p;
    p.a = 10;
    p.b = 20;
    //默认无法输出自定义类对象
    cout << p <<endl;//重载链式<<cout
}
```

## ++

递增运算符重载

* 通过`++`重载,实现自定义整型数据
  * `++MyInt`
  * `MyInt++`**需要运用占位参数`int`,用于区分前置后置`++`**

```cpp
class MyInt{
    friend &ostream operator<<(osstream& cout, MyInt myInt);//全局函数做友元,访问本类num私有属性
    public:
        MyInt(){
            num=0;
        }

        //成员函数实现++重载
        //重载++myint
        &MyInt operator++(){
            num++;
            return *this;//外部拿一个引用类型来接收*this对象本身???
            //此处不返回MyInt原因: 提高效率,外部不必创建副本
        }

        //重载myint++
        // int为占位参数,用于区分前置后置++
        MyInt operator++(int){
            MyInt temp = *this;
            num++;
            return temp;//注意返回的是值,因为temp是局部变量(弹栈析构),不能用引用接收
        }

    private:
        int num;//内部维护
}

//全局函数实现<<重载
//注意!!myint传值而不是引用,因为传值传入副本,
// 之后的++重载会返回局部变量, 不能返回引用
ostream& operator<<(ostream& cout, MyInt myInt){
    cout << myInt.num;//注意num为私有成员属性,要友元
}

void test(){
    MyInt myInt;
    cout << myInt <<endl;
    cout << ++myInt <<endl;
    cout << myInt++ <<endl;
}

```

### 引用 & 值 & 链式操作

为什么`++myInt`返回引用才支持链式?

* 因为内部操作`num++`后,返回对象本身`*this`
  * **如果用值副本接收**, 只作用于当前链式, 每一次都对新副本进行操作
    * 操作结束副本就没了
  * **如果用引用接收**,本质为第一次创建的对象指针, 作用于任何链式, 每次都对其对象本身的属性进行操作

为什么`myInt++`返回副本就支持链式?

* 首先,内部返回的是`MyInt temp = *this`,**新的局部变量**
  * <font color="red">局部变量本身就不能作为引用的返回值</font>,弹栈直接被析构,可能造成非法访问
* 其次,内部对对象本身的属性`num++`递增, 每次都对其对象本身进行操作,**没有任何对象副本**
  * 所以链式生效