# Markdown 专业指南

## 标题

# H1 标题

## H2 标题

### H3 标题

#### H4 标题

##### H5 标题

###### H6 标题

## 文本样式

*这是斜体*
_这也是斜体_

**这是粗体**
__这也是粗体__

~~删除线文本~~

`行内代码`

## 列表

### 无序列表

- 项目一
- 项目二
  - 子项目一
  - 子项目二

### 有序列表

1. 第一项
2. 第二项
   1. 子项一
   2. 子项二

## 链接和图片

[Markdown官方文档](https://daringfireball.net/projects/markdown/)

![替代文本](https://markdown-here.com/img/icon256.png)

## 引用块

> 这是引用文本
> 多行引用
>
> — 作者名称

## 代码块

```python
def hello_world():
    print("Hello, World!")
    return True
```

## 代码块

```cpp
int main (){
    int n = 5, step = 0;
    while (n != 1){
        if (n % 2 == 0){
            n /= 2;
        }else{
            n = 3 * n + 1;
        }
        step++;
    }
    // printf("The number of steps is %d", step);
    cout << "The number of steps is " << step << endl;
    return 0;
}
//输出：The number of steps is 5
```

==marked==
==???==

## 画图：

### 1. Mermaid（最推荐，通用性强）

1. 流程图示例

```mermaid
graph TD
    A[开始] --> B{判断条件}
    B -->|条件成立| C[执行操作]
    B -->|条件不成立| D[结束]
    C --> D
```

2. 时序图示例

```mermaid
sequenceDiagram
    participant 用户
    participant 系统
    用户->>系统: 提交请求
    系统->>系统: 处理请求
    系统-->>用户: 返回结果
```

### 2. 流程图（Flowchart）语法

```mermaid
gantt
    title 项目时间表
    dateFormat YYYY-MM-DD
    section 阶段一
    任务一 :a1, 2024-01-01, 30d
    section 阶段二
    任务二 :after a1, 20d
    任务三 : 2024-02-20, 12d
```

### 3. 甘特图示例

```mermaid
gantt
    title 项目时间表
    dateFormat YYYY-MM-DD
    section 阶段一
    任务一 :a1, 2024-01-01, 30d
    section 阶段二
    任务二 :after a1, 20d
    任务三 : 2024-02-20, 12d
```

### 4. 类图示例

```mermaid
classDiagram
    class Animal {
        +String name
        +void speak()
    }
    class Dog {
        +void bark()
    }
    Animal <|-- Dog
```

### 5.
```mermaid
flowchart TD
    A[内核加载 initramfs] --> B[initramfs 执行 /init]
    B --> C[加载必要内核模块]
    C --> D[准备根文件系统<br>解密/LVM/RAID/网络]
    D --> E[挂载真实根文件系统]
    E --> F[执行 switch_root]
    F --> G[卸载 initramfs 并释放内存]
    G --> H[启动真实根文件系统上的 systemd<br>PID=1]
    H --> I[systemd 解析 default.target]
    I --> J[并行启动系统服务]
    J --> K[进入用户登录界面]
```

### 
```markdown
---
-->
===
==>
--o
--x
<-->
-.-
-.->
-.text.->
```

```mermaid
graph LR
    A[A] --- B{B} --> C(C) --o D{D} <--> E{E} -.-> F{F}
    A === B ==> C --x D -.- E -.text.-> F

```

## 字体颜色

- <b style="color:red">唯一能够 “执行程序” 的系统调用 </b>唯一能够 “执行程序” 的系统调用
- <b style="color:#4169E1">重置 </b>重置
- <font color="red">你的文本</font>你的文本

- <table><tr><td bgcolor="#F5EEFD">文字</td></tr></table> 重置
- <mark style="background-color: red">文字 </mark>重置
- <span style="background-color: lightgreen">文字重置

## 首行缩进
操作系统通过虚拟内存为每个进程提供独立的地址空间，实现了进程间的隔离和保护。操作系统通过 mmap/munmap 实现地址空间的管理，并且还提供特定机制 (如 procfs、ptrace、process_vm_writev、共享内存等) 访问彼此的地址空间。
　　操作系统通过虚拟内存为每个进程提供独立的地址空间，实现了进程间的隔离和保护。操作系统通过 mmap/munmap 实现地址空间的管理，并且还提供特定机制 (如 procfs、ptrace、process_vm_writev、共享内存等) 访问彼此的地址空间。

全角空格
