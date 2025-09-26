# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

## 8. 终端和 UNIX Shell

我们已经知道如何用 “文件描述符” 相关的系统调用访问操作系统中的对象：`open, read, write, lseek, close`。操作系统也提供了 `mount, pipe, mkfifo` 这些系统调用能 “创建” 操作系统中的对象。当然，我们也知道操作系统中的对象远不止于此，还有很多有趣的对象我们还没有深入了解过——终端就让人细思恐极。

**本讲内容**：从大家每天用的终端模拟器开始，一探究竟 Ctrl-C 到底做了什么——在此基础上，我们就可以实现自己的 “多任务管理器” 了。

## 8.1 终端

---

### 打字机 (Typewriter)

**QWERTY 键盘 (1860s)**

- 为降低打字速度设计的防卡纸方案
  - 毕竟机械结构，每一下都需要足够的力量

---

### 打字机时代的遗产

**Shift**

- 字模向上移动一段距离，切换字符集

**CR & LF**

- `\r` CR (Carriage Return): 回车，将打印头移回行首
  - `print('Hel\rlo')`
- `\n` LF (Line Feed): 换行，将纸张向上移动一行
  - UNIX 的 `\n` 同时包含 CR 和 LF

**Tab & Backspace**
位置移动 (~~Backspace + 减号 = 错了划掉~~)

```py
print('Hello\n', end = '')
print('Hel\rlo\n', end = '')
print('Hello\r\n', end = '')
# 输出 Hello
# 输出 lol
# 输出 Hello
```

---

### 电传打字机 (Teletypewriter)

**为了<b style = "color:#4169E1">发电报</b>设计 (收发两端同时打印)**

- Telex (teleprinter exchange): 1920s，早于计算机
  - 使用 Baudot Code (5-bit code)
  - 很自然地也能用在计算机上

---

### 电传打字机 (cont'd)

