# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

---

[PPT](https://jyywiki.cn/OS/2025/lect22.md)

---
## 22. 文件系统 API
存储器之上，操作系统 (文件系统) 实现了 “目录树” 结构的文件系统，使我们能以一种直观、自然、有序的方式管理操作系统里数以百万计的持久化对象。“目录和文件” 的简单概念，在今天的操作系统中又是如何得以延续和扩充的呢？

**本讲内容**：操纵目录和文件系统的 API。

---
## 22.1 目录树
**树状分层索引：利用信息的局部性**
```
.
└── 学习资料
    ├── .
    ├── ..
    ├── .学习资料(隐藏)
    ├── 问题求解1
    ├── 问题求解2
    ├── 问题求解3
    ├── 问题求解4
    └── 操作系统
```
- 隐藏 “.” 开头的文件不是操作系统的行为，只是为了<b style="color:#4169E1">偷懒</b>
    - if (fname[0] == '.') continue;

```bash
ls
ls -a
ls -a ~

pwd
cd .
cd ..

ls/
```

**Filesystem Hierarchy Standard**
**约定俗成的目录结构**
- [FHS](http://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html) enables software and user to predict the location of installed files and directories.
    - 例子：macOS 是 UNIX 的内核 (BSD), 但不遵循 Linux FHS

**“增删改查”**
- mkdir: 创建目录
- rmdir: 删除目录
- getdents: 读取目录
```c
int mkdirat(int dirfd, const char *pathname, mode_t mode);
int unlinkat(int fd, const char *path, int flag);
ssize_t getdents64(int fd, void *dirp, size_t count);
```
- 看看 `bash -c 'echo /etc/**/*'` 的 strace
    - 更多的工具，例如 fzf 也是同样的实现

```bash
cd /tmp/
strace mkdir hello
strace rm -r hello
mkdir hello
rm hello
rm hello

strace rm hello &| vim - # fish

echo /etc/**/*.conf
cat /etc/**/*.conf

strace bash -c 'echo /etc/**/*.conf' 

sudo apt install fzf
fzf # 搜索
bash: vim $(fzf) 
fish: vim (fzf)
```

**图书馆的索引系统其实可以淘汰了**
- 一本书的内容就是它的索引
- 由计算机决定最优的陈列方式 (就像书店)
- 路径 → 结构化查询 (wildcard & globbing) → 智能检索

**硬 (hard) 链接**
**需求：系统中可能有同一个运行库的多个版本**
- `libc-2.27.so`, `libc-2.26.so`, ...
- 还需要一个 “当前版本的 libc”
    - 程序需要链接 “`libc.so.6`”，能否避免文件的一份拷贝？

**(硬) 链接：允许一个文件被多个目录引用**
- 文件系统实现的特性 (ls -i 查看)
    - 不能链接目录、不能跨文件系统
    - 删除文件的系统调用称为 “unlink” (refcount--)
        - 现在用 “万能” 的 unlinkat，也可以删除空目录

- [x] 同一个文件可以有多个名称，但它们都指向同一个内容：a.txt → hello; b.txt → hello。
```shell
ls /lib64/ -l

cd /tmp/
mkdir hello
cd hello/
vim a.txt
ls
cat a.txt
ls -l
-rw-rw-r-- 1 hhu hhu 6 Sep 18 02:02 a.txt
# 1 代表链接数

strace ln a.txt b.txt

vim a.txt
编辑 a.txt，保存并退出
vim b.txt # 变了 继续改
cat a.txt # 继续变化

ls -i
168904 a.txt  168904 b.txt
编号一样，指向同一个文件
```

**软 (symbolic) 链接**
**软链接：在文件里存储一个 “跳转提示”**
- 软链接也是一个文件
    - 当引用这个文件时，去找另一个文件
    - 另一个文件的绝对/相对路径以文本形式存储在文件里
    - 可以跨文件系统、可以链接目录、……
**几乎没有任何限制**
- 类似 “快捷方式”
    - 链接指向的位置不存在也没关系
    - (也许下次就存在了)

```shell
ln -s nonexist test
ls -l
cat test
strace cat test &| vim - # fish
vi nonexist # Hello
cat nonexist
strace cat test &| vim -


ls -l /lib64
lrwxrwxrwx 1 root root 9 Jan  7  2025 /lib64 -> usr/lib64

cd /usr/lib64/
ll .
lrwxrwxrwx 1 root root 42 May 26 15:25 ld-linux-x86-64.so.2 -> /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
```

**软链接：甚至可以用来制作 Galgame**
**游戏 = 状态机**
- 用当前目录表示状态，符号连接实现迁移 (图像: nyaigc)

```shell
# ggmaker
make
./start.sh
ps
ls
ls -l
cd .
```

**软连接：还可以用来 “伪造” 文件系统！**
Nix 系统中，所有的文件都以树状结构存储在 `/nix/store` 目录下。

---
> **globbing**: 在 pstree 中，我们实现了目录树的遍历——我们几乎总是需要对底层文件系统 API 的封装，例如十分方便的 glob()。

> **Symlink Game**: 我们可以使用符号链接创建 “近乎任意” 的目录结构，包括任意的图结构 (状态机)，操作系统也能正确解析。操作系统的机制 (系统调用、文件系统……) 给了我们无限的创作空间。

---
## 22.2 文件的元数据
**文件：操作系统中的对象**
**对象就有属性**
- ls -l 就可以查看对象的属性
```bash
$ ls -l example.txt
-rw-r--r-- 1     alice staff 1024 Mar 10 12:34 example.txt
mode       link  owner group size modified     name
```
**元数据**
- Type: d (directory), l (link), p (pipe), c (char), b (block)
- Mode: rwx (user, group, other)
    - 例子：0o755 = rwx (111) r-x (101) r-x (101)
- Links: 引用计数 (硬链接，包括目录)

```shell
ls -l

cd /tmp/hello/
mkfifo pipe
ll

ll /dev/

ls -al

ls -l /etc/passwd
-rw-r--r-- 1 root root 1522 Sep 18 12:54 /etc/passwd
```

**更多的元数据**
**Extended Attributes (xattr)**
```c
ssize_t fgetxattr(int fd, const char *name,
                  void value[.size], size_t size);
int fsetxattr(int fd, const char *name,
              const void value[.size], size_t size,
              int flags);
```
- 每个文件可以维护一个任意的 key-value dictionary
    - 例子：macOS 的 com.apple.metadata 会保存每个互联网下载文件的 url

```bash
man 2 fgetxattr 
```

**文件系统的向量索引：vectorfs**
- vfs search cat ~/Photos/ | ag --summary

**致命的缺陷**
- 这是后加的特性
    - 不是所有的文件系统都支持
- 兼容性奇差
    - cp 文件时，xattrs 就会丢失，需要 cp --preserve=xattr
    - 期待革命时刻

**Access Control List (访问控制列表)**
**比 user, group, other 更精细的访问控制**
- 格式
    - [d:]<u | g | m | o>:name:perms
- 用法
    - setfacl -m u:jyy:--- file
    - getfacl file
    - 通过 xattr system.posix_acl_access 实现
        - 我怎么知道的？
- (Access Control 专门用一次课讲)
> **class 26**

```bash
cd /tmp/
vi hello.txt
setfacl -m u:mail:rwx hello.txt
vi /etc/passwd

chmod 700 hello.txt
ll
sudo -u mail bash
cat hello.txt
cat: hello.txt: Permission denied

exit

strace setfacl -m u:mail:rwx hello.txt
ls -l
sudo -u mail bash
cat hello.txt
vi hello.txt 写入失败？？？

cp hello.txt 1.txt
ls -l 
没有'+'
```
## 写入失败？？？
- [x] 在权限字符串末尾如果出现一个 ​​加号（+）​​，例如 -rwx------+，这表示该文件或目录设置了 ​​ACL（访问控制列表, Access Control List）​
- [x] 文件名后面的​​星号`*`​​，例如 hello.txt*，通常是一个​​ shell 的提示符​​，而不是文件本身元数据的一部分。它表示这个文件是一个​​可执行文件​*​（具有执行权限，x）

---
## 22.3 更重量级的操作 🌶️

**文件系统目录树**
**UNIX/Linux: 一切都在 /**
- “/” 到底是什么？

**Windows 的设计**
- 一个驱动器一棵树：A:, B:, C:, ...

```shell
mkdir mnt
lsblk 
sudo su
mount /dev/sdd mnt
ls
cd mnt/
ls
cd ..
umount mnt
```

**M8: 文件系统格式化恢复 (fsrecov)**
```shell
wget https://box.nju.edu.cn/f/0764665b70a34599813c/?dl=1

file index.html\?dl=1 
显示为 DOS/MBR boot sector 或 filesystem data​

mv "index.html?dl=1" fs.img

sudo mount fs.img mnt/
挂载镜像
sudo umount mnt/

sudo strace -f mount fs.img mnt/

lsblk | less

ls /dev/loop*
```

**创建一个 loopback (回环) 设备**

**OverlayFS (“UnionFS”, 联合挂载)**
**我们可以虚拟化磁盘，为什么不能虚拟化目录？**
- 你看到的每个目录，都可能是**假的**
- OverlayFS
    - lowerdir: 只读层 (修改会被丢弃)c
    - upperdir: 可写层 (修改会被保留)
    - workdir: 操作系统用的临时目录

**以及更多的 “文件系统级” API**
- 基于 Copy-on-Write 的文件系统级快照
    - LVM (lvcreate --snapshot) 或文件系统支持 (btrfs, zfs)
    - 实现系统备份与回滚、测试隔离、快速恢复

> **OverlayFS**: 一种联合文件系统，允许将多个目录 “层叠” 在一起，形成单一的虚拟目录。OverlayFS 是容器 (如 docker) 的重要底层机制。它也可以用于实现文件系统的快照、原子的系统更新等。

```shell
sudo ./demo.sh
./watch.py

运行有问题不显示内容
```

---
## 22.4 总结
　　***Take-away Messages***: 目录 (链接) 和文件 (对象) 的简洁抽象赋予了我们管理对象的能力。操作系统的设计者也扩展了文件的元数据，使我们能给文件打上复杂的标签，从而使应用程序 (和操作系统) 提供更好的服务；甚至还引入了操作目录树的 API，例如 OverlayFS。

---
好的，我们来详细对比一下这两个命令，它们看起来相似，但行为和结果却截然不同。

### 总结对比

| 特性 | `echo /etc/**/*.conf` | `cat /etc/**/*.conf` |
| :--- | :--- | :--- |
| **命令** | `echo` | `cat` |
| **功能** | 将参数打印到终端（标准输出） | 连接文件并将其内容打印到终端 |
| **对通配符的处理** | 展开为匹配的文件路径列表 | 展开为匹配的文件路径列表 |
| **最终结果** | **显示文件名** | **显示文件内容** |
| **如果无匹配项** | 原样输出字符串 `/etc/**/*.conf` | 报错：`cat: /etc/**/*.conf: No such file or directory` |
| **主要用途** | **查看哪些文件会被匹配** | **查看被匹配文件的具体内容** |

---

### 详细解释

#### 1. Shell 的通配符扩展

首先，两个命令都使用了 `**` 通配符。这是一个强大的功能，在大多数现代 Shell（如 `bash`、`zsh`）中，如果开启了 `globstar` 选项（在 `bash` 中默认未开启，需要 `shopt -s globstar`），`**` 会匹配**零个或多个目录和子目录**。

所以，`/etc/**/*.conf` 这个模式会递归地匹配 `/etc` 目录及其所有子目录下任何以 `.conf` 结尾的文件。

**关键点是：Shell 会在命令执行之前，先把这个模式扩展成一个由所有匹配文件路径组成的列表。**

#### 2. 命令一：`echo /etc/**/*.conf`

*   **发生了什么**：
    1.  Shell 首先查找所有匹配 `/etc/**/*.conf` 的文件。
    2.  假设找到了 `/etc/dnsmasq.conf`、`/etc/rsyslog.conf`、`/etc/apache2/apache2.conf` 等文件。
    3.  Shell 将扩展后的文件列表作为参数传递给 `echo` 命令。
    4.  `echo` 命令简单地接收这些参数（即文件名），并把它们全部打印到屏幕上，每个文件名之间用空格隔开。

*   **输出示例**：
    ```bash
    /etc/adduser.conf /etc/apache2/apache2.conf /etc/apache2/mods-available/alias.conf ...（很长的一串列表）
    ```
*   **用途**：你只是想**看看这个模式到底能匹配到哪些文件**，而不是看文件里的内容。这是一个非常有用的调试技巧。

#### 3. 命令二：`cat /etc/**/*.conf`

*   **发生了什么**：
    1.  和上面一样，Shell 首先查找所有匹配 `/etc/**/*.conf` 的文件，并扩展成一个文件路径列表。
    2.  Shell 将这个文件列表作为参数传递给 `cat` 命令。
    3.  `cat` 命令的职责是**读取文件的内容**。于是它按照列表顺序，依次打开每一个文件，将其所有内容读取出来，并连续地打印到终端上。

*   **输出示例**：
    ```bash
    # 这是 /etc/dnsmasq.conf 的内容
    port=53
    listen-address=127.0.0.1
    ...
    # 这是 /etc/rsyslog.conf 的内容
    module(load="imuxsock")
    ...
    # 这是 /etc/apache2/apache2.conf 的内容
    DefaultRuntimeDir ${APACHE_RUN_DIR}
    ...
    ```
*   **用途**：你想要**一次性查看所有这些配置文件的实际内容**。**警告**：如果匹配的文件非常多（`/etc` 下确实有很多 `.conf` 文件），这个命令会瞬间向你的终端刷出成千上万行文本，导致终端卡顿甚至崩溃。通常更好的做法是将其输出重定向到文件（`cat /etc/**/*.conf > all_conf.txt`）或用分页工具查看（`cat /etc/**/*.conf | less`）。

---

### 一个重要注意事项：`globstar` 选项

在 `bash` 中，`**` 通配符默认是**不启用**的。如果你在 `bash` 中运行上述命令，可能会看到这样的结果：
```bash
# 在未开启 globstar 的 bash 中
$ echo /etc/**/*.conf
/etc/**/*.conf  # 没有被扩展，原样输出
```
你需要先启用它：
```bash
shopt -s globstar
```
然后命令就能正常工作了。

而在 `zsh` 等 Shell 中，`**` 通常是默认启用的。

### 结论

*   使用 **`echo`** 来**预览和检查**你的通配符模式是否正确匹配到了你想要的文件。
*   使用 **`cat`**（或类似工具如 `less`, `bat`）来**实际查看或处理**这些匹配文件的**内容**。

记住，是 Shell 负责扩展 `*` 和 `**`，而扩展后的结果传递给不同的命令（`echo` 或 `cat`），才导致了最终行为的巨大差异。

---
## hhu@DESKTOP-UUJIN0R /t/hello [127]> ls -i
168904 a.txt  168904 b.txt

你看到的 `127` 是 Shell（这里是 Fish Shell）中上一条命令的**退出状态码（Exit Status Code）**，它明确表示 **"命令未找到"（command not found）**。

Linux 或类 Unix 系统中，命令执行后都会返回一个整数值作为状态码，范围通常是 0 到 255。其中 **0 表示成功**，**任何非零值都表示某种错误或异常情况**。

为了让你更清晰地了解 127 及其他常见状态码的含义，请看下表：

| 退出状态码 | 常见含义                               | 简单说明                                                                 |
| :--------- | :------------------------------------- | :----------------------------------------------------------------------- |
| **0**      | 成功 (Success)                         | 命令执行成功。                                      |
| **1**      | 一般性错误 (General error)             |  catch-all 错误，表示未知错误或一般性失败。                |
| **2**      | 误用 Shell 命令 (Misuse of shell commands) | 比如 shell 命令语法错误或无效参数。                      |
| **126**    | 命令不可执行 (Command cannot execute)   | 通常是因为权限不足，没有可执行权限。                      |
| **127**    | **命令未找到 (Command not found)**      | **你遇到的问题，系统找不到你输入的命令**。                   |
| 128+N      | 命令被信号终止 (Fatal error signal "N")  | 命令被系统信号中断，如 `130` (128+2) 通常由 Ctrl+C 触发。 |
| 255        | 退出状态越界 (Exit status out of range) | 退出码超出了 0-255 的范围。                              |

### 🔍 导致 "127" 的常见原因及解决

出现 127 错误，主要是系统找不到你输入的命令，可能的原因和解决思路如下：

| 可能原因                 | 解决思路                                                                                               | 常用命令示例                                                                 |
| :----------------------- | :--------------------------------------------------------------------------------------------------- | :--------------------------------------------------------------------------- |
| **命令拼写错误**           | 仔细检查命令名是否输入正确                                                                                   |                                                                              |
| **命令确实没有安装**       | 确认并安装对应的软件包                                                                                       | `apt install <包名>` 或 `dnf install <包名>` (请根据你的发行版使用合适的包管理器)                |
| **命令不在 PATH 环境变量中** | 检查命令是否位于非标准路径，或通过源码安装但未配置 PATH                                                               | `echo $PATH` 查看当前路径；<br> `which <命令名>` 或 `whereis <命令名>` 查找命令位置；<br> 临时添加路径：`export PATH=$PATH:/新路径` |
| **脚本文件缺乏执行权限**    | 为脚本文件添加可执行权限                                                                                       | `chmod +x /path/to/script.sh`                                                    |

### 💡 如何检查退出状态码

在大多数 Shell（如 Bash、Zsh）中，可以使用 `echo $?` 来查看**上一条命令**的退出状态码。
```bash
# 示例：执行一个不存在的命令
some_nonexistent_command
echo $? # 这会输出 127
```

希望这些信息能帮你解决问题。如果经过以上排查仍无法解决，可以考虑提供更具体的命令和错误信息，以便进一步分析。

---
## mount fs.img mnt/

好的，您提到了核心概念：**块设备 (Block Devices)**。这确实是理解上一操作（`mount fs.img mnt/`）为何能成功的关键。

这是一个非常重要的 Linux/Unix 概念。让我们来详细解释一下。

### 什么是块设备？

**块设备**是一种计算机数据存储设备，其特点是数据以固定大小的“块”为单位进行读写。

*   **类比**：想象一栋大楼，数据存储在每个房间里。要存取数据，你必须指定“去几楼的几号房间”（即块的地址），而不是说“从大门进去走37步”（像串行设备那样）。这种“按地址随机访问”的方式就是块设备的特性。
*   **与之相对的是“字符设备”**：数据以字符流（一个接一个的字节）的形式处理，例如键盘、鼠标、打印机。

### 块设备的常见例子

*   **硬盘驱动器 (HDD)**：最典型的块设备（如 `/dev/sda`, `/dev/sdb`）。
*   **固态硬盘 (SSD)**：同上。
*   **USB 闪存驱动器/U盘**：当它被系统识别后，也会表现为一个块设备（如 `/dev/sdc1`）。
*   **硬件 RAID 阵列**：由多个物理磁盘组成的虚拟块设备。
*   **光盘驱动器 (CD/DVD/BD)**：虽然介质是光学的，但对系统来说也表现为块设备。
*   **环回设备 (Loop Devices)**：**这就是您刚才命令的核心！**

---

### 关键：环回设备 (Loop Devices) - `/dev/loop*`

您执行的 `sudo mount fs.img mnt/` 命令之所以能工作，秘诀就在于 **环回设备**。

*   **是什么？** 环回设备是一种伪设备（软件模拟的设备），它**可以将一个普通文件（如 `fs.img`）映射成一个块设备**。
*   **如何工作？**
    1.  当您使用 `mount` 去挂载一个文件（而不是一个像 `/dev/sda1` 这样的硬件设备）时，Linux 内核会自动帮你找到一个空闲的环回设备（例如 `/dev/loop0`）。
    2.  内核将这个环回设备**关联 (attach)** 到您的 `fs.img` 文件上。此刻，`/dev/loop0` 就表现得像一块独立的“硬盘”，而其数据源就是 `fs.img` 文件。
    3.  然后，`mount` 命令再将这个新创建的“虚拟硬盘”（即 `/dev/loop0`）挂载到您指定的目录（`mnt/`）上。

*   **查看当前使用的环回设备：**
    您可以使用 `losetup` 命令来查看哪些环回设备正在被使用，以及它们关联到了哪些文件。
    ```bash
    sudo losetup -a
    ```
    在您挂载 `fs.img` 后，这个命令可能会输出类似这样的内容：
    ```
    /dev/loop0: []: (/t/hello/fs.img)
    ```
    这证实了 `/dev/loop0` 设备正在代表您的 `fs.img` 文件。

*   **手动管理环回设备（高级用法）：**
    虽然 `mount` 能自动处理，但你也可以手动操作，这有助于理解其原理。
    ```bash
    # 1. 将一个文件关联到一个环回设备
    sudo losetup --find --show fs.img  # 会自动找一个空闲loop设备并输出其名，如 /dev/loop1
    # 2. 现在，你可以像对待普通硬盘一样，挂载这个环回设备
    sudo mount /dev/loop1 mnt/
    # 3. 使用完毕后，先卸载文件系统，再断开环回设备
    sudo umount mnt/
    sudo losetup -d /dev/loop1  # 断开关联
    ```

### 总结表：块设备 vs. 普通文件

| 特性 | 块设备 (e.g., `/dev/sda1`, `/dev/loop0`) | 普通文件 (e.g., `fs.img`, `document.txt`) |
| :--- | :--- | :--- |
| **接口** | 块设备接口，支持随机访问固定大小的块 | 文件流接口，按字节序列读写 |
| **用途** | 存储文件系统，作为系统的“磁盘” | 存储任意数据，由应用程序解析 |
| **访问方式** | 可以被**挂载**到一个目录，成为文件树的一部分 | 不能被挂载，只能用 `read`, `write`, `open` 等系统调用访问 |
| **创建工具** | `fdisk`, `parted` (分区), `losetup` (关联文件) | `touch`, `dd`, 文本编辑器, 编译器 |
| **例子** | 硬盘分区、U盘、**环回设备** | 文本文档、图片、可执行程序、**磁盘镜像文件** |

**结论：**
您成功使用 `mount` 命令，是因为 Linux 内核通过**环回设备**这一机制，巧妙地将一个**普通文件** (`fs.img`) 伪装成了一个**块设备**，从而允许文件系统被识别和挂载。这是虚拟机、容器和系统维护中非常基础和强大的一个功能。


---

好的，我们来详细讲解一下 OverlayFS（通常也被泛称为“联合文件系统”或“联合挂载”）。

这是一个非常重要且广泛应用的技术，尤其在容器化（Docker）、嵌入式系统和 Live CD/USB 等领域。

---

### 1. 什么是 OverlayFS？

OverlayFS 是一种**联合挂载文件系统**。它的核心思想是将**多个不同的目录（称为“层”，Layers）** 透明地合并成一个统一的视图。

简单来说，它允许你将一个目录（A）“覆盖”在另一个目录（B）之上。对用户而言，看到的是 A 和 B 合并后的内容。如果两个目录中有同名文件，上层的文件会“遮盖”下层的文件。

### 2. 核心概念与工作层次

OverlayFS 的挂载需要指定至少两个，通常是四个目录：

1.  **lowerdir**：**下层目录**。通常是只读的（read-only），提供基础文件层。可以有一个或多个 lowerdir（用 `:` 分隔），越靠前的层优先级越低。
2.  **upperdir**：**上层目录**。通常是可读写的（read-write）。所有新增、修改的文件都会存放在这一层。
3.  **workdir**：**工作目录**。OverlayFS 内部使用，用于准备文件拷贝等操作（例如，在修改一个来自 lowerdir 的文件之前）。必须是一个空目录，且与 upperdir 位于同一文件系统上。
4.  **merged**：**合并点**。这是最终呈现给用户的统一视图目录。用户在此目录下进行所有文件操作。

**关系图：**
```
                    +-----------------------------------+
                    |        用户看到的统一视图           |
                    |            (merged)              |
                    +-----------------+-----------------+
                                      |
                                      | (联合挂载)
                                      |
+-----------------+      +------------+------------+      +-----------------+
|    lowerdir     |      |         upperdir        |      |     workdir     |
|   (只读，基础层)  |      |   (读写，变更层)         |      | (内部工作目录)    |
|  /path/to/lower |      |    /path/to/upper       |      |  /path/to/work  |
+-----------------+      +-------------------------+      +-----------------+
```

---

### 3. 工作原理（“写时复制”，Copy-on-Write, CoW）

OverlayFS 的核心是“写时复制”机制：

*   **读文件**：
    *   如果文件存在于 `upperdir`，则从 `upperdir` 读取。
    *   如果文件只存在于 `lowerdir`，则从 `lowerdir` 读取。

*   **写文件**：
    *   **修改一个文件**：如果要修改一个来自 `lowerdir` 的文件，OverlayFS 会首先将该文件**完整复制到 `upperdir`**，然后在 `upperdir` 中的副本上进行修改。原始的 `lowerdir` 文件保持不变。
    *   **创建新文件**：新文件会直接创建在 `upperdir` 中。
    *   **删除文件或目录**：
        *   删除一个 `lowerdir` 中的文件：会在 `upperdir` 中创建一个**同名的“白障”（whiteout）文件**（字符设备文件，设备号为 `0/0`），该文件在合并视图中会“遮盖”掉下层的文件，使其看起来像被删除了。
        *   删除一个 `lowerdir` 中的目录：会在 `upperdir` 中创建一个**不透明的目录（opaque directory）**（该目录具有特定的 `xattr` 扩展属性），使其看起来像被删除了。

*   **重命名**：通常只在对源和目标都在 `upperdir` 中的文件进行操作时才被允许，这是为了防止破坏下层只读文件的一致性。

---

### 4. 实际应用示例

**场景**：假设我们有一个基础系统（`lower`）和一个用于存储修改的目录（`upper`），我们想将它们合并。

```bash
# 创建所需的目录结构
sudo mkdir /tmp/{lower,upper,work,merged}

# 在下层（基础层）创建一些文件
sudo echo "I am from lower.txt" > /tmp/lower/file1.txt
sudo echo "I am also from lower.txt" > /tmp/lower/file2.txt

# 挂载 OverlayFS
sudo mount -t overlay overlay \
  -o lowerdir=/tmp/lower,upperdir=/tmp/upper,workdir=/tmp/work \
  /tmp/merged

# 现在查看合并后的视图
ls -l /tmp/merged/
# 输出： file1.txt  file2.txt
# 它们都来自 lowerdir

cat /tmp/merged/file1.txt
# 输出： I am from lower.txt
```

**进行一些操作，体验 OverlayFS 的行为：**

1.  **修改下层文件**：
    ```bash
    # 尝试修改 file1.txt
    echo "This is a modification." >> /tmp/merged/file1.txt

    # 检查文件：原 lowerdir 的文件未变
    cat /tmp/lower/file1.txt
    # 输出： I am from lower.txt

    # 修改后的内容已保存在 upperdir
    cat /tmp/upper/file1.txt
    # 输出： I am from lower.txt\nThis is a modification.

    # 在 merged 层看到的是修改后的版本
    cat /tmp/merged/file1.txt
    # 输出： I am from lower.txt\nThis is a modification.
    ```

2.  **创建新文件**：
    ```bash
    # 创建一个新文件
    touch /tmp/merged/new_file.txt

    # 它出现在 upperdir，而不在 lowerdir
    ls /tmp/upper/
    # 输出： new_file.txt (可能还有 file1.txt)
    ls /tmp/lower/
    # 输出： file1.txt file2.txt (没有 new_file.txt)
    ```

3.  **删除下层文件**：
    ```bash
    # 删除 file2.txt
    rm /tmp/merged/file2.txt

    # 检查 upperdir，会看到一个特殊的“白障”文件
    ls -l /tmp/upper/
    # 可能会看到： c--------- ... file2.txt  # 这是一个字符设备文件，标志文件被删除

    # file2.txt 从 merged 视图中消失了
    ls /tmp/merged/
    # 输出： file1.txt new_file.txt
    ```

4.  **卸载**：
    ```bash
    sudo umount /tmp/merged
    ```

---

### 5. 主要应用场景

1.  **Docker 容器**：这是 OverlayFS 最著名的应用。Docker 镜像的每一层都作为一个 `lowerdir`。当你启动一个容器时，Docker 会在镜像层之上添加一个薄薄的可读写层（`upperdir`）。所有容器内的修改都发生在这个读写层，而不会影响底层的基础镜像。这实现了**高效的镜像分层和容器隔离**。

2.  **Live CD/USB 系统**：如 Ubuntu Live CD。只读的 CD/USB 内容作为 `lowerdir`，系统运行时将内存的一部分（通常是 tmpfs）作为 `upperdir`，这样用户可以在 Live 环境中安装软件或创建文件，但重启后所有更改都会丢失，因为 `upperdir` 在内存中。

3.  **嵌入式系统**：提供一个只读的根文件系统（`lowerdir`），同时允许用户进行有限的、可重置的定制（`upperdir` 放在可读写分区）。

4.  **软件测试与快照**：可以快速创建一个干净的测试环境，所有测试产生的“污染”都存放在 `upperdir` 中，测试完成后只需删除 `upperdir` 即可恢复纯净状态。

---

### 6. OverlayFS vs. UnionFS

*   **UnionFS**：这是一个更早的、广义的“联合文件系统”概念的总称，曾有多种实现（如早期的 unionfs、aufs 等）。
*   **OverlayFS**：是后来被合并到 Linux 内核主线的一种**具体的、高效的联合文件系统实现**。

由于 OverlayFS 自 Linux 内核 3.18 版本起就成为内核的一部分，其稳定性和性能都很好，因此它已经基本取代了其他旧的联合文件系统实现（如 aufs），成为当前的事实标准。所以现在人们提到“联合挂载”，通常指的就是 OverlayFS。

### 总结

| 特性 | 描述 |
| :--- | :--- |
| **本质** | 联合挂载文件系统 |
| **核心机制** | 写时复制（Copy-on-Write） |
| **关键目录** | `lowerdir`（只读基础层），`upperdir`（读写变更层），`workdir`（内部工作），`merged`（合并视图） |
| **最大优点** | 节省磁盘空间和内存，提高性能（无需复制整个底层） |
| **典型应用** | **Docker 容器**、Live 系统、嵌入式系统 |

希望这个详细的解释能帮助你彻底理解 OverlayFS！