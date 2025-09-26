# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

---
==由于学习进度慢,后面只注意重点内容。==

[PPT](https://jyywiki.cn/OS/2025/lect16.md)

```makefile
# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib
```

## 16.1 信号量
### 计数型的同类资源：实现同步
```c
void enter_parking() {
    mutex_lock(&lk);
    while (!(in_parking < capacity)) {
        cond_wait(&cv, &lk);
    }
    in_parking++;  // 这个时候我已经 “进入” 了
    mutex_unlock(&lk);
}

void leave_parking() {
    mutex_lock(&lk);
    in_parking--;
    cond_broadcast(&cv);  // 退出以后，可能有人能进入
    mutex_unlock(&lk);
}
```
- 这是生产者-消费者呀
    - 确保进入前存在一个 “空位” (count < capacity) 就行

---
### 计数型的同类资源：实现同步另一种方法
```c
void consume_parking() {  // enter_parking
    mutex_lock(&lk);
    while (!(parking_spot > 0)) {
        cond_wait(&cv, &lk);
    }
    count--;
    mutex_unlock(&lk);
}

void magic_parking() {  // leave_parking
    mutex_lock(&lk);
    parking_spot++;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
}
```
- “空位” 和 “占用” 是相对的
    - 停车 = “吃掉” 车位；离开 = “创造” 车位 (允许凭空创造)

---
### 于是你发明了 “信号量”！
```c
void P(sem_t *sem) {
    // Prolaag - try + decrease/down/wait/acquire
    mutex_lock(&sem->lk);
    while (!(sem->count > 0)) {
        cond_wait(&sem->cv, &sem->lk);
    }
    sem->count--;  // 消耗一个信号 (车位/手环/...)
    mutex_unlock(&sem->lk);
}

void V(sem_t *sem) {
    // Verhoog - increase/up/post/signal/release
    mutex_lock(&sem->lk);
    sem->count++;  // 创建一个信号 (车位/手环/...)
    cond_broadcast(&sem->cv);
    mutex_unlock(&sem->lk);
}
```

---
### 我们可以把信号量当互斥锁用
```c
sem_t sem = SEM_INIT(1);

void lock() {
    P(&sem);
}

void unlock() {
    V(&sem);
}
```
- 回到了我们开头的代码
    - 允许在不同的线程的 release/acquire
    - “信号量是扩展的互斥锁”

---
> **用互斥锁实现同步**：通过用一个线程等待一个已经被其他线程持有的互斥锁——再由另一个线程释放，我们能用互斥锁实现 happens-before。当然，这个 hack 是 undefined behavior，只作课堂展示，不能在生产环境使用。

> **使用互斥锁实现计算图**：通过在一个线程获得互斥锁，在另一个线程释放，我们能实现 “计算图” 的计算。在这里，每条边上的互斥锁充当了一单位的 “许可”，release 和 acquire 形成了代表同步的 happens-before 关系。

```bash
# gragh
# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

./graph
# Start 1
# End 1
# Start 2
# End 2
# Start 3
# Start 5
# Start 4
# End 3
# End 5
# End 4
# Start 6
# Start 7
# End 6
# End 7
```

## 16.2 用 “互斥” 实现同步
---
### 信号量的两种典型应用
**1. 实现一次临时的 happens-before: $A \rightarrow B$**

- $ A \rightarrow V(s) \rightarrow P(s) \rightarrow B$
    - 这就是刚才的 “互斥锁实现同步”

**2. 管理计数型资源**
- 游泳池里的人不能超过 n 个
- 停车场只有 n 个车位
- 餐厅只有 n 桌
    - 当然，可以分成大桌、中桌、小桌

---
### 例子：优雅地实现生产者-消费者
```c
sem_t empty = SEM_INIT(depth);
sem_t fill = SEM_INIT(0);

void T_produce() {
    P(&empty);
    printf("(");
    V(&fill);
}

void T_consume() {
    P(&fill);
    printf(")");
    V(&empty);
}
```
- 从 empty 袋子里拿球 $ \rightarrow $  produce (然后把球放到 fill)
- 从 fill 袋子里拿球 $ \rightarrow $ consume (然后把球放回 empty)

---
> **使用信号量实现线程 join**：我们既可以用一个信号量实现一次临时的 happens-before，也可以用一个计数型信号量等待数量正确的线程结束。

```bash
./join-1
Thread 1 start.
Thread 3 start.
Thread 4 start.
Thread 2 start.
Thread 1 end.
Thread 4 end.
Thread 3 end.
Thread 2 end.
Workers joined.

Thread 1 start.
Thread 2 start.
Thread 3 start.
Thread 4 start.
Thread 3 end.
Thread 2 end.
Thread 1 end.
Thread 4 end.
Workers joined.

### 
./join-2
Thread 2 start.
Thread 4 start.
Thread 1 start.
Thread 3 start.
Thread 2 end.
Thread 1 end.
Thread 3 end.
Thread 4 end.
Workers joined.
```

> **使用信号量实现生产者-消费者问题**：信号量给了生产者-消费者问题一个非常精巧的实验，生产者把球从 empty 口袋取走，push 之后把球放入 filled 口袋；消费者则恰好相反。整个系统满足 empty + filled + 正在打印的线程 = 缓冲区大小的全局约束。

```bash
# pc-sem
./pc 1
./pc 2
```

---
## 16.3 信号量、条件变量与同步
### 信号量 v.s. 条件变量
**信号量**
- 干净、优雅，完美地解决了生产者-消费者问题
- 但 “count” 不总是能很好地代表同步条件

**条件变量**
- 万能：适用于任何同步条件
- 丑陋：代码总感里有什么脏东西 (spin loop)

```java
synchronized (obj) {  // reads better in Java
    while (!cond) {
        obj.wait();
    }
    ...
}
```

---
### 让我们上一点难度
**Fish**
- $T_a$ 打印 `<`, $T_b$ 打印 `>`, $T_c$ 打印 `_`
- 保证打印出 `<><_` 和 `><>_` 的序列？

**一个小困难**
- 假设刚打印完一条完整的鱼
    - `<><_` 或 `><>_`
- `<` 和 `>` 都是可行的
    - 信号量似乎不太好表达 “二选一”
    - 除非手动构建 happens-before

---
### 面对更复杂的同步问题……
**哲 ♂ 学家吃饭问题 (E. W. Dijkstra, 1960)**
- 哲学家 (线程) 有时思考，有时吃饭
- 吃饭需要同时得到左手和右手的叉子

---
### 尝试
**条件变量**
- 同步条件：`avail[lhs] && avail[rhs]`
- 背模板即可
    - (期末考试 100% 会考，这就是通关密码)

**信号量**
- `P(&sem[lhs]) && P(&sem[rhs])`
- 看起来没什么问题？
    - 当互斥锁用就行了

---
> **哲学家吃饭问题**：通过一个额外的信号量，我们限制上桌吃饭的人数不超过 4 人。上桌的 4 人之中至少有一人可以获得左右手的叉子，然后释放后退出临界区。这个协议的正确性并不是显然的：我们必须非常小心地对待任何并发问题。

```bash
# philosopher
./philosopher
+ 0 by T1
+ 1 by T2
+ 2 by T3
+ 4 by T5
+ 3 by T4
死锁！

```
---
### 成功的尝试：信号量
**如果 5 个哲学家同时举起左手的叉子……**
- 我们需要禁止这件事发生

**Workaround 1: 从桌子上赶走一
个人**
- 直观理解：大家先从桌上退出
    - 袋子里有 4 张卡
    - 拿到卡的可以上桌吃饭 (拿叉子)
    - 吃完以后把卡归还到袋子

**Workaround 2: Lock Ordering
- 给叉子编号，总是先拿编号小的**

```c
        // Come to table
        P(&table);

        // Leave table
        V(&table);
```
```bash
# philosopher
./philosopher

    if (lhs > rhs) {
        int tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
```
---
### 不！这不 “成功”
**信号量不总是 “优雅”**
- Systems 要的是 absolutely correct 的方案
- 数值型资源不总是能很好地代表同步条件

---
### 用信号量实现条件变量 🌶️
> Implementing condition variables out of a simple primitive like semaphores is surprisingly tricky. (from a [2003 report](http://birrell.org/andrew/papers/ImplementingCVs.pdf))
```c
void wait(cond_t *cv, mutex_t *mutex) {
    atomic_inc(&cv->nwait);
    mutex_unlock(mutex);
    P(&cv->sleep);
    mutex_lock(mutex);
}

void broadcast(cond_t *cv) {
    mutex_lock(&cv->lock);
    for (int i = 0; i < cv->nwait; i++)
        V(&cv->sleep);
    cv->nwait = 0;
    mutex_unlock(&cv->lock);
}
```
- <b style="color:#4169E1;">唤醒丢失</b>: 一个 “早就 wait 但没有 P” 的线程会抢走唤醒

---
### 实现困难的本质原因 🌶️
**先释放锁，再执行 P**
- 释放锁的一瞬间可能与 broadcast 并发

**先执行 P，再释放锁**
- `P(&cv->sleep)` 会 “永久睡眠”

**那怎么办 😂**
- Release-wait 必须实现成 “不可分割的原子操作”
- - 解决不了，问操作系统吧 (实际实现靠得是 futex)
- 信号量：<b style="color:#4169E1;">在合适的时候好用；但不总是好用</b>

> **使用信号量实现条件变量**：在这个失败的尝试中，我们发现条件变量的 wait 中的 “释放锁并睡眠” 需要被实现成一个原子操作 (例如，用自旋实现)，但这一点并不容易用信号量实现——条件变量虽然看起来更 “笨拙”，却捕捉了同步条件的本质，因此也比信号量更为通用。

---
## 16.4 总结
　　***Take-away Messages***: 信号量可以看做是互斥锁的一个 “推广”，可以理解成游泳馆的手环、停车场的车位、餐厅的桌子和袋子里的球，通过计数的方式实现同步——在符合这个抽象时，使用信号量能够带来优雅的代码。但信号量不是万能的——理解线程同步的条件才是真正至关重要的。