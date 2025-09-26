# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

## 10. 可执行文件
有了系统调用和 libc，我们就真的可以实现 “任何程序” 了——例如，你可以想一想，如果要实现一个 MicroPython 解释器，我们需要实现什么，又需要借助哪些系统调用？当然，我们需要编译器帮我们编译 python.c 到可执行文件——我们一直以来都 “默认” 了编译器工具链可以帮助我们实现高级语言到可执行文件的翻译。今天是时候 “打开” 这部分内容了。

---
### Prompt: 如果要实现一个 MicroPython 解释器，我们需要实现什么，又需要借助哪些系统调用？
实现 MicroPython 解释器需要以下核心组件和步骤：

**核心实现部分：**
1. **词法分析（Lexer）**
将源代码分割为 token，识别关键字、变量名、操作符等。

2. **语法分析（Parser）**
构建抽象语法树（AST），验证语法结构是否符合 Python 规范。

3. **字节码生成（Compiler）**
将 AST 转换为可执行的字节码（或直接解释执行）。

4. **虚拟机（VM）**
执行字节码，管理运行栈、作用域和内存。

5. **内置类型与函数**
实现 Python 基础类型（如 int, str, list）和内置模块（如 sys, io）。

6. **内存管理**
通过垃圾回收（GC）机制管理动态内存，通常采用标记-清除算法。

7. **硬件抽象层（HAL）**
针对嵌入式平台实现 GPIO、I2C 等外设驱动接口。

**依赖的系统调用（以类 Unix 系统为例）：**
1. **内存管理**
    - brk/sbrk：扩展堆内存（若使用动态内存分配）。
    - mmap/munmap：映射内存页（用于大块内存或特殊设备）。

2. **文件操作**
    - open/read/write：读写文件系统。
    - ioctl：控制硬件设备（如终端 I/O）。

3. **进程与信号**
    - fork/exec：支持多进程（若需扩展功能）。
    - signal：处理中断信号（如 Ctrl+C）。

4. **时间管理**
    - gettimeofday/clock_gettime：获取系统时间。
    - nanosleep：实现延时函数（如 time.sleep()）。

5. **输入输出**
    - select/poll：非阻塞 I/O 或多路复用（用于 REPL 交互）。

**嵌入式系统差异：**
在无操作系统的微控制器上（如 STM32）：
- 直接操作寄存器或通过厂商 SDK 控制外设（如 GPIO）。
- 替换系统调用为裸机驱动（如自定义 _read()/_write() 实现 UART 通信）。
- 静态内存分配替代动态 GC（可选优化）。

**工具链依赖：**
- **交叉编译器（如** ARM-GCC）：生成目标平台二进制。
- **链接脚本**：定义内存布局（代码/数据/堆栈分区）。
- **固件烧录工具**（如 OpenOCD）：部署到硬件。

通过分层设计（如分离核心解释器与平台适配层），可提高跨平台兼容性。

---
## 10.1 可执行文件
### 什么是可执行文件？
**学习操作系统前**
- 那个 “双击可以弹出窗口的东西”
picture

**学习操作系统后**
- 一个操作系统中的对象 (文件)
- 一个字节序列 (我们可以把它当字符串编辑)
- 一个描述了状态机初始状态的<b style="color:#4285F4">数据结构</b> (打扰了)

```bash
# ww
ls (-l) /bin/ls
cat /bin/ls | xxd | less
vim /bin/ls
```
---
## /bin/ls这个文件怎么找不到? AIGC:
您好，这个问题非常好！它触及了现代 Linux 发行版的一个重要变化。

您找不到 `/bin/ls` 的主要原因很可能是：**在新版本的 Ubuntu（包括 WSL2 中的 Ubuntu）中，`/bin` 目录已经变成了一个指向 `/usr/bin` 的符号链接（Symlink）。**

这意味着，`/bin/ls` 和 `/usr/bin/ls` 现在是**同一个文件**。

---

### 详细解释和验证方法

#### 1. 检查 `/bin` 的本质

您可以通过 `ls` 命令本身（是不是很巧妙？）来查看 `/bin` 的真实身份。在终端中输入：

```bash
ls -l / | grep bin
```

您会看到类似这样的输出：

```
lrwxrwxrwx   1 root root      7 Jul 27  2022 bin -> usr/bin
lrwxrwxrwx   1 root root      7 Jul 27  2022 sbin -> usr/bin
drwxr-xr-x   2 root root  4096 Jul 27  2022 usr/bin
drwxr-xr-x   2 root root  4096 Jul 27  2022 usr/sbin
```

请注意第一行：
*   `lrwxrwxrwx`：开头的 `l` 表示这是一个**符号链接**（类似于 Windows 的快捷方式）。
*   `bin -> usr/bin`：这表示 `/bin` 目录指向（链接到） `/usr/bin` 目录。

所以，当您尝试访问 `/bin/ls` 时，系统会自动跳转到 `/usr/bin/ls`。

#### 2. 直接查找 `ls` 命令的位置

有几种更可靠的方法来定位 `ls` 这个命令文件：

**方法一：使用 `which` 命令**
`which` 命令用于查找某个命令的可执行文件路径。
```bash
which ls
```
输出结果几乎肯定是：
```
/usr/bin/ls
```

**方法二：使用 `type` 命令**
`type` 命令更强大，它会告诉你命令的类型（是内建命令、别名，还是外部可执行文件）。
```bash
type ls
```
输出通常为：
```
ls is /usr/bin/ls
```

**方法三：使用 `ls` 命令本身查找**
您甚至可以用 `ls` 命令来查找它自己：
```bash
ls -l $(which ls)
```
或者
```bash
ls -l /usr/bin/ls
```
这会显示 `ls` 命令的详细信息，包括其大小、权限和位置。

---

### 为什么会发生这种变化？

