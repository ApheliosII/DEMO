# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

---
==由于学习进度慢,后面只注意重点内容。==

[PPT](https://jyywiki.cn/OS/2025/lect20.md)

---
## 20. 设备和驱动程序
虚拟化和并发两个主题的内容为我们展示了操作系统为应用程序提供的各类 API——我们可以通过系统调用和基于系统调用封装的库函数创建进程和线程使用多个处理器、访问文件系统中的操作系统对象等。是时候回到 “everything is a file” 的 “everything” 了。

**本讲内容**：计算机系统的最后一块拼图：I/O 设备原理、构造与实现，包括键盘、鼠标、打印机、显卡……你会感到 “实现计算机系统” 真的是可以做到的。

---
## 20.1 输入/输出设备
**I/O设备**

**Everything is a File**
**文件：有 “名字” 的数据对象**

- 字节流 (终端，random)
- 字节序列 (普通文件)

**文件描述符**
- <b style="color:#4169E1">指向操作系统对象的 “指针”</b>
    - Everything is a file
    - 通过指针可以访问 “一切”
- 对象的访问都需要指针
- open, close, read/write (解引用), lseek (指针内赋值/运算), dup (指针间赋值)

```bash
lsblk
ls /dev/
```
**没那么简单！**
**让我们插个优盘试试……**
- 优盘的文件系统会自动 “出现”
- 但你是专业人士
    - 看看 /dev/ 是不是发生了一些什么变化

**水面下的冰山**
- /dev/ 下的对象不会凭空创建
    - [udev](https://www.freedesktop.org/software/systemd/man/latest/systemd-udevd.html) - /lib/udev/rules.d 💩🏔️
    - udisks2 - 这才是真正执行 mount 的程序

```bash
cd /lib/udev/
cd rules.d/
ls

systemctl list-units --type=service
/udisks2
```

**“计算” 和 “物理世界” 之间的桥梁**
**I/O 设备 = <b style="color:#4169E1">一个能与 CPU 交换数据的接口/控制器</b>**
- 就是 “几组约定好功能的线” (寄存器)
    - 通过握手信号从线上读出/写入数据
- 给寄存器 “赋予” 一个内存地址 (Address Decoder)
    - CPU 可以直接使用指令 (in/out/MMIO) 和设备交换数据
    - 是的，就这么简单！

协议

**答案：一根线、一条指令 (树莓派上就有)
GPIO (General Purpose Input/Output)**
- 极简的模型：Memory-mapped I/O 直接读取/写入电平信号

---
## 20.2 输入/输出设备案例
**串口，打印机和总线**

**#1: 串口 (UART)**
**“COM1” (Communication 1)**
```c
#define COM1 0x3f8

static int uart_init() {
  outb(COM1 + 2, 0);   // 控制器相关细节
  outb(COM1 + 3, 0x80);
  outb(COM1 + 0, 115200 / 9600);
  ...
}

static void uart_tx(AM_UART_TX_T *send) {
  outb(COM1, send->data);
}

static void uart_rx(AM_UART_RX_T *recv) {
  recv->data = (inb(COM1 + 5) & 0x1) ? inb(COM1) : -1;
}
```

**#2: 键盘控制器**
**IBM PC/AT 8042 PS/2 (Keyboard) Controller**
- PS/2 接口的 6 根线分别是什么作用？

74ls系列 实验电路

**#3: 磁盘控制器**
**ATA (Advanced Technology Attachment)**
- IDE 接口磁盘 (40pin data 很 “肥” 的数据线 + 4pin 电源)
    - primary: 0x1f0 - 0x1f7; secondary: 0x170 - 0x177

**#4: 打印机**
- 打印机将字节流描述的文字/图形打印到纸张上

**PostScript 和打印机
PostScript: 一种描述页面布局的 DSL**
- 类似于汇编语言 (由 “编译器”，如 latex，生成)
    - PDF 是 PostScript 的 superset

**打印机 (没错，实现自己的打印机没有那么困难)**
- 将汇编语言翻译成机械部件动作的设备
    - PCL, PostScript, [IPP](https://www.rfc-editor.org/rfc/rfc8011)(AirPrint)


```bash
# page.ps
evince page.ps # wsl2 fail --> linux物理机

vi page.pdf
```

**#5: 总线**
**提供设备的 “虚拟化”：<b style="color:#4169E1">注册</b>和<b style="color:#4169E1">转发</b>**
- 把收到的地址 (总线地址) 和数据转发到相应的设备上
- 例子: port I/O 的端口就是总线上的地址
    - IBM PC 的 CPU 其实只看到这一个 I/O 设备

**PCIe 总线**
**今天获得 “CPU 直连” 的标准设备**
- 接口
    - 75W 供电
    - - 所以我们需要 6-pin, 8-pin 的额外供电
- 数据传输
    - PCIe 6.0 x16 带宽达到 128GB/s
        - 于是我们有了 800Gbps 的网卡 😂
    - 总线自带 DMA (专门执行 memcpy 的处理器)
- 中断管理
    - 将设备中断转发到操作系统 (Message-signaled Interrupts)

```bash
lspci
lspci -t
lspci -tv
lspci -tv | ag -q what are these
```

**支撑了现代 I/O 设备的体系**
- 高速设备都是直插 PCIe 的
    - FPGA
    - 显卡
    - 网卡
    - ……
- USB Bridge
- NVMe

---
> **PostScript**: PostScript是一种页面描述语言 (PDL)，由 Adobe Systems 在 1980 年代初开发。它是一种编程语言，专门用于描述图形和文本的布局和外观，主要用于打印和显示系统。PostScript 文件包含了详细的指令，告诉打印机或显示设备如何生成页面上的每一个元素，包括字体、图形、颜色和图像。

---
## Prompt: NVMe 是如何接入 PCIe 总线的？
NVMe（Non-Volatile Memory Express）是一种为高速存储器（如SSD）设计的主机控制器接口协议。它直接通过PCIe（Peripheral Component Interconnect Express）总线与主板相连，绕过传统的SATA或SAS通道，大幅提升数据传输速率和并发处理能力。

详细描述如下：

1. **物理层面**：NVMe设备通常为M.2、U.2或PCIe扩展卡形态，插入主板相应的PCIe插槽。这样，存储器与CPU之间建立起物理连接，使用PCIe通道（如x2、x4、x8）。

2. **链路层与传输层**：NVMe利用PCIe的高速点对点通道，支持多条并行通路，实现大带宽、低延迟的数据传输。NVMe协议使SSD能充分利用PCIe 3.0、4.0或更高版本的带宽。

3. **协议层面**：主机操作系统通过NVMe驱动，与SSD上的NVMe控制器通信。PCIe作为物理和数据链路的载体, NVMe作为协议负责命令、队列管理和数据传输。

4. **并发处理**：NVMe支持多队列（主机和控制器可各自支持多至64K队列，每队列64K命令），显著提升并发和效率，这是基于PCIe总线的多通道特性实现的。

总结：NVMe设备直接插接在PCIe总线上，利用PCIe的高速通道和NVMe协议实现高效的数据交互，显著提升SSD的性能。

---
## 20.3 设备驱动程序
**用程序访问设备**
**程序<b style="color:#4169E1">不能</b>直接访问寄存器**
center

- 设备是可以在程序之间<b style="color:#4169E1">共享</b>的

**仔细想：CPU 和内存也都是 “设备**”
- 操作系统实现了<b style="color:#4169E1">虚拟化</b>
- 我们也实现设备的<b style="color:#4169E1">虚拟化</b>就行了！

**Everything is a File**
**File = 实现了文件操作的 “Anything”**

**设备驱动程序**
**一个 struct file_operations 的实现**
- <b style="color:#4169E1">把系统调用 “翻译” 成与设备能听懂的数据</b>
    - 就是一段普通的内核代码

**例子**
- devfs 中的 “虚拟” 文件
    - /dev/pts/[x] - pseudo terminal
    - /dev/zero, /dev/null ([实现](https://elixir.bootlin.com/linux/v6.14.5/source/drivers/char/mem.c)), /dev/random, ...
- procfs 中的 “虚拟文件”
    - 只要实现读/写操作即可
    - 例子：[/proc/stat 的实现](https://elixir.bootlin.com/linux/v6.14.5/source/fs/proc/stat.c)

```bash
ll /dev/null
cat /dev/null
cat /dev/null | wc
echo hello > /dev/null

cat /proc/self/cmdline
cat /proc/self/status
```

**配置设备**
设备不仅仅是数据，还有**配置**
- 打印机的卡纸、清洁、自动装订……
    - 一台几十万的打印机可不是那么简单 😂
- 键盘的跑马灯、重复速度、宏编程……
- 磁盘的健康状况、缓存控制……

**两种实现方法**
- 控制作为数据流的一部分 (ANSI Escape Code)
- 提供一个新的接口 (request-response)

**ioctl**
> The ioctl() system call manipulates the underlying device parameters of special files. In particular, many operating characteristics of character special files (e.g., terminals) may be controlled with ioctl() requests. The argument fd must be an open file descriptor.

**“非数据” 的设备功能几乎全部依赖 ioctl**
- “Arguments, returns, and semantics of ioctl() vary according to the device driver in question”

```bash
man 2 ioctl
```

> **一个设备驱动程序**：理解了设备驱动程序的职责是把系统调用 “翻译” 成与设备能听懂的数据，我们也可以实现 file_operations 中相应的操作，从而模拟一个设备。

```bash
make fail
wsl2 fail --> linux物理机

ls /dev/nuke*
sudo insmod driver.ko
ls /dev/nuke*

sudo car /dev/nuke0

sudo bash -c 'echo hello > /dev/nuke0'

sudo ./launch 
```

> **隐藏在 libc 中的设备查询**: libc (musl libc) 会根据是否输出到 tty 控制缓冲行为；glibc 则是使用 fstat。功能的增加势必带来了操作系统和应用程序的复杂性。

```bash
make
./hello
./hello | cat
```
TIOCGWINSZ

> **KVM Device**: KVM 设备提供了硬件虚拟化的机制，允许我们在用户空间通过 /dev/kvm 在虚拟化的环境中运行一段代码直到 VM Exit。

```bash
ls /dev/kvm
ls -l /dev/kvm

./kvm
strace ./kvm
open /dev/kvm: Permission denied
```

---
## 20.4 总结
　　***Take-away Messages***: 输入/输出设备可以说是五花八门，你也看到越来越多的设备上甚至 “自带电脑”。但无论如何，操作系统都把它们抽象成一个可以读写、可以控制的，实现了 struct file_operations 的文件 (操作系统对象)。

---
KVM 通常在计算机领域，它更常指 **基于内核的虚拟机（Kernel-based Virtual Machine）**，这是一种集成于 Linux 内核的开源虚拟化技术。下面我将为你详细解释。

### 🖥️ 1. KVM (Kernel-based Virtual Machine)：基于内核的虚拟机

KVM 全称为 **Kernel-based Virtual Machine**，它是一个开源的**系统虚拟化模块**，自 Linux 2.6.20 版本起被集成到 Linux 内核中，可以将 Linux 内核转变为一个**虚拟机监控程序（Hypervisor）**。这使得一台物理计算机（称为宿主机 Host）能够同时运行多个相互隔离的虚拟环境，即虚拟机（Guest VM）。

#### 核心工作原理与架构
*   **硬件支持需求**：KVM 需要 CPU 支持硬件虚拟化扩展（如 Intel VT 技术或 AMD-V 技术）。你可以通过检查 `/proc/cpuinfo` 中的 `vmx` (Intel) 或 `svm` (AMD) 标志来确认你的处理器是否支持。
*   **与 QEMU 的关系**：KVM 本身专注于 CPU 和内存的虚拟化，以及拦截虚拟机的 I/O 请求。它并不直接模拟硬件设备，这部分工作由一个修改版的 **QEMU**（通常是 `qemu-kvm`）来完成。QEMU 运行在用户空间，负责处理 I/O 虚拟化和模拟外部设备，并通过 `/dev/kvm` 接口与 KVM 模块交互。这种分工合作使得 KVM 在保持高性能的同时，能支持丰富的设备模拟。
*   **虚拟机即进程**：在 Linux 系统中，每个 KVM 虚拟机实际上表现为一个标准的 **Linux 进程**，其虚拟 CPU（vCPU）对应进程中的线程，由 Linux 内核自身的调度器进行管理。虚拟机的内存则是该进程的地址空间。

#### 主要特性与功能
KVM 继承并利用了 Linux 内核的诸多成熟特性，因此具备强大的功能：
*   **高性能**：得益于其集成于内核的架构和硬件辅助虚拟化，KVM 的性能开销很小，尤其适合服务器负载。
*   **内存管理**：支持内存超分（Overcommit）、大内存页、NUMA（非统一内存访问结构），以及通过 **KSM（内核同页合并）** 共享相同内存页来节省内存。
*   **动态迁移（Live Migration）**：可以在不中断服务的情况下，将运行中的虚拟机从一台物理主机迁移到另一台。
*   **硬件支持广泛**：支持多种硬件平台（x86, ARM, s390, PowerPC等）。
*   **安全隔离**：可与 SELinux 和 sVirt 结合，为虚拟机提供强制的安全边界和隔离。
*   **其他高级功能**：支持半虚拟化 I/O（virtio）以提升效率、热插拔（CPU、磁盘、网卡等）、对称多处理（SMP）、PCI 设备直通等。

#### 管理工具
管理 KVM 虚拟机的常用工具包括：
*   **libvirt**：一个用于管理虚拟化平台的开源 API 和守护进程，提供了多种语言接口。
*   **virsh**：基于 libvirt 的命令行管理工具。
*   **virt-manager**：一个图形化管理工具，适合桌面环境。

#### 与其它虚拟化方案的比较
*   **与传统 VM（如 VMware Workstation, VirtualBox）**：这类软件通常被称为 **Type-2 Hypervisor**，它们安装并运行在现有的主机操作系统之上。KVM 由于其内核模块的特性，在架构上更接近 **Type-1 Hypervisor**（裸机管理程序），性能通常更高，尤其适合数据中心和服务器场景。而传统 VM 解决方案可能在桌面环境的图形支持和跨平台兼容性上更有优势。
*   **与 Xen**：Xen 是另一种著名的开源虚拟化技术。早期 Xen 基于半虚拟化（Para-Virtualization），而新版本也支持硬件辅助的全虚拟化。Xen 拥有自己独立的调度器和存储管理模块，代码体量相对较大。KVM 则直接利用 Linux 内核的调度器等组件，核心源码更少，集成度更高。


### 💎 总结

当你听到“KVM”时，需要根据上下文来区分：
*   在 **Linux、虚拟化、云计算** 的语境下，它几乎总是指 **Kernel-based Virtual Machine**，一种强大且高效的开源虚拟化解决方案。

---
好的，我们用一个清晰、易懂的方式来解释 KVM。

### 核心定义

**KVM（Kernel-based Virtual Machine）** 是一个开源的**原生（原生）虚拟化解决方案**，它将自己直接集成到 Linux 内核中。简单来说，它可以将 Linux 内核本身转变为一个**裸机管理程序（Type-1 Hypervisor）**，从而允许主机机器运行多个独立的、隔离的虚拟环境，这些虚拟环境被称为**虚拟机（VM）**。

你可以把它想象成：给你的 Linux 系统赋予了“分身”的能力，让它能同时运行多个不同的操作系统（如 Windows, Linux 发行版等）。

---

### 核心工作原理与架构

1.  **它不是一個独立的程序**
    KVM 本身并不执行任何模拟器功能。相反，它只是暴露了一个 `/dev/kvm` 的设备接口。这个接口允许用户空间的程序（如 QEMU）利用内核提供的虚拟化功能来创建和运行虚拟机。

2.  **与 QEMU 的完美搭档**
    KVM 通常与 **QEMU**（一个开源的机器模拟器和虚拟化器）结合使用。在这种组合中：
    *   **QEMU**：负责模拟虚拟机的硬件（如 CPU、内存、磁盘、网卡等），并处理 I/O（输入/输出）。
    *   **KVM**：负责接管 CPU 和内存的虚拟化工作，利用硬件辅助虚拟化技术（如 Intel VT-x 或 AMD-V）来以近乎原生的速度运行虚拟机代码。

    这种分工合作使得 **QEMU+KVM** 的组合既功能完整（能模拟各种硬件），又性能极高（直接使用硬件虚拟化扩展）。

3.  **内存管理**
    KVM 使用 Linux 内核成熟的内存管理功能，包括分页、KSM（内核同页合并）等，来高效地管理虚拟机的内存。

4.  **硬件支持**
    KVM 需要 CPU 支持硬件虚拟化扩展（**Intel VT-x** 或 **AMD-V**）。现代绝大多数服务器和台式机 CPU 都支持此功能。

---

### KVM 的主要特点

*   **高性能、低开销**：由于它直接集成到内核并利用硬件辅助虚拟化，其性能非常接近物理机，开销极小。
*   **开源**：作为 Linux 内核的一部分，它是完全免费和开源的。
*   **安全**：虚拟机作为普通的 Linux 进程运行，受到 Linux 内核的安全模型（如 SELinux）的保护。
*   **原生支持**：是 Linux 的一部分，无需额外安装核心组件（但需要安装管理工具）。
*   **强大的生态系统**：被众多强大的管理工具所支持，如 **libvirt**, **virt-manager** 等。
*   **支持多种操作系统**：可以在虚拟机中运行各种 Windows、Linux、Unix 等客户机操作系统。
*   **实时迁移**：支持将运行中的虚拟机从一台物理主机无缝迁移到另一台，服务不中断。

---

### KVM 与其它虚拟化技术的对比

| 特性 | KVM | VMware ESXi | VirtualBox / VMware Workstation |
| :--- | :--- | :--- | :--- |
| **类型** | **Type-1 (裸机管理程序)** | **Type-1 (裸机管理程序)** | **Type-2 (托管式管理程序)** |
| **集成度** | 集成到 Linux 内核 | 独立的专有内核 | 安装在宿主操作系统上的应用程序 |
| **性能** | **非常高**（接近原生） | **非常高**（接近原生） | 较低（有额外开销） |
| **成本** | 免费和开源 | 商业付费（有免费版） | 免费 |
| **主要应用** | 数据中心、云服务、企业服务器 | 企业级虚拟化、私有云 | 桌面开发、测试、个人使用 |

---

### 谁在使用 KVM？

KVM 是许多大型**公有云**和**企业IT基础设施**的基石：
*   **Google Cloud**：其计算引擎（Compute Engine）大量使用 KVM。
*   **Amazon Web Services (AWS)**：在推出 Nitro 系统之前，其 EC2 服务基于 Xen，后来也大量转向 KVM。
*   **IBM Cloud**, **Oracle Cloud** 等众多云服务商。
*   **OpenStack**：这个著名的开源云操作系统默认使用 KVM 作为其虚拟化引擎。
*   无数企业的私有云和服务器虚拟化环境。

### 总结

**KVM 是一个将 Linux 内核转变为强大、高效、企业级的裸机管理程序的核心技术。它通过与 QEMU 等工具合作，提供了一个功能完整且性能卓越的开源虚拟化平台，是现代云计算和数据中心不可或缺的基石之一。**

对于普通用户，你可以通过像 **virt-manager**（一个图形化管理工具）这样的软件来轻松管理和创建 KVM 虚拟机，就像使用 VirtualBox 一样简单，但能获得更好的性能。