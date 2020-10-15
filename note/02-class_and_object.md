# Class & Object

类&对象

## encapsulation

封装意义

* **属性&行为作为一个整体，表现生活中的事物**
  * 属性&行为加以权限控制
* **类设计，可以有不同访问权限**
  * **public**
  * protected
    * 子 & 本类
  * **private**
    * 本类

example

```cpp
class Student{
    public://public access modifier
        // properties
        string m_name;
        int m_id;

    // display name & id
    void showStudent(){
        cout<< "name:" << m_name << "id:" << m_id<< endl;
    }
};

int main(){
    Student stu;
    stu.m_name = "a";
    stu.m_id = 123;
    system("pause");
}
```

access modifier example

```cpp
class Person{
    public:
        string m_name;
    protected:
        string m_car;// can only be accessed by itself & its subclass
    private:
        int m_password;// cannot be accessed unless the class itself
}

int main() {

    Person p;
    p.m_Name = "李四";
    //p.m_Car = "奔驰";  //保护权限类外访问不到
    //p.m_Password = 123; //私有权限类外访问不到

    system("pause");

    return 0;
}
```

## struct vs class

the only difference between struct & class

* <font color="red">default access modifier is different</font>
  * **struct**
    * public(default)
  * **class**
    * private(default)

```cpp
class c1{
    int m_A;//default:private
}

struct c2{
    int m_A;//default:public
}

int main(){
    c1 c;
    c.m_A = 10;//cannot work, since its private

    c2 c2;
    c2.m_A = 10;//works, privilege is public
}
```

## why encapusulation: privacy

成员属性私有化

* if all the members are private, can have the **i/o permission controlled**
* can check the **effectiveness of the data(regarding the writing permission)**

design **corresponding getter & setter**

* **depends on its accessbility**

### example

1. cube

![](/static/2020-10-14-22-20-56.png)

```cpp
class Cube{
    private:
        int length;
        int width;
        int height;

    public:
        void setLength(){
            ...
        }
        int getLength(){
            ...
        }
    //  ...

        int area(){
            return length * width + length * height + width * height;
        }

        int volume(){
            return length*width*height;
        }

        bool equals(Cube &other){
            //using reference: simplifies the using of pointer & avoiding wrongly operating
            if (length==other.getLength() &&...) return true;
            else return false;
        }
}

bool isSame(Cube c1, Cube c2){
    if (c1.getLength() == c2.getLength() &&...) return true;
    else return false;
}

```

2. point & circle

![](/static/2020-10-14-22-29-57.png)

the distance between point to the circle center

* `==`radius
  * point is on the circle
* `>` r
  * point is outside the circle
* `<` r
  * point is within the circle

the distance between 2 points

* `sqrt((x1-x2) ^ 2 + (y1-y2) ^ 2))`
* **hence the distance from the point to the circle center**

```cpp
class Point{
    private:
        int m_X;
        int m_Y;
    int getX(){
        //...
    }
    int setX(int x){
        //...
    }
    //...
}

class Circle{
    public:
        void setR(int r){
            //...
        }
        int getR(){
            //...
        }
        Point getCenter(){
            //...
        }
        //...

    // checking the relationship between points & circle
    void isInCircle(Circle &c, Point &p){
        // check distance between 2 points(point x and circle center)
        //...

        // calculate the square of the radius

        // compare the distance between radius, to decide wether the point is on/within/outside the circle
    }

    private:
        int m_R;//radius
        Point m_Center;// circle center
}

```

## Constructors & Destructors

构造函数 & 析构函数

* <font color="red">C++ will automatically call these two func</font> to finish the object initialisation & cleaning(garbage collection)
  * **constructors**
  * **destructors**
* **if not provide the con/destructors, complier would implemente a default one**
  * <font color="blue">but the body is empty</font>

🍊 syntax

![](/static/2020-10-14-22-59-07.png)

* **constructor**
  * `className(){}`
* **destructor**
  * `~className(){}`
  * **no args, no overloads feats**
  * delete object?

```cpp
class Person
{
public:
	//构造函数
	Person()
	{
		cout << "Person的构造函数调用" << endl;
	}
	//析构函数: no args no overloads
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

};

void test01()
{
	Person p;
}

int main() {
	
	test01();

	system("pause");
	return 0;
    
    // before the program terminates, destroy(collect) the object from the heap
}
```

### constructors: category & call

构造函数的分类

