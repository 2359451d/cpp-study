# Lecture Note 6: CI

* [Lecture Note 6: CI](#lecture-note-6-ci)
  * [CI实践：continuous integration practices](#ci实践continuous-integration-practices)
  * [变更管理：Change Management](#变更管理change-management)
    * [集成频率：Integration Frequence](#集成频率integration-frequence)
  * [CI中的新特性分支选项:Feature branching options in CI](#ci中的新特性分支选项feature-branching-options-in-ci)
  * [维护多个 CI 进程: Maintaining Multiple CI Processes](#维护多个-ci-进程-maintaining-multiple-ci-processes)
  * [监控&维护软件质量：Monitor & Maintain Software Quality](#监控维护软件质量monitor--maintain-software-quality)
  * [部署环境：Staging Environments](#部署环境staging-environments)
  * [CI环境：CI Environments](#ci环境ci-environments)
  * [CI环境工作流程：CI Environment Workflow](#ci环境工作流程ci-environment-workflow)
  * [管理可见性 & 度量指标：Maintaining Visibility & Metrics](#管理可见性--度量指标maintaining-visibility--metrics)
    * [CI Gitlab Metrics](#ci-gitlab-metrics)
  * [Fast build are essential](#fast-build-are-essential)
  * [Advanced topics](#advanced-topics)
  * [Summary](#summary)

## CI实践：continuous integration practices

![](/static/2020-11-17-22-04-41.png)

* **change management 变更管理实践**
  * 维护一个原repo
  * 每个人**每天**向mainline提交
    * mainline- master branch, trunk
  * 每次提交都在集成机器上构建 mainline
  * 每个人能看见发生什么
    * make transparency in single source repo
* **quality assurance CI质量保证实践**
  * 自动化构建
  * 自动测试构建
    * 有unit-test suite， 针对每个commit都能执行
  * 测试在生产环境的克隆版本中进行
  * 保证构建快速
    * within 10min
* **deployment 部署实践**
  * 保证每个人能获取最新可执行文件
    * build should be automatically & accessble by anyone who wanted
  * **自动部署**
    * make it part of the pipeline

## 变更管理：Change Management

### 集成频率：Integration Frequence

![](/static/2020-11-17-22-11-43.png)

* **late integration strategy**
  * developers work on each branch, implementing the new features within a sprint
  * at the end of the sprint, the developers submit a change to master to re-integrated
  * 更改提交可能是同时发生的，造成冲突。因此迭代的结束，团队可能需要花时间合并
* 纵坐标表示 branch&master的差异

![](/static/2020-11-17-22-11-58.png)

* small integration to trunk
* change be integrated much more frequently(at least 1 day)
  * small tasks finished, immediately commit to the master

## CI中的新特性分支选项:Feature branching options in CI

![](/static/2020-11-17-22-12-27.png)

* option1-在主干上实现新的特性，频繁地提交一些小的更改
* 在分支中实现新特性，并经常合并主干trunk中的更改
  * merge change from master frequently
* **将特性作为一个原型分支**，然后以一些小的变化中在主干上重新实现这个特性
  * **rather than merging from the prototype branch to trunk directly**
  * useful to evaluate /explore the development of a **high risk feature**
* 将**特性**作为一个**永久的分支**来实现
  * create a **folk** of the repo
  * as seperate trunk alternative provided to customers or maintain similar code base within its parent project

## 维护多个 CI 进程: Maintaining Multiple CI Processes

![](/static/2020-11-17-22-14-58.png)

假设每个repo，project的CI都是独立的。但有情况需要一起管理不同分支上的CI

* 主干线开发
* 为特定客户或目的而进行fork开发
* 只接收缺陷修复的最新稳定版本
* 重要特性分支
  * 避免defects in branch before integrated into master

## 监控&维护软件质量：Monitor & Maintain Software Quality

![](/static/2020-11-17-22-29-19.png)

* process to maintain software quality to 检测破损的构建builds
  * 应该在生产环境的源代码克隆中编译系统
  * 应该在整个系统上执行一套自动化的回归测试
  * 应该执行适当的静态分析检查(例如代码样式的符合性) ，并与基准进行比较

🍬 如果以上步骤fails，builds可看为损坏的

🍬 选项1-避免损坏的公共builds
![](/static/2020-11-17-22-31-43.png)

1. clone & checking the branch
2. change made to code
3. private(testing) build
   1. compilation of the code
   2. running unit-test
   3. running appropriate analysis check
   4. 如果失败，回到2，重新测试
4. 如果build成功，merge to mainline
5. 进行public build,（testing步骤与3相同）
   1. pass
   2. fail回到2

🍬 选项2-避免**分支**中损坏的构建
![](/static/2020-11-17-22-32-28.png)

* 有些团队使用feature branching, 并对每个分支应用CIpipeline
  * 对比上面选项1描述的步骤，需要**额外步骤**
* develop a feature in branch
* merge the change from the trunk **into the branch**
  * perform a successful build on **branch**
* merge the change to the branch **into the trunk**
  * perform a successful build on **trunk**

🍬 尽管可以减少broken builds的数量

* **缺点**
  * 增加提交的频率
  * 每个commit的大小变大
    * 这是因为集成一个新特性需要花费大量的精力，这使得频繁地执行这个commit变得不那么有吸引力

## 部署环境：Staging Environments

![](/static/2020-11-17-22-59-28.png)

change to software, need to be checked before release to wider user base

* 保证任何change不会引入额外的defects
* 会使用**staging platform/environment**，用于配置/复制软件当前环境
  * 用于在投入使用前，测试软件
  * 根据当前硬件&依赖配置
* 有时候需要配置多个staging environment（不同分布式平台）
  * 因此软件component需要能在每个平台执行
* 环境也需要能够测试

配置环境的局限性 - 不是总能为相同生产配置环境

* 系统分布在太多的计算节点上，以测试真实的场景
  * **too large to replicate** on too many computing nodes
* **该系统将在太多不同的平台配置上使用，以至于无法全部测试**
* 该系统将有太多的同时用户
* 有太多不同类型的用户需要测试
* 只有一个平台的软件是可用的，
* 生产软件依赖项，
  * 如网络端点和数据集不能从生产**外部访问**（数据集出于安全，可信度原因不允许外部访问）

## CI环境：CI Environments

![](/static/2020-11-17-23-01-35.png)

实际上，CI pipeline配置&执行由CI环境管理

* 每个环境被配置用于执行pipeline或job
  * **每次commit**，都会执行。或**调度周期执行**

## CI环境工作流程：CI Environment Workflow

![](/static/2020-11-17-23-02-03.png)

workflow of a CI environment for a typical job or pipeline（执行某特定job/pipeline的CI环境例子）

1. 检查repo代码
   1. 来源于schedule build or new commit的代码
2. Build（compilation）
3. 产生**build report**
   1. 反应构建成功or失败
4. 假如build成功，对build中编译后的代码，
   1. 应用**unit & integration test**
   2. 产生**test report**
   3. 产生最新的可执行文件，latest executble【**注意某些CI环境可能会先执行test，在生成可执行文件，避免生成不通过测试的可执行文件**】

## 管理可见性 & 度量指标：Maintaining Visibility & Metrics

![](/static/2020-11-17-23-02-33.png)

维护可见性 - **发送项目进展信息的常用方式↓**

* 推送通知，如短信或电子邮件
* 广播机制，例如在开发区域的大屏幕显示上显示**状态监视器**

有用的维护度量标准【可以包含在上述通知方式中的信息】

* static analysis - 不成功的构建的数量
  * 测量项目失败构建的频率
* 平均不成功的测试
  * 可以用来估计**实现新特性会引入缺陷至项目的比例**
* **Time** to build
  * 监视CI过程保持可行的时间长短
  * 构建耗时过长，会阻止开发人员进行频繁提交

### CI Gitlab Metrics

![](/static/2020-11-17-23-12-22.png)

gitlab CI pipeline

## Fast build are essential

2 reasons

* **delays of completing the build would also delay discovering any problems 构建过慢可能导致难以发现存在的问题**
  * developers would continue working while build is still in progress without realise the broken build **开发者会没察觉到build已经失败的情况下继续开发**
* deter from make frequent commit **阻止开发者进行频繁commit**
  * 因为在提交后续进展之前，可能需要等待先前commit的构建结果

🍬 推荐的max构建时间 - 10min

* 项目规模变大，很难保证构建时间，**需要一些妥协performing & complete the build**

🍬 不同妥协形式

* 重配置build过程
  * 保证构建中没有不必要的步骤
  * 可以进行优化（但这并不会降低以前质量检查的严格性）
* 针对项目不同部分，配置多种不同builds
  * 对于published & public API没影响的change变更，可能只需要进行subsystem的build
* 使用策略，对test case进行优先化
  * partition to different categories of builds **将不同测试用例分给不同build**
  * 测试用例的选择需要妥协效率
* 将大项目划分成小的可并行组成partition larger projects into smaller well-defined components that can be developed concurrently
  * 小组成可为大项目的依赖
  * 当有变更change时，只有被影响的组成需要被构建&测试

## Advanced topics

CD

* continuours deployment
* 自动集成项目 & 自动部署给user
* 部署的风险降低了，因为部署过程是自动化的
* 也可能包含一个回滚rollback新部署的自动化过程
* 同时将为不同用户集提供项目，特性的变体成为可能
  * 可应用AB测试

chaos engineering

* 在软件系统中引入defects/failures
  * 为了确认软件能应对这些failures的程度

## Summary

![](/static/2020-11-17-23-13-16.png)

Ci实践最大限度地减少了对**软件系统的快速并发更改**所造成的干扰

