# example makefile

src=$(wildcard *.c ./sub/*.c) # 展开./目录 & ./sub/目录下 所有后缀为 .c的文件

# 如找到当前目录下及当前目录子目录inc/中所有.c文件 
#src= $(wildcard *.c) $(wildcard inc/*.c)

dir=$(notdir $(src)) # 把src变量展开文件的路径信息全部去除
obj=$(patsubst %.c,%.o,$(dir)) # 把dir变量中符合.c后缀的文件全替换成.o
#等同于 obj=$(dir:%.c=%.o) 都为文本匹配替换

#syntax $(patsubst <pattern>,<replacement>,<text> ) 
# syntax $(var:a=b) 替换变量var中所有“a”结尾(空格之前)的字为“b”结尾(空格之前，空格分隔多个变量)
#foo=a.o b.o c.o
#bar=$(foo:.o=.c)