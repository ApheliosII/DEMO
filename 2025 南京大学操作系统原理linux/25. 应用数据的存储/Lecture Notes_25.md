# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

[PPT](https://jyywiki.cn/OS/2025/lect25.md)

---
## 25. 应用数据的存储
操作系统为我们的应用程序提供了多种持久化控制的机制，包括 fsync 系列 API。在此基础上，我们可以在应用程序中实现更为可靠、更为可用的数据存储方法。

**本讲内容**：数据库系统的设计原理与实现技术。

```bash
../../mosaic/mosaic.py -c file-write.py | ../../mosaic/collect.py
```

## Review & Comments
**上次视频翻车了**
**持久数据的可靠性**
- RAID 和云存储系统

**崩溃一致性**
- 数据结构的 multi-write 在崩溃时导致不一致状态
- 通过 flush 机制和 journaling 实现崩溃一致性

---
**文件系统 API 到此结束**
**文件 (数据 & 元数据) 管理**
- open, read, write, close, stat, chmod, chown, fsetxattr/fgetxattr, ftruncate, ...

**目录树管理**
- mount, mkdir, readdir, link, symlink, unlink, rename, chdir, ...

**一致性管理**
- sync > syncfs > fsync > fdatasync

**其他相关的操作系统 API**
- flock, mmap, ...

```bash
a.txt.new()
# rm a.txt # linux不需要rm,会crash, 目录结构更重要，原数据写入优先
rename a.txt.new a.txt
```

---
**暗藏杀机的系统调用**
**复杂数据结构都涉及 multiple writes**
```c
write(fd, buf, 4096); // append
```
- 分配数据块: bwrite(d-bitmap)
- 写入数据块: bwrite(data)
- 更新 size, time, index, ...: bwrite(inode)

```bash
cd ~/.ssh
ls -l
cat id_rsa.pub

man 2 sync

time sync
touch ~/a.txt; time sync
```

```bash
tree .git | less
```

---
## 25.1 关系代数、SQL 和数据库 🌶️
**什么是 “应用程序”？**
> 软件是物理世界过程在信息世界中的投影。

- 软件天生有 persist data 的需求
    - 个人信息 (学籍……)
    - 订单
    - 日志 (支付记录、维护记录……)
    - ……
- 让我们 “重新实现” 教务系统吧！
    - 先让我们去 ehall.nju.edu.cn 看一眼

**保存应用数据 (1)**
**在文件 (虚拟磁盘) 上构建数据结构**
- 就像 ELF, BMP, ...
```c
struct superblock {
    struct student *s;
    struct course *c; 
}
struct student { char stuid[16]; ...  };
struct course  { char cid[16]; ...  }
```
- 需求：expel(s); enroll(s, c); ...
    - 应用系统实现翻译成 read, write, lseek 系统调用
    - (也可以 mmap/msync)

**典型的应用数据结构**
**游戏是一个状态机 (Everything is a state machine)**

回放工具：BWChart

**保存应用数据 (2)**
**利用目录树**
- UNIX 世界中的工具都能用了：find, grep, ...
    - 如何关联学生和选课/成绩？Copy? Symlink?
    - 如何实现并发访问 (和 crash) 的 consistency?
> M7 HTTP

个人/团队-->国民级

**我们需要的到底是什么？**
**Concurrency (Parallelism)**
- 全校一起选课，系统不能崩 (不能一把大锁保平安)

**Persistence (Crash Consistent)**
- 系统故障，数据不能丢

**Atomicity 😊**
```c
enroll_list = random_enroll()
with AllOrNothing():
    for id in enroll_list:
        Path(f'enrollment/{id}.md').write_text('y')
    ...
```
`man 2 flock`

**Relational Database (关系型数据库)**
**一个 surprisingly simple 的模型**
- A relational model of data for large shared data banks
    - Edgar F. Codd: 1981 Turing Award Winner
    - “Future users of large data banks must be protected from having to know how the data is organized in the machine.”
        - 我做了很多年 program synthesis; 但凡是 end-user 的，最后的设计理念都会回到这一篇 paper
- Everything is a table
    - 每行一个对象；对象可以用 id 索引其他对象

**关系数据库模型**
**“对象和指针”**

**关系数据库查询：指针 “配对”**
```sql
SELECT Courses.Title
FROM Student 
JOIN Takes_Course
    ON Student.ID = Takes_Course.ID  -- Key
JOIN Courses
    ON Takes_Course.ClassID = Courses.ClassID  -- Key
WHERE Student.Name LIKE '张%'
```

- [ ] JOIN

- [ ] DBA 数据库管理员

**数据库系统开启软件的新时代**
**“ACID” 数据库**
- A (Atomicity), C (Consistency), I (Isolation), D (Durability)
    - Strong serializability: 查询结果 “按照某种顺序完成”
    - Strong crash consistency: 系统 crash 也不会损坏或丢失

**支持任意长 (允许混合任意计算) 的 Transaction**
- 这个特性太重要了
```sql
tx_begin();
if (user1.balance < m) tx_abort();  // SQL
user1.balance -= m;  // SQL
user2.balance += m;  // SQL
tx_commit();
```

**ACID 数据库**
**学过《操作系统》就很好理解了**
- 一把大锁保平安的效果
- 大规模并行执行的性能
- 完全自动的崩溃回复
    - 应用数据交给数据库 = 一劳永逸; 甚至还可以 Hack

**关系数据库：海量的实现优化**
- 查询优化 (rewriting)
- 连接索引 (B+ Tree)
- 缓存、分库分表、并发控制、读写分离……
    - 只要不是大到 “国民级” 的应用，数据库都能搞定

---
## 25.2 关系数据库：实现 🌶
**Databases v.s. Compilers**
**实现查询 = 实现编译优化 (语义等价的 rewriting)**

**一个超级复杂的并发程序**
**每个 SQL 都操作数据库的一部分**

**例子：SQLite**
- Android, iOS, macOS, Chrome, ... 中广泛内嵌了 SQLite
    - Zero Configuration (发行版自带 libsqlite3.so；适合 “年轻人的第一个应用”)

---
## Prompt: 为什么关系型数据库不能 scale 到国民级体量的应用？
关系型数据库难以扩展到国民级体量，主要原因包括：

1. 水平扩展困难：关系型数据库天然以一致性（ACID）为核心，数据分表分库（sharding）和跨节点事务实现复杂，导致很难进行高效的横向扩展。
2. 性能瓶颈：随着数据量和并发用户数剧增，单机数据库在CPU、内存、磁盘和网络等资源上面临瓶颈，查询和写入速度下降。
3. 高可用与容灾复杂：大规模分布式环境下，保证数据一致性、故障自动恢复和多点写入的复杂性极高。
4. 成本高昂：用昂贵的高性能服务器来叠加关系型数据库的能力，成本远高于典型分布式NoSQL解决方案。

所以，国民级大规模应用通常采用分布式NoSQL数据库或混合架构，以获得更好的扩展性和高可用性。

---
## 25.3 不用关系的数据库 🌶
**SQL → NoSQL (NewSQL)**

**如果要实现 “国民级” 的应用？**
**“透明” 的 SQL 就有些困难了**
```sql
SELECT *
FROM chat_records
WHERE (sender_id = @user_id1 AND receiver_id = @user_id2)
   OR (sender_id = @user_id2 AND receiver_id = @user_id1)
ORDER BY timestamp DESC
LIMIT 10
```
- 正确，但压力给到数据库引擎
    - 分库、分表、读写分离、索引、缓存、优化……
- **永远无法预知程序员会写出怎样的 query**
    - 提供了功能 = 被滥用 → Performance Bug
    - 任何 “Systems” 都无法避免的 tech debt
        - 例子：fork()

**解决办法：做减法**
**更少的能力，更好的性能、更高的扩展性**
- Key/Value
    - 简单、高效 (缓存、计数器、队列)
- Document (JSON/XML/...)
    - NoSQL 实现 “国民级” 应用的主力
- Graph
- Column

**AI 时代**
- Vector 💡

**Key-Value Store**
**这个就好 scale 多了！**
- 给 key 做个 hash
- 扔到对应的 (多台机器) 上
    - Append-only 写到 log
    - 分布式高可靠就完成了 (甚至可以不 persist)

**应用程序：全靠 key 管理数据**
- user:{uid}
- user:{uid}:like_history (a list)
    - List 支持 append/pop/range 等操作
    - 应用场景：🍠 上的点赞/浏览/历史记录

**Redis: Everything is In-memory**
****Key-value**
GET, SET

**数据结构**
String, JSON, List, Set, Hash, Sorted Set, ..., Stream

**Query**
FT.SEARCH products "@price:[200 300] @category:misc"

**Transactions**
MULTI/WATCH/EXEC (也支持持久化)

**持久化：NoSQL**
**提供 SQL 的一个子集**

---
## 25.4 总结
　　***Take-away Messages***: 在操作系统为我们提供的文件、目录、网络 API 上，开发者可以自由地创建更多、更复杂、更可靠的系统。我们看到了关系数据库的兴起，看到了云计算时代下 NoSQL 的繁荣，和今天的 AI 时代——在这几波浪潮之间，虽然操作系统内核的实现发生了巨大的变化，但操作系统的 API 相当惊人地稳定，这种 “稳定性” 支撑了应用生态的繁荣，这也是操作系统作为 “平台” 的使命。