* based on the args
  * **有参**
  * **无参**
    * 编译器默认提供的（如不显式声明）
    * <font color="red">注意：调用默认构造函数时，不要加`()`，不然编译器会看作函数声明</font>
* based on the type
  * normal constructor普通构造
  * **copy constructor拷贝构造**
    * <font color="red">注意不要利用拷贝构造函数初始化匿名对象`Person(10)`</font>

🍊 调用方式

* **括号**
  * <font color="red">注意：调用默认构造函数时，不要加`()`，不然编译器会看作函数声明</font>
* **显式法**
* **隐式转换法**

```cpp
Person() {
  cout << "no args constructor" << endl;
}
// 拷贝构造函数: 完全拷贝基于传入的类的构造函数（只读，不能修改指向&值）
Person(const Person& p){
    age = p.age;//将传入的p的age，完全拷贝一份到this.age
    cout << "copying constructors"<<endl;
}

// destructor
~Person(){
    //...
}
```

调用

```cpp
// 括号法

Person p;//默认构造函数（无参）, 不要写括号，不然编译器会看作函数声明
Person p2(10);//有参调用

// 显式法

Person p2 = Person(10);//有参Person(int)
Person p3 = Person(p2);//有参拷贝Person(const Person& p)

Person(10);//匿名对象，当前行执行结束系统立即回收(析构)
//注意不要利用拷贝构造函数初始化匿名对象，
//编译器会认为Person(p3) === Person p3; 对象声明

// 隐式转换

Person p4 = 10;//相当于 Person p4 = Person(10);

Person p5 = p4;//拷贝构造,Person p5 = Person(p4);

```

### 拷贝构造调用时机

何时调用拷贝函数?

* 使用一个**已经创建完毕的对象来初始化一个新对象**
* **值传递的方式给函数参数传值**
  * 传值形参
* 以**值方式返回局部对象**

```cpp
class Person{
    public:
        Person(){}
        Person(int age){}
        Person(const Person& p){
            age = p.age;
        }//copy constructor
        ~Person(){}

        int age;
}

// 使用创建完毕的对象初始化一个新对象
void test01(){
    Person p1(20);
    Person p2(p1);//p2.age=20;
}

// 值传递方式给函数参数传值
Person doWork(Person p){
    //...
}

void test02(){
    Person p;//无参
    doWork(p);
}

// 值方式返回局部对象

Person doWork2(){
    Person p1;
    cout << (int*) &p1<<endl;
    return p1;//返回的是p1的副本, 此时会调用拷贝构造
    //弹栈后p1被析构
}

void test03(){
    Person p = doWork2();
    cout << (int*) &p<<endl;
    //弹栈后p被析构
}

```

### 构造函数调用规则

默认情况,编译器给**一个类**自动添加

* **默认构造函数**
  * 无参,空
* **默认析构**
  * 无参,空
* **默认拷贝构造函数**
  * 对属性进行值拷贝

🍊 构造函数调用规则

* 用户定义**有参构造**
  * 编译器**不再提供无参(默认)构造**
  * **会提供默认拷贝构造**
* 用户定义**拷贝构造**
  * 编译器<font color="red">不再提供其他构造函数</font>

```cpp
// c++最多提供3个构造
// 默认构造,默认析构,默认拷贝构造
class Person{
    public:
      Person(){}
      Person(int age){}
      Person(const Person& p){
          age = p.age;
      }
      ~Person(){}
      int age;
}
```

### 深拷贝 & 浅拷贝

浅拷贝

* 简单的赋值拷贝
* <font color="red">使用编译器提供的拷贝构造函数</font>
* <font color="blue">可能造成堆区内存重复释放</font>
  * **利用深拷贝解决**

深拷贝

* **在堆区重新申请空间,进行拷贝操作**
  * <font color="red">需要手动开辟`new`,手动释放(否则程序/栈帧结束后os回收)</font>
* <font color="blue">如果属性在堆区开辟,一定要自己提供拷贝构造函数, 防止浅拷贝带来问题</font>

```cpp
class Person{
    public:
        Person(){};
        Person(int age, int height){
            age = age;
            height = new int(height);//指针接收堆中数据
        };
        /* 默认拷贝构造:浅拷贝,造成堆空间重复释放问题  
        Person(const Person& p){
            age = p.age;
            height=p.height;//指针交叉
        }
        */

        ~Person(){
            if (height!=NULL)
            {
                delete height;
                height = null;
            }
        };//释放堆区开辟的数据

        int age;
        int &height;//要使用至堆,所以为引用指针
}

void main(){
    /* 默认浅拷贝会出现问题,
        先进后出,先析构p2,释放堆内存
        导致p1释放时异常
     */
    Person p1(18,160);
    Person p2(p1);
    cout<<"p2:"<<p2.age<<*(p2.height)<<endl;
}
```

