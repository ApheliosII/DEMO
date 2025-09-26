# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

---
==由于学习进度慢,后面只注意重点内容。==

[PPT](https://jyywiki.cn/OS/2025/lect19.md)

```makefile
# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib
```
## 19. 真实世界的并发编程 (2)
**背景回顾**：针对不同的应用场景的，我们对基础的并发控制机制做出适当的限制，就能让开发者又快又好地编写并发程序。无论是 OpenMP 还是 Javascript 的事件模型，都是十分值得学习的设计。与此同时，人们也开始发现，对于一些特别的应用场景，CPU 和线程也许并不是最 “高效” 的解决方法。

**本讲内容**：CPU 的局限、加速器和人工智能背后的并行编程。

---
## 19.1 熟悉又陌生的 CPU 🌶️
**SIMD 和 大小核**
**CPU内的并行编程**

**什么是 CPU？
概念：无情的执行指令的机器**

**实际的 CPU (Instruction-level Parallelism)**
- 没有想到的是：你一直都在 (自动) <b style="color:#4169E1">并行编程</b> 
    - 每个 CPU 核心都是一个<b style="color:#4169E1">编译器</b> 
        - 动态 (运行时) 数据流分析和指令调度
        - 服务器 CPU 上可能<b style="color:#4169E1">同时有上千条指令在执行</b> 
    - 可以看看平时用的程序的 IPC 是多少？
     
IPC: Instructions Per Cycle > 1 
//每个时钟周期执行指令数

**这意味着什么？
在<b style="color:#4169E1">能效</b>和<b style="color:#4169E1">性能</b>之间，CPU 选择了后者**
- 跑得越快，浪费得越多
    - 每一个门电路的翻转都会产生<b style="color:#4169E1">热量</b>
    - CPU 里的编译器会消耗巨量的能量
        - 这些能量使计算 “尽快完成”
        - 但并不等同于 “单位时间完成尽可能多的计算”

**Dark Silicon “暗硅时代”**
- $P = C \times V^2 \times f$
- “功耗墙”：纵使有更大的电路，热功耗限制了性能上限

电容，电压，频率

**面对功耗墙**
$P = C \times V^2 \times f$
- 如何在降低 $V$ 和 $f$ 的同时，用面积换性能？

**1. 让一条指令能处理更多的数据**
- SIMD (Single Instruction, Multiple Data)
    - “一条指令” 浪费的能量大致是定数
    - 处理的数据越多，浪费越少

- 可以一次让一条指令对连续的操作数做相同运算！
    - Intel MMX: MultiMedia eXtension

- 增加一些 “超大” 的寄存器
    - 64-bit “mm” 寄存器

**2. 用更多更简单的处理器**
- 多处理器系统、异构多处理器
    - 同等面积，处理器越简单，数量越多

**SIMD: 没能完全解决问题
SIMD 指令依然是在 CPU 里调度的**
- 参与到缓存和动态流水线中
    - 宽度不能做得太宽
    - 并行度有限

**我们实在是太想要性能了**
- 只能<b style="color:#4169E1">横向扩展</b>
    - 单 CPU → 多 CPU
    - 多 CPU → 大小核 CPU

**2. 同等面积可以放置更多 “高能效” 计算单元**
- Apple M1: 4 Performance + 4 Efficiency
    - Trick: 降低频率 = 降低电压 (“热功耗分配”)


---
> **RISC-V 处理器模拟器**：C 语言实现的 single-header RISC-V32IMA 系统模拟器 (项目源自[mini-rv32ima](https://github.com/cnlohr/mini-rv32ima))。因为有 M-Mode，这个模拟器可以运行几乎 “任意复杂” 的程序——甚至是没有 MMU 的 Linux。我们稍稍修改了这份代码，更好地体现《操作系统》课程的教学目标。

> **指令级并行**: CPU 会在一个时钟周期发射多条指令。指令之间的数据依赖关系同样形成了一个计算图。因为电路是天然 “并行” 的，通过合理的电路实现 (Tomasulo 算法)，就能实现计算图的并行实现，从而把顺序程序自动 “并行化”。

```bash
sudo apt update
需要安装perf工具

ls
./ilp-test
objdump -d ilp-test | less

perf stat -e instructions,cycles ./ilp-test

perf stat -e instructions,cycles ls
0.37

perf stat -e instructions,cycles lpython3 -c '2**1000000'
```

---
## 19.2 GPU 和 GPGPU 🌶️
生于娱乐，长于智能

**用更多更简单的处理器**
- 同等面积，处理器越简单，数量越多
- 我们<b style="color:#4169E1">甚至不需要处理器有 CPU 指令集的计算能力</b>！
    - “领域专用加速器”
        - ISP: Image Signal Processing (手机相机)
        - GPU: Graphics Processing Unit (图形渲染)
        - DPU: Data Processing Unit (网络/数据处理)

DMA : Direct Memory Access (直接内存访问)

**至少有一件事，可以让专用处理器来做
画图**
- 对 $f_{i,j}$ 的计算是 “massive parallel” 的
```c
for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x)
        putchar(f(x, y) ? '*' : ' ');
    putchar('\n');
}
```
- 对 CPU 来说是个根本不可能完成的任务
    - NES: MOS 6502 @ 1.79Mhz; IPC ≈ 0.43
    - 屏幕共有 256 x 240 = 61K 像素 (256 色)
    - 60FPS → 10K 条指令完成 61K 像素的渲染

> LiteNES: 简易的 C 语言 NES 模拟器 (forked from Stanislav Yaglo's mynes (https://github.com/yaglo/mynes). 我们可以在 ppu.c 的 ppu_draw_sprite_scanline() 实现中看到 PPU 逐行遍历 sprite RAM 的逻辑。

./litenes yie-ar-kung-fu.nes
wsl2 fail --> linux运行

---
## 19.3 AI 时代的并行编程 🌶️
**SIMT 和 CUDA**
Single Instruction, Multiple Threads
Compute Unified Device Architecture

**为什么不把 Shader 实现成线程呢？**
```c
__device__ int *map;

// row = 1, 2, 3, 4, ..., 1080
// col = 1, 2, 3, 4, ..., 1920
void kernel(int row, int col) {
    t = ...;  // 任意 C/C++ 代码
    map[row * 1920 + col] = t;
}
```
- 在 GPU 上启动 2,073,600 个线程
    - 并行执行，允许访问 shared memory
    - 恭喜！你发明了 CUDA (的 programming model)

**同样的面积，更多的线程
Single instruction, multiple threads**
- 一个 PC (program counter) 管多个线程
    - 假设 (3,0), (3,1),..., (3,31) 都被分配到了同一个 core 上
        - map[3 * 1920 + 0] = t;
        - map[3 * 1920 + 1] = t;
        - ...
        - map[3 * 1920 + 31] = t;
            - 魔法发生了！Memory coalescing
```c
void kernel(int row, int col) {
    t = ...;  // 任意 C/C++ 代码
    map[row * 1920 + col] = t;
}
```
**当然，这也意味着 CUDA 程序很难写**
```c
void kernel(int row, int col) {
    t = ...;  // 任意 C/C++ 代码

    map[row * 1920 + col] = t;
    map[row + col * 1080] = t;
    // 等价的写法，可能导致性能下降
    // SIMT 处理分支也并不擅长
}
```

**难写，意味着有收益**
**渲染 25600×25600 的 Mandelbrot Set**
- Ryzen 5 9600X: 25.1s @ 65Watt
- RTX 4060Ti (16GB): 6.1s @ 42Watt
    - 这已经是对 CUDA “很不友好” 的程序了
    - 不确定的 while 循环

**我们甚至可以直接阅读 GPU 上的代码**
- 经过编译器优化，比大家想象得要短 😊   
- (GPU 并不擅长执行数据中心中的业务逻辑)

**CUDA 擅长什么呢……？
固定模式、海量计算的，它最擅长**
- cuBLAS: Basic Linear Algebra
- cuFFTDeepGEMM 就是其中重要的 matrix multiplication

**看看 gpt.c?**
- 代码怎么都这么像矩阵乘法？
    - 没错！固定模式、海量的计算！

**AlexNet 一战成名**

> CUDA 实现的 Mandelbrot Set: 和 “原版” C 代码对比，实际计算的 mandelbrot 函数完全没有任何修改，只是增加了 “kernel” 的修饰。此外，worker 线程被 mandelbrot_kernel 函数取代，这个函数在 GPU 上运行，通过 blockIdx, blockDim 和 threadIdx 计算出线程对应的像素坐标。没错，CUDA 是另一种 “启动百千万个轻量级线程” 的机制。

```bash
cuda程序环境安装

makefile
nvcc
nsys profile
```

---
## 19.4 总结
　　***Take-away Messages***: 人类世界的需求一直是驱动技术革新的原动力。回头看历史，波澜壮阔的旅程又是显得那么理所应当——从 CPU 到领域加速器，再变得 “通用” 一点，就是 GPGPU。也许有些出乎 Nvidia 意料的是，CUDA 没有在大家看好的科学计算领域掀起革命，却引领了人工智能的时代。回望历史、展望未来，同学们将在人类历史上找到自己的位置。