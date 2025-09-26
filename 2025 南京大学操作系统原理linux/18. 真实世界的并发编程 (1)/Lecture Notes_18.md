# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

---
==由于学习进度慢,后面只注意重点内容。==

[PPT](https://jyywiki.cn/OS/2025/lect18.md)

```makefile
# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib
```
## 18. 真实世界的并发编程 (1)
背景回顾：并发编程的基础机制 (线程、互斥锁、条件变量、信号量等) 足够实现高效的并发/并行编程，但它们的正确使用是**完全由使用者**负责——这毫无疑问是个过于乐观的假设。因此，编程语言的设计者们在不同的应用场景下，实现了许多并发/并行编程的机制。

**本讲内容**：(本次课为科普，不需要掌握相关编程技术) 高性能计算、Web 和数据中心的并发 (并行) 编程模型。

## 18.1 高性能计算中的并发编程
---
**CRAY-1 超级计算机**
“[The world's most expensive love-seat](https://dl.acm.org/doi/10.1145/359327.359336)” (1976)
- 138 MFLOPS @ 115kW (Apple M4 iPad Pro: 3.8 TFLOPS)
    - ≈ 27,000 台 CRAY-1 😂

---
**(经典) 高性能计算**
> “A technology that harnesses the power of supercomputers or computer clusters to solve complex problems requiring massive computation.” (IBM)

**源自数值密集型科学计算任务**
- 物理系统模拟
    - 天气预报、航天、制造、能源、制药、……
    - 大到宇宙小到量子，有模型就能模拟
- 矿厂
- AI: 新时代的高性能计算之王 (下节课)
- [HPC-China 100](http://www.hpc100.cn/top100/23/)
    - 是的，单位是 PFLOPS

---
**高性能计算程序：特点**
**物理世界具有 “空间局部性”**
- “模拟物理世界” 的系统具有 embarrassingly parallel 的特性

---
> **绘制 Mandelbrot set**: Mandelbrot set，描绘了函数 f(z) = z^2 + c 的轨迹是否有界。对于复平面上每一个点，求值都是完全独立的，因此对计算图的静态划分也是显然的。我们混用了 OpenMP 和我们的线程库。我们的线程库仅限于隔一段时间将当前渲染的结果显示在屏幕上，并在所有线程结束后输出渲染图。

```bash
-fopenmp编译选项

    #pragma omp parallel num_threads(nthread)
    #pragma omp for schedule(static)

./mandelbrot 1
sh: 1: viu: not found
viu 是一个用 Rust 编写的终端图像查看器。它可以在不支持图形界面的终端环境中显示图片，对于通过 SSH 管理服务器或在命令行环境下工作的人来说非常方便。
sudo apt install cargo
cargo install viu
16.0s

./mandelbrot 2
8.0s

./mandelbrot 16
2.0s

fprintf(fp, "P6\n%d %d 255\n", w, h);

convert mandelbrot.ppm mandelbrot.jpg
# sudo apt update
# sudo apt install imagemagick
# convert --version
firefox mandelbrot.jpg
```

---
**实验 (gpt.c) 通关密码
大家不要偷看 [llm.c](https://github.com/karpathy/llm.c/blob/master/train_gpt2.c)**
- 但可以看一下头
```c
#ifdef OMP
#include <omp.h>
#endif
```
**整个代码和并行计算相关的就只有 5 行**
- 如果没有 -fopenmp 编译选项，#pragma 会被直接忽略
```c
#pragma omp parallel for
#pragma omp parallel for collapse(2)
```
- 这个机制对非计算机专业的人实在太友好了
    - 偷看了就偷看了，翻译成条件变量，就有<b style="color:#4169E1">对比</b>了

---
## Prompt: 高性能计算中的并行编程，通常计算图容易静态切分，例如物理模拟的网格划分。网格边界通常是怎么并行处理的？
在高性能计算中的并行编程，网格边界的处理通常涉及**数据交换（通信）和边界条件处理**两个核心方面，常用的方法有：

1. **重叠区域（Ghost/halo cells）设计**
每个并行子区块（子网格）在实际计算区域外，保留一圈冗余的网格（称为ghost cells或halo cells），用于存储来自相邻进程（或线程）边界上的数据。这样每个计算单元处理本地数据时，可以“看到”邻居的边界数值。

2. **邻域通信**
在每个迭代步开始时，子区块通过通信（如MPI完成的Send/Recv）更新自身ghost cells的内容，把与邻接计算单元“接壤”的边界数据交换过来，实现边界一致性。

3. **边界条件处理**

- 对外部边界，通常在各自进程或线程上结合计算物理模型，设定特定边界条件（如Dirichlet、Neumann或周期边界）。
- 对内部边界（即子区块之间接口），通过数据交换保持同步。

4. **通信与计算重叠**
为提升效率，常采用异步通信（如MPI的Isend/Irecv），在等待数据传输的同时计算内部非边界点，减少等待耗时。

5. **典型实现框架**
如MPI（分布式内存）、OpenMP（共享内存）、CUDA（GPU域分块），都具有边界数据同步的机制。

**总结**：网格边界的并行处理核心是利用ghost cells实现邻区块之间的数据交换，通过高效的通信机制和异步计算，实现全局网格上的一致性和高效性。

---
## 18.2 我们身边的并发编程
web前端

javascript

HTML: hypertext markup language

---
**互联网的开始：Web 1.0
从 PC 时代到互联网时代 (1990s)**

- Amazon (1994), Yahoo (1994), eBay (1995), Google (1998)
- HTTP (RFC 2018 HTTPS: 2000.5), HTML，但没有 CSS
    - 中国互联网初代 “三巨头”：新浪、搜狐、网易诞生

`<font>, <table>, vbscript` 和切图工程师一统天下

```html
<script language="vbscript">
Function validateForm()  ' 仅限 Internet Explorer
  If document.myForm.username.value = "" Then
    MsgBox "请输入姓名！"
    validateForm = False
  Else
    validateForm = True
  End If
End Function
</script>
```
- 设计师用 Photoshop 画出像素级精确的网页，然后<b style="color:#4169E1">切成表格</b>
    - Responsive design? 不存在的

---
**从 Web 1.0 到 Web 2.0
Asynchronous JavaScript and XML (Ajax; ~1999)**
- <b style="color:#4169E1">允许网页实现 “后台刷新”</b>
    - 悄悄请求后端，然后更新 DOMTree
    - “应用” 可以做的，网页也都可以做了！
- (你没看错，竟然不是 JSON)
    - 原因：后端 (Java) 应用广泛使用 XML

**jQuery \$ (2006): A DOM Query Language (编程抽象)**
- 让我们优雅地打开 [jw.nju.edu.cn](https://jw.nju.edu.cn/)
    - 2000s 的 “土味动画” 来啦！
```
$(".news_list li a").text("这是假新闻哦，骗你的~");  // By GPT-4.1
```

**从此，做 “任何事” 都只要浏览器就行**
center

**甚至诞生了 ChromeOS**
- HTML + CSS 构建应用的方便程度超过传统 GUI 编程
- GTK, Qt, MFC 谁用谁知道 😂
    - ChromeOS 没能成功
    - 微信小程序继承了 ChromeOS 的遗志 😂

---
**Web 2.0 时代的并发编程
Challenges**
- 线程 (在 1990s) 开销很大
- 连程序都写不利索的人，让他并发编程？
    - Data race, atomicity violation, ... 分分钟教你做人

**于是有了 event-based concurrency (动态计算图)**
- <b style="color:#4169E1">禁止任何计算节点并行</b> (和高性能计算完全不同的选择)
    - 允许网络请求、sleep 在后台执行
    执行完后产生一个新的<b style="color:#4169E1">事件</b> (计算节点)
    - 假设网络访问占大部分时间；浏览器内计算只是小部分
    - <b style="color:#4169E1">事件可以在浏览器里看到！</b>

**混沌时代的计算图
“Callback hell (回调地狱)”**
2025 年，教务系统里还能看到明文 💩🏔️
```
$.ajax({
    url: '/api/user',
    success: function(user) {
        $.ajax({
            url: `/api/user/${user.id}/friends`,
            success: function(friends) {
                $.ajax({
                    url: `/api/friend/${friends[0].id}`,
                    ...
                });
            },
            error: function(err) { ... }
        });
    }, ...
});
```

**回归 “描述计算图”
Promise: 描述动态计算图**
```
useEffect(() => {
    fetch(`/api/localhost/?action=demo&path=${path}`)
        .then(response => response.json())
        .then(fetchedData => setData(fetchedData))
}, []);
Promise.all([
    fetch(...).then(...),
    fetch(...).then(...),
    fetch(...).then(...),
]).then(
    // succeeded
).catch(
    // error handling (catches exceptions in the fetch)
)
```

**更多的语法糖**
```
async function fetchData() {
  const response = await fetch(
    '/api/submissions/?token=12345678'
  )
  return response.json()
}
await fetchData()
function makeItAsync(fn) {
  return function(...args) {
    return new Promise((resolve, reject) => {
      try { resolve(fn.apply(this, args)); }
      catch (e) { reject(e); }
  });
  }
}
```

**从 “前端” 到 “全栈”
ECMAScript 2015 (ES6)**
- 一统第三方库 “军阀混战” 的局面
- 开源生态开始起飞

**现代前端的代表作品**
- Angular, React, Vue
- Express.js, Next.js
- Bootstrap, Tailwindcss
- Electron ([vscode](https://code.visualstudio.com/Docs/editor/whyvscode#:~:text=Using%20Electron%2C%20VS%20Code%20combines%20web%20technologies%20such,editor%2C%20Internet%20Explorer%27s%20F12%20Tools%2C%20and%20other%20projects.))
- asm.js (和之后的 [WebAssembly](https://webassembly.org/docs/faq/))

**我们看到历史车轮碾过
PC → Web → Web 2.0 (UGC) → AI (AGI)**
- “框架” 是驱动技术发展的原动力
- 我们需要<b style="color:#4169E1">好的抽象</b>来表达人类世界中的需求
    - <b style="color:#4169E1">简单可靠</b>，聚集大量行业开发者
        - AI 也许是这里的 “开发者”
    - <b style="color:#4169E1">灵活通用</b>，构造各种应用程序

**单机 → 互联网 → 移动计算 → ???**
- 机遇和不确定
- 风险和回报

---
## 18.3 数据中心中的并发编程
**数据中心：互联网 & AI 时代的幕后英雄
乌兰察布云谷：全国最低电价 + 全年 10 个月自然风冷**

**数据中心程序：特点**
> “A network of computing and storage resources that enable the delivery of shared applications and data.” (CISCO)

**以海量分布式数据 (存储) 为中心**
- 实时的 “小数据处理”
    - 内容分发、用户认证、视频直播、弹幕……
- 离线的 “大数据处理”
    - 内容索引、数据挖掘……

**我们的生活离不开数据中心应用**
- 搜索、社交、支付、游戏……

**以及，为 AI 提供支持**
center

- 基础模型的 “下半场”: 调用服务、执行代码、生成图像……

**数据中心里的并发编程
高吞吐 (QPS) & 低延迟的事件处理**
- 处理事件可能需要读写持久存储或请求网络上的服务
延迟不确定
- 线程维护和上下文切换都会带来开销

**假设有数千/数万个请求同时到达服务器……**
- “Denial of Service, DoS”
    - 全国的小爱音箱在小米汽车发布会上同步瘫痪

**The C10K Problem
Dan Kegel, 1999**
> It's time for web servers to handle ten thousand clients simultaneously, don't you think? After all, the web is a big place now.
```c
while (true) {
    Request *rq = get_request();
    pthread_create(&tid, NULL, handle_request, rq);
}
```
- 10K 个请求，每个请求需要 1ms 处理
    - 需要 10s 才能处理完
    - 这简直就是 fork bomb!

**今天的版本答案
Serverless Computing: 我才不管并发呢**
- Function as a Service (FaaS): 系统自动 scale 到 C10M
    - 大号的 JavaScript 程序 (但没有 shared memory)
    - 需要 [idempotence](https://www.usenix.org/conference/osdi23/presentation/ding)
```js
const AWS = require('aws-sdk');
const dynamo = new AWS.DynamoDB.DocumentClient();

exports.handler = async (event) => {
    const body = JSON.parse(event.body);
    const { username, password } = body;

    await dynamo.put({
        TableName: 'Users',
        Item: { username, password, }
    }).promise();
    return { statusCode: 201, body: JSON.stringify(...), };
};
```

**用户是爽了，系统谁来实现？
Challenge: 高可靠、低延迟的多副本分布式存储和计算**
- 数据保持一致 (Consistency)、服务时刻可用 (Availability)、容忍机器离线 (Partition tolerance) 不可兼得

**协程：操作系统 “不感知” 的上下文切换
和线程概念相同**
- 进程内独立堆栈、共享内存的<b style="color:#4169E1">状态机</b>
- 但 “一直执行”，直到 yield() 主动放弃处理器
    - yield() 是函数调用
        - 只需保存/恢复 non-volatile 的寄存器
        - (线程切换需要保存/恢复全部寄存器)
    - 但 sleep (I/O) 时，所有协程都 “卡住了”
        - 失去了并行

**协程：例子**
```python
import random

def T_worker(name):
    i = 0
    while (i := i + 1):
        print(f'[{name}] i = {i}')
        yield()

threads = [T_worker(i) for i in range(1000000)]
while True:
    random.choice(threads).send(None)
```
- 在同一个操作系统线程中执行
    - 可以由程序控制调度
    - 除了内存，不占用额外操作系统资源

`python3 a.py`

---
**Go 和 Goroutine
小孩子才做选择，多处理器并行和轻量级并发我全都要！**
- Goroutine: 概念上是线程，实现是线程和协程的混合体

**Goroutine 实现**
- 每个 CPU 上有一个 Go Worker Thread (协程调度器)
- 协程执行 blocking API (sleep, read)
    - 偷偷调用 non-blocking 的版本
    - 成功 → 立即继续执行
    - 失败 → 立即 yield 到另一个需要 CPU 的 goroutine
        - 完全可以在单个服务器上启动 1,000,000 个 goroutine 共享处理器算力

**Go 语言中的同步与通信**
> Do not communicate by sharing memory; instead, share memory by communicating. ——Effective Go

**共享内存 = 万恶之源**
- 信号量/条件变量：实现了同步，但没有实现 “通信”
    - 数据传递完全靠手工 (没上锁就错了)

**但 UNIX 时代就有一个实现并行的机制了**
- `cat *.txt | wc -l`
    - 管道是一个天然的生产者/消费者！
    - 为什么不用 “管道” 实现协程/线程间的同步 + 通信呢？
        - Channels in Go

---
> **Golang 并发编程案例**：Go 语言为数据中心应用提供了高 I/O 并发的基础机制和 goroutine 之间的同步机制。在概念上，goroutine 等同于线程；但实现却比线程轻量得多：Go worker 在一个线程内同时实现了协程和 I/O 的调度。

```bash
sudo apt update && sudo apt install golang-go
go run fib.go
```

---
## 总结
　　***Take-away Messages***: 我们在 “更好的编程” 这条路上从未停止过努力。针对不同应用的应用，最终形成了 “领域特定” 的解决方案：Web 中的异步编程、高性能计算中的 MPI 和 OpenMI、数据中心中的 goroutines。更有趣的是，我们可以看到：改变世界的技术，往往只是一个小小的奇思妙想，最终坚持到底得到的。

---
## matlab parfor是不是也是并发编程

是的，你说的没错。在 MATLAB 中，`parfor`（Parallel for-loop）正是一种用于**并发编程**的工具，它属于 MATLAB 并行计算工具箱（Parallel Computing Toolbox）的一部分。它的主要目的是将传统的 `for` 循环迭代任务自动分发到多个计算单元（称为 "workers"）上同时执行，从而利用多核处理器或计算集群来加速计算。

为了让你更清晰地理解 `parfor` 并发与普通 `for` 循环的区别，请看下面的对比表格：

| 特性         | `for` 循环                                  | `parfor` 循环 (并发)                                                                                              |
| :----------- | :------------------------------------------ | :------------------------------------------------------------------------------------------------------------------- |
| **运行方式**   | 串行执行：迭代依次进行                          | 并行执行：多个迭代同时在不同 Worker 上运行                                                                      |
| **速度**     | 相对较慢                                      | 通常更快（尤其当迭代任务独立且耗时较长时）                                                                           |
| **内存使用**   | 单一 MATLAB 进程使用内存                        | 每个 Worker 都有自己独立的内存空间，需要传输数据                                                                     |
| **适用场景**   | 通用循环，迭代间有依赖关系也可                    | **迭代间相互独立**、无数据依赖（例如，参数扫描、蒙特卡洛模拟）                                                               |
| **开销**     | 无额外通信开销                                  | 有进程启动、数据分发和结果收集的通信开销                                                                             |
| **编程复杂性** | 简单                                          | 需注意变量分类（如广播变量、切片变量、归约变量）和数据独立性                                                                  |

---

### 🔧 `parfor` 的主要特性和要点

1.  **循环独立性**：`parfor` 要求每次循环迭代必须是**独立的**，即一次迭代的结果不依赖于另一次迭代的结果。这是 `parfor` 能并行执行的前提。
2.  **变量分类**：在 `parfor` 循环中，变量被分为几类，例如**循环变量**（如 `i`）、**切片变量**（从外部传入且索引与循环变量相关的数组）、**广播变量**（外部传入但在循环内只读的变量）、**归约变量**（用于累积结果的特殊变量，如 `+` 操作）以及**临时变量**（循环内部创建和使用）。正确理解这些变量类型对于编写正确的 `parfor` 代码至关重要。
3.  **Worker 数量**：你可以通过 `parpool` 命令启动一个并行池（parallel pool）来指定使用的 Worker 数量（例如 `parpool('local', 4)` 启动 4 个 Worker）。也可以在 `parfor` 语句中直接指定最大线程数，例如 `parfor (i = 1:n, numThreads)`。
4.  **开销与加速比**：虽然 `parfor` 可以加速计算，但进程间通信、数据传输等会带来额外开销。因此，**并非所有 `for` 循环改为 `parfor` 都能获得加速**。通常，当循环体内计算量较大（耗时较长）、迭代次数较多，且迭代间真正独立时，加速效果才比较明显。对于非常快速的循环，并行化的开销可能反而会使总时间增加。
5.  **工具箱支持**：使用 `parfor` 需要安装并拥有 Parallel Computing Toolbox 的许可证。

---

### ⚠️ 使用 `parfor` 的注意事项

*   **数据依赖性**：务必确保循环迭代之间没有数据依赖性。尝试并行化有依赖关系的循环会导致不可预测的结果或错误。
*   **无法嵌套**：通常不能直接嵌套 `parfor` 循环（即一个 `parfor` 循环内部不能再包含另一个 `parfor` 循环）。但外层使用 `parfor`，内层使用普通 `for` 循环是常见的做法。
*   **某些函数或操作的限制**：在 `parfor` 循环体内，某些操作可能受到限制，例如不能使用 `save` 函数直接保存文件（除非通过特殊处理）、不能调用 `coder.extrinsic`等。
*   **调试**：并行代码的调试比串行代码更复杂。

---

### 💡 何时考虑使用 `parfor`

*   **计算密集型任务**：循环体内每次迭代的计算需要较多时间（例如，复杂的数学运算、大型矩阵操作、图像处理、仿真等）。
*   **迭代次数多**：有大量的迭代需要执行。
*   **任务相互独立**：每次迭代的计算不依赖于其他迭代的结果。
*   典型的应用场景包括：
    *   蒙特卡洛模拟（Monte Carlo simulations）
    *   参数扫描（Parameter sweeping）
    *   对大量独立数据元素进行相同的操作（如对图像集合应用相同的滤镜）

---

### 📌 总结

`parfor` 是 MATLAB 中实现**数据并行**的一种重要并发编程工具。它通过将独立的循环迭代分发到多个计算核心上同时执行来加速计算，非常适合处理计算密集型和**可并行化**的循环任务。

不过，使用 `parfor` 的关键在于确保**循环迭代的独立性**，并且要注意并行化带来的开销，权衡其是否真的能为你的特定代码带来性能提升。对于简单的循环或者迭代间有紧密依赖关系的循环，坚持使用传统的 `for` 循环可能是更好的选择。

希望这些信息能帮助你更好地理解 `parfor`。