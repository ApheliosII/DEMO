# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

## 7. 访问操作系统对象
我们已经知道，进程从 `execve` 后的初始状态开始，可以通过 `mmap` 改变自己的地址空间，通过 `fork` 创建新的进程，再通过 `execve` 执行新的程序——我们慢慢已经开始理解 “操作系统上的应用生态“ 并没有魔法了。

**本讲内容**：操作系统还必须给应用程序提供访问操作系统对象的机制。当然，我们可以直接以 API 的形式提供，例如 Win32 API 包含 “RegOpenKeyEx” 访问注册表。这节课我们学习 UNIX 的 “Everything is a file” 带来的方便 (和不便)。

### Review & Comments
> testkit: Writing test cases fearlessly! 这是同学们的第一个测试框架：支持单元测试和系统测试，自动注册测试用例并在程序退出后运行。最重要的特点是它使用简单：你只需要包含 testkit.h，并且链接 testkit.c 即可。

---

### 昨天很热门的 (反转) 事件

**高校教师的经典三输局面**
- 忽悠了国家的科研经费，压榨了学生，人还猝死了 😭
    - 在座各位才是破局之人

---

### TestKit Bug
**SystemTest...**
- atexit() handler run_all_tests()
    - fork() 后 System Test 执行 exit()
    - 退出了 😂 后续的测试代码都不执行了

<b style="color:#4169E1">未测代码永远是错的 </b>
- 感谢何棋同学指出

---

### 怎么修复？
**明确需求**
- 我们需要一个<b style="color:#4169E1">状态 </b> (Everything is a state machine)
    - <b style="color:#4169E1">tests 里有全部测试用例且程序还没结束 </b>
- 需要遵守 libc 的约定
    - tk_add_test 和 tk_register_hook 执行顺序<b style="color:#4169E1">不确定 </b>
    - System test 里还可能调用 atexit()

**解决问题**
- tk_register_hook 时立即创建一个进程
    - 等程序 atexit() 的时候把 tests 送过来
    - 程序之间交换数据：“serialization”

---

### 更好的工程实现
**我们的做法：利用编程语言机制 hack**
- 并不是好的 practice (但有时候需要)
**方法一：请开发者主动调用 API**
- 在 main 里 run_all_tests()
**方法二：提供一个特别的编译器**
- JavaScript: 这个我懂 😂
**方法三：更好的编程语言**
- JVMTI: Tool Interface

---

### 操作系统中的对象
**进程**
- 进程 = 状态机
- 进程管理 API: fork, execve, exit

**连续的内存段**
- 我们可以把 “连续的内存段” 看作一个对象
    - 可以在进程间共享
    - 也可以映射文件

内存管理 API: mmap, munmap, mprotect, msync
**操作系统肯定还有其他对象的！**

---

## 7.1 文件描述符
> 文件描述符：文件描述符是指向操作系统对象的 “指针”——系统调用通过这个指针 (fd) 确定进程希望访问操作系统中的哪个对象。我们有 open, close, read/write, lseek, dup 管理文件描述符。

---

### 文件和设备
**文件：有 “名字” 的数据对象**
- 字节流 (终端，random)
- 字节序列 (普通文件)

**文件描述符**
- <b style="color:#4169E1">指向操作系统对象的 “指针” </b>
    - Everything is a file
    - 通过指针可以访问 “一切”
- 对象的访问都需要指针
    - open, close, read/write (解引用), lseek (指针内赋值/运算), dup (指针间赋值)

```bash
ll /dev/null
# crw-rw-rw- 1 root root 1, 3 Sep  1 17:10 /dev/null
ll /dev/urandom
# crw-rw-rw- 1 root root 1, 9 Sep  1 17:10 /dev/urandom
# c 字符设备，r 只读，w 只写，rw 读写
touch /tmp/a.c # 创建文件
ll /tmp/a.c # 查看文件信息
# -rw-rw-r-- 1 hhu hhu 0 Sep  2 06:15 /tmp/a.c

cat /dev/urandom
cat /dev/urandom | head -c 10 | hexdump -C # 随机生成 10 字节数据并以十六进制显示 -C 的输出包含​​偏移量、十六进制字节值及其对应的ASCII字符​​，非常便于人工阅读和比较

rm /tmp/a.c # 删除文件
```
```bash
man 2 read
```

```text
read(fd, from = 128, count = 400)
fd = open("a.txt") # fd指针 指向 a.txt
```

---

### 文件描述符：访问文件的 “指针”
- open
    - p = malloc(sizeof(FileDescriptor));
- close
    - delete(p);
- read/write
    - *(p.data++);
- lseek
    - p.data += offset;
- dup
    - q = p;

==deepseek:???==

