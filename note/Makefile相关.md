# Makefile补充

快速案例

```makefile
# example makefile

src=$(wildcard *.c ./sub/*.c) # 展开./目录 & ./sub/目录下 所有后缀为 .c的文件

# 如找到当前目录下及当前目录子目录inc/中所有.c文件 
#src= $(wildcard *.c) $(wildcard inc/*.c)

dir=$(notdir $(src)) # 把src变量展开文件的路径信息全部去除, 取文件名
obj=$(patsubst %.c,%.o,$(dir)) # 把dir变量中符合.c后缀的文件全替换成.o
#等同于 obj=$(dir:%.c=%.o) 都为文本匹配替换

#syntax $(patsubst <pattern>,<replacement>,<text> ) 
# syntax $(var:a=b) 替换变量var中所有“a”结尾(空格之前)的字为“b”结尾(空格之前，空格分隔多个变量)
#foo=a.o b.o c.o
#bar=$(foo:.o=.c)
```

## include, sinclude

[参考](https://blog.csdn.net/guozhongwei1/article/details/104006457)

> 在 Makefile 使用 **include 关键字可以把别的 Makefile 包含进来**，这很像 C 语言的#include，被包含的文件会原模原样的放在当前文件的包含位置

`include <filename>`

* `sinclude`与`include`作用是一样的,为兼容而存在.

```makefile
# 假如有makefile：a.mk b.mk c.mk
# 文件 foo.make
# 变量bar=e.mk f.mk
include foo.make *.mk $(bar)

#相当于include foo.make a.mk b.mk c.mk e.mk f.mk
```

## export

属于shell关键字

* 设置make生命周期内的环境变量
  * **全局使用**，其他makefile可以使用

## dir & notdir

取目录函数`dir`

* `$(dir <pathname>)`

```makefile
path=$(dir src/foo.c hacks)
# 取出所有路径 src/ ./
```

取文件名函数`notdir`

* `$(notdir <pathname>)`
* 整理所有目标源文件时实用，可以只保留需要的文件名

```makefile
obj=$(notdir src/foo.c hacks)
# 取出所有文件名 foo.c hacks
```

## suffix & basename

取后缀函数`suffix`

* `suffix <pathname>`

```makefile
suffix_name=$(suffix src/foo.c src-1.0/bar.c hacks)
# 后缀 .c .c
```

取前缀函数`basename`

* `$(basename <pathname>)`

```makefile
$(basename src/foo.c src-1.0/bar.c hacks)
# 前缀 src/foo src-1.0/bar hacks
```

## addsuffix & addprefix

加后缀函数`addsuffix`

* `$(addsuffix <pathname>)`

```makefile
$(addsuffix .c,foo bar)
# 加后缀 foo.c bar.c
```

加前缀函数`addprefix`

* `$(addprefix <pathname>)`

```makefile
$(addprefix src/,foo bar)
# 加前缀 src/foo src/bar
```

## join

连接函数`join`

* `$(join word1 word2, <file...>)`

```makefile
$(join aaa bbb, 111 222 333)
# 连接 aaa111 bbb222 333
```

## subst

字符串处理函数`subst` （根`patsubst`一样?）

* `$(subst FROM,TO,TEXT)`
* 讲`TEXT`中匹配`FROM`的东西变为`TO`

```makefile
$(subst a,the, There is a big tree)
#等同 var=There is a big tree $(var:a=the)
# $(patsubst a,the,There is a big tree)
```

## 特殊字符 $x

`$@`

* 表示**目标文件集**

`$^`

* 所有的**依赖文件的集合**
* `$+`类似，**不过不去除重复依赖**

`$<`

* 依赖中**第一个依赖名**
* **如果以`%`模式定义，则为依赖文件集（一个个取出来）**

`$?`

* 所有比目标新的依赖目标的集合

`$%`

* 仅当目标是**函数库文件时**，
  * **表示规则中的目标成员名**
* 如目标`foo.a(bar.o)`
  * `$%`为`bar.o`
  * `$@`为`foo.a`
* <font color="red">如目标不是函数库文件，`.a`(unix), `.lib`(win)。`$%`值为空</font>

## 隐含变量

`CFLAGS`

* 执行“CC”编译器的命令行参数(编译.c源文件的选项)。

`CC`

* c编译程序
* 默认cc

`CXX`

* c++编译程序
* 默认`g++`

`RM`

* 删除命令
* 默认`rm -f`