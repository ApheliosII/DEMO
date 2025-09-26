# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

---
## 11. 动态链接和加载
可执行文件 (和 Core Dump) 都是描述进程状态的数据结构。对于 ELF 文件来说，其中最重要的部分是一些 PT_LOAD 的数据段，正确在进程地址空间中 (用 mmap) 映射它们，就能实现程序的加载——就像我们在 Funny Little Executable 里做的那样。

**本讲内容**：当开发者希望把库函数和应用程序 “分离” 开，但又希望库函数可以被调用，应该怎么办？

---
## 11.1 动态链接：机制
### “动态链接库”
**熟悉的 .dll 文件**

Dynamic Link Library

---
### 为什么需要动态链接？
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
- d3dx9_xxx.dll 就这样为每个游戏复制了一份
    -似乎不是个好想法？
    - 我们希望<b style="color:#4169E1"> “拆解” 应用程序</b>

---
### “拆解应用程序” 的需求 (1)
**实现运行库和应用代码分离**
- 应用之间的库共享
    - 每个程序都需要 glibc
    - 但系统里只需要<b style="color:#4169E1"> 一个副本</b>就可以了
        - 是的，我们可以用 ldd 命令查看
        - 运行库和应用代码还可以分别独立升级
- 大型项目的分解
    - 改一行代码不用重新链接 2GB 的文件
    - libjvm.so, libart.so, ...
        - NEMU: “把 CPU 插上主板”
```bash
ls /bin/ # 系统工具
ls /bin/ | wc -l # 工具数量

ldd /bin/ls # 依赖库
ldd /bin/ls
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 
file /lib/x86_64-linux-gnu/libc.so.6
file /bin/ls
# /bin/ls: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=36b86f957a1be53733633d184c3a3354f3fc7b12, for GNU/Linux 3.2.0, stripped
man ldd
```

