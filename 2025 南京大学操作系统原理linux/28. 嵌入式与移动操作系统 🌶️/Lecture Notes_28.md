# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]


[PPT](https://jyywiki.cn/OS/2025/lect28.md)

---
## 28. 嵌入式与移动操作系统 🌶️
虚拟化和容器技术使我们可以管理成千上万台计算机，为小到一个班集体、大到全世界人提供互联网的购物、娱乐、社交、工作、学习等服务。而连接每一个人的，不仅是云端的超级分布式应用，还有万千终端设备。显然，Linux、Windows 操作系统的 API 完全可以胜任管理这些设备；但它们的操作系统，和数据中心又似乎有些不同。

**本讲内容**：嵌入式 (实时) 和移动操作系统的设计与实现原理。

---
## 28.1 嵌入式操作系统
**嵌入式系统**
**“Embedded”: 计算机系统是 “嵌入” 到设备中的**
- 人造卫星、工业控制、家用电器、医疗器械、穿戴设备……
- 体积小、功耗低、可靠性高
    - 操作系统通常<b style="color:#4169E1">更简单</b> (领域限定)；但 Linux 也是可以的

**例子：PLC (Programmable Logic Controller) 和工控**

**典型设计：Event-based**
**通常有实时 (real-time) 保障**
- 在严格的时间限制内对外部事件作出可预测响应
- 例子：无论车机多花哨，最终实时控制的仍然是 MCU

**例子：FreeRTOS**
>A FreeRTOS application will start up and execute just like a non-RTOS application until vTaskStartScheduler() is called.

**优先级带来的麻烦**
```python
def jyy():
    set_priority(1)
    mutex_lock(restroom_lock)

def 马院长():
    set_priority(10)
    long_work()

def 校长():
    set_priority(100)
    mutex_lock(restroom_lock)
```
**如果只有一个处理器**
- jyy 在持有互斥锁的时候被中优先级进程赶下了处理器……
- “优先级反转 (Priority Inversion)”

**The First Bug on Mars”**
**登上火星的计算机系统**
- Lander (登陆舱)
    - IBM Rad6000 SC (20 MIPS), 128 MiB RAM, 6 MiB EEPROM
- Rover (火星车)
    - Intel 80C85 (0.1 MIPS), 512K RAM, 176K Flash
- VxWorks “实时” 任务操作系统
    - ASI/MET task: 大气成分监测 (低)
    - `bc_dist` task: 分发任务 (中)
    - `bc_sched` task: 总线调度 (高)
    - 着陆后开始出现系统重启

---
## 28.2 移动操作系统
**Android**
- Nokia 5310 XpressMusic (2007): 320 x 240 Screen; 2 MP Camera; 30 MB Storage (非常精细)
- Symbian S40 (相比于 “功能机” 已经是巨大的进步了)

Symbian 和 J2ME 的时代

iPhone : memeroy & storage

HTC

**Android 的兴起**
**Linux + Full JVM + Framework API + 开放平台**
- Dalvik VM → Android Runtime @ 5.0
- 那么，代价呢？<b style="color:#4169E1">卡到爆啊</b>！
    - HTC G1: Qualcomm MSM7201
        - 32-bit ARMv6 @ 528MHz (1 CPU, TSMC 90nm)
        - 顺序八级流水线 (IPC < 1)，地图都会卡

**但这其实是一个高瞻远瞩的决定**
- <b style="color:#4169E1">他们赌摩尔定律会生效</b>！(同年: i7-965, 4C8T, 6 发射)
- Symbian: 暴毙于 C++; Windows Phone: 暴毙于 C#
    - (其实也许熬到网页时代，就都能活下来了)

**One More Comment**
**初期的 “低性能” 总会解决的**
- 算法 (软件) 会进步
- 硬件也会进步
    - 摩尔定律还没死呢！
**在大语言模型时代，同样成立**
- 600B 模型能做到的，30B 的模型也能做到
- 一定存在一个临界点，能实现 “实时推理无处不在”

**Android Apps**
**首先，是一个 Java 程序 (Kotlin)**
**其次，有运行模型**
- Android Platform APIs
    - android.view.View: “the basic building block for user interface components”
    - android.webkit.WebView - 嵌入应用的网页
    - android.hardware.camera2 - 相机
    - android.database.database - 数据库
- 四大组件：Activity, Service, ContentProvider, BroadcastReceiver

**Platform API 之下：一个 “微内核”**

ahead of time编译

![android-stack](C:/Users/Administrator/Desktop/android-stack.webp)

**例子：Binder IPC**
**Remote Procedure Call (RPC)**
- `remote.transact()`

**在性能优化和易用之间的权衡**
- 注册机制
    - 相比之下，管道/套接字就太 “底层” 了，需要手工管理的东西太多
- 基于共享内存实现
    - Linux Kernel binder driver
    - Copy once
- 服务端线程池

**例子：Activity Stack**
- 在微信拉起知乎，知乎可以返回到微信
    - 这行为在 “切换应用” 后仍能保持
- 与窗口管理器的 Alt + Tab 稍微不同

> **AOSP 计算器**: 这个例子展示了一个最基础的 Android 应用——是的，Android 开发和普通的 Java 程序开发并没有什么 “本质” 区别；但 Google 精心设计了 Android Studio，包括界面设计、虚拟设备、测试和调试等，造就了繁荣的应用生态。

---
## 28.3 每个人都可以是生活的黑客
**Hacking Android**
**Android: 不只是应用生态**
**还是开发者生态**

**Android Debug Bridge (adb)**
- adb push/pull/install
- adb shell (screencap /sdcard/screen.png)
- adb forward/logcat/jdwp, ...


```shell
adb --help
adb shell
ls
which ls
ls/
ls/dev
ls --help
file $(which ls)
file toybox
ps
pmap # ppid #
```

**我们可以做什么？**
**scrcpy**
- 在设备上捕获视频流 (通常有硬件加速)，再传递给 Host

**UI Automation (Monkey)**
- Infinite Monkey Theorem: 给 10,000 只猴子和打字机，只有一只能打出 C 程序，其他只能打出 Perl 程序 😊
    - 我们的工作：Cross-device record & replay

**甚至可以 “任意改变” App 的行为**

**Hacking Android 👿**
**如何杀死一个 Android 进程？**
- RTFSC: ActivityManagerService.java
    - Android 每个 App 都有独立的 uid
    - 遍历进程表，找到属于 uid 的进程
    - Process.KillProcessGroup
        - 间隔 5ms，连续杀死 40 次，防止偶然 “杀不干净”

**那么，我们是不是就可以利用数据竞争进程保活了呢？**
- 成为孤儿进程从而不会立即收到 SIGKILL 信号
- 在被杀死后立即唤醒另一个进程 😂
    - “Diehard apps” (EuroSys'19)

应用：“强行停止”
flock
腾讯apps
强行停止都停止不了

**在 Android 的浪潮里**
center

**我们也想过做一些很有趣的事**
- 甚至也做成了 (Jigsaw paper)
    - 在 LLM 时代，更容易做成、跟容易做好
- 我们都被 “publish or perish” 束缚了
    - <b style="color:#4169E1">每个人都可以是生活的黑客</b>

---
## 28.4 总结
　　***Take-away Messages***: 在每个应用领域，操作系统都会做出一些面向领域的特殊设计——例如 real-timeliness，或是面向应用生态的编程模型。回到应用视角的操作系统：它是一组 API，使开发者能愉快地构建应用，是的，就是这么简单。