这种将 `/bin` 和 `/sbin` 合并到 `/usr` 目录下的做法，是 Linux 世界一个名为 **“usrmerge”** 的重大变革。其主要目的是：

1.  **减少冗余**：避免同一个程序在 `/bin` 和 `/usr/bin` 中重复存在。
2.  **简化系统结构**：使文件系统层次标准（FHS）更加清晰和简洁。
3.  **符合历史发展**：早期 Unix 中，`/usr` 被认为是“用户目录”，但如今它早已成为存放绝大多数用户程序和系统程序的地方。

几乎所有主流的 Linux 发行版（如 Debian、Ubuntu、Fedora、Arch Linux 等）都已经默认采用了这种新的结构。

---

### 总结

*   **您没有找错地方，只是概念更新了。**
*   `/bin/ls` 仍然是一个有效的路径，但它现在只是一个指向 `/usr/bin/ls` 的“快捷方式”。
*   如果您想确认 `ls` 命令的真实位置，最可靠的方法是使用 `which ls` 或 `type ls`。
*   这个变化是现代 Linux 系统进化的一个正常部分，旨在使系统更高效、更统一。

所以，请放心，您的 WSL2 Ubuntu 系统是完全正常的！`ls` 命令好好地待在 `/usr/bin/ls` 那里呢。