🍊 解决方式

![](/static/2020-10-15-14-45-22.png)

```cpp
Person(const Person&p)
{
    age = p.age;
    // height = p.height;//编译器默认的拷贝构造实现,会造成指针交叉问题
    height = new int(*p.height);//深拷贝,开辟int堆空间,指针接收新空间地址
    cout<<"自定义拷贝构造"<<endl;
}
```

### 初始化列表

c++提供初始化列表语法

![](/static/2020-10-15-16-00-55.png)

* 用于**初始化类属性**
* `构造函数(type value1, value2, value3): field1(value1), field2(value2), ...`

```cpp
class Person
{
    public:
        /*
            传统方式初始化
            Person(int a, int b, int c){
                m_A = a;
                m_B = b;
                m_C = c;
            }
         */

        //初始化列表: 初始化类属性
        Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c){}

        int m_A;
        int m_B;
        int m_C;
}

int main(){
    Person p(1,2,3);
    // Person p = Person(1,2,3);显式法
    // Person p = 1,2,3;隐式转换法
}
```

### 他类对象作为类成员

类成员可以作为另一个类的对象,

* 称为对象成员

```cpp
class A{}
class B{
    A a;
}
```

🍊 创建B对象时,**A & B的构造析构顺序?**

* <font color="red">会先初始化其他类对象,再构造本类对象</font>
* <font color="red">先析构本类对象,再析构其他类对象</font>

### 静态成员

成员变量&函数用`static`修饰

* **静态成员变量**
  * 所有对象共享同一份数据
  * 在**编译阶段分配内存**
  * 类内声明，类外初始化
* **静态成员函数**
  * **所有对象共享同一个函数**
  * <font color="red">静态成员函数只能访问静态成员变量</font>

🍊 example

静态成员变量

```cpp
class Person{
    public:
        static a;//static variable

        //静态成员函数：只能访问静态成员变量
        static void func(){
            //..
            a=100;
        }
    private:
        static b;//外部始终不能访问
}

void test01(){
    // 通过对象访问
    Person p;
    p.a = 10;
    Person p2;
    p2.a = 100;//a属性共享

    // 通过类名访问
    Person::a = 1000;

}
```

## 对象模型：成员变量 & 函数

🍊 对象模型

* <font color="blue">成员变量 & 成员函数分开存储</font>
* **只有【非静态成员变量】，才属于类对象**

```cpp
class Person{
}

void test01(){
    //空对象占用空间 - 1B
    //为了区分每个空对象所占内存位置
    Person p;
    sizeof(p);
}

```cpp
class Person{
    int a;//非静态成员变量，属于类对象的一部分
}

void test(){
    Person p;
    sizeof(p);//非空对象，占4B
}
```

```cpp
class Person{
    int a;
    static b;//静态成员变量，不属于类对象
    void func(){};//非静态成员函数，不属于类对象
    static func2(){};//静态成员函数，不属于类对象
}
int Person::b = 0;

void test(){
    Person p;
    sizeof(p);//仍为4B
}
```

## this指针

通过对象模型，c++成员变量&函数分开存储

* 每个**非静态成员函数，只产生一份函数实例**
  * **`this`指针区分是哪个对象调用该普通方法**
* **this指针本质：**
  * 指针常量，<font color="red">指针指向不可以修改 `void* const this`;</font>

🍊 `this`

* `this`指针<font color="red">指向被调用的成员函数，所属的对象</font>
* `this`指针**存在每个非静态成员函数中**
* <font color="blue">**当形参和成员变量同名时**，可用this指针来区分</font>
* 在类的<font color="blue">非静态成员函数中返回对象本身</font>，可使用`return *this`
  * <font color="red">以值方式返回局部对象，属于拷贝构造的调用，【返回的是副本！！】</font>

```cpp
// 1.解决名称冲突: 成员变量 & 形参名
class Person{
    public:
        Person(int age){
            this->age =age;
        }
        int age;

