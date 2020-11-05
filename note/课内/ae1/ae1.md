# Requirements

每个 Web 服务器都定期记录从其他 Web 服务器和浏览器访问的日志

* each line
  * date
    * `dd/mm/yyyy`
  * hostname
    * 由**2-letter country code**结尾，如`uk/fr/com（3-letter）`。前面加上`.`
* hostname中最后一个token为
  * **TLD(top level domain)**

```txt
05/11/2018 www.intel.com
12/12/2018 www.dcs.gla.ac.uk
05/11/2019 www.mit.edu
31/12/2018 www.cms.rgu.ac.uk
25/12/2017 www.informatik.tum.de
01/04/2018 www.wiley.co.uk
01/01/2019 www.fiat.it
14/02/2018 www.valentine.com
```

一项新的欧盟法规要求我们按照国家追踪访问情况 track access by country，

**能够显示每个国家在[给定时间]段内的访问百分比**demonstrate the percentage of accesses from each country over given period

政客们已经允许**通过TLD追踪访问**以满足监管要求 tracking accesse by TLD

* given peroid of interest `01/12/2017` to `31/12/2018`
  * access tracking(不用按顺序) [百分比 TLD]
  * `33.33 com`
  * `16.67 de`
  * `50.00 uk`

```txt
05/11/2018 www.intel.com
12/12/2018 www.dcs.gla.ac.uk
05/11/2019 www.mit.edu
31/12/2018 www.cms.rgu.ac.uk
25/12/2017 www.informatik.tum.de
01/04/2018 www.wiley.co.uk
01/01/2019 www.fiat.it
14/02/2018 www.valentine.com
```

## Specification

给定

* given period
  * start date
  * end date
* 多个log文件（包含TLD tracking）

需要

* 确定给定period中
  * 每个TLD的访问百分比 **percentage of access from each TLD**
* 格式
  * `percentage TLD`记得乘100%，（最后乘精确）
  * **大小写不敏感**
    * `X.Y.UK` and `a.b.uk` **TLD相同**

## Design

给定源文件

* `tldmonitor.c`
  * `main`
* 头文件(abstract data type ADT)
  * `date.h`
  * `tldlist.h`

### date.h

`typedef struct date Date`

* `Date`代表`struct date`

---

`Date* date_create(char* datestr)`

* 根据`char* datestr`，创建`Date`类型
  * `datestr`需要符合`dd/mm/yyyy`格式
* <font color="red">使用`malloc()`为`Date`分配内存</font>
* 如创建成功，返回`Date*`指针
* 创建失败，返回`NULL`

`Date* date_duplicate(Date* d)`

* 创建`d`Date结构的拷贝
* <font color="red">使用`malloc()`为`Date`分配内存</font>
* 创建成功，返回`Date*`
* 创建失败，返回`NULL`

`int date_compare(Date* date1, Date* date2)`

* 比较两个`Date`
* `<0`
  * `date1<date2`
* `=0`
  * `date1=date2`
* `>0`
  * `date1>date2`

`void date_destroy(Date* d)`

* 销毁`Date* d`指向的`Date`结构
  * `free`在堆上分配的`Date`对象

### tldlist.h

#include "date.h"

`TLDList`
`TLDNode`
`TLDIterator`

---

`TLDList* tldlist_create(Date* begin, Date* end)`

* list结构
* 根据TLD strings，存储生成日志条目计数 counts of log entries
* `begin`&`end`筛选过滤首选日期
* 成功返回list指针，否则NULL

`void tldlist_destroy(TLDList* tld)`

* 清空`tld`遍历list结构
  * free

`int tldlist_add(TLDList* tld, char* hostname, Date* d)`

* 根据`hostname`添加TLD节点进tldlist
  * 如果传入的`d`符合list首选日期范围内
* 返回 `1`
  * 成功？，if the entry was counted
* `0`
  * 失败？

`long tldlist_count(TLDList* tld)`

* 返回自TLDList创建以来，`tldlist_add()`成功次数
* 返回TLDlist中，日志条目数量
  * number of log entries

`TLDIterator *tldlist_iter_create(TLDList* tld)`

* 创建iterator
* 成功，返回iterator指针
* 失败，`NULL`

`TLDNode* tldlist_iter_next(TLDIterator* iter)`

* 返回list中下一`TLDNode`元素
* 成功，返回`TLDNode*`
* 无元素，返回`NULL`

`void tldlist_iter_destroy(TLDIterator* iter)`

* 摧毁`iter`指针所指iterator结构
  * free

`char* tldnode_tldname(TLDNode* node)`

* 返回节点代表的TLD名称

`long tldnode_count(TLDNode* node)`

* 返回tld节点加入tldlist的次数
  * log entry

### tldmonitor.c

包括以上要用的头文件，用于test log files在实现的AVL上是否正常工作

* 使用
  * `./tldmonitor begin_date end_date [file]`
* workflow功能
  * 处理参数
  * 创建TLDList
  * 如果无file args
    * 处理stdin
  * 有file args
    * 打开file
    * 处理file
    * 关闭file
  * 创建TLDIterator
    * 如果iterator中有entry，打印其百分比和TLD
  * 清空TLDIterator
  * 清空TLDList中使用的其他东西
    * 节点，iterator之类的
  * 清空TLDList
* 静态func`process`
  * 处理特定log文件中所有log条目

## Implementation

实现`date.c`&`tldlist.c`

* 实现所有头文件中描述原型

`tldlist.c`两种实现，2选1【AVL】

* BST
* 根据 Adelson-Velskii and Landis algorithm算法建立AVL

不能出现内存泄漏

🍊 `tldlist.o`为`tldlist.c`的链表实现

* 可用于查看，测试`date.c`是否正常实现

🍊 用于输出log

```command
% ./tldmonitor 01/01/2017 01/09/2020 <small.txt | sort -n | diff - small.out
% ./tldmonitor 01/01/2017 01/09/2020 <large.txt | sort -n | diff - large.out
```