# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

## 9. C 标准库和实现
操作系统为我们提供了对象和操作它们的 API：我们学习了进程管理的 `fork, execve, exit, waitpid`；内存管理的 `mmap；文件` (对象) 管理的 `open, read, write, dup, close, pipe, ……`大家观察到这些 API 的设计有一个有趣的原则：“非必要不实现” (“机制与策略分离”、“最小完备性原则”)：但凡应用程序能自己搞定的功能，操作系统就不需要提供——在一定程度上，这样的设计能防止 “包揽一切” 导致代码膨胀，甚至在长期演化的过程中成为历史的包袱。

**本讲内容**：在操作系统 API 之上，为了服务应用程序，毋庸置疑需要有一套 “好用” 的库函数。虽然 `libc` 在今天的确谈不上 “好用”，但成就了 C 语言今天 “高级的汇编语言” 的可移植地位，以 ISO 标准的形式支撑了操作系统生态上的万千应用。

---
## 9.1 libc 简介

---
### 从 “最小” 的 C 程序出发
```c
void _start() {
    __asm__("mov $60, %eax\n"  // syscall: exit
            "xor %edi, %edi\n" // status: 0
            "syscall");
}
```
**我们可以构建 “整个应用世界”**
- C 的语言机制
    - 指针、数组、结构体、函数……
- 系统调用
    - fork, execve, mmap, open, ...

---
### 系统调用是地基，C 语言是框架
**C 语言：世界上 “最通用” 的高级语言**
- C 是一种 “高级汇编语言”
    - 作为对比，C++ 更<b style="color:#4169E1">好用</b>，但也更<b style="color:#4169E1">难移植</b>
- 系统调用的一层 “浅封装”

**C23: 演进没有完全停止**
```c
constexpr int n = 5 + 4;  // ???
typeof(n) arr[n];  // ???

[[maybe_unused]] auto* ptr = foo();  // ???
ptr = nullptr;  // ???
```

---
Hardware 
Kernel
Shell ksh bash csh
Utilities cat vl nano ls wget

```bash
#ww
syscall -- ABI
```

---
### 当然：没有库函数，寸步难行
**就算有系统调用，也没法编程啊**
- 道理上可行，工程上不行
```c
int read(int fd, void *buf, size_t count);
int write(int fd, const void *buf, size_t count);

int main() {
    int a = ???; // 读入 a
    int b = ???; // 读入 b
    int sum = a + b;
    // 输出 sum ???
}
```

---
### The C Standard Library
**语言机制上的运行库**
- 大部分可以用 C 语言本身实现
- 少部分需要一些 “底层支持”
    - 例子：体系结构相关的内联汇编

**库也被标准化**
- ISO IEC 标准的一部分
- POSIX C Library 的子集
    - 稳定、可靠 (不用担心升级版本会破坏实现)
    - 极佳的移植性：包括你自己的操作系统！

---
### 如何 “实现” 一个 libc？


(当然是让 “老师” 当着你的面实现一个！)


---
### minilibc: 
>一个用于教育目的的 C 标准库的简化实现 (claude-3.7-sonnet Cursor IDE)，展示了 C 库的核心组件，包括程序的启动和结束、基本的内存管理、字符串操作以及简化的 I/O 功能。该库实现了 _start 函数以设置环境，并提供了简单的 malloc, free, strlen 和 strcpy。构建该库只需运行 make 命令，生成静态库和测试程序。

```bash
#ww
Makefile 好好研究
$ make 
$ cat Makefile | ag -q Help me explain # 可以用网页端AI
$ ./test/test
$ ./test/test Hello World
查看上一条命令的退出状态码（返回码）
$ echo $status # fish
$ echo $? # bash
42
```
---
### 然后打脸 😂
**我修了好多 bug**
- Inline assembly 忘记 %%
- _start 的 rsp 已经被改过了
- mmap 的参数顺序错了
- mumap 忘记处理头上的 8 字节 size
    - 也只是让 test.c 能正常运行了
    - 不知道还有没有更多的问题
**代码：谨慎使用 AIGC**

---
### Prompt: 我希望学习 libc 中一些重要函数的实现，但 glibc 太复杂了。有哪些更简单的 libc，让我能链接、调试库的代码？
推荐以下几个轻量级 libc 实现，适合学习核心函数源码：

1. **musl-libc**
✅ 代码简洁规范，模块化设计
✅ 支持动态/静态链接，调试符号完整
✅ 常用函数如 malloc, strlen 实现清晰
使用：gcc -static -nostdlib -I musl/include -L musl/lib 链接

2. **dietlibc**
✅ 极简设计（约 100KB）
✅ 适合嵌入式场景，POSIX 兼容
✅ 提供 diet 工具链简化编译
示例：diet gcc -o program program.c

3. **pdclib (Public Domain C Library)**
✅ 专为教学设计的微型实现
✅ 仅实现 ISO C 标准函数
✅ 代码注释详细，适合逐行分析

**调试建议：**

- 编译时添加 -g 保留调试符号
- 使用 gdb 单步跟踪函数调用
- objdump -d 反汇编观察指令级实现
- 结合标准文档 (如 POSIX) 对照源码理解设计逻辑

---
## 9.2 基础编程机制的抽象

计算的封装