        // 2.返回普通方法中本对象自身
        Person PersonAddAge(const Person& p){
            this->age +=p.age;
            return * this;//解引用，以值方式返回局部对象（会调用拷贝构造），返回副本
        }
}
```

## 空指针访问成员函数

c++**空指针也可以调用成员函数**

![](/static/2020-10-15-17-19-36.png)

* <font color="red">需要注意有没有用到`this`指针</font>
  * 如果用到`this`，需要判断保证代码健全性soundness
  * <font color="blue">访问属性时，编译器会隐式通过`this->field`访问</font>

```cpp
void ShowClassName() {
    cout << "我是Person类!" << endl;
}

void ShowPerson() {
    if (this == NULL) {
        return;
    }
    cout << mAge << endl;//此行访问属性，隐式this->mAge，需要判断指针是否为空
}

void test(){
    Person *p=NULL;//空指针
    p->showClassName();//空指针，可以调用成员函数，因为该函数没有使用this指针
    p->ShowPerson(); //成员函数中用到了this指针, 需要加以判断，不然异常
}
```

## const修饰成员函数

常函数

* 成员函数后加`const`称这个函数为**常函数**
* 常函数内**不可以修改成员属性**
  * this指针本质：
    * 指针常量，指针指向不可以修改 `void* const this`;
  * <font color="red">相当于`cosnt Person* const this;`</font>
* **成员属性**声明时加关键字`mutable`后，**常函数中仍然可以修改**

常对象

* 声明对象前加`const`
  * **该对象为常对象**
* <font color="red">常对象不可以修改成员属性</font>
  * 可以访问
* <font color="blue">可以修改`mutable`修饰的成员属性</font>
* <font color="red">常对象只能调用常函数</font>

```cpp
class Person{
    public:
    //常函数
        void showPerson() const{
            m_A = 100;//默认this->m_A = 100, 如果是常函数，则不能修改该成员属性
            //相当于cosnt Person* const this;
        }
        int m_A;
        mutable int m_B;//mutable修饰后，可以在常函数中修改
}
```

```cpp
// 常对象
void test1(){
    const Person person;//常对象
    // person.m_A = 100;.//常对象不能修改成员变量的值,但可以访问
    person.m_B = 100;//常对象可以修改mutable修饰的成员变量
}

```

## 友元 friend class

🍊 友元意义

* 允许本类外**其他函数/类进行私有成员的访问**
* `friend`

🍊 友元的三种实现

* **全局函数做友元**
* 类做友元
* 成员函数做友元

### 全局函数: 友元

```cpp
class Building{
    friend void friendAccess(Building * b);//全局函数做友元,此时该函数能访问该类私有成员

    Building(){
        m_sittingRoom = "1";
        m_bedRoom = "2";
    }
    public:
      string m_sittingRoom;// living room
    private:
        string m_bedRoom;
}

// 全局函数做友元
void friendAccess(Building * b){
    cout << "I'M ACCESSING NOW"<< b->m_sittingRoom<<endl;
    cout << "I'M ACCESSING NOW"<< b->m_bedRoom<<endl;
}

```

### 类: 友元

```cpp
class Building{
    friend class Friend;//类做友元,访问该类的私有成员
    public:
        string m_sittingRoom;
    private:
        string m_bedRoom;
}

// 类外写构造函数
Building::Building(){
    m_sittingRoom = "1";
    m_bedRoom = "2";
};

class Friend{
    public:
        // void visit(){
        //     //访问building的成员
        // }
        Building* buiding;
}

//类外声明
Friend::Friend(){
    building = new Building;//返回的是指针在堆中的地址
};

void Friend::visit(){
    cout<<"accessing" <<building->sittingRoom<<endl;
    cout<<"accessing" <<building->bedRoom<<endl;//类做友元,访问其他类的私有成员
}

```

### 成员函数: 友元

```cpp
class Building;
class Friend{
    public:
        Friend();
        void visit();
        Building* b;
}
//类外实现
Friend::Friend(){
    b = new Building;//调用无参,堆中开辟,返回指针地址
}
//成员函数做友元,访问私有成员
void Friend::visit(){
    cout<<"accessing"<<b->m_sittingRoom<<endl;
    cout<<"accessing"<<b->m_bedRoom<<endl;//成员函数做友元,访问私有成员
};

class Building{
    friend void Friend::visit();//其他类成员函数做友元,访问本类私有成员
    public:
        Building();
        string m_sittingRoom;
    private:
        string m_bedRoom;
}
//类外实现
Building::Building(){
    m_sittingRoom = "1";
    m_bedRoom = "2";
}
```