---
### “拆解应用程序” 的需求 (2)
**库的依赖也是一种代码克隆**
- 震惊世界的 [xz-utils (liblzma) 投毒事件](https://scout.docker.com/vulnerabilities/id/CVE-2024-3094)
    - JiaT75 甚至悄悄[绕开了 oss-fuzz](https://github.com/google/oss-fuzz/pull/10667)
    - [Linux incident](https://cse.umn.edu/cs/linux-incident); [Greg Kroah-Hartman revert all commits from umn.edu](https://lore.kernel.org/lkml/20210421130105.1226686-1-gregkh@linuxfoundation.org/); [S&P'21 Statement](https://www.ieee-security.org/TC/SP2021/downloads/2021_PC_Statement.pdf) ☢️☢️☢️

**如果 Linux 应用世界是静态链接的……**
- libc 紧急发布安全补丁 → 重新链接<b style="color:#4169E1">所有</b>应用 😂
- [Semantic Versioning](https://semver.org/)
    - “Compatible” 是个有些微妙的定义
    - “Dependency hell”

```bash
gcc --version
# gcc (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0
ps --version
# ps from procps-ng 3.3.17

主版本号.次版本号.修订号
“Compatible” “Dependency hell”
“兼容性”与“依赖地狱”
```

---
>系统中安装的包: 我们可以使用脚本列出 (甚至画出) 系统中安装的包的依赖关系：只需要一个 prompt 就可以了——这让我们 “理解” 和 “探索” 计算机系统变得前所未有的容易。
```bash
# list-dep 列出当前系统apt安装的所有包和Dependency
./list-dep.py | less
# gcc_11 -> binutils [label=">= 2.38"];
>= =
手动安装包影响依赖关系

make
系统中没有安装 Graphviz 软件包中的 sfdp 命令
sudo apt update
sudo apt install graphviz
dot -V
which sfdp
make
firefox output.svg  # 画出依赖关系图

find . | less
find . -name '*.so'
```

---
## 11.2 mmap 和虚拟内存
### 一个有趣的实验
**程序**
- 构造一个非常大的 libbloat.so
    - 我们的例子：100M of nop (0x90)

**实验**
- 创建 1,000 个进程动态链接 libbloat.so 的进程
- 观察系统的内存占用情况
    - 100MB or 100GB?
    - (如果是后者，直播会立即翻车)
        - Prototypes are easy. Production is hard. (Elon Musk)

---
>共享库测试：我们启动 100 个代码为 100M 的函数，通过观察系统中的内存占用来测试多个独立启动的进程是否只保留一份共享库的代码副本。
```bash
# so-test
make
# gcc -shared -o libbloat.so bloat.c
# cc    -c -o main.o main.c
# gcc -o bloat main.o -L. -lbloat
ll libbloat.so
# -rwxrwxrwx 1 hhu hhu 104872736 Sep  8 15:35 libbloat.so*

./bloat
LD_LIBRARY_PATH=. ./bloat

./run &
ps
ps ax | grep bloat
pmap 7800
free -h
jobs
pkill bloat
free -h
```
---
# Bash 与 Fish Shell 中命令组合的差异

在 Fish shell 中能运行 `strace ./a.out &| vim -` 而在 Bash 中不能运行的原因在于两个 shell 对 `&|` 操作符的处理方式不同。

## 差异解释

### Fish Shell 中的 `&|`
- 在 Fish 中，`&|` 是一个特殊操作符，表示将命令放入后台**同时**将其输出通过管道传递
- 这相当于同时使用 `&`（后台执行）和 `|`（管道）的组合操作
- Fish 专门设计了这个语法糖来简化此类操作

### Bash Shell 中的情况
- Bash 不支持 `&|` 操作符
- 在 Bash 中，`&|` 会被解析为两个独立的字符：`&`（后台执行）和 `|`（管道）
- 这会导致语法错误，因为 Bash 期望管道符号后面必须紧跟另一个命令

## 解决方案

如果你需要在 Bash 中实现类似功能，可以使用以下几种方法：

### 方法 1：使用命名管道
```bash
mkfifo /tmp/mypipe
strace ./a.out > /tmp/mypipe &
vim - < /tmp/mypipe
rm /tmp/mypipe
```

### 方法 2：使用进程替换（Bash 特有）
```bash
vim - <(strace ./a.out)
```

### 方法 3：使用临时文件
```bash
strace ./a.out > /tmp/strace_output &
vim /tmp/strace_output
```

## 推荐方案

对于你的具体需求，最简单的方法是使用 Bash 的进程替换功能：

```bash
vim - <(strace ./a.out)
```

这个命令会：
1. 执行 `strace ./a.out` 并将其输出重定向到一个临时文件描述符
2. 将临时文件描述符作为参数传递给 `vim -`
3. Vim 会读取 strace 的输出内容

这样就能在 Bash 中实现与 Fish 的 `&|` 类似的效果。

---
### 共享库的加载
**<b style="color:#4169E1">计算机世界里没有魔法</b>**
- 你总能溯源到正确的行为
- a.out (动态链接) 的第一条指令不在程序里
    - 可以 starti 验证 (在 ld.so 里)
    - 这是 “写死” 在 ELF 文件的 INTERP (interpreter) 段里的
        - (我们甚至可以直接编辑它)
- a.out 执行时，libc 还没有加载
    - 可以 info proc mappings (pmap) 验证
- libc 是用 mmap 系统调用加载的
    - 可以 strace 验证
- <b style="color:#4169E1">只读方式 mmap 同一个文件，物理内存中只有一个副本</b>

```bash
$ vi a.c
$ gcc a.c
$ ./a.out
$ strace ./a.out *| vim - # fish
vim - <(strace ./a.out) # bash
ps
#  71631 pts/2    00:00:00 bash
pmap 71631 # libc.so.6

file a.out
readelf -h a.out
# Entry point address:               0x1060

gcc -static a.c
gdb a.out
starti
layout asm
# 0x401650 <_start> endbr64
readelf -h a.out
#  Entry point address:               0x401650

gcc a.c
gdb a.out
starti
# 0x00007ffff7fe3290 in _start () from /lib64/ld-linux-x86-64.so.2
info proc
# process 72539

# new bash
pmap 72539
# 0000555555554000      4K r---- a.out
# 0000555555555000      4K r-x-- a.out
# 0000555555556000      4K r---- a.out
# 0000555555557000      8K rw--- a.out
# 00007ffff7fbd000     16K r----   [ anon ]
# 00007ffff7fc1000      8K r-x--   [ anon ]
# 00007ffff7fc3000      8K r---- ld-linux-x86-64.so.2
# 00007ffff7fc5000    168K r-x-- ld-linux-x86-64.so.2
# 00007ffff7fef000     44K r---- ld-linux-x86-64.so.2
# 00007ffff7ffb000     16K rw--- ld-linux-x86-64.so.2
# 00007ffffffde000    132K rw---   [ stack ]
#  total              412K
没有libc
readelf -l a.out | less
# Program Headers:
#   INTERP  
#   [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]

这是 “写死” 在 ELF 文件的 INTERP (interpreter) 段里的
(我们甚至可以直接编辑它)
vim a.out
```

---
### 背后的机制：虚拟内存管理
**地址空间表面是 “若干连续的内存段”**
- 通过 mmap/munmap/mprotect 维护
- 实际是分页机制维护的 “幻象”

---
### 操作系统的 Tricks (1) 🌶️
**Virtual Memory**
- 操作系统维护 “memory mappings” 的数据结构
    - 这个数据结构很紧凑 (“哪一段映射到哪里了”)
- 延迟加载
    - 不到万不得已，不给进程分配内存
- 写时复制 (Copy-on-Write)
    - fork() 时，父子进程先只读共享全部地址空间
        - Page fault 时，写者复制一份

---
### 操作系统的 Tricks (2) 🌶️
**Memory Deduplication; Compression & Swapping**
- 反正都是虚拟内存了
    - 悄悄扫描内存
        - 如果有重复的 read-only pages，合并
        - (如果硬件提供 page hash 就更好了)
    - 悄悄扫描内存
        - 发现 cold pages，可以压缩/swap 到硬盘
        - (硬件提供了 Access/Dirty bit)
    - 我们还能悄悄扫描内存做什么？
        - 看看 AIGC 的答案吧！

`ww:` 内存去重、内存压缩、交换

---
### Prompt: (slides contents...) 我们还可以扫描内存做什么？
在虚拟内存机制下，通过后台扫描内存可探索以下研究方向：

1. **预测性内存优化**
- 基于访问模式识别高频使用的关联页面组，动态调整物理内存布局，提升缓存局部性。
- 结合硬件性能计数器（PMC），实现细粒度访存预测。
2. **安全增强型扫描**
- 检测敏感数据残留（如加密密钥），通过主动覆写降低侧信道攻击风险。
- 基于Page Fault的轻量级内存完整性验证，兼顾性能与安全。
3. **异构内存管理**
- 识别不同寿命周期的页面，将短生命周期页面优先分配至NVM（非易失内存），延长DRAM寿命。
- 结合内存类型感知的压缩策略，优化混合内存系统能效。
4. **语义感知去重**
- 利用程序分析技术识别逻辑重复但二进制不同的页面（如相同数据结构的不同实例），实现跨进程语义级去重。
5. **动态页粒度调整**
- 根据工作负载特征，在2MB大页与4KB小页间动态切换，平衡TLB命中率与内存碎片。
6. **跨虚拟机协同**
- 在云环境中实现Hypervisor层级的全局冷热页检测，协调多VM间的内存压缩/交换策略。
7. **持久化内存加速**
- 利用PMEM的字节寻址特性，将高频修改的元数据页定向到持久化内存，同时保障数据一致性。

这些方向均需结合硬件特性（如Intel CAT/CET、ARM MTE）与新型存储介质（CXL内存池、SCM），兼顾性能、安全与能效的协同优化。

---
## 11.3 实现动态链接
实现动态链接和加载
>All problems in computer science can be solved by another level of indirection. (Butler Lampson)

---
### 实现应用程序的拆解
**方案 1: libc.o**
- 在加载时完成重定位
    - 加载 = 静态链接
    - 省了磁盘空间，但没省内存
    - 致命缺点：时间 (链接需要解析很多不会用到的符号)

**方案 2: libc.so (shared object)**
- 编译器生成<b style="color:#4169E1">位置无关代码</b>
    - 加载 = mmap
    - 但函数调用时需要额外一次查表
- 这才对：映射<font color="#4169E1">同一个</font> libc.so，内存中只需要一个副本

---
### 动态加载：A Layer of Indirection
**编译时，动态链接库调用 = 查表**
```
call  *TABLE[printf@symtab]
```
**链接时，收集所有符号，<font color="#4169E1">“生成” 符号信息和相关代码</font>：**
```c
#define foo@symtab     1
#define printf@symtab  2
...

void *TABLE[N_SYMBOLS];

void load(struct loader *ld) {
    TABLE[foo@symtab] = ld->resolve("foo");
    TABLE[foo@printf] = ld->resolve("printf");
    ...
}
```
---
>dlbox: “极小” 动态链接和加载器，通过查表的方式实现动态链接符号的调用。有兴趣的同学可以在课后阅读 ELF 动态链接和加载的细节。
```bash
make
gcc  dlbox.c -o dlbox
# ./dlbox gcc libhello.S
# ./dlbox gcc libc.S
# ./dlbox gcc main.S
# ./dlbox objdump libhello.dl > libhello.txt
# sh: 1: ndisasm: not found
# ./dlbox objdump libc.dl > libc.txt
# sh: 1: ndisasm: not found
# sh: 1: ndisasm: not found
# ./dlbox objdump main.dl > main.txt
# sh: 1: ndisasm: not found
# rm -f *.o
sh: 1: ndisasm: not found
!!!
系统缺少 ndisasm这个反汇编工具。ndisasm通常是 ​​NASM​​ (Netwide Assembler) 软件包的一部分
sudo apt update && sudo apt install nasm

ls
./dlbox
./dlbox readdl libc.dl
# DLIB file libc.dl:

# 00000080  putchar
# 000000a7  exit
file libc.dl
# libc.dl: data
file libhello.dl
file main.dl
./dlbox readdl libhello.dl
./dlbox readdl main.dl

./dlbox objdump main.dl # 反汇编
./dlbox objdump libhello.dl # 反汇编
./dlbox objdump libc.dl # 反汇编

./dlbox interp main.dl # 请位于当前目录的 dlbox程序，以解释执行的方式，运行同一目录下名为 main.dl的脚本文件。​
strace ./dlbox interp main.dl

xxd libc.dl 
```

---
### dlbox: 再次 “实现” binutils
**编译和链接**
- 偷 GNU 工具链就行
    - ld = objcopy (偷来的)
    - as = GNU as (偷来的)

**解析和加载**
- 剩下的就需要自己动手了
    - readdl (readelf)
    - objdump
    - 同样可以山寨 addr2line, nm, objcopy, ...
- 加载器就是 ELF 中的 “INTERP”

---
### 我们实现了什么？
**我们 “发明” 了 GOT (Global Offset Table)！**
对于每个需要动态解析的符号，GOT - 中都有一个位置
- ELF: Relocation section “.rela.dyn”
```
  Offset          Info           Type        Sym. Name + Addend
...
000000003fe0  000300000006 R_X86_64_GLOB_DAT printf@GLIBC_2.2.5 + 0
...
```
- objdump 查看 3fe0 这个 offset ，位于 “GOT”:
    - printf("%p\n", printf); 看到的不是真正的 printf
    - *(void **)(base + 0x3fe0) 才是
    - 我们可以设置一个 “read watch point”，看看谁读了它

---
### 动态链接的主要功能
**实现<font color="#4169E1">代码</font>的动态链接和加载**
- main (.o) 调用 printf (.so)
- main (.o) 调用 foo (.o)

**难题：怎么决定到底要不要查表？**
```c
int printf(const char *, ...);
void foo();
```
- 是在同一个二进制文件 (链接时确定)？还是在库中 (运行时加载)？

`$ ww:`
- call <短跳转> a.out链接时确定
```bash
gcc main.c
objdump -d a.out | less
# .plt.sec:
# <printf@plt>
# jmp *0x2f75(%rip)
```

---
### 历史遗留问题：先编译、后链接
**编译器的选择 1: 全部查表跳转**
```
ff 25 00 00 00 00   call *FOO_OFFSET(%rip)
```
- 调用个 foo 都多查一次表，性能我不能忍 ❌

**编译器的选择 2: 全部直接跳转**
```
e8 00 00 00 00      call <reloc>
```
- %rip: 00005559892b7000
- libc.so.6: 00007fdcdf800000
    - 相差了 2a8356549000
    - 4-byte 立即数放不下，无论如何也跳不过去 ❌

---
### 还能那怎么办？
**为了性能，“全部直接跳转” 是唯一选择**
```
e8 00 00 00 00      call <reloc>
```
- 如果这个符号在链接时发现是 printf (来自动态加载)，就在 a.out 里 <b style="color:#4169E1">“合成” 一段小代码</b>：
```
printf@plt:
    jmp *PRINTF_OFFSET(%rip)
```
- 我们发明了 PLT (Procedure Linkage Table)！

---
### PLT: 没能解决数据的问题
**对于 `extern int x`，我们不能 “间接跳转”！**
- x = 1, 同一个 .so (或 executable)

`mov $1, offset_of_x(%rip)`

- x = 1, 另一个 .so
```
mov GOT[x], %rdi
mov $1, (%rdi)
```
**不优雅的解决方法**
- -fPIC 默认会为所有 extern 数据增加一层间接访问
    - `__attribute__((visibility("hidden")))`

---
>dsym: 动态链接库允许数据之间的共享；我们通过实现多个共享库来观察这一行为的实现。
```bash
make 
# gcc -Wall -fPIC -Os -c main.c -o main.o
# gcc -Wall -fPIC -Os -c liba-1.c -o liba-1.o
# gcc -Wall -fPIC -Os -c liba-2.c -o liba-2.o
# gcc -shared -o liba.so liba-1.o liba-2.o
# gcc -Wall -fPIC -Os -c libb-1.c -o libb-1.o
# gcc -Wall -fPIC -Os -c libb-2.c -o libb-2.o
# gcc -shared -o libb.so libb-1.o libb-2.o -L. -la
# gcc -o main main.o -L. -la -lb
// fPIC
objdump -d liba-2.o | less
# mov    0x0(%rip),%rax  
# mov    (%rax),%edx
# mov    %ecx,(%rax)
```

---
### LD_PRELOAD
**一个神奇的 “hook” 机制**
- 允许 “preload” 一个自己的库
    - 当然，没有魔法
    - LD_PRELOAD 会传递给 ld-linux.so
- 我们可以在运行时，用一个自己的库替换掉某个库
```
LD_PRELOAD=./mylib.so ./a.out
```

```bash
$ ww
LD_LIBRARY_PATH=. ./bloat
LD_LIBRARY_PATH=/ ./bloat
```

---
>LD_PRELOAD 机制: ld-linux 为我们提供了 “preload” 机制，通过 LD_PRELOAD 环境变量，我们可以指定一个动态链接库，在程序启动时，动态链接库中的函数会被优先调用，从而实现对程序的拦截和修改。
```bash
# ldpreload
make 
# gcc -Wall -Wextra -fPIC -shared -ldl -o libmalloc_hook.so malloc_hook.c
# gcc -Wall -Wextra -fPIC -o test_program test.c
./test_program
# Testing malloc/free hooks...
# Allocated 100 bytes at 0x56b55ab506b0
# Allocated 200 bytes at 0x56b55ab50720
# Allocated 300 bytes at 0x56b55ab507f0
LD_PRELOAD=./libmalloc_hook.so ./test_program
# [TRACE] malloc(1024) = 0x5c152f4d52a0
# Testing malloc/free hooks...
# [TRACE] malloc(100) = 0x5c152f4d56b0
# Allocated 100 bytes at 0x5c152f4d56b0
# [TRACE] free(0x5c152f4d56b0)
# [TRACE] malloc(200) = 0x5c152f4d5720
# [TRACE] malloc(300) = 0x5c152f4d57f0
# Allocated 200 bytes at 0x5c152f4d5720
# Allocated 300 bytes at 0x5c152f4d57f0
# [TRACE] free(0x5c152f4d57f0)
# [TRACE] free(0x5c152f4d5720)

LD_PRELOAD=./libmalloc_hook.so python3
1 enter
2 enter
```

---
## 11.4 总结
　　**Take-away Messages**: 找到正确的思路，我们就能在复杂的机制中找到主干：在动态链接的例子里，我们试着自己实现动态链接和加载——在这个过程中，我们 “发明” 了 ELF 中的重要概念，例如 Global Offset Table, Procedure Linkage Table 等。

---
# `.s` 文件？

Linux 系统中的 `.s` 文件是**汇编代码文件**（Assembly Source File），它包含的是人类可读的汇编指令，是高级语言代码（如 C/C++）与机器可执行的二进制代码之间的一个重要桥梁。

为了让你快速建立整体概念，我们先通过下面这张图了解 `.s` 文件在程序编译过程中的位置：

```mermaid
flowchart LR
    A[源代码<br>main.c] -->|预处理器<br>cpp / gcc -E| B[预处理文件<br>.i 文件]
    B -->|编译器<br>cc1 / gcc -S| C[汇编代码文件<br>.s 文件]
    C -->|汇编器<br>as / gcc -c| D[目标文件<br>.o 文件]
    D -->|链接器<br>ld / gcc| E[可执行文件]
```

### 🧠 为什么要了解 

你可能会问，我们平时都用 C、Python 或 Java 这些高级语言，为什么还要关心底层的汇编文件呢？主要有以下几个原因：

*   **深入理解计算机**：阅读 `.s` 文件就像直接看机器的“思考过程”，能让你真正理解代码是如何在 CPU 上执行的，理解内存、寄存器等概念。
*   **性能调优与排查问题**：当你要进行极端性能优化，或者排查一些极其诡异的 bug（比如某段 C 代码产生的行为就是不符合预期）时，查看编译器生成的汇编代码往往是最终手段。
*   **嵌入式与系统编程**：在嵌入式开发、操作系统、驱动开发等领域，经常需要直接与硬件打交道。有时为了极致的效率或直接控制硬件，必须编写或调试汇编代码。

### 📖 `.s` 文件里有什么？

一个典型的 `.s` 文件内容看起来是这样的（以 x86-64 架构为例）：

```nasm
    .file   "hello.c"          @ 源文件信息
    .text                      @ 表明以下是代码段
    .globl  main               @ 声明 main 为全局符号
    .type   main, @function    @ 指定 main 的类型是函数
main:                          @ main 函数标签
.LFB0:
    .cfi_startproc             @ 调用帧信息开始
    pushq   %rbp              @ 保存旧的栈帧基址
    movq    %rsp, %rbp        @ 建立新的栈帧基址
    movl    $.LC0, %edi       @ 将字符串地址放入 edi 寄存器
    call    puts              @ 调用 puts 函数
    movl    $0, %eax          @ 将返回值 0 放入 eax
    popq    %rbp              @ 恢复旧的栈帧基址
    ret                       @ 函数返回
    .cfi_endproc              @ 调用帧信息结束
.LFE0:
    .size   main, .-main       @ 设置 main 函数的大小
    .section    .rodata        @ 以下位于只读数据段
.LC0:
    .string "Hello, World!"   @ 字符串常量
```

它主要包含两种元素：

1.  **汇编指令**：如 `pushq`, `movl`, `call`。这些直接对应 CPU 能执行的机器指令，是**真正干活**的部分。
2.  **伪指令**（Assembler Directives）：以 `.` 开头，如 `.text`, `.globl`, `.size`。它们是**给汇编器的指示**，本身不生成机器码，用来指导汇编器如何工作，比如定义段、设置符号属性等。

### 🛠️ 如何生成并查看 `.s` 文件？

假设你有一个简单的 C 程序 `hello.c`：

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

使用 GCC 编译器可以轻松生成它的汇编文件：

```bash
gcc -S hello.c
```

执行后，当前目录下就会生成一个名为 `hello.s` 的文件。你可以用任何文本编辑器（如 `vim`, `nano`, `gedit`）或查看命令（如 `cat`, `less`）来打开它：

```bash
cat hello.s
```

**常用 GCC 选项说明**：
*   `-S`：让 GCC 在编译阶段（生成汇编代码后）停止。
*   `-o hello.s`：可以指定输出的文件名，例如 `gcc -S hello.c -o my_assembly.s`。
*   `-O2`：可以在生成汇编时启用优化，例如 `gcc -S -O2 hello.c`。对比优化前后的汇编代码变化是学习编译器优化的好方法！

### ⚙️ 汇编、链接与执行

生成了 `.s` 文件后，你还可以继续走下去，把它变成可执行程序：

1.  **汇编**：使用汇编器（如 `as`）将 `.s` 文件**汇编**成机器码（`.o` 目标文件）。
    ```bash
    as hello.s -o hello.o
    # 或者直接用 gcc 驱动
    gcc -c hello.s -o hello.o
    ```

2.  **链接**：使用链接器（如 `ld`）将目标文件与所需的库（如 C 标准库）**链接**成最终的可执行文件。
    ```bash
    gcc hello.o -o hello
    ```

3.  **运行**：
    ```bash
    ./hello
    ```

### ⚠️ 注意事项

*   **架构依赖性强**：不同 CPU 架构（如 x86、ARM、MIPS）的汇编指令集完全不同。你的 `.s` 文件通常只适用于一种特定的架构。
*   **调试信息**：在编译时加上 `-g` 选项（如 `gcc -S -g hello.c`）可以在生成的 `.s` 文件中包含更多的调试信息和符号，有时更便于阅读。
*   **与 `.S` 文件的区别**：注意文件名后缀的大小写！`.s`（小写 s）通常表示**不需要再经过预处理器**处理的纯汇编文件。而 `.S`（大写 S）文件则可以包含 `#include`、`#define` 等预处理指令，需要先由预处理器展开后再交给汇编器。

希望这份介绍能帮助你迈出探索底层世界的第一步！汇编语言是理解计算机真正如何工作的强大工具。

---
# 附录：`.S` 文件的语法和用法
在 Linux 开发中，`.S`（大写 S）文件也是**汇编代码文件**，但它和 `.s`（小写 s）文件有一个关键区别：`.S` 文件**会经过预处理阶段**，而 `.s` 文件不会。

为了让你快速理解它们的区别和用途，我准备了一个对比表格：

| 特性 | `.S` 文件 (大写) | `.s` 文件 (小写) |
| :--- | :--- | :--- |
| **预处理** | **支持**。编译器会先处理 `#include`, `#define`, `#ifdef` 等预处理指令。 | **不支持**。编译器会直接将其视为纯汇编代码进行汇编。 |
| **常见来源** | 多为**手工编写**的汇编源文件，常见于操作系统内核、Bootloader（如 Linux Kernel、U-Boot）。 | 多为由 **GCC** 等编译器**自动生成**（使用 `gcc -S` 选项）。 |
| **使用场景** | 需要**条件编译**、**宏替换**或**包含头文件**的复杂汇编程序。 | 无需预处理或已被预处理过的**纯汇编程序**。 |
| **编译命令** | `gcc -c source.S -o output.o` （GCC 会自动调用预处理器和汇编器） | `gcc -c source.s -o output.o` 或 `as source.s -o output.o` |

简单来说，`.S` 文件是“**待预处理的汇编代码**”，而 `.s` 文件是“**纯汇编代码**”。

### 🛠️ 如何编译 `.S` 文件

编译 `.S` 文件非常简单，GCC 会自动识别文件扩展名并安排预处理和汇编的流程：

```bash
gcc -c hello.S -o hello.o
```

这条命令会：
1.  先对 `hello.S` 文件进行**预处理**（展开所有 `#include`、`#define` 等）。
2.  将预处理后的结果交给汇编器（`as`）进行**汇编**，生成目标文件 `hello.o`。

之后，你就可以像平常一样链接目标文件来生成可执行文件了：

```bash
gcc hello.o -o hello
```

### 💡 为什么需要 `.S` 文件？

在系统级编程中，`.S` 文件非常有用，因为它结合了预处理器的灵活性和汇编语言的强大功能：

*   **条件编译**：你可以使用 `#ifdef`、`#if`、`#elif`、`#else`、`#endif` 等指令，根据不同的平台或配置编译不同的汇编代码。
*   **宏定义**：你可以使用 `#define` 来创建常量或宏，使代码更易读和维护，避免使用“魔法数字”。
*   **文件包含**：你可以使用 `#include` 将其他的头文件或汇编代码文件包含进来，便于代码的组织和复用。

这些特性在复杂的项目（如 Linux 内核）中几乎是必不可少的。

希望这个解释能帮你理清 `.S` 文件和 `.s` 文件之间的关系和区别！

---
## 一个典型的 `.S` 文件（支持预处理的汇编源文件）
包含 **预处理指令**、**汇编指令** 和 **汇编器伪操作**。下面是一个基于 x86/Linux 平台的简单示例，演示了如何使用汇编语言实现一个输出 "Hello, World!" 的程序：

```asm
# hello.S - 一个简单的 Linux x86 汇编程序，使用系统调用输出 "Hello, World!"
# 此文件使用 AT&T 汇编语法，并且支持 C 预处理器指令

# 1. 预处理指令（以 '#' 开头）
#include <asm/unistd.h>        /* 包含系统调用号定义，如 SYS_write */
#define STDOUT_FD 1            /* 标准输出文件描述符 */
#define MSG_LEN 13              /* 消息长度 */

# 2. 数据段：定义已初始化的数据
.section .data
    msg:
        .ascii "Hello, World!\n"   /* 定义要输出的字符串 */

# 3. 文本段（代码段）：存放程序指令
.section .text
    .globl _start                 /* 声明 _start 为全局符号，链接器需知 */
    .type _start, @function       /* 指定 _start 的类型为函数 */

_start:
    # 4. 系统调用：写入消息到标准输出
    movl $SYS_write, %eax        # 系统调用号：sys_write (4) 放入 eax
    movl $STDOUT_FD, %ebx         # 文件描述符：stdout (1) 放入 ebx
    movl $msg, %ecx              # 字符串地址放入 ecx
    movl $MSG_LEN, %edx          # 字符串长度放入 edx
    int $0x80                    # 触发软中断，调用内核

    # 5. 系统调用：退出程序
    movl $SYS_exit, %eax         # 系统调用号：sys_exit (1) 放入 eax
    xorl %ebx, %ebx              # 退出码：0 (异或操作清零 ebx)
    int $0x80                    # 触发软中断，调用内核

# 6. 文件结束
.size _start, . - _start         /* 定义 _start 函数的大小 */
```

### 🔍 关键组成部分解析（基于 AT&T 语法）

1.  **预处理指令 (`#`开头)**
    *   这些指令由 C 预处理器处理，**不是**汇编指令。
    *   `#include`：用于包含其他文件，例如系统调用号的定义。
    *   `#define`：用于定义常量，提高代码可读性和可维护性。
    *   这使得 `.S` 文件比 `.s` 文件更灵活。

2.  **段定义 (Sections)**
    *   `.section .data`：**数据段**。用于声明**已初始化**的全局变量或静态变量。这里的 `msg` 字符串在程序加载时就已经存在。
    *   `.section .text`：**文本段（代码段）**。用于存放实际的程序指令（代码）。该段通常是只读的。

3.  **汇编器伪操作 (Assembler Directives)**
    *   这些指令以 `.` 开头，指导汇编器如何工作，自身不生成机器码。
    *   `.globl _start`：声明 `_start` 为全局符号，使得链接器知道程序的入口点。
    *   `.type _start, @function`：指明 `_start` 符号的类型是一个函数。
    *   `.ascii`：在内存中分配并初始化一个字符串（不以空字符结尾）。
    *   `.size`：设置符号的大小（这里设置为从 `_start` 开始到当前地址的长度）。

4.  **汇编指令**
    *   这是实际的 CPU 指令，采用 **AT&T 语法**（在 Linux 中常见）。
    *   **操作数顺序**：`movl source, destination`（与 Intel 语法相反）。
    *   **操作数后缀**：`mov` 后的 `l` 表示操作长字（32 位）。类似的还有 `b`（字节，8 位）、`w`（字，16 位）。
    *   **寄存器前缀**：寄存器前加 `%`，如 `%eax`。
    *   **立即数前缀**：立即数前加 `$`，如 `$1`。
    *   **系统调用**：通过 `int $0x80` 软中断实现。参数通过寄存器传递（`eax`=调用号，`ebx`, `ecx`, `edx` 等依次传递参数）。

5.  **程序入口和退出**
    *   `_start` 是链接器默认的入口点（而不是 C 语言中的 `main`）。
    *   通过 `sys_exit` 系统调用正常退出程序，并将退出状态码返回给操作系统。

### 🛠️ 如何编译和运行

1.  **编译**（使用 GCC 预处理和汇编）：
    ```bash
    gcc -c hello.S -o hello.o
    ```
    或者直接生成可执行文件：
    ```bash
    gcc -nostdlib hello.S -o hello
    ```
    （`-nostdlib` 表示不链接标准 C 库，因为我们直接使用了系统调用）

2.  **链接**（如果你只生成了目标文件 `.o`）：
    ```bash
    ld hello.o -o hello
    ```

3.  **运行**：
    ```bash
    ./hello
    ```
    输出应为：
    ```
    Hello, World!
    ```

### 💡 示例说明

此程序没有使用任何 C 标准库函数，而是直接通过 Linux 内核提供的**系统调用**（syscall）来完成输出和退出操作。这展示了汇编语言与操作系统交互的最底层方式。

希望这个示例和解释能帮助你理解 `.S` 文件的基本结构和语法！

---
# 附录：`.s` 和 `.S` 文件的新手友好教程。

### 一句话总结

`.s` 和 `.S` 文件都是**汇编语言源代码文件**，但它们有一个关键区别：
*   **`.s`** 是**纯汇编代码**，编译器会直接将其翻译成机器码。
*   **`.S`**（大写S）是**需要“预处理”的汇编代码**，在翻译成机器码之前，会先由预处理器处理（比如处理 `#include`, `#define` 等指令），就像 C 语言一样。

你可以把 `.S` 文件想象成 **“加了调料和半成品菜”的汇编代码**，而 `.s` 文件是 **“已经切好、洗好的净菜”**。

---

### 详解与比喻

#### 1. 它们是什么？（汇编语言源代码）

计算机CPU（大脑）真正能读懂的是由 `0` 和 `1` 组成的**机器码**。但人类很难直接写 `0101`，所以发明了**汇编语言**。

汇编语言用一些**英文单词的缩写（称为“助记符”）** 来代替二进制的机器指令，让人更容易理解和编写。

例如：
*   `movl $10, %eax` 意思是 “将数字 10 移动到名叫 eax 的寄存器（CPU内部的小存储单元）里”。
*   `addl %ebx, %eax` 意思是 “将 eax 和 ebx 里的值相加，结果存回 eax”。

`.s` 和 `.S` 文件就是用来写这些汇编指令的**文本文件**。

#### 2. 关键区别：小写 `.s` vs 大写 `.S`

这是最容易混淆，也最重要的地方。

| 特性 | **小写 `.s` 文件** | **大写 `.S` 文件** |
| :--- | :--- | :--- |
| **预处理** | **不经过**预处理器 | **需要经过**预处理器 |
| **功能** | **纯汇编**。里面的内容必须是汇编器能直接看懂的指令。 | **“增强版”汇编**。除了汇编指令，还可以使用**预处理指令**。 |
| **类比** | **净菜**。下锅就能炒。 | **半成品菜包**，里面可能有酱料包（`#include`）、需要泡发的干菜（`#define`）。下锅前需要先打开处理一下。 |
| **常用指令** | `mov`, `add`, `jmp`, `.section`, `.globl` 等**汇编指令/伪指令** | **除了汇编指令，还可以用：** <br> • `#include "header.h"` （包含头文件）<br> • `#define MAX 100` （定义宏）<br> • `#ifdef DEBUG` （条件编译）<br> • `#include "another_file.s"` （包含其他汇编文件） |

**为什么这个区别很重要？**
因为预处理功能能让写汇编代码**更方便、更强大**！

**举个例子：**

假设你有一个常量 `0x400000`，它在代码里出现了几十次。现在需要把它改成 `0x500000`。

*   **如果用 `.s` 文件**：你只能手动找到并修改这几十个地方，非常容易出错。
*   **如果用 `.S` 文件**：你可以在文件开头写 `#define MY_ADDR 0x500000`，然后在代码里统一使用 `MY_ADDR`。要修改时，只需改这一行定义即可。

```S
# 这是一个 .S 文件的例子
#include <asm/asm.h>  // 包含一些平台相关的汇编宏定义

#define BUFFER_SIZE 1024

.section .text
.globl main

main:
    movl $BUFFER_SIZE, %eax  // 使用宏定义
    // ... 其他代码
```

#### 3. 它们有什么用？（应用场景）

你通常会在以下地方看到它们：

1.  **操作系统内核开发**（如 Linux Kernel）：
    *   系统启动时最早执行的代码（设置CPU模式、初始化内存等）必须用汇编编写，因为高级语言的环境还没建立起来。
    *   直接和硬件交互的底层操作（如开关中断）。
    *   实现一些非常关键、需要精确控制的性能优化代码。

2.  **编译器和标准库**：
    *   一些极其基础的函数（如 `memcpy`, `strcpy`）有时会用汇编精心优化，以达到极致的速度。

3.  **嵌入式系统和单片机编程**：
    *   在资源极其有限的设备上，为了精确控制硬件和节省每一字节的内存，常常直接使用汇编。

4.  **逆向工程与安全**：
    *   分析恶意软件或挖掘软件漏洞时，经常需要阅读反汇编工具生成的汇编代码（类似于 `.s` 文件）。

#### 4. 如何编译它们？

通常使用 `gcc`（GNU编译器集合）来编译。`gcc` 会根据文件后缀自动调用正确的工具链。

*   **编译 `.S` 文件**：
    ```bash
    gcc -c example.S -o example.o
    ```
    `gcc` 会先调用**预处理器**（cpp）处理 `#include` 和 `#define`，然后调用**汇编器**（as）将处理后的文本翻译成机器码文件 `example.o`（目标文件）。

*   **编译 `.s` 文件**：
    ```bash
    gcc -c example.s -o example.o
    ```
    `gcc` 会直接调用**汇编器**（as）进行翻译，因为不需要预处理。

最后，你需要用**链接器**（ld）将一个或多个 `.o` 目标文件链接成最终的可执行程序或库。

---

### 给新手的建议与总结

1.  **先学C语言**：理解指针、内存布局、函数调用栈等概念后，再学汇编会容易得多。
2.  **从阅读开始**：不要先想着写复杂的汇编。可以尝试用 `gcc -S` 命令把一个简单的C程序编译成 `.s` 文件，看看编译器是怎么生成汇编代码的。
    ```bash
    gcc -S hello.c  # 这会生成一个 hello.s 文件
    ```
3.  **记住区别**：新手最容易犯的错误就是给 `.S` 文件用了 `.s` 的后缀，导致预处理器指令（如 `#include`）报错。**当你看到关于 `#` 开头的指令报错时，第一反应就应该是：我是不是该把文件后缀改成大写的 `.S`？**
4.  **用途广泛**：虽然现在直接用汇编写整个程序的人很少了，但在底层系统、驱动、高性能计算等领域，理解和能阅读汇编仍然是**一项非常有价值的高级技能**。

希望这个解释对你有帮助！汇编是连接软件和硬件的桥梁，理解它会让你的编程功力更上一层楼。