```bash
ps
# PID TTY          TIME CMD
# 819 pts/2    00:00:00 bash
# 982 pts/2    00:00:00 ps
ls -l /proc/819/fd
# 0 -> /dev/pts/2
# 1 -> /dev/pts/2
# 2 -> /dev/pts/2

man 2 dup # dup 和 dup2 是 Linux 系统调用中用于复制文件描述符的函数
```

---

### 文件描述符的分配
**总是分配最小的未使用描述符**
- 0, 1, 2 是标准输入、输出和错误
- 新打开的文件从 3 开始分配
    - 文件描述符是进程文件描述符表的索引
    - 关闭文件后，该描述符号可以被重新分配

**进程能打开多少文件？**
- ulimit -n (进程限制)
- sysctl fs.file-max (系统限制)

```bash
ulimit -n
# 1048576
sysctl fs.file-max
# fs.file-max = 9223372036854775807
```

---

### 文件描述符中的 offset
**文件描述符是 “进程状态的” 的一部分**
- 存在操作系统中；程序只能通过整数编号访问
- 文件描述符自带一个 offset

**Quiz: fork() 和 dup() 之后，文件描述符共享 offset 吗？**
- 这就是 fork() 看似优雅，实际复杂的地方

```bash
man 2 write
# ssize_t write(int fd, const void *buf, size_t count);

./fd-offset
# Content of sample.txt: AB
# Content of sample.txt after fork: DC
```

---

### Windows 中的文件描述符
**Handle (把手；握把；把柄)**
- 比 file descriptor 更像 “指针”
- 你有一个 “handle” 在我手上，我就可以更好地控制你

---

### 句柄 (柄 = 握把)
D.Gries著《Compiler Construction for Digital Computer》(Wiley,1971年) 定义2.3.10 
(2.3.10) A handle of any sentential form is a leftmost simple phraser.

仲萃豪中译本(科学出版社，1976年)
(2.3.10)定义，任一句型的**句柄**就是此句型的最左简单短语。

---

### Windows 的进程创建
**面向工程的设计**
- 默认 handle 是<b style="color:#4169E1">不继承</b>的 (和 UNIX 默认继承相反)
    - 可以在创建时设置 bInheritHandles，或者运行时修改
    - “最小权限原则”
- lpStartupInfo 用于配置 stdin, stdout, stderr

**Linux 引入了 O_CLOEXEC**
- fcntl(fd, F_SETFD, FD_CLOEXEC)

---

## 7.2 访问操作系统中的对象
>UNIX 管道：UNIX 管道 (pipe) 是一种典型的进程间通信机制，允许数据在不同的进程之间单向流动。管道可以被视为一种特殊的文件，其中一个进程将数据写入管道的一端，而另一个进程从另一端读取数据。

---

```bash
ls
# bin dev lib opt sbin srv ...
ag: what are they?
```

---

### 操作系统里都有什么文件？
**Filesystem Hierarchy Standard [FHS](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html)**
- enables *software and user* to predict the location of installed files and directories: 例如 macOS 就不遵循 FHS

---

### 冷知识
**只要拷对了文件，操作系统就能正常执行啦！**
1. 创建 UEFI 分区，并复制正确的 Loader
2. 创建文件系统
    - mkfs (格式化)
3. cp -ar 把文件正确复制 (保留权限)
    - 注意 fstab 里的 UUID
    - 你就得到了一个可以正常启动的系统盘！
4. 运行时挂载必要的其他文件系统
    - 磁盘上的 /dev, /proc, ... 都是空的
    - mount -t proc proc /mount/point 可以 “创建” procfs

```bash
cd /proc
ls
```

---

### 任何 “可读写” 的东西都可以是文件
**真实的设备**
- /dev/sda
- /dev/tty