- Teletype Model 28 (1951); [technical data sheet](https://www.samhallas.co.uk/repository/telegraph/teletype_28_tech_data.pdf)

---

### VT100: 封神之路

**Video Teletypewriter (DEC, 1978)**

- 成为事实上的行业标准
  - 首个完整实现 ANSI Escape Sequence 的终端
  - 80 × 24 字符显示成为标准布局

---

### 计算机终端：原理

**作为输出设备**

- 接受 UART 信号并显示 (Escape Sequence 就非常自然了)

**作为输入设备**

- 把按键的 ASCII 码输出到 UART (所以有很多控制字符)

---

### 今天：伪终端 (Pseudo Terminal)

**一对 “管道” 提供双向通信通道**

- 主设备 (PTY Master): 连接到终端模拟器
- 从设备 (PTY Slave): 连接到 shell 或其他程序
  - 例如 `/dev/pts/0`

**伪终端经常被创建**

- ssh, tmux new-window, ctrl-alt-t, ...
- `openpty()`: 通过 `/dev/ptmx` 申请一个新终端
  - 返回两个文件描述符 (master/slave)
  - (感受到 “操作系统对象” 的恐怖体量了吧)

```bash
ps
#    9323 pts/2    00:00:00 bash
ll /proc/9323/fd
# /dev/pts/2
```

```bash
# 新建几个终端
tty
# /dev/pts/3
tty
# /dev/pts/4
tty
# /dev/pts/5
echo hello > /dev/pts/4
# hello
tmux # 同理

man openpty # 3

## 用 AI 翻译 需要配置
man openpty | ag -q Translate to Chinese

man ptmx
```

---
### 终端模拟器 (Terminal Emulator)

**这下你也会实现了**

- openpty + fork
  - 子进程：stdin/stdout/stderr 指向 slave
  - 父进程：从 master 读取输出显示到屏幕; 将键盘输入写入 master

**甚至可以扩展 Escape Sequence 来显示图片**

- Kitty: `\033[60C\_` 开头，`\033\` 结尾
  - 允许控制大小、位置、动画等
  - `kitten icat img.png | cat`
- 应该内嵌 WebView 的 😭 期待这个革命性的产品
```bash
tty

# xterm.js 二次开发 : 网页显示终端
ttyd
ttyd -W login
ttyd -W bash
localhost:7682

kitty # 显示图片，动画
```

---

### 终端：更多功能

**终端模式**

- Canonical Mode: 按行处理
  - 回车发送数据 (终端提供行编辑功能)
- Non-canonical Mode: 按字符处理
  - 每个字符立即发送给程序
  - 用于实现交互式程序: vim, ssh sshtron.zachlatta.com

**终端属性控制**

- tcgetattr/tcsetattr (terminal control)
- 可以控制终端的各种行为：回显、信号处理、特殊字符等
  - (你输密码的时候关闭了终端的回显)
```bash
ssh sshtron.zachlatta.com

在 ​​Linux 或 macOS 终端​​中，你可以使用 stty 命令来手动开关回显：
stty -echo 关闭回显
stty echo 开启回显
```

---

## 8.2 终端和操作系统

---

### 程序是怎么和终端 “配对” 的？

**用户登录的起点**

- 系统启动 (内核 → init → getty)
- 远程登录 (sshd → fork → openpty)
  - stdin, stdout, stderr 都会指向分配的终端
- vscode (fork → openpty)

**login 程序继承分配的终端**

- (是的，login 是一个程序)
- fork() 会继承文件描述符 (指针)
  - 因此，子进程也会指向同一个终端
```bash
man getty 
# getty 是 Linux 系统中一个非常重要的​​终端登录管理程序
man openpty  
# openpty() 函数是一个​​创建伪终端（pseudo-terminal，简称 PTY）对​​的低级系统调用
```

---

### 终于，我们有了足够的机制实现 “用户界面

---

### 当然，不是图形的

**UNIX Shell: “终端” 时代的经典设计**

- “Command-line interface” (CLI) 的巅峰

---

### 进程管理：要解决的问题

> 我们有那么大一棵进程树，都指向同一个终端，有的在前台，有的在后台，Ctrl-C 到底终止哪个进程？

**答案：终端才不管呢**

- 它只管传输<b style = "color:#4169E1">字符</b>
  - Ctrl-C: End of Text (ETX), \x03
  - Ctrl-D: End of Transmission (EOT), \x04
  - stty -a: 你可以看到按键绑定 (奇怪的知识增加了)
- 但<b style = "color:#4169E1">操作系统</b>收到了这个字符
  - 就可以对 “当前” 的进程采取行动

```bash
# ww
python3
`ctrl+c`
# KeyboardInterrupt
`ctrl+d`

cat
hello
`ctrl+c`
`ctrl+d`

stty -a
... intr = ^C; quit = ^\; eof = ^D;...
python3
`ctrl+\` 
```

---

### 终端上的 “当前进程”

> 作为操作系统的设计者，需要在收到 Ctrl-C 的时候找到一个 “当前进程”

**你会怎么做？**

- fork() 会产生树状结构
  - (还有托孤行为)
- Ctrl-C 应该终止所有前台的 “进程们”
  - 但不能误伤后台的 “进程们”

```bash
# ww
python3
`^z` # stopped
jobs
vim
`^z`
jobs
# [1]-  Stopped                 python3
# [2]+  Stopped                 vim
`^c`无反应
fg %2 # 切换到 vim
i # 进入编辑模式
hello # 输入内容
esc # 退出编辑模式
`^z`
fg %2
tty
# /dev/pts/2 # 在同一终端完成
```

---

>创建一棵进程子树: 创建一棵 5 层的进程树，并随机退出其中的一些进程——我们可以观察进程退出前后父子进程的关系。

---

### 会话 (Session) 和进程组 (Process Group)
Picture:

Controlling terminal
- Foreground PGID g= 660
- Controlling SID= 400

```bash
# ww
# fork() 默认同一进程组
python3
`^z`
ps
  #   PID TTY          TIME CMD
  #  3596 pts/2    00:00:00 bash
  #  4247 pts/2    00:00:00 python3
  #  4402 pts/2    00:00:00 vim
  #  5078 pts/2    00:00:00 python3
  #  5130 pts/2    00:00:00 ps
`^c`终止哪个呢？

jobs -l
# [1]   4247 Stopped                 python3
# [2]-  4402 Stopped                 vim
# [3]+  5078 Stopped                 python3

vim # 回车 == windows双击打开
`^z` # windows 最小化
jobs -l
fg %3 # windows 切换到 vim
```

---

### 会话和进程组：机制

**给进程引入一个额外编号 (Session ID，大分组)**

- 子进程会继承父进程的 Session ID
  - 一个 Session 关联一个控制终端 (controlling terminal)
  - Leader 退出时，全体进程收到 Hang Up (SIGHUP)

**再引入另一个编号 (Process Group ID，小分组)**

- 只能有一个前台进程组
- 操作系统收到 Ctrl-C，向前台进程组<b style = "color:#4169E1">所有进程</b>发送 SIGINT
  - (真累……但你也想不到更好的设计了)

```bash
# ww
ssh: nohup # 后台运行
```

---
### 会话和进程组：API
**太不优雅了**
- setsid/getsid
  - setsid 会脱离 controlling terminal
- setpgid/getpgid
- tcsetpgrp/tcgetpgrp
  - 迷惑 API

ww
***deepseek-V3-241226:***
- `setpgid'和‘getpgid'用于设置和获取进程的进程组ID，主要涉及进程组的管理。‘setpgid'可以将指定进程移动到新的进程组，"getpgid则获取指定进程的进程组ID.
- 'tcsetpgrp’和tcgetpgrp用于控制终端的前台进程组。‘tcsetpgrp’设置终端的前台进程组，‘tcgetpgrp’获取终端的前台进程组ID.

*简而言之，前者管理进程组，后者管理终端的前台进程组。*


**以及……uid, effective uid (?), saved uid (???)**
- [Setuid Demystified](https://www.usenix.org/conference/11th-usenix-security-symposium/setuid-demystified)
  - 任何软件都很难逃脱千疮百孔的设计

```bash
# ww
uid,euid,suid ????

PTY（Pseudo-Terminal，伪终端）是 Linux 和其他类 Unix 操作系统中一种强大的进程间通信机制
```

---
### 终于能实现 Job Control 了
**窗口和多任务：终端可以有 “一个前台进程组”**
- “最小化” = Ctrl-Z (SIGTSTP)
  - SIGTSTP 默认行为暂停进程，收到 SIGCONT 后恢复
- “切换” = fg/bg (tcsetpgrp)

**为了实现 “窗口栏上的按钮”，还很是大费周章**
- 还不如 tmux 管理多个 pty 呢 (选择性 “绘制” 在终端上)
  - 那是因为发明 session/pg 的时候还没有 pty 呢……

---
### Prompt: 在有了 pty 机制之后，我们可以用 session 的机制，为每个 “窗口” 分配一个新的 pty，这样可以简化系统调用，例如 process group 的概念可以消除。是否可以这样设计新的操作系统？
理论上，这种设计是可行的，但需要谨慎权衡利弊：

**1. 可行性分析**
- PTY与会话的1:1绑定确实能简化部分终端管理逻辑
- 进程组原有的作业控制功能（如信号广播、终端抢占）可被会话继承
- 现代容器化趋势下，会话级的资源隔离更符合最小化原则

**2. 潜在优势**
- 减少进程组/会话组ID的维护开销
- 窗口崩溃时可通过会话机制自动回收资源
- 更清晰的层次结构：终端→会话→进程树

**3.关键挑战**
- POSIX兼容性问题：许多程序依赖setsid()/tcsetpgrp()等系统调用
- 精细控制需求：某些场景仍需进程组级别的信号传递
- 内核调度影响：会话级cgroup可能比进程组更重量级

**4. 折中建议**
- 保留进程组作为可选机制
- 在用户空间抽象会话管理(如systemd-style)
- 通过命名空间隔离增强会话安全性

这种设计在嵌入式/专用系统中有应用前景，但通用系统需保持向后兼容。当前Linux的cgroups v2已部分实现类似理念，通过进程树替代进程组管理资源。

---
### 是的，历史的糟粕
**但是，这是 POSIX 的一部分……**
- 😂 几乎任何人都无法预知 “软件” 的未来

**回头看这个问题**
- 我们不需要 “绑定进程到设备”
- 管理程序 (tmux, gnome, ...) 去模拟就行
  - Window Manager: 只需要 “进程组” 就行了
    - 关窗口，全部 ❌ 一个不留
  - Android: 每个 app 都是不同的用户
    - 强行终止 = 杀掉属于这个用户的所有进程
  - Snap: 程序在隔离的沙箱运行
    - AppArmor + seccomp + namespaces (真狠)

```bash
# ww
ps ax 
强行终止==遍历所有进程xxx
```

---
### 在未来回头看现在
**人机交互的方式根本不应该是这样的**
- 我们很少能清醒地认识到
  - 我要做 X
  - 应该分解成 Y → (Z,W) → T
- 因此，<b style = "color:#4169E1">坐在电脑前的大部分时间都浪费了</b>

---
### 最后：Ctrl-C 到底做了什么？
**signal**
- 注册一个信号的 “处理程序” f
  - 操作系统会记下这个 f

**kill**
- 在程序从操作系统返回时，强制加一个向 f 的跳转
  - 程序 = 状态机
  - 只要 “模拟” 调用 f 的行为即可

**今天有更可靠的版本 (sigaction)**
- 让 AI 帮你解释吧

```bash
# ww
jump
pending signals + SIGINT
hack
```

---

>信号处理：我们可以通过 signal (sigaction) 注册信号处理程序——这也解释了为什么有些程序不能用 Ctrl-C 退出。即便是终止信号，我们也可以执行清理代码退出。
```bash
# ww
./signal & # 后台运行 == ./signal + ^z
jobs -l
fg %1 # 切换到后台进程
输入
`^c`
`^\`
```

---
### Prompt: 为什么我们需要 sigaction 替代 UNIX 的信号机制？
使用 sigaction 替代传统的 UNIX signal 机制，主要出于以下原因：

**1. 行为可靠性**
- **传统 signal 的缺陷**：早期 signal 函数在信号处理完成后，**自动将信号处理程序重置为默认行为**（如 SIG_DFL），需要手动重新注册，易导致信号丢失或竞态条件。
- sigaction **改进**：通过 **SA_RESTART 标志支持系统调用自动重启**，避免因信号中断导致的系统调用意外终止，提升程序健壮性。

**2. 精确控制信号行为**
- **屏蔽信号**：sigaction 允许在信号处理期间，通过 sa_mask 字段**阻塞特定信号**，防止嵌套信号干扰，确保处理逻辑的原子性。
- **上下文信息**：通过 siginfo_t 结构体可获取信号的**来源信息**（如发送进程 PID、错误地址等），增强调试能力。

**3. 可移植性**
- 传统 signal 函数在不同 UNIX 系统中的实现不一致（如 BSD 和 System V）。sigaction 是 POSIX 标准化的接口，提供统一行为，避免跨平台兼容性问题。

**4. 避免信号丢失**
- sigaction 的 SA_NODEFER 和 SA_RESETHAND 标志允许更灵活控制信号递送，避免传统机制中因信号处理重置导致的多次信号丢失。

**示例对比**
```c
// 传统 signal 的脆弱实现
void handler(int sig) {
    signal(SIGINT, handler);  // 必须手动重新注册
    // 处理逻辑
}
signal(SIGINT, handler);

// 使用 sigaction 的可靠实现
struct sigaction sa;
sa.sa_handler = handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART;  // 自动重启系统调用
sigaction(SIGINT, &sa, NULL);
```
**总结**
sigaction 通过提供**原子性注册、阻塞控制、上下文信息和标准化行为**，解决了传统 signal 的不可靠性和平台依赖问题，是现代 UNIX 系统编程中推荐使用的信号处理机制。

---
## 8.3 UNIX Shell 编程语言
### “多任务” 不是人机交互的全部

Windows 3.2 (1992): “多窗口管理器” 并不那么好用

---
### The Shell Programming Language
**UNIX 的用户可都是 hackers!**
- UNIX Shell: <b style = "color:#4169E1">基于文本替换的极简编程语言</b>
  - 只有一种类型：字符串
  - 算术运算？对不起，我们不支持 😂 (但可以 expr 1 + 2)

**语言机制**
- 预处理: `$()`, `<()`
- 重定向: `cmd > file < file 2> /dev/null`
- 顺序结构: `cmd1`; `cmd2`, `cmd1 && cmd2`, `cmd1 || cmd2`
- 管道: `cmd1 | cmd2`
  - 这些<b style = "color:#4169E1">命令</b>会被被翻译成<b style = "color:#4169E1">系统调用</b>序列 (open, dup, pipe, fork, execve, waitpid, ...)

```bash
# ww
123 + 456
# 123: command not found bash里面没有整数，被当作命令

python3
123
# 123

echo $(( 123 + 456 ))
# 579
expr 123 + 456
# 579
echo result = `expr 123+456` # expr 123+456 文本的粘贴
# result = 579
echo $(echo hello)
# hello
echo <(echo hello)
# /dev/fd/63

diff a b # 两文件比较
diff echo hello echo world ???
diff <(echo hello) <(echo world)
# 1c1
# < hello
# ---
# > world

echo hello && echo world
# hello
# world

echo hello || echo world
# hello
echo hello || echo Error

123 || echo Error
# 123: command not found
# Error
```


---
### 例子：实现重定向
**利用子进程继承文件描述符的特性**
- 在父进程打开好文件，到子进程里腾挪
  - 发现还是 Windows API 更 “优雅”
```c
int fd_in  = open(..., O_RDONLY | O_CLOEXEC);
int fd_out = open(..., O_WRONLY | O_CLOEXEC);

int pid = fork();
if (pid == 0) {
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    execve(...);
} else {
    close(fd_in);
    close(fd_out);
    waitpid(pid, &status, 0);
}
```

```bash
# ww
cmd < infile > outfile
# 过程简述​​：命令 cmd 会读取 infile 文件的内容作为输入，经过处理，将其结果输出到 outfile 文件中。

(a | b | c | d | e) < infile > outfile
# ​​过程简述​​：文件 infile 的内容首先传递给命令 a 处理，a 的结果传递给 b 处理，依次传递，最终由命令 e 处理后的结果保存到 outfile 文件中。

cmd > file < file 2> /dev/null
# 让 cmd 命令从 file 文件中读取输入，将其正常输出内容写入（覆盖）到同一个 file 文件中，同时丢弃所有错误信息。
```

---
>Freestanding Shell: 这个 Shell 没有引用任何库文件——它只通过系统调用访问操作系统中的对象。为了便于调试，我们编写了 Python 脚本，打印出当前所有被调试进程打开的文件，包括读写权限和文件。没错——进程的任何瞬间都能表示成状态机的状态，包括指向操作系统对象的指针 (文件描述符)。


```bash
# ww
make
./sh
  ls
  ls | wc -l 
  ls | wc -l | wc -l 

man sh
```

---
### 读一读手册 (为数不多还值得读的手册)
**man sh: dash — command interpreter (shell)**
- <b style = "color:#4169E1">dash</b> is the standard command interpreter for the system. The current version of dash is in the process of being changed to conform with the POSIX 1003.2 and 1003.2a specifications for the shell.
- The shell is a command that reads lines from either a file or the terminal, interprets them, and generally executes other commands. It is the program that is running when a user logs into the system (although a user can select a different shell with the chsh(1) command).

---
### UNIX Shell: 优点
**优点：高效、简介、精确**
- 一种 “自然编程语言”：一行命令，协同多个程序
  - `make -nB | grep ...`
  - 最适合 quick & dirty 的 hackers

**AI 时代的 UNIX Philosophy**
- `man tcsetpgrp | ag -q 帮我生成新手友好的教程`
- 出了问题还可以 [fxxk](https://github.com/nvbn/thefuck)
  - 带过一个同学毕设改进 fxxk (现在他已经在 DeepSeek 开源周发代码了); 再想改进的时候，ChatGPT 来了 😭

---
### UNIX Shell: 有优点就有缺点
**无奈的取舍**
- Shell 的设计被 “1970s 的算力、算法和工程能力” 束缚了
  - 后人只好将错就错 (PowerShell: 我好用，但没人用 😭)

**例子：操作的 “优先级”？**
- `ls > a.txt | cat`
  - 我已经重定向给 a.txt 了，cat 是不是就收不到输入了？
- `bash/zsh` 的行为是不同的
  - 所以脚本用 `#!/bin/bash` 甚至 `#!/bin/sh` 保持兼容
- 文本数据 “责任自负”
  - 空格 = 灾难

```bash
# ww
ls > a.txt | cat
cat a.txt
zsh ??
```

---
### 另一个有趣的例子
Picture:
A: Make me a sandwich!
B: What？ Make it yourself!
A: Sudo make me a sandwich!
B: Okay.
```bash
$ echo hello > /etc/a.txt
bash: /etc/a.txt: Permission denied

$ sudo echo hello > /etc/a.txt

# ww
$ sudo bash -c "echo hello > /etc/a.txt"
```

---
### A Zero-dependency UNIX Shell
**真正体现 “Shell 是 Kernel 之外的 壳”**
- 来自 xv6
- 完全基于系统调用 API，零库函数依赖
  - -ffreestanding 编译、ld 链接

**支持的功能**
- 重定向/管道 `ls > a.txt`, `ls | wc -l`
- 后台执行 `ls &`
- 命令组合 `(echo a ; echo b) | wc -l`

---
### 展望未来
**去年留下的 Open question**
- <b style = "color:#4169E1">Shell (CLI/GUI) 的未来是什么？</b>

**今年有了一些想法**
- 是一个 “半结构化” 的 “编程语言”
  - project files | filter out generated files | zip them
  - make a slides of UNIX shell | play it
  - 我就可以退休啦 😄

---
## 8.5 总结
　　**Take-away Messages**: 通过 freestanding 的 shell，我们阐释了 “可以在系统调用上创建整个操作系统应用世界” 的真正含义：操作系统的 API 和应用程序是互相成就、螺旋生长的：有了新的应用需求，就有了新的操作系统功能。而 UNIX 为我们提供了一个非常精简、稳定的接口 (fork, execve, exit, pipe ,...)，纵然有沉重的历史负担，它在今天依然工作得很好。