---
### ELF: Executable and Linkable Format
**我们在《计算机系统基础》中学到的**
- [binutils](https://www.gnu.org/software/binutils/) 中的工具可以让我们查看其中的重要信息
    - 《计算机系统基础》常备工具
        - readelf & objdump
    - binutils 里原来还有不少宝藏！

**我们在《计算机系统基础》里没学到的**
- 如果我们想了解关于 ELF 文件的信息，有什么不那么 “原始” 的现代工具可用？
    - 哦，有 elfcat，以及更多
```bash
readelf -a /usr/bin/busybox | less
```
- [ ] AI:如果我们想了解关于ELF文件的信息，有什么不那么“原始”的现代工具可用？

---
### AI:如果我们想了解关于 ELF 文件的信息，有什么不那么 “原始” 的现代工具可用？ 我想用elfcat，在linux要怎么安装，帮我生成新手友好的教程/介绍/解释
当然！你提出了一个非常好的问题。传统的命令行工具（如 `readelf`, `objdump`）功能强大，但对于新手来说，输出信息确实非常“原始”和复杂。

很高兴地告诉你，**`elfcat` 是一个真实存在的现代工具！** 它属于新一代的、对用户更友好的二进制分析工具。下面我将为你提供一个全新的、新手友好的 `elfcat` 安装和使用教程。

---

### 什么是 `elfcat`？为什么说它更现代？

`elfcat` 是一个用 Rust 语言编写的命令行工具。它的核心思想是：**“既然 `cat` 可以打印文本文件的内容，为什么不能有一个工具以彩色、高亮、易于阅读的方式‘打印’ELF 二进制文件的内容呢？”**

**它与传统工具（如 `readelf`）的主要区别：**

| 特性 | 传统工具 (`readelf`) | `elfcat` (现代工具) |
| :--- | :--- | :--- |
| **可读性** | 输出是大段的纯文本，需要专业知识来解析 | **彩色高亮输出**，不同部分用不同颜色区分，一目了然 |
| **交互性** | 无交互，一次性输出所有信息 | 无交互，但视觉上做了极大优化 |
| **设计哲学** | 为程序员和编译器设计，提供**所有**原始数据 | 为**人类**设计，提供**直观**的**可视化**概览 |
| **使用体验** | 像在阅读一份冰冷的机器报告 | 像在浏览一个语法高亮的代码文件 |

简单来说，`elfcat` 给了你一个“语法高亮”的视角来观察二进制文件，这让理解 ELF 结构变得前所未有的直观。

---

### 如何安装 `elfcat`

`elfcat` 是通过 Rust 的包管理器 `cargo` 来分发和安装的。因此，安装过程分为两步：

#### 第 1 步：安装 Rust 编程语言环境（`cargo`）

打开你的终端（Terminal），输入以下命令：

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

**对于新手的解释：**
*   这个命令会从官方下载一个脚本，并自动安装 Rust 和它的包管理器 `cargo`。
*   运行后，它会提示你进行选择。直接按 **回车** 选择默认选项（`1`）即可。
*   安装完成后，它会提示你需要**重启终端**或者运行一个命令来刷新环境变量。最简单的方法就是：**关闭当前终端窗口，再打开一个新的**。

**验证安装：**
在新终端中，输入：
```bash
cargo --version
```
如果你能看到版本号（例如 `cargo 1.75.0`），说明安装成功！

> **备选安装方法**：你也可以通过系统的包管理器安装，但版本可能较旧。例如在 Ubuntu/Debian 上可以尝试 `sudo apt install cargo`，但**强烈推荐使用上述官方脚本**，它能保证你获得最新的版本。

#### 第 2 步：使用 `cargo` 安装 `elfcat`

在新的终端中，输入以下命令：

```bash
cargo install elfcat
```

**对于新手的解释：**
*   `cargo install` 命令会从 Rust 的官方包仓库（crates.io）下载 `elfcat` 的源代码，自动编译，并将生成的可执行文件安装到你的系统上。
*   这个过程需要一点点时间，请耐心等待它完成。

安装成功后，`elfcat` 命令就可以使用了！

---

### 如何使用 `elfcat`：新手实战

现在，让我们用你最初的想法来试试这个酷炫的工具！

#### 基础用法

在你的终端中，输入：

```bash
elfcat /usr/bin/ls
```

**发生了什么？**
你会立刻看到与 `cat` 或 `readelf` 完全不同的输出！终端里会显示彩色的内容。`elfcat` 会自动解析 `/usr/bin/ls` 这个 ELF 文件，并以不同的颜色高亮显示不同的部分，例如：

*   **ELF 文件头**（ELF Header）
*   **程序头**（Program Headers）：可能用一种颜色表示
*   **节头**（Section Headers）：可能用另一种颜色表示
*   **代码节**（.text）
*   **数据节**（.data, .rodata）
*   **字符串表**（.strtab）

你不需要记住这些，颜色已经帮你区分开了。你可以清晰地看到这个二进制文件的“骨架”。

#### 进阶用法：输出到文件

`elfcat` 的输出是带颜色代码的文本。如果你想把它保存到一个文件中以便稍后查看，直接重定向会丢失颜色。为了保留颜色，你可以使用 `aha`（ANSI-to-HTML）这样的工具来生成一个带颜色的 HTML 网页。

1.  **首先安装 `aha`**：
    ```bash
    # 在 Ubuntu/Debian 上
    sudo apt install aha

    # 在 Fedora/CentOS 上
    sudo dnf install aha
    ```

2.  **生成一个彩色的 HTML 报告**：
    ```bash
    elfcat /usr/bin/ls | aha --black > ls_elf_analysis.html
    ```
    这个命令会将 `elfcat` 的彩色输出通过 `aha` 转换成 HTML，并保存到 `ls_elf_analysis.html` 文件中。你可以用任何浏览器打开这个文件，就能看到和终端里一模一样的彩色高亮内容了！

---

### 除了 `elfcat`，还有什么其他现代工具？

你问到了“以及更多”，这里再推荐两个同样基于 Rust 的明星工具，它们共同构成了现代二进制分析的“三剑客”：

1.  **`bat`**：一个带有语法高亮和 Git 集成的 `cat` 克隆。用于查看**文本文件**（如源代码、配置文件）的终极工具。
    *   安装：`cargo install bat`
    *   使用：`bat /etc/hosts` （试试看，效果惊艳！）

2.  **`hexyl`**：一个彩色的十六进制控制台查看器。用于查看**任何二进制文件**（如图片、压缩包）的原始内容，比 `hexdump` 和 `xxd` 直观得多。
    *   安装：`cargo install hexyl`
    *   使用：`hexyl /usr/bin/ls | less`

### 总结

| 工具 | 用途 | 安装命令 |
| :--- | :--- | :--- |
| **`elfcat`** | **可视化分析 ELF 文件结构** | `cargo install elfcat` |
| **`bat`** | 优雅地查看**文本文件** | `cargo install bat` |
| **`hexyl`** | 彩色查看**任何二进制文件**的十六进制内容 | `cargo install hexyl` |

现在，你不仅解决了最初的错误，还解锁了一套强大又美观的现代命令行工具。希望 `elfcat` 彩色的输出能让你对看似神秘的二进制世界产生更大的兴趣！Enjoy！

---
```bash
# ww
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
重启终端
cargo --version
cargo install elfcat
elfcat /usr/bin/ls
ls
open ls.html # 浏览器打开 HTML 文件

```

---
### 可执行文件：字节序列
无论如何，可执行文件都是字节序列

ELF header

program header

the program

---
>ELF 可执行文件：ELF 是 Executable and Linkable Format 的缩写，是 Linux 系统上的一种可执行文件格式。我们可以试着去构造、理解、可视化 ELF 文件的结构。
```bash
python3 elf-minimal.py
# ELF>x@@@8xx@j<X1�
python3 elf-minimal.py > a.out
ls -l a.out
chmod +x a.out
./a.out
strace ./a.out
# execve("./a.out", ["./a.out"], 0x7ffdab2fdec0 /* 34 vars */) = 0
# exit(0)                                 = ?
# +++ exited with 0 +++

gdb a.out
starti
layout asm

open a.html # 浏览器打开 HTML 文件

elf ==== 一种数据结构
```

---
### 可执行文件：进程初始状态的描述
回顾：[System V ABI](https://jyywiki.cn/OS/manuals/sysv-abi.pdf)
- Section 3.4: “Process Initialization”
    - 只规定了部分寄存器和栈
    - 其他状态 (主要是内存) 由<b style="color:#4285F4">可执行文件</b>指定

**“可执行文件” 需要包含什么？**
- (今天先假设不依赖 “动态链接库”)
- 基本信息 (版本、体系结构……)
- 内存布局 (哪些部分是什么数据)
- 其他 (调试信息、符号表……)

---
### 于是我有了一个想法
**可执行文件其实<b style="color:#4285F4">不需要那么复杂</b>**
- 一个头 (类似 7f 45 4c 46; 这是一个 jg 71)
- 一段 Trampoline Code (PIC)
    - 操作系统会给一个文件描述符 (指向文件本身)
    - 这段代码直接执行 hardcoded mmap
- (就能实现 “加载” 的功能)

**剩下的信息都可以用更友好的方式表示**
- 反正是数据结构，一个 json
    - 符号表，调试信息，……

---
## 10.2 和 ELF 搏斗的每一年
### ELF: 不仅是 “可执行文件”
**一个经典、没有任何问题的设计**
- E = Executable
- L = Linkable
    - 一个标准，管好所有相关工具链
    - 甚至还有 Core Dump

**但是**
- ……

```bash
gcc a.c -c
ls
file a.o
# a.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
```

---
### 被《计算机系统基础》支配的恐惧？

---
### 和 ELF 搏斗的每一年
**你期末复习的时候吐血了吗？**
- 同学 A: 吐了
- 同学 B: 吐了
    - “连 CSAPP 这一章都讲得不怎么样”

**不只是你们，我们也在吐血**
- 任课教师 A: 第一次打开 ppt 真的有点吐血的感觉
- 任课教师 B: 根本讲不完，我估计听懂的人也不多
- 任课教师 C (我自己)：太好了，再也不用教了

**我们面对的挑战：到底要不要读手册呢？**

---
### 为什么？
**反思**
- ELF 不是一个<b style="color:#4285F4">人类友好</b>的 “状态机数据结构描述”
    - 为了性能，彻底违背了可读 (“信息局部性”) 原则

**几乎让你直接去读一个内存里的二叉树**
- “Core dump”
    - Segmentation fault (core dumped)
    - (为什么叫 “core dump”？)
- 地狱笑话：今天的 core dump 是个 ELF 文件
    - “状态快照”——Everything is a state machine
```bash
offset???
```

---
### 64 × 64 Bit Magnetic Core Memory
电磁铁

---
>Core Dump: 通过设置 core dump size，我们可以在程序发生 core dump 时保存到文件系统，并且在后续使用 gdb 调试它。
```bash
# ww
fish
./crash
# fish: Job 1, “./crash” terminated by signal SIGSEGV (Address boundary error)
bash
./crash
# Segmentation fault (core dumped)
ulimit -c unlimited  # 临时允许生成无限大小的 core 文件
```

---
```bash
bash
ulimit -c unlimited
./crash

Ubuntu 系统，其默认开启了 apport服务来捕获和处理崩溃信息
# 查看 core 文件
cat /proc/sys/kernel/core_pattern
# |/wsl-capture-crash %t %E %p %s
# 临时修改
echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern
./crash
# core-crash-4658-1757225133 但没有内容 
2. 文件系统问题
如果您在 Windows 文件系统（如 /mnt/c/）中运行程序，NTFS 文件系统可能无法正确处理 Linux 的核心转储文件，导致生成的文件为空。
ls
ps
ls
file core.1153
# core.1153: ELF 64-bit LSB core file, x86-64, version 1 (SYSV), SVR4-style, from './crash', real uid: 1000, effective uid: 1000, real gid: 1000, effective gid: 1000, execfn: './crash', platform: 'x86_64'
elfcat core.1153 翻车
readelf -a core.1153 | less

gdb crash core.1153
layout src
bt  # 查看回溯
p x
x x
p $rdi
# $2 = 3
```

---
>PROMPT: echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern后有文件为什么没有内容

# 🔍 WSL2 Ubuntu 中 Core Dump 文件为空的原因分析与解决

您遇到的问题是：在 WSL2 Ubuntu 中执行 `echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern` 后，程序崩溃时生成了 core 文件，但文件内容为空。这是一个常见但令人困惑的问题，下面我将详细解释可能的原因和解决方案。

## 🧠 可能的原因分析

### 1. **WSL2 特有的限制**
WSL2 作为一个在 Windows 上运行的 Linux 子系统，对核心转储的支持可能不完全。特别是当 `core_pattern` 之前被设置为管道 `|/wsl-capture-crash` 时，这表明 Microsoft 可能为 WSL2 实现了一个特殊的核心转储捕获机制，而这个机制可能与直接文件输出不兼容。

### 2. **文件系统问题**
如果您在 Windows 文件系统（如 `/mnt/c/`）中运行程序，NTFS 文件系统可能无法正确处理 Linux 的核心转储文件，导致生成的文件为空。

### 3. **权限问题**
虽然您使用了 `sudo` 修改了 `core_pattern`，但程序运行时可能没有足够的权限写入完整的核心转储。

### 4. **程序本身的问题**
某些类型的崩溃（如堆栈溢出）可能无法生成有效的核心转储，或者程序可能设置了某些标志阻止核心转储的生成。

## 🛠️ 解决方案

### 1. **使用 WSL2 本地文件系统**
首先，确保您在 WSL2 的本地文件系统（如 `/home/yourusername` 或 `/tmp`）中运行程序，而不是在 `/mnt/c/` 等挂载的 Windows 文件系统中。

```bash
# 切换到 WSL2 本地文件系统
cd /tmp
# 复制您的程序到当前目录
cp /path/to/your/crash .
# 设置核心转储
ulimit -c unlimited
echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern
# 运行程序
./crash
```

### 2. **验证核心转储配置**
确保您的配置已正确应用：

```bash
# 检查 ulimit 设置
ulimit -c
# 应该显示 "unlimited"

# 检查 core_pattern 设置
cat /proc/sys/kernel/core_pattern
# 应该显示 "core.%p" 而不是管道
```

### 3. **使用更详细的核心转储格式**
尝试使用包含更多信息的核心转储格式：

```bash
# 设置包含程序名、PID 和时间戳的 core 文件命名
echo "core.%e.%p.%t" | sudo tee /proc/sys/kernel/core_pattern
```

### 4. **使用绝对路径指定核心转储位置**
创建一个专用目录用于存储核心转储文件：

```bash
# 创建核心转储目录
sudo mkdir -p /var/cores
sudo chmod 777 /var/cores  # 设置宽松权限以便所有用户可写

# 设置核心转储到该目录
echo "/var/cores/core.%e.%p.%t" | sudo tee /proc/sys/kernel/core_pattern

# 运行程序后检查该目录
ls -la /var/cores/
```

### 5. **测试简单程序**
创建一个简单的测试程序来验证核心转储功能：

```bash
# 创建测试程序
cat > test_segfault.c << 'EOF'
#include <stdlib.h>
int main() {
    int *ptr = NULL;
    *ptr = 42;  // 这一定会导致段错误
    return 0;
}
EOF

# 编译测试程序
gcc -g test_segfault.c -o test_segfault

# 运行测试
ulimit -c unlimited
./test_segfault

# 检查是否生成了有效的核心转储
ls -la core.*
```

### 6. **检查系统日志**
查看系统日志以获取更多信息：

```bash
dmesg | tail -20
```

日志中可能会提供关于为什么核心转储失败或为空的线索。

### 7. **使用 GDB 直接调试**
如果核心转储仍然为空，尝试使用 GDB 直接运行程序：

```bash
gdb ./crash
(gdb) run
# 当程序崩溃时，GDB 会捕获现场，您可以输入：
(gdb) bt  # 查看回溯
(gdb) info registers  # 查看寄存器状态
```

### 8. **检查程序编译选项**
确保程序编译时包含了调试信息（使用 `-g` 选项）：

```bash
# 重新编译程序，包含调试信息
gcc -g -o crash crash.c
```

### 9. **尝试不同的崩溃类型**
有些类型的崩溃（如除以零）可能比空指针解引用更能可靠地生成核心转储：

```bash
# 创建除以零测试程序
cat > test_divzero.c << 'EOF'
#include <stdlib.h>
int main() {
    int a = 10;
    int b = 0;
    int c = a / b;  // 除以零
    return 0;
}
EOF

gcc -g test_divzero.c -o test_divzero
./test_divzero
```

### 10. **检查 WSL2 版本和更新**
确保您的 WSL2 是最新版本，因为 Microsoft 经常更新 WSL2 以改进与 Linux 功能的兼容性：

```bash
# 在 Windows PowerShell 或命令提示符中检查 WSL 版本
wsl --list --verbose
wsl --update
```

## 📝 永久配置

要使配置在重启后仍然有效，请编辑 sysctl 配置文件：

```bash
# 编辑 sysctl 配置
sudo nano /etc/sysctl.conf

# 在文件末尾添加以下行
kernel.core_pattern = /var/cores/core.%e.%p.%t

# 保存文件后，应用配置
sudo sysctl -p
```

## 🔍 验证核心转储内容

生成了核心转储文件后，使用以下命令验证其内容：

```bash
# 检查文件类型
file core.12345

# 检查文件大小
ls -lh core.12345

# 尝试使用 GDB 读取核心转储
gdb ./crash core.12345
```

如果 GDB 能够读取核心转储并显示回溯信息，说明核心转储是有效的。

## 💡 总结

在 WSL2 Ubuntu 中核心转储文件为空的问题通常与 WSL2 的特殊环境有关。通过以上步骤，您应该能够诊断并解决这个问题。关键点包括：

1. 使用 WSL2 本地文件系统而不是 Windows 挂载的文件系统
2. 验证核心转储配置是否正确应用
3. 使用包含更多信息的核心转储命名格式
4. 创建一个专用目录用于存储核心转储
5. 使用简单的测试程序验证功能

如果所有方法都失败，考虑直接在 GDB 中运行程序进行实时调试，这通常比分析核心转储文件更可靠。

---
>PROMPT: wsl2 ubuntu :cat /proc/sys/kernel/core_pattern输出的是管道|/wsl-capture-crash %t %E %p %s，怎么设置能在同目录输出core.pid帮我生成新手友好的教程/介绍/解释

我了解你在 WSL2 的 Ubuntu 中希望程序崩溃时能在**同一目录**下生成 `core.PID` 文件，而不是被管道截取。这对调试程序很有帮助。下面是一个新手友好的分步教程。

# 🔧 WSL2 Ubuntu 中配置 Core Dump 文件生成指南

## 📌 核心配置步骤概览

以下是实现你需求的快速操作摘要，接下来我会详细解释每一步。

| 步骤 | 命令 | 说明 |
| :--- | :--- | :--- |
| **1. 启用 core dump** | `ulimit -c unlimited` | 设置当前会话 core 文件大小无限制 |
| **2. 设置生成路径与格式** | `echo "core.%p" \| sudo tee /proc/sys/kernel/core_pattern` | 设置在当前目录生成 `core.PID` 文件 |
| **3. (可选) 永久生效** | 编辑 `/etc/sysctl.conf` 并添加 `kernel.core_pattern=core.%p` | 重启 WSL2 后配置依然有效 |

## 💡 关于 Core Dump 和 WSL2 的默认行为

当 Linux 程序发生严重错误（如段错误 Segmentation Fault）时，系统默认可以生成一个 **core dump** 文件。这个文件包含了程序崩溃时的内存状态，是调试的重要依据。

在你的 WSL2 Ubuntu 中，`cat /proc/sys/kernel/core_pattern` 输出 `|/wsl-capture-crash %t %E %p %s`，这表明 core dump 被默认配置为通过管道发送给一个名为 `wsl-capture-crash` 的工具处理，而不是直接生成文件。这或许是 WSL2 为了与 Windows 系统集成所做的设置。

## 🛠️ 详细配置步骤

### 1. 启用 core dump 生成

首先，你需要取消 shell 的 core 文件大小限制。

```bash
# 设置 core 文件大小为无限制，此设置仅对当前终端会话有效
ulimit -c unlimited
```

**验证设置**：
```bash
ulimit -c
```
如果输出 `unlimited`，说明设置成功。

### 2. 修改 core 文件生成路径和命名规则

接下来是关键步骤，修改 `core_pattern`，覆盖默认的管道行为。

```bash
# 此命令告诉系统将 core dump 写入当前目录，文件名为 core.%p
# %p 是一个占位符，会被触发 core dump 的进程的 PID (进程 ID) 替换
echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern
```

**常用 `core_pattern` 格式符**：
| 符号 | 含义 | 示例文件名 |
| :--- | :--- | :--- |
| `%p` | **进程 PID** | `core.1234` |
| `%e` | 可执行程序文件名 | `core.myapp` |
| `%t` | Unix 时间戳 | `core.1623456789` |
| `%u` | 用户 ID | `core.1000` |
| 组合使用 | | `core.myapp.1234` |

### 3. (强烈推荐) 使配置永久生效

通过 `echo` 命令的修改在 **WSL2 重启后会失效**。要永久生效，需修改 sysctl 配置文件。

```bash
# 使用 nano 编辑器编辑 sysctl 配置文件 (也可选用 vim)
sudo nano /etc/sysctl.conf
```
在文件末尾添加以下一行：
```
kernel.core_pattern=core.%p
```
保存并退出编辑器（在 nano 中按 `Ctrl+X`，然后按 `Y` 确认，最后按 `Enter`）。

**应用新的配置**：
```bash
# 重新加载 sysctl 配置
sudo sysctl -p
```
现在，即使重启 WSL2，配置也会保持。

## 🧪 测试配置是否成功

让我们创建一个必定会崩溃的小程序来测试。

1.  **创建测试程序**：
    ```bash
    # 创建一个简单的 C 程序文件
    cat > test_crash.c << 'EOF'
    #include <stdio.h>
    int main() {
        int *p = NULL;
        *p = 42; // 对空指针写入，必然引发段错误
        return 0;
    }
    EOF
    ```

2.  **编译程序**（需要安装 `build-essential`）：
    ```bash
    # 如果尚未安装 gcc，请先运行: sudo apt update && sudo apt install build-essential
    gcc -g test_crash.c -o test_crash  # -g 选项包含调试信息
    ```

3.  **运行并触发 core dump**：
    ```bash
    # 确保已在要生成 core 文件的目录设置了正确的权限
    ./test_crash
    ```
    如果看到 `Segmentation fault (core dumped)`，说明系统已尝试生成 core dump。

4.  **检查结果**：
    ```bash
    ls -la core.*
    ```
    你应该能看到一个类似于 `core.1234` 的文件（1234 是当时进程的 PID）。

## 🔍 使用 GDB 分析 Core Dump 文件

生成了 core 文件后，你可以使用 GDB 来诊断程序崩溃的原因。

1.  **安装 GDB**（如果尚未安装）：
    ```bash
    sudo apt install gdb
    ```

2.  **使用 GDB 加载 core 文件**：
    ```bash
    # 格式: gdb <你的程序可执行文件> <core文件>
    gdb ./test_crash core.1234
    ```

3.  **常用 GDB 命令**：
    -   输入 `bt`（backtrace）：查看**调用堆栈**，这是定位问题最重要的信息，它能显示程序崩溃时执行到了哪个函数的哪一行。
    -   输入 `f #`（frame）：切换到堆栈跟踪中的第 `#` 层帧，查看特定层的代码和变量。
    -   输入 `p variable`（print）：打印变量的值。
    -   输入 `q`（quit）：退出 GDB。

## ⚠️ 注意事项和故障排除

*   **当前目录权限**：确保运行程序的用户对当前目录有**写入权限**。你可以使用 `ls -ld .` 检查权限。如果权限不足，可以尝试在 `/tmp` 目录下进行操作。
    ```bash
    cd /tmp
    cp /path/to/your/program .
    ./program
    ```
*   **WSL2 文件系统**：建议在 WSL2 的 Linux 原生文件系统（如 `/home/yourusername` 或 `/tmp`）下进行测试，而不是在 `/mnt/c/` 挂载的 Windows 文件系统中，以避免潜在的权限问题。
*   **确认配置生效**：修改 `core_pattern` 后，再次运行 `cat /proc/sys/kernel/core_pattern` 确认其值已从管道变为 `core.%p`。
*   **如果仍未生成**：
    *   检查 `ulimit -c` 是否返回 `unlimited`。
    *   运行 `dmesg | tail -n 20` 查看系统日志，有时会有生成失败的线索。

## 📚 总结

通过以上步骤，你已成功将 WSL2 Ubuntu 从默认的管道处理 core dump 行为，配置为在程序当前目录下生成 `core.PID` 文件。这对于本地调试程序问题非常方便。

记住两个关键点：
1.  **临时设置**：使用 `ulimit -c unlimited` 和 `echo "core.%p" | sudo tee /proc/sys/kernel/core_pattern`。
2.  **永久设置**：在 `/etc/sysctl.conf` 中添加 `kernel.core_pattern=core.%p` 并运行 `sudo sysctl -p`。

希望本教程能帮助你更有效地进行开发调试。

---
### 既然提到 Core Dump 了
**在不那么方便 gdb 的时候**
- ulimit -c unlimited (或者一个你认为合理的值)
- Crash (SIGSEGV, SIGABRT, SIGILL, ...) 时会做 core dump
    - 适合于 production systems

**但 gdb 竟然不允许我继续执行**
- 明明状态里该有的都有啊 (内存 + 寄存器)
    - 往回走呢？2018 年你还可以发一篇 [OSDI](https://www.usenix.org/conference/osdi18/presentation/weidong) 了
- 想要继续执行？可以用 [CRIU](https://criu.org/Main_Page)
    - 智能 Agent 时代，这玩意可好用了

ww:
电脑休眠：可以断电 ==== core dump 快照？

迁移难点：
操作系统 
pid = 1234
fd

---
### 但曾经，并不是这样的
**UNIX [a.out](https://man.freebsd.org/cgi/man.cgi?a.out(5)) “assembler output”**
一个相对平坦的数据结构
```c
struct exec {
    uint32_t  a_midmag;  // Machine ID & Magic
    uint32_t  a_text;    // Text segment size
    uint32_t  a_data;    // Data segment size
    uint32_t  a_bss;     // BSS segment size
    uint32_t  a_syms;    // Symbol table size
    uint32_t  a_entry;   // Entry point
    uint32_t  a_trsize;  // Text reloc table size
    uint32_t  a_drsize;  // Data reloc table size
};
```
- 功能太少 (不支持动态链接、调试信息、内存对齐、thread-local……)，自然被淘汰

---
### 换句话说……
**支持的特性越多，越不人类友好**
- 听到 “程序头表”、“节头表”，大脑需要额外转译
- 含义隐晦的 `R_X86_64_32`, `R_X86_64_PLT32`
- 大量的 “指针” (人类无法阅读的偏移量)
    - (我竟然已经被训练成基本可以正常阅读了 😂)
    - 卷王们在考试周经历了同样的魔鬼训练
        - <b style="color:#4285F4">这就是大学需要改变的地方</b>

**人类友好的方式**
- <b style="color:#4285F4">越 “平坦”，越容易理解</b>
- 所有需要的信息都立即可见

---
### 给你一次重新设计的机会
**那就设计一个 FLE 吧**
- Funny (Fluffy) Linkable Executable
- AIGC
    - Friendly Learning Executable (GPT-4o)
    - Fast Learner's Executable (DeepSeek-r1)

**核心设计思路**
- 一切都<b style="color:#4285F4">对人类直接可读</b> (所有信息都在局部)
- 回归链接和加载中的核心概念：代码、符号、重定位
    - 你们会怎么设计？

---
## 10.3 Funny Little Executable
### 代码 (🔢)、符号 (📤)、重定位 (❓)
- 凑齐这三要素，我们就可以完成链接到加载的全流程了！

```c
🔢: ff ff ff ff ff ff ff
🔢: ff ff ff ff ff ff ff
📤: _start
🔢: 48 c7 c0 3c 00 00 00
🔢: 48 c7 c7 2a 00 00 00
             ^
             |
          This byte is return code (42).
🔢: 0f 05 ff ff ff ff ff
🔢: ff ff ff ff ff ff ff
❓: i32(unresolved_symbol - 0x4 - 📍)
```

```bash
objdump -d a.o
# a.o:     file format elf64-x86-64


# Disassembly of section .text:

# 0000000000000000 <foo>:
#    0:   f3 0f 1e fa             endbr64 
#    4:   55                      push   %rbp
#    5:   48 89 e5                mov    %rsp,%rbp
#    8:   b8 00 00 00 00          mov    $0x0,%eax
#    d:   e8 00 00 00 00          call   12 <foo+0x12>
#   12:   90                      nop
#   13:   5d                      pop    %rbp
#   14:   c3                      ret    
bar() 未实现
a.o 有空白

readelf -a a.o | less
# R_X86_64_PLT32
```

---
### 这是一个 DSL (Domain-specific Language)
**我们为什么需要 DSL？**
- 只要领域内的表达能力
    - 做了减法，就可以更<b style="color:#4285F4">专注</b>

**DSL 的例子**
- 正则表达式
- Markdown, TeX, ...
- [abcjs](https://www.abcjs.net/)

```c
DSL: 领域特定语言
AI:如何用正则表达式提取内容?
```

---
>Funny Little Executable: 我们 “自行设计” 了能实现 (静态) 链接和加载的二进制文件格式，以及相应的编译器、链接器 (复用 gcc/ld) 和加载器。FLE 文件直接将一段可读、可写、可执行的位置无关代码连通数据映射到内存并跳转执行。
```bash
./minimal.fle
echo $? # == fish: echo $status
# 42
`2a`-->`2b`
# 43

./readfle minimal.fle
./objdump minimal.fle 
./objdump libc.fle
./nm minimal.fle 
```

---
### 实现 FLE Binutils
**实现的工具集**
- objdump/readfle/nm (显示)
- cc/as (编译)
- ld (链接)

**大部分都复用自 GNU binutils**
- elf_to_fle

```bash
make
# ./cc -Wall -g -Os foo.c -o foo.o
# ./cc -Wall -g -Os libc.c -o libc.o
# ./cc -Wall -g -Os main.c -o main.o
# ./ld foo.fle libc.fle main.fle -o hello
file hello 
./hello 
echo $? 
./nm hello 

objdump -d foo.o
foo.c vs foo.o

0x4
为什么要减去4：因为调用函数真正的地址 = call指令的下一条指令的地址 + call 指令后面的地址
```

---
（以下是为汇编和链接新手设计的友好教程，尽量使用类比和直观解释）

# 🌟 轻松理解：为什么代码中会有"print - 0x4 - 📍"？

## 1. 先打个比方：导航系统中的"相对位置"

想象一下你在开车，导航说：
> "请在**前方500米**处右转"

这里的"前方500米"就是一个**相对距离** - 它相对于你**当前的位置**。

在计算机世界中，代码中的跳转指令（如`call print`）也需要计算这样的"相对距离"，这就是`print - 0x4 - 📍`的由来！

---

## 2. 三个关键角色

在理解这个表达式前，先认识三位"演员"：

### 🎯 `print` - 目的地
- 这是你想要去的函数（比如`print`函数）
- 相当于导航中的"目标地址"

### 📍 `📍` - 当前位置
- 当前指令在内存中的地址
- 相当于你开车时的"当前位置"

### 🔢 `0x4` - 特殊调整值
- 这是一个技术性的"微调值"
- 因为CPU执行指令时总是"看着前方"

---

## 3. 为什么需要"-0x4"？CPU的"小怪癖"

关键原因：**CPU总是超前看**！

当CPU执行一条指令时：
1. 它已经**预先读取**了下一条指令的地址
2. 这个"预读地址"就是**当前指令地址 + 指令长度**

在x86-64架构中：
- `call`指令长度是5字节（1字节操作码 + 4字节偏移量）
- CPU执行`call`时，实际上已经指向了下一条指令

所以需要**减去4字节**来补偿这个"超前"！

```plaintext
实际需要的偏移量 = 目标地址 - (当前位置 + 5)
但通过：目标地址 - 4 - 当前位置 = 同样的结果！
```

---

## 4. 具体例子：call print指令

假设我们有这样的代码：
```asm
call print
mov eax, 0
```

在内存中的布局：
```
地址        指令
0x1000:     e8 ?? ?? ?? ??    ; call print（5字节）
0x1005:     b8 00 00 00 00    ; mov eax, 0（下一条指令）
```

计算过程：
1. 📍 = 0x1001（偏移字段的地址）
2. CPU执行call时，RIP = 0x1005（指向下一条指令）
3. 需要计算：print地址 - 0x1005
4. 但通过：print - 4 - 0x1001 = print - 0x1005

看到吗？两种算法结果相同！这就是魔法的所在✨

---

## 5. 现实生活中的类比

想象你在数步数：
- 你站在第10步的位置
- 你想走到第30步的位置
- 但你的步伐长度是5步

正确的数法："我需要走**20步**"（30 - 10 = 20）

汇编器的做法："30 - 4 - 10 = 16"，然后因为知道步伐长度，会做相应调整。

虽然算法不同，但最终都能让你准确到达目的地！

---

## 6. 总结：一句话理解

**`print - 0x4 - 📍` 就像是在说：**
> "从我现在的位置，考虑到CPU总是多看4字节的习惯，到print函数还需要多少距离？"

---

## 7. 给初学者的建议

如果还是觉得抽象，没关系！记住这些关键点：
1. 这是**链接器**的工作，不是你需要手动计算的
2. 所有相对跳转都需要这种计算
3. `-0x4`是x86架构的特殊要求
4. 不同的CPU架构可能有不同的调整值

当你以后看到这样的表达式，只需要知道："啊，这是在计算相对跳转的距离！" 👍

希望这个解释对你有帮助！编程路上一起加油！💪

---
### 生成可执行文件 (1)：预编译 & 编译
**源代码 (.c) → 源代码 (.i)**
- Ctrl-C & Ctrl-V (#include)
- 字符串替换
- 今天：我们有[过程宏](https://doc.rust-lang.org/reference/procedural-macros.html)

**源代码 (.i) → 汇编代码 (.s)**
- “高级状态机” 到 “低级状态机” 的翻译
- 最终生成带标注的指令序列

---
### 生成可执行文件 (2)：汇编
**汇编代码 (.s) → 目标文件 (.o)**
- 文件 = sections (.text, .data, .rodata.str.1, ...)
    - 对于 ELF，每个 section 有它的权限、内存对齐等信息
- section 中的三要素
    - <b style="color:#4285F4">代码</b> (字节序列)
    - <b style="color:#4285F4">符号</b>：标记 “当前” 的位置
    - <b style="color:#4285F4">重定位</b>：暂时不能确定的数值 (链接时确定)
        - Quick Quiz: ELF 中全局和局部符号有什么区别？还有其他类型的符号吗？

---
### 生成可执行文件 (3)：(静态) 链接
**多个目标文件 (.o) → 可执行文件 (a.out)**
- 合并所有的 sections
    - 分别合并 .text, .data, .bss 中的代码
    - 把 sections “平铺” 成字节序列
    - 确定所有符号的位置
    - 解析全部重定位
- 得到一个<b style="color:#4285F4">可执行文件</b> 
    - (程序初始内存状态的描述)

---
### 最后一步：加载
**把 “字节序列” 搬到内存**
- 没错，就只做这一件事
- 然后设置正确的 PC，开始运行
```py
mem = mmap.mmap(
    fileno=-1, length=len(bs),
    prot=mmap.PROT_READ | mmap.PROT_WRITE | mmap.PROT_EXEC,
    flags=mmap.MAP_PRIVATE | mmap.MAP_ANONYMOUS,
)
mem.write(bs)
mem.flush()
call_pointer(mem, fle['symbols']['_start'])
```
```bash
# ww 
fle.py 慢慢看
```

---
## 10.4 操作系统和加载器
### 加载器是内核实现的一部分
**execve(path, argv, envp)**
- 操作系统内核解析 path、完成加载
- 还有[代码 (binfmt_elf.c)](https://elixir.bootlin.com/linux/v6.13.7/source/fs/binfmt_elf.c)呢
    - 可以在源码里找到手册 (System V ABI)中的概念
        - argc, argv, envp:
            ```c
            if (put_user(argc, sp++))
                    return -EFAULT;
            ```
    - 关键字搜索：PT_LOAD
    - 有代码的地方就有 bug: [CVE-2024-46826](https://cvefeed.io/vuln/detail/CVE-2024-46826)

---
### 等等
**运行程序的两种方法**
/bin/ls (这是一个 ELF) v.s. ./a.py (这可是文本啊！)
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"a.py", NULL};
    extern char **environ;

    execve(args[0], args, environ);

    // 如果execve失败，执行到这里
    perror("execve");
    return 1;
}
```
```bash
/bin/ls

file a.py
# a.py: Python script, ASCII text executable

gcc -Wall -g a.c
./a.out
修改a.py
./a.out 

```
---
### #! - Shebang
**UNIX 对 # 注释的 “妙用”**
- any_file: `#!A B C`
    - 操作系统会执行 execve(A, ["A", "B C", "any_file"], envp)
    - (我们的 FLE 文件是可以<b style="color:#4285F4">直接执行</b>的)
- Linux 的实现：[binfmt_script.c](https://elixir.bootlin.com/linux/v6.13.7/source/fs/binfmt_script.c)
    - 优先使用 `#!` 作为解释器 (Magic Number)
```c
/* Not ours to exec if we don't start with "#!". */
if ((bprm->buf[0] != '#') || (bprm->buf[1] != '!'))
        return -ENOEXEC;
...
file = open_exec(i_name);
```

---
>Shebang: 在 UNIX 的早期，为了能更方便地将脚本作为可执行文件，实现了 #! 开头的 “可执行文件”，并沿用至今。Shebang 会调用第一行中执行的命令和参数，并把这个脚本文件作为命令行参数传入。

---
## 10.5 总结
　　**Take-away Messages**: 可执行文件是一个描述状态机初始状态的数据结构 (字节序列)；加载器就是把这个 “初始状态” 搬运到操作系统中的程序。用数据结构的眼光看可执行文件，就不难发现它不好阅读的原因：它的设计者并没有打算让你阅读它。这样的难题在《操作系统》课程中经常出现；而我们的应对方法是先理解一个粗糙但重要的模型，然后在此基础上理解工业级实现面临的挑战和问题。