**虚拟的设备 (文件)**
- /dev/urandom (随机数), /dev/null (黑洞), ...
    - 它们并没有实际的 “文件”
    - 操作系统为它们实现了特别的 read 和 write 操作
        - [/drivers/char/mem.c](https://elixir.bootlin.com/linux/v6.14-rc5/source/drivers/char/mem.c#L430)
        - 甚至可以通过 /sys/class/backlight 控制屏幕亮度
- procfs 也是用类似的方式实现的

```bash
cd /sys/class/backlight # 屏幕亮度
ls

/proc/1/status

/proc/fs

cd /tmp
mkdir proc
cd proc/
ls
pwd

sudo su # 1. 切换到 root 用户
# rootajyy-usb:/tmp/proc# 
    mount -t proc proc . == mount -t proc proc /tmp/proc # 2. 将 proc 文件系统挂载到当前目录
    exit # 3. 退出 root 用户

cd ..
ls
cd proc/
ls
pwd
# /tmp/proc
ps
# PID TTY          TIME CMD
# 3223 pts/2    00:00:00 bash
# 4572 pts/2    00:00:00 ps
cd 3223
cat cmdline
# /bin/bash--init-file/home/hhu/.vscode-server/cli/servers/Stable-6f17636121051a53c88d3e605c491d22af2ba755/server/out/v
cd fd
ll
pwd
# /tmp/proc/3223/fd


```

---

### 任何 “可读写” 的东西都可以是文件 (cont'd)
**管道：一个特殊的 “文件” (流)**
- 由读者/写者共享
    - 读口：支持 read
    - 写口：支持 write

**匿名管道**
```c
int pipe(int pipefd[2]);
```
- 返回两个文件描述符
- 进程同时拥有读口和写口
看起来没用？不，fork 就有用了 (testkit)

```bash
man 2 pipe
# ​​参数​​ pipefd[2]：这是一个整型数组，用于返回两个文件描述符。
# pipefd[0] 是管道的​​读端​​，用于从管道读取数据。
# pipefd[1] 是管道的​​写端​​，用于向管道写入数据。

ls | wc -l # 统计文件行数
ls
ls > a.txt
cat a.txt
ls | wc -l
```
```bash
./anonymous-pipe
# [6693] Write: 'Hello, world!'
# [6694] Got: 'Hello, world!'
# [6693] Done.

./named-pipe
ll /tmp/my_pipe

tmux # 终端复用器
./named-pipe write Hello --- ./named-pipe read
./named-pipe write 12345678 --- ./named-pipe read
ll /tmp//my_pipe


```

---

## AIGC(Artificial Intelligence Generated Content)--pipe:

`man 2 pipe` 是 Linux 系统中查看 `pipe` 系统调用手册页的命令。`pipe` 系统调用用于创建一个**匿名管道**，这是一种基本的进程间通信（IPC）机制，特别适用于具有亲缘关系（如父子进程、兄弟进程）的进程间进行单向数据传递。

以下是 `pipe` 系统调用的核心信息摘要：

### 📌 1. **函数原型与头文件**
```c
#include <unistd.h>
int pipe(int pipefd[2]);
```
*   **参数** `pipefd[2]`：这是一个整型数组，用于返回两个文件描述符。
    *   `pipefd[0]` 是管道的**读端**，用于从管道读取数据。
    *   `pipefd[1]` 是管道的**写端**，用于向管道写入数据。
*   **返回值**：
    *   成功时返回 `0`。
    *   失败时返回 `-1`，并设置相应的错误代码 `errno`。

### 🔧 2. **管道的特性与工作原理**
*   **单向通信**：数据从写端 (`pipefd[1]`) 流向读端 (`pipefd[0]`)，是**半双工**的。
*   **内核缓冲区**：管道在内核中通过一个环状缓冲区实现，数据由内核进行管理和缓冲。
*   **进程间共享**：管道创建后，通过 `fork` 创建的子进程会继承父进程的文件描述符表，从而使得父子进程可以看到并操作同一个管道，这是实现通信的基础。
*   **同步与阻塞**：
    *   当尝试从**空管道**读取数据时，读操作会被阻塞，直到有数据写入。
    *   当向**满管道**写入数据时，写操作会被阻塞，直到有数据被读走。
    *   如果所有写端都被关闭，读端调用 `read` 会返回 `0`（表示文件结束）。
    *   如果所有读端都被关闭，写端继续写入会收到 `SIGPIPE` 信号，通常会导致进程终止。

### ⚠️ 3. **使用限制**
*   **亲缘关系**：匿名管道通常只能用于具有亲缘关系的进程之间（如由 `fork` 创建的进程）。
*   **生命周期**：管道的生命周期随进程。当所有打开它的进程都终止时，管道也被释放。
*   **原子性**：写入的数据量不大于 `PIPE_BUF`（一个系统定义的值，通常为 4096 字节或 512 字节）时，Linux 保证写入的原子性（即一次写入操作的数据不会与其他进程的写入操作交叉）。写入数据大于 `PIPE_BUF` 时，则不保证原子性。

### 🖥️ 4. **基本使用示例**
下面是一个简单的 C 语言示例，演示了如何在父子进程中使用管道通信：
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buf[1024];

    // 1. 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 2. 创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {     // 子进程
        close(pipefd[1]); // 关闭子进程不需要的写端
        read(pipefd[0], buf, sizeof(buf)); // 从管道读取数据
        printf("Child received: %s\n", buf);
        close(pipefd[0]); // 关闭读端
        exit(EXIT_SUCCESS);
    } else {            // 父进程
        close(pipefd[0]); // 关闭父进程不需要的读端
        const char *msg = "Hello from parent!";
        write(pipefd[1], msg, strlen(msg) + 1); // 向管道写入数据
        close(pipefd[1]); // 关闭写端
        wait(NULL);       // 等待子进程退出
    }
    return 0;
}
```
这个例子中，父进程向管道写入一条消息，子进程从管道读取并打印该消息。

### 💡 5. **常见用途**
管道的一个常见用途是在 Shell 中连接两个命令，例如 `ls | wc -l`。其中，`|` 符号就是创建了一个匿名管道，将 `ls` 命令的输出作为 `wc -l` 命令的输入。

### 📚 6. **相关命令和函数**
*   `man 7 pipe`：查看更详细的管道说明，包括容量、行为等。
*   `man 2 fork`：了解创建进程的函数。
*   `mkfifo`：用于创建命名管道（FIFO），允许无亲缘关系的进程进行通信。

### 🔍 7. **如何查看手册页**
在终端中输入以下命令即可查看 `pipe` 的详细手册：
```bash
man 2 pipe
```

总结来说，`pipe` 是一个用于创建匿名管道的系统调用，是 Linux 进程间通信的基础机制之一，尤其适合具有亲缘关系的进程间进行数据交换。

---

### 于是你已经有 “实现一切” 的基础知识了！
**进程管理**
- fork, execve, waitpid, exit
**内存管理**
- mmap, munmap, mprotect, msync
**文件管理**
- open, close, read, write, lseek, dup

---

## 7.3 一切皆文件Everything is a File ... ?

---

### 一切皆文件的好处
**一套 API 访问所有对象**
- 一切都可以 | grep (G​​lobal ​​R​​egular ​​E​​xpression ​​P​​rint)
    - Introducing `ag -g`

**同时，UNIX Shell 的语法广受诟病**
- 稍大一些的项目就应该用更好的语言 (Python, Rust!)
- 但是：We all love quick & dirty!
```bash
# 查看系统中进程打开的文件描述符（file descriptor）信息
ls -l /proc/*/fd/* 2>/dev/null | awk '{print $(NF-2), $(NF-1), $NF}'
# ​​统计 Linux 系统中所有进程当前占用的物理内存总量​​的实用单行脚本
grep -s VmRSS /proc/*[0-9]/status | awk '{sum += $2} END {print sum " kB"}'

AIGC:???
```

```bash
cat README.md | grep UNIX == grep UNIX README.md
ls | grep \.c # 匹配所有.c 文件

ls **/* # 递归搜索当前目录及其子目录中的所有文件