---
### 学习已有 libc 的实现
**调试 glibc？**
- 不，你不想
- glibc 的代码有非常沉重的历史包袱
    - 以及非常多的优化——都是对 “理解原理” 的阻碍
    - 新手阅读体验极差

基本原则：<b style="color:#4169E1">总有办法的</b>
- 让 AI Copilot 帮你解释代码 (这个可以有)
- 是否有比 glibc 更适合学习的 libc 实现？
    - (我的知识储备跟不上 AI，更跟不上有 RAG 的 AI)
    - 幸好我还做了正确的选择：[musl](https://musl.libc.org/)

---
### 调试 “小程序”：
>再次回到学习 C 语言时 “最简单” 的例子；但当我们有了操作系统的知识以后，我们就可以深入调试其中的每一个细节。从汇编指令到系统调用到，我们可以看到程序和处理器、操作系统的所有交互。
```bash
# ww
sudo apt update
sudo apt install -y musl-tools # 不建议，musl-demo gdb进不去printf源代码是怎么回事？
卸载
sudo apt purge musl-tools && sudo apt autoremove
验证
dpkg -l | grep musl
which musl-gcc

# 下面会使用源码编译musl

gcc --verbose
musl-gcc --verbose
```
```bash
# /usr/lib/x86_64-linux-musl/musl-gcc.specs
%rename cpp_options old_cpp_options

*cpp_options:
-nostdinc -isystem /usr/include/x86_64-linux-musl -isystem include%s %(old_cpp_options)

*cc1:
%(cc1_cpu) -nostdinc -isystem /usr/include/x86_64-linux-musl -isystem include%s

*link_libgcc:
-L/usr/lib/x86_64-linux-musl -L .%s

*libgcc:
libgcc.a%s %:if-exists(libgcc_eh.a%s)

*startfile:
%{!shared: /usr/lib/x86_64-linux-musl/Scrt1.o} /usr/lib/x86_64-linux-musl/crti.o crtbeginS.o%s

*endfile:
crtendS.o%s /usr/lib/x86_64-linux-musl/crtn.o

*link:
-dynamic-linker /lib/ld-musl-x86_64.so.1 -nostdlib %{shared:-shared} %{static:-static} %{rdynamic:-export-dynamic}

*esp_link:


*esp_options:


*esp_cpp_options:



```

`AI: explain this musl gcc conf`
这是一个用于配置Gcc以使用musllibc的spec文件。以下是关键部分的解释：...

```bash
vim
"
#include <stdio.h>

int main() {
}
"
:w a.c
:q
gcc --verbose a.c
# #include "..." search starts here:
# #include <...> search starts here:
#  /usr/lib/gcc/x86_64-linux-gnu/11/include
#  /usr/local/include
#  /usr/include/x86_64-linux-gnu
#  /usr/include
musl-gcc --verbose a.c
# #include "..." search starts here:
# #include <...> search starts here:
#  /usr/include/x86_64-linux-musl
#  /usr/lib/gcc/x86_64-linux-gnu/11/include

./configure每个工具都有自己的配置文件

# ./printf
export PATH="/usr/local/musl/bin:$PATH"
make
./printf
gdb printf
starti
layou asm
si
si
# 0x40102f <_start>
readelf -h printf
# Entry point address:               0x40102f
si
layout src

musl-demo gdb进不去printf源代码是怎么回事？
# musl编译前configure没加--enable-debug选项
# musl编译选项怎么设置?见下文
n
p argc
p argv
p argv[0]
n
s

# vscode 调试 musl-gcc printf
```
---
### 源码编译
从源码编译 musl，指的是直接获取 musl 库的源代码，并在你的本地机器上通过编译器（如 GCC 或 Clang）将其构建成二进制库文件（如 `libc.a` 静态库或 `libc.so` 动态库）的过程，而不是直接通过系统的包管理器（如 `apt`）安装预编译好的二进制包。`sudo apt install -y musl-tools`

为了让你更清楚地了解“从源码编译”与“包管理器安装”的区别，我准备了一个表格：

| 特性         | 从源码编译                                                                                              | 通过包管理器安装 (如 `apt`)                                                                                                                              |
| :----------- | :------------------------------------------------------------------------------------------------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **获取内容**   | musl 的源代码文件（通常是 `*.c`, `*.h`, `Makefile` 等）                                                       | 预编译好的二进制库文件（如 `/usr/lib/x86_64-linux-musl/libc.so`）以及必要的头文件。                                                                                  |
| **过程**     | **配置** (`./configure`)、**编译** (`make`)、**安装** (`make install`)。                                          | **下载** (`apt download`)、**解压**、**安装** (`apt install`)。                                                                                             |
| **控制权**   | **高**。可以自定义编译器选项、优化级别、目标架构、安装路径，以及选择启用或禁用特定功能。                                           | **低**。使用发行版维护者预设好的配置和选项，通常无法更改。                                                                                                             |
| **依赖处理**   | 可能需要手动确保系统已安装必要的编译工具（如 `make`, `gcc`）和依赖库。                                                | **自动**。包管理器会自动处理依赖关系，安装所需的所有其他软件包。                                                                                                         |
| **难度和时间** | 相对复杂耗时，需要一定的技术背景。                                                                               | **简单快捷**，一条命令即可完成。                                                                                                                               |
| **适用场景**   | 需要特定配置、交叉编译、深度定制、学习研究 musl 内部机制，或为特定硬件平台优化。                                              | 快速获取稳定、通用的 musl 库用于开发或运行程序，追求方便和稳定性。                                                                                                    |

🧭 **编译步骤简介**
从源码编译 musl 通常包含以下几个核心步骤：
1.  **获取源码**：从 musl 的官方网站或 Git 仓库下载源代码包。
2.  **配置**：运行 `./configure` 脚本。这是**实现“更大控制权”的关键一步**，你可以通过许多参数来自定义编译行为。
3.  **编译**：运行 `make` 命令，调用编译器和链接器将源代码转换成二进制库。
4.  **安装**：运行 `make install` 命令，将编译好的库文件和头文件安装到系统指定的目录（如 `/usr/local/musl`）。

🔧 **“更大控制权”体现在哪里？**
从源码编译 musl 能给你更大的控制权，主要体现在以下几个方面：

*   **自定义编译选项**：你可以通过 `CFLAGS` 等环境变量传递特定的编译器标志。例如，为了**更好的调试体验**，你可以在配置时指定 `CFLAGS='-g -O0'` 来包含调试信息并关闭编译器优化。这在通过 `apt` 安装的预编译包中通常是默认优化过的，不包含丰富的调试信息。
*   **启用或禁用功能**：musl 的配置脚本可能提供一些选项来启用或禁用特定功能（虽然 musl 本身以精简著称，选项相对较少）。例如，使用 `--enable-debug` 选项来启用调试符号，这对调试 musl 库本身或使用它的程序非常有用。
*   **指定安装路径**：你可以使用 `--prefix` 选项来指定 musl 的安装路径，例如 `--prefix=/usr/local/musl`。这允许你将 musl 安装到一个独立目录，避免与系统自带的 glibc 或其他库发生冲突。通过 `apt` 安装则通常遵循系统标准的目录布局。
*   **交叉编译**：这是源码编译的一大优势。你可以为不同的目标架构（如 ARM、RISC-V）编译 musl，只需在配置时指定 `--host` 参数和相应的交叉编译工具链。这对于嵌入式系统开发至关重要，而通过 `apt` 通常只能安装适用于本机架构的预编译包。
*   **针对特定平台优化**：你可以针对你使用的特定 CPU 型号进行优化，以获取可能的性能提升，但这需要较高的技巧和对硬件、编译器的深入理解。

📦 **一个简单的编译示例**
```bash
# 1. 下载并解压源码 (以 musl-1.2.2 为例)
wget https://musl.libc.org/releases/musl-1.2.2.tar.gz
tar -xzf musl-1.2.2.tar.gz
cd musl-1.2.2

# 2. 配置：启用调试符号，并指定安装到 /usr/local/musl
./configure --prefix=/usr/local/musl --enable-debug CFLAGS="-g -O0"

# 3. 编译
make -j$(nproc)

# 4. 安装到系统 (可能需要 sudo)
sudo make install
```
安装后，你就可以使用 `/usr/local/musl/bin/musl-gcc` 来编译你的程序，并将其链接到你刚刚编译的 musl 库。
```bash
sudo apt update
sudo apt install build-essential git curl

从官方 Git 仓库克隆（推荐，这样可以获取最新的代码）：
cd ~  # 切换到用户主目录
git clone git://git.musl-libc.org/musl
cd musl

从官网下载稳定版本的源码压缩包（例如 musl-1.2.2.tar.gz）：
cd ~  # 切换到用户主目录
curl -LO http://musl.libc.org/releases/musl-1.2.2.tar.gz
tar -xzf musl-1.2.2.tar.gz
cd musl-1.2.2

配置编译环境
./configure --prefix=/usr/local/musl
./configure --prefix=/usr/local/musl --enable-debug
./configure --prefix=/usr/local/musl CFLAGS='-O2 -v'
# 你可以根据需要更改此路径，例如 --prefix=$HOME/musl 会安装到当前用户的家目录下。
./configure --prefix=/usr/local/musl \ # 指定安装目录
            --enable-debug \           # 包含调试符号，便于调试[8](@ref)
            --enable-warnings          # 启用编译器警告
实际上--enable-debug会给musl编译加上-g，你对比一下生成的config.mak或者看下configure源码就明白了

执行编译
make -j$(nproc)

安装到系统
sudo make install
# 安装完成后，你可以查看 /usr/local/musl 目录下的内容来确认安装是否成功。

# 为了方便使用，可以将 Musl 添加到你的 PATH 

# 临时添加到当前会话的 PATH
export PATH="/usr/local/musl/bin:$PATH"

# 永久添加到 PATH（添加到 ~/.bashrc 或 ~/.bash_profile）
echo 'export PATH="/usr/local/musl/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

```bash
# 卸载
# 进入你当时编译 musl 的源码目录
cd /path/to/musl-source-code
# 如果之前用了 `make install` 并且记得安装路径，可以尝试卸载
sudo make uninstall

# 或者 你需要手动删除相关的文件和目录（请谨慎操作，确保你知道要删除的是什么）：
# 例如，你可能需要删除手动安装的路径
sudo rm -rf /usr/local/musl
然后从 ~/.bashrc 中移除之前添加的 PATH 设置。如何删除环境变量？
# 请注意：对于通过包管理器 (apt) 安装的软件，永远不要手动删除 /usr/ 下的文件，只应使用 apt 进行管理。
# 手动删除仅适用于你自己从源码编译并指定安装到 /usr/local/ 或自定义路径的软件。

```

💡 **总结一下**

从源码编译 musl 就像是从头开始做一道菜，你可以自由选择食材、调整调料和烹饪方法，最终做出最符合自己口味的菜肴。而通过包管理器安装则是下馆子或买预制菜，虽然方便快捷，但口味是固定的。

如果你的需求只是**快速在开发环境中使用 musl**，那么 `apt install musl` 足够了。但如果你需要**为特定环境定制、进行底层调试、交叉编译，或者单纯想学习和探索**，那么从源码编译 musl 会为你打开一扇门，给你更大的控制权和灵活性。

---
### 学习已有 libc 的实现 (cont'd)
**下载源码不难，难的是怎么 “使用” 下载的 libc**
- 我们知道可以使用 gcc 和 ld
- 但到底应该用什么编译选项？

**如何使用我自己的 clang、musl 替代 glibc 编译程序？**
- 当然，我们还是选择自己编译
    - 比较重要的选项
        - -O1: 减少优化级别，便于查看状态
        - -g3: 增加调试信息
    - 使用 musl-gcc 静态编译
- 试一试：从第一条指令开始调试一个 C 程序

---
### 基础数据的体系结构无关抽象
**[Freestanding 环境](https://en.cppreference.com/w/cpp/freestanding.html)下也可以使用的定义**
- [stddef.h](https://cplusplus.com/reference/cstddef/) - `size_t`
    - 还有一个有趣的 “offsetof” (Demo; 遍历手册的乐趣)
- [stdint.h](https://cplusplus.com/reference/cstdint/) - `int32_t`, `uint64_t`
- [stdbool.h](https://cplusplus.com/reference/cstdbool/) - `bool`, `true`, `false`
- [float.h](https://cplusplus.com/reference/cfloat/)
- [limits.h](https://cplusplus.com/reference/climits/)
- [stdarg.h](https://cplusplus.com/reference/cstdarg/)
- [inttypes.h](https://cplusplus.com/reference/cinttypes/)
    - 打印 intptr_t 变量 printf 的格式字符串是什么？

---
### 字符串和数组操作
**[string.h](https://cplusplus.com/reference/cstring/): 字符串/数组操作**
- memcpy, memmove, strcpy, ...

**[stdlib.h](https://cplusplus.com/reference/cstdlib/): 常用功能**
- rand, abort, atexit, system, atoi, ...
- 看起来就不像是人用的
```c
// C
void qsort(void*, size_t, size_t, int (*)(const void*, const void*));
```
```cpp
// C++
std::ranges::sort(xs, [](const auto& x, const auto& y) { ... });
```

---
### 更多的例子
**在 AI 的指导下阅读手册**
- 更多的 [stdlib.h](https://cplusplus.com/reference/cstdlib/) 中的例子
    - atoi, atol, atoll, strtoull, ...
    - rand (注意线程安全), ...
- [math.h](https://cplusplus.com/reference/cmath/)
    - [FP8: E4M3/E5M2](https://arxiv.org/pdf/2209.05433.pdf); [Quantization](https://spectrum.ieee.org/number-representation)
    - 一个原本就深奥的课题；AI 时代变得更复杂困难
- [setjmp.h](https://cplusplus.com/reference/csetjmp/)
    - 这个好玩！要用状态机去理解
- 实现库函数 = C 语言课程习题

---
### 关于 AI 擅长做什么、不擅长做什么
**“Attention is all you need.”**
- 你需要给他 “关键词” (prompt engineering)
- 推理模型降低了对 “关键词” 的依赖
    - 但 “神来之笔” 的关键词仍然能起决定性的作用

---
## 9.3 系统调用与环境的抽象

---
### 输入/输出
**Standard I/O: [stdio.h](https://www.cplusplus.com/reference/cstdio/)**
- `FILE *` 背后其实是一个文件描述符
- 我们可以用 gdb 查看具体的 `FILE *`
    - 例如 stdout
- 封装了文件描述符上的系统调用 (fseek, fgetpos, ftell, feof, ...)

**The printf() family**
- 这些代码理应没有 “code clones”
```c
printf("x = %d\n", 1);
fprintf(stdout, "x = %d\n", 1);
snprintf(buf, sizeof(buf), "x = %d\n", 1);
```

---
### popen 和 pclose
**我们在游戏修改器中使用了它**
- 一个设计有历史包袱和缺陷的 API
    - Since a pipe is by definition unidirectional, the type argument may specify only reading or writing, not both; the resulting stream is correspondingly read-only or write-only.

**为什么我们要用现代编程语言？**
```c
let checksum = {
  Exec::shell("find . -type f")
    | Exec::cmd("sort") | Exec::cmd("sha1sum")
}.capture()?.stdout_str();  // ()? returns "std::nullopt"
```

```bash
man popen
```

---
### err, error, perror
**所有 API 都可能失败**
```bash
$ gcc nonexist.c
gcc: error: nonexist.c: No such file or directory
```
**反复出现的 “No such file or directory”**
- 这不是巧合！
    - 我们也可以 “山寨” 出同样的效果
- Quiz: errno 是进程共享还是线程独享？
    - 线程有一些我们 “看不到” 的开销：ucontext, errno, ...

```bash
# ww
./perror
# open: No such file or directory
man 2 fork
#-1
```

---
### environ (7)
```c
int main(argc, char *argv[], char *envp[]);
```
**envp: execve() 传递给进程的 “环境”**
- 全局变量 environ 是谁赋值的？
    - 是时候请出我们的老朋友 watch point 了
- RTFM: [System V ABI](https://jyywiki.cn/OS/manuals/sysv-abi.pdf)
    - p33
    - Figure 3.9 Initial Process Stack
        - 操作系统有一个 “初始状态”
        - libc 调用 main 前还会继续初始化这个 “初始状态”

```bash
./env 
env

gdb env
wa environ # 观察 environ 的变化
layout src
r
p environ
# $1 = (char *) 0x7fffffffdfd8
p __environ
# $2 = (char * *) 0x7fffffffdfd8

b 17
p end # 未正确解析
# $1 = (void ******************************) 0x0
p/x end
# $2 = 0x0
x end
# 0x0:    Cannot access memory at address 0x0
```

---
## 9.4 动态内存管理

动态内存管理 (1)

顺序内存管理

---
### malloc() 和 free()
>I call it my billion-dollar mistake. It was the invention of the null reference in 1965. (Tony Hoare)

**编程语言抽象不足**
- malloc/free 也有类似的问题
    - Use after free
    - Double free
    - Memory leak
- “最小完备性原则” 和 “机制策略分离” 的反面教材
    - “每一个 malloc 在任何可能路径上都必有一次配对的 free，且之后不再使用”
    - 在复杂系统里太难保证了

---
### malloc() 和 free()
**使用的系统调用：mmap (历史：sbrk)**
- 大段内存，要多少有多少
    - 用 MAP_ANONYMOUS 申请
    - 超过物理内存上限都行 (Demo)

**反而，操作系统<b style="color:#4169E1">不支持</b>分配一小段内存**
- 这是应用程序自己的事
    - 应用程序可以每次向操作系统 “多要一点” 内存
    - 自己在内存上实现一个数据结构

---
### 实现 malloc(n)
**如果 n 足够大**
- 直接用 mmap 分配内存

**如果 n 不够大**
- 从一个 mmap 得到的内存池中分配
    - 我们有一个大区间 [L,R)
    - 维护其中不相交的小区间集合
        - 啊！太好了！这是个数据结构问题……
        - Interval tree 可以实现 O(logn) 的分配/回收

---
你们对 “现实” 的恐怖一无所知
**早在 1995 年：这才叫 [research](https://jyywiki.cn/OS/manuals/malloc-survey.pdf)**
>Understanding real program behavior still remains the most important first step in formulating a theory of memory management. Without doing that, we cannot hope to develop the science of memory management; we can only fumble around doing ad hoc engineering, in the too-often-used pejorative sense of the word. At this point, the needs of good science and of good engineering in this area are the same—a deeper qualitative understanding. We must try to discern what is relevant and characterize it; this is necessary before formal techniques can be applied usefully.

- 停止无意义的 “科研实践”，去做真正有价值的事情

---
### 实现高效的 malloc/free
>Premature optimization is the root of all evil.
>——D. E. Knuth

**重要的事情说三遍：**
- <b style="color:#4169E1">脱离 workload 做优化就是耍流氓</b>
    - 在开始考虑性能之前，理解你需要考虑什么样的性能

**然后，去哪里找 workload?**
- 当然是 paper 了 (顺便白得一个方案)
    - [Mimalloc: free list sharding in action](https://www.microsoft.com/en-us/research/uploads/prod/2019/06/mimalloc-tr-v1.pdf) (APLAS'19)
    - [卷到今天](https://dl.acm.org/doi/10.1145/3620666.3651350)大家做的事情也没变：看 workload 调性能

---
/ww$
- 过早的优化是万恶之源。

- 脱离 workload 做优化就是耍流氓?
    - 在IT领域，​​workload​​ 的概念更加技术化，指​​计算资源为完成任务或产生结果所执行的处理类型和数量​​。任何在计算机上运行的程序或应用都可以被视为一个 workload


---
### 理论 v.s. 实践
**在实际系统中，我们通常不考虑 adversarial worst case**
- 现实中的应用是 “正常” 的，不是 “恶意” 的
    - 但这给了很多 Denial of Service 的机会：[Cross container attack](https://dl.acm.org/doi/abs/10.5555/3620237.3620571)

**malloc() 的观察**
- <b style="color:#4169E1">大对象分配后应，读写数量应当远大于它的大小</b>
    - 否则就是 performance bug
    - 申请 16MB 内存，扫了一遍就释放了😂
        - 这不是 bug，难道还是 feature 吗？
- 推论：<b style="color:#4169E1">越小的对象创建/分配越频繁</b>

```c
// memory allocation free
```
---
### malloc() 的观察
**我们需要管理的对象**
- 小对象：字符串、临时对象等；生存周期可长可短
- 中对象：容器、复杂的对象；更长的生存周期
- 大对象：巨大的容器、分配器；很长的生存周期

**结论**
- <b style="color:#4169E1">我们几乎只要管好小对象就好了</b> (当然，仅针对 oslabs)
- 由于所有分配都会在所有处理器上发生
    - 小对象分配/回收的 <b style="color:#4169E1">scalability</b> 是主要瓶颈
    - 使用链表/区间树 (first fit) 可不是个好想法

---
### malloc, Fast and Slow
**人类也是这样的系统**
- *Thinking, Fast and Slow* by Daniel Kahneman

**设置两套系统**
- Fast path (System I) ← <b style="color:#4169E1">AI 已经开始超越 System I 人类</b>
    - 性能极好、覆盖大部分情况
    - 但有小概率会失败 (fall back to slow path)
- Slow path (System II) ← <b style="color:#4169E1">人类也已经失守了</b>
    - 不在乎那么快
    - 但把困难的事情做好
- 计算机系统里有很多这样的例子 (比如 cache)

// 缓存

---
### 人类的智慧：空间换简洁
**分配: Segregated List (Slab)**
- 每个 slab 里的每个对象都<b style="color:#4169E1">一样大</b>
    - 每个线程拥有每个对象大小的 slab
    - fast path → 立即在线程本地分配完成
    - slow path → mmap()

/ww$
- Segregated List，在 Linux 内核中更常被称为 ​​Slab 分配器​​，是一种用于高效管理内核对象缓存的内存分配策略。它的核心思想是​​通过对象缓存来实现内核对象的高效分配和释放​​。

- “Fast Path”（快路径）和“Slow Path”（慢路径）是系统性能优化中非常普遍的设计理念，​​用于区分处理请求的不同方式，以优化整体性能和资源利用率​​。

见附录

---
### Prompt: 为什么称 C 语言是高级的汇编语言？
C语言被称为“高级的汇编语言”，主要因其兼具高级语言的抽象能力和接近硬件的底层控制特性：

1. **硬件级操作**
C语言支持指针、直接内存访问和位操作，能精准控制硬件资源（如寄存器、内存地址），这与汇编语言相似。

2. **高效性**
C代码经编译后生成的机器指令效率接近汇编，且可通过内联汇编进一步优化关键代码，适合系统级开发。

3. **结构化抽象**
相比汇编的指令式编程，C语言提供函数、循环、条件分支等结构化语法，显著提升了代码可读性和可维护性。

4. **跨平台与可移植**
C语言通过编译器实现硬件适配，避免了汇编语言对特定架构的强依赖，同时保留了对底层细节的控制权。

这一设计使C语言成为操作系统、嵌入式系统等对性能和底层控制要求较高场景的理想选择。

---
### Prompt: 解释 C 标准库中的 offsetof，以及它有什么应用？
offsetof 是 C 标准库中的一个宏，定义在 <stddef.h> 头文件中。它用于计算结构体中某个成员的偏移量（相对于结构体起始地址的字节数）。

**语法：**
```c
offsetof(type, member)
```
**参数：**

- type：结构体类型。
- member：结构体中的成员名称。

**返回值：** 返回 member 在 type 中的偏移量，类型为 size_t。

**应用：**
1. **内存布局分析**：用于了解结构体内部的内存布局，便于调试或优化。
2. **低级编程**：在需要直接操作内存或与硬件交互时，计算偏移量可以避免硬编码。
3. **序列化/反序列化**：在将结构体数据转换为字节流时，可以利用偏移量精确访问特定字段。

**示例：**
```c
#include <stdio.h>
#include <stddef.h>

struct Example {
    int a;
    char b;
    double c;
};

int main() {
    printf("Offset of 'a': %zu\n", offsetof(struct Example, a)); // 输出 0
    printf("Offset of 'b': %zu\n", offsetof(struct Example, b)); // 输出 4
    printf("Offset of 'c': %zu\n", offsetof(struct Example, c)); // 输出 8
    return 0;
}
```
这个宏在需要精确控制内存布局或进行底层操作时非常有用。

---
### mmap: 
>Linux 系统使用 anonymous 的 mmap 来实现大段连续内存的分配——甚至在系统调用返回的瞬间，进程可以没有得到任何实际的内存，而是只要在首次访问时 (触发缺页异常) 分配即可。AddressSanitizer 就用 mmap 分配了 shadow memory，我们可以使用 strace 观察到这一点。

---
## 9.5 总结
　　**Take-away Messages**: 在系统调用和语言机制的基础上，libc 为我们提供了开发跨平台应用程序的 “第一级抽象”。在此基础上构建起了万千世界：C++ (扩充了 C 标准库)、Java、浏览器世界……今天，C 语言在应用开发方面有很多缺陷，但仍然为 “第一级抽象” 提供了一个有趣的范本：

- [C is not a low-level language](https://dl.acm.org/doi/pdf/10.1145/3209212)
- [C isn't a programming language any more](https://faultlore.com/blah/c-isnt-a-language/)

---

# 附录
>AI : Segregated List (Slab)  / fast path / slow path帮我生成新手友好的教程/介绍/解释

理解内存管理和系统性能优化中的一些概念可能会让人望而生畏，但掌握它们对编程和系统理解非常有益。我会用尽可能清晰的方式为你解释 Segregated List (Slab)、Fast Path 和 Slow Path 这三个概念。

# 🧠 内存管理与性能优化基础：Segregated List (Slab), Fast Path, Slow Path

## 1 Segregated List (Slab) 分配器

### 1.1 基本概念
Segregated List，在 Linux 内核中更常被称为 **Slab 分配器**，是一种用于高效管理内核对象缓存的内存分配策略。它的核心思想是**通过对象缓存来实现内核对象的高效分配和释放**。你可以把它想象成一个专门为特定“物件”准备的“零件盒”，每次需要时都能快速拿到合适尺寸的零件，用完后放回原处，而不是每次都去翻一个大工具箱。

Slab 分配器最初由 Sun 公司的工程师 Jeff Bonwick 在 Solaris 2.4 内核中实现。Linux 系统为其提供了三种选择：
*   **SLAB**: 最初的分配器，基于 Bonwick 的论文，自 Linux-2.2 开始可用。它功能完备但设计有些臃肿。
*   **SLUB** (Next Generation): 下一代内存分配器，自 Linux-2.6.23 以来一直是内核的**默认分配器**。它继承了 SLAB 的基本模型，但修复了其缺陷，特别是在多处理器系统上的问题，并且设计更简单。
*   **SLOB** (Simple List Of Blocks): 一种针对**内存非常少**（例如只有几兆字节）的嵌入式系统进行优化的内存分配器。它使用简单的首次适应算法，几乎消除了所有内存分配开销，但容易产生碎片，也不提供 SLAB/SLUB 的高级特性。

### 1.2 为什么需要 Slab 分配器？
这主要是为了克服**伙伴系统 (Buddy System)** 的局限性。伙伴系统是内核中管理物理内存的基础机制，但它以**页（通常为 4KB）为单位**进行分配。如果内核仅仅需要为一个很小的对象（比如只有几十字节的进程描述符）分配内存，直接使用伙伴系统就会导致**大量内存浪费**（内部碎片）和**内存碎片化**。

Slab 分配器作为伙伴系统的补充，它先通过伙伴系统申请一整页（或连续多页）内存，然后将其**切割成多个相同大小的块**（对应于特定内核对象的大小），并将这些块缓存起来。当需要分配该大小的对象时，直接从缓存中获取；释放时，也归还到缓存中，而不是立即还给伙伴系统。这样就极大地提升了小内存对象分配和释放的效率，并减少了碎片。

### 1.3 Slab 的工作原理与核心结构
Slab 分配器是**基于对象进行管理**的，相同类型的对象归为一类。它的核心框架主要由三个数据结构组成：

*   **`kmem_cache`**: 每个不同大小的内存块（或每种类型的对象）都会有一个 `kmem_cache` 进行管理。所有的 `kmem_cache` 通过一个双链表链接起来。它包含了该缓存的所有信息，例如对象大小、每个 Slab 有多少个对象等。
*   **`kmem_cache_cpu`**: 这是一个**每 CPU 变量**，每个 CPU 都独享一个。它的目的是为了**避免锁竞争**。它内部有一个 `freelist` 指针，始终指向下一个可用的空闲内存块（这些空闲块本身也通过指针链成一个单链表）。分配内存时，优先从这个本地缓存获取，速度极快。
*   **`kmem_cache_node`**: 这是**每个 NUMA 节点**的数据结构，主要用于管理**部分空闲**的 Slab。它包含了三个链表：`slabs_full` (完全分配的 Slab), `slabs_partial` (部分分配的 Slab), `slabs_free` (完全空闲的 Slab)。

**内存分配流程**可以简化为：
1.  **快速路径 (Fast Path)**: 尝试从当前 CPU 的 `kmem_cache_cpu->freelist` 直接获取一个空闲对象。这是最快捷的路径。
2.  **中速路径**: 如果 CPU 本地缓存空了，就从 `kmem_cache_node` 的 `partial`（部分空闲）链表上迁移一些空闲对象到 CPU 本地缓存，然后再分配。
3.  **慢速路径 (Slow Path)**: 如果 `partial` 链表上也没有空闲对象，就需要向伙伴系统申请新的内存页，创建一个新的 Slab，并将其加入到管理结构中，然后再分配。

### 1.4 一个生动的比喻：餐厅备菜
想象一下一个繁忙的餐厅：
*   **伙伴系统**就像是**背后的中央厨房**，它每天进货大量的食材（整页内存），但食材都是未加工的（大块内存）。
*   **Slab 分配器**就像是**餐厅的备餐台**。厨师（内核）预见到某些菜品（内核对象，如 `task_struct`）会经常被点单（频繁创建），于是提前从中央厨房取来整块食材，在备餐台上切好、配好，分成一份份标准大小的“半成品”（缓存的对象）。
*   当订单（分配请求）来时，厨师可以直接从备餐台拿起半成品进行烹饪（初始化使用），速度极快。用餐结束后（对象释放），盘子（内存）被清洗后放回备餐台，等待下一次使用，而不是立即扔回中央厨房。

### 1.5 编程接口与应用场景
Linux 内核为 Slab 分配器提供了简洁的 API，用于创建专用的缓存：

```c
#include <linux/slab.h>

/* 创建一个名为 "my_cache" 的 Slab 缓存，每个对象大小为 sizeof(struct my_object) */
struct kmem_cache *my_cache = kmem_cache_create("my_cache", sizeof(struct my_object), 0, 0, NULL);

/* 从该缓存中分配一个对象 */
struct my_object *obj = kmem_cache_alloc(my_cache, GFP_KERNEL);

/* 使用对象... */
obj->data = 42;

/* 释放对象回缓存 */
kmem_cache_free(my_cache, obj);

/* 最后，销毁缓存 */
kmem_cache_destroy(my_cache);
```

**Slab 分配器的典型应用场景**包括管理频繁创建和销毁的内核对象，例如：
*   进程描述符 (`task_struct`)
*   文件描述符
*   网络协议栈中的数据结构（如 `sk_buff`）
*   索引节点 (`inode`) 和目录项 (`dentry`) 缓存

## 2 Fast Path 与 Slow Path

“Fast Path”（快路径）和“Slow Path”（慢路径）是系统性能优化中非常普遍的设计理念，**用于区分处理请求的不同方式，以优化整体性能和资源利用率**。

### 2.1 核心概念
*   **Fast Path (快路径)**: 指的是**最常见、最标准、优化程度最高的处理路径**。在这条路径上，系统通常利用已有的缓存、预计算的结果或简单的逻辑，以**最小的开销和最快的速度**完成请求的处理。目标是最大化吞吐量和降低延迟。
*   **Slow Path (慢路径)**: 指的是**不常见、更复杂、需要额外处理或资源访问的处理路径**。这条路径通常涉及复杂的计算、访问较慢的存储介质（如磁盘）、获取新的状态信息或处理异常情况。它的速度较慢，但能处理快路径无法处理的特殊情况。

### 2.2 在网络设备中的经典示例
这个概念在网络包处理中非常直观：
*   **Fast Path**: 一个数据包到达网络设备（如路由器），设备查看其目标 IP 地址，发现**路由表（转发表）中已经有明确的下一跳信息**，并且 MAC 地址等信息也都已知。于是，设备可以**不缓存这个包，直接、快速地将其转发出去**。这个过程几乎不需要思考，速度极快。
*   **Slow Path**: 一个数据包到达，设备发现它的目的地在路由表中**没有记录**（缓存未命中），或者它是一个需要特殊处理的**首包**（如 TCP 连接建立的 SYN 包）。这时，设备需要**暂停转发这个包**，可能要将它缓存到慢速的 DRAM 中，然后启动路由查找、ARP 解析等复杂流程来获取必要的信息。等这些信息准备好后，后续的包就可以走 Fast Path 了。

### 2.3 在更广泛系统设计中的含义
Fast/Slow Path 的思想远远超出了网络范畴：
*   **CPU 分支预测**: CPU 会预测条件跳转最可能走向的分支（Fast Path）并提前执行，如果预测失败（Slow Path），则需要清空流水线，带来巨大性能惩罚。
*   **数据库查询**: 如果查询所需的数据页都在内存缓冲池中（Buffer Pool Hit），查询会非常快（Fast Path）。如果需要从磁盘读取数据（Buffer Pool Miss），速度就会慢很多（Slow Path）。
*   **Web 服务**: 常见的请求可以直接返回缓存的结果（Fast Path），而需要复杂计算或查询数据库的请求则需要更长时间（Slow Path）。
*   **内存分配**: 正如前面 Slab 分配器提到的，从每 CPU 缓存中分配是 Fast Path，而需要向伙伴系统申请新内存页则是 Slow Path。

### 2.4 一个简单的比喻：餐厅点餐
想象一家餐厅：
*   **Fast Path**: 一位常客进门，点了他的“老样子”。服务员立刻就知道他要什么（缓存的信息），直接下单给厨房，流程极快。
*   **Slow Path**: 一位新客人进门，需要仔细看菜单（查找路由），询问服务员菜品的细节（额外信息），甚至提出一些特殊的定制要求（复杂计算）。这个过程显然要慢得多。

## 3 概念之间的联系

虽然 Segregated List (Slab) 和 Fast/Slow Path 看似是不同的概念，但它们在设计哲学上是相通的，并且在实际应用中常常协同工作。

**Slab 分配器本身就是 Fast/Slow Path 设计思想的完美体现**：
*   它的 **`kmem_cache_cpu->freelist`** 就是最极致的 **Fast Path**。分配和释放操作在绝大多数情况下只需要操作这个链表，速度极快，且避免了锁竞争。
*   当 CPU 本地缓存不足时，从 **`kmem_cache_node->partial`** 链表迁移对象，可以看作是一种 **中速路径**。
*   而当必须向**伙伴系统申请新内存页**时，这就是分配器的 **Slow Path**。这个过程涉及系统全局锁、页面分配和初始化，开销最大。

这种分层处理的设计——**优先尝试最快的方式，失败后再逐级 fallback 到更慢但更通用的方式**——是构建高性能系统的核心模式之一。

## ✨ 核心概念对比表

| 特性 | Segregated List (Slab) | Fast Path | Slow Path |
| :--- | :--- | :--- | :--- |
| **核心目标** | 高效管理小内存对象，减少碎片 | 最大化吞吐量，最小化延迟 | 处理复杂、异常或未缓存的情况 |
| **实现方式** | 预分配内存池、对象缓存、每CPU变量 | 缓存、预计算、简单逻辑、专用硬件 | 复杂计算、访问慢速存储、获取新状态 |
| **性能** | **极高**（相比通用分配器） | **极高** | **较低**（相对Fast Path） |
| **适用场景** | 内核频繁分配/释放的小对象（如`task_struct`) | 常见请求、数据包转发、缓存命中 | 异常处理、首包处理、缓存未命中、冷启动 |
| **设计哲学** | **空间换时间**，通过缓存和预分配提升效率 | **优化常见 case**，保证整体高性能 | **处理全部 case**，保证系统正确性和完整性 |

希望这份解释能帮助你理解这些重要的系统设计概念！如果你对某个特定方面还有疑问，我很乐意进行更深入的探讨。