echo {1..100}
echo 192.168.1.{1..100}
echo 192.168.1.{1..100} | wc -l
echo 192.168.1.{1..100} | xargs cat
echo 192.168.1.{1..100} | xargs ping
```
---
**Prompt: 什么是 glob patterns? 有什么实际中常用的扩展？**
Glob patterns 是一种用于匹配文件路径名的模式，常用于文件搜索和操作。常见的通配符包括：

- *：匹配任意数量的字符（包括零个）
- ?：匹配单个字符
- []：匹配指定范围内的字符

实际中常用的扩展包括：

- **：递归匹配任意层级的子目录
- {}：匹配多个模式，如 {a,b,c} 匹配 a、b 或 c
- !(pattern)：排除指定模式

这些扩展增强了 glob patterns 的灵活性和功能性。

---

### 文件描述符适合什么？
**字节流**
- 顺序读/顺序写
    - 没有数据时等待
    - 典型代表：<b style="color:#4169E1">管道</b>

**字节序列**
- 其实就有一点点不方便了
    - 需要到处 lseek 再 read/write
        - mmap 不香吗？指针指哪打哪
        - madvise, msync 提供了更精细的控制
```bash
man 2 lseek
# off_t lseek(int fd, off_t offset, int whence);
```

---

### 反思 Everything is a File
**优点**
- 优雅，文本接口，就是好用

**缺点**
- 和各种 API 紧密耦合
    - [A fork() in the road](https://www.microsoft.com/en-us/research/wp-content/uploads/2019/04/fork-hotos19.pdf)
- 对高速设备不够友好
    - 额外的延迟和内存拷贝
    - 单线程 I/O

---

### 出路：API + 封装 🌶️
>Any problem in computer science can be solved with another level of indirection. (Butler Lampson)

- Windows NT: Win32 API → POSIX 子系统
Windows Subsystem for Linux (WSL)
- macOS: Cocoa API → BSD 子系统
- Fuchsia: Zircon 微内核 → POSIX 兼容层

**兼容当然没法做到 100%**
- sysfs, procfs 就是没法兼容
- 优雅的 WSL1 已经暴毙 😂
“Windows Subsystem for Linux”
“Linux Subsystem for Windows” (wine)
```bash
man syscalls
```

---

### 还有 OpenHarmony 呢！


---

## 7.4 总结
　　**Take-away Messages**: 操作系统必需提供机制供应用程序访问操作系统对象。对于 UNIX 系统，文件描述符是操作系统中表示打开文件 (操作系统对象) 的指针；而 Windows 则更直接地提供了 handle 机制。