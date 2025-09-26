# 2025 南京大学操作系统原理

> 操作系统原理课程学习笔记
> 包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

[toc]

[PPT](https://jyywiki.cn/OS/2025/lect23.md)

---
## 23. 文件系统实现
文件系统为我们实现了树 (和图) 状的目录结构，并提供了丰富的 API 让我们实现增删改查——实际上，文件系统就是在存储系统 (block I/O) 之上实现的一个支持修改查询操作的数据结构，实现它也是理所应当的。

**块设备上的数据结构 Abstract DataType (ADT)**

**用块设备虚拟块设备**
**Logical Volume Manager (LVM)**

**今天的文件系统可以扩容了**
**AI 时代的正确解决方法**
- 知道什么可以做
    - 有一天，你在任何地方看到了 LVM
    - 多嘴问一句：LVM 可以做什么？

**世界上的东西已经多到 “不可能全部搞清楚” 了**
- 但不妨碍我们很好地使用它们
    - 我有一个 LVM vg1，如何将分区扩容到 100%？
    - AI 会提供有效的线索：vgdisplay, lvextend, resize2fs
- Anyway, 它就是一个块设备

---
## 23.1 File Allocation Table

**实现文件系统：敌人和朋友**
**敌人：读/写放大**
- 存储设备的特性：被迫只能读写连续的一块数据
- 不能像 memory hierarchy 那样随心所欲 new/delete

**朋友：局部性**
- 适当地排布数据，使得临近的数据有 “一同访问” 的倾向
- 数据暂时停留在内存，延迟写回

**5.25" 软盘：单面 160 KiB**
- `struct block *` 的链表
    - 任何复杂的高级数据结构都显得浪费

- 目录就是一个普通的文件 (虚拟磁盘；“目录文件”)
- 操作系统会把文件内容解读成 `struct dentry[];`

**用链表存储数据：两种设计**
1. 在每个数据块后放置指针
2. 将指针集中存放在文件系统的某个区域-next数组

哪种方式的缺陷是致命、难以解决的？

12*320/8 

**文件系统设计者：先算账**
**160 KB 的软盘，512 字节扇区**
- 320 个扇区
- 12-bit entry, 480B
    - 竟然只要**只有一个扇区**就能存下 next[]
    - 容量翻倍，也就 2 个扇区
**File Allocation Table: 集中保存所有指针**
- 在**内存**里缓存一份 FAT (天生一次也要读完一个 512B)
- 延迟写回，读/写放大的问题就完全解决了
    - 但**可靠性**是个大问题

**集中存储的指针容易损坏？**
- 存 n 份就行！延迟写回，写放大就不那么严重了

**FAT: 链接存储的文件**
**File Allocation Table: int next[];**
- next[i] == 0: Free (本块未分配)
- next[i] == -1: EOF (本块是文件的最后一个块)

> **readfat**: 通过摘抄手册，可以得到 fat32.h 并明确每个字段的含义，mmap 把磁盘镜像映射到内存就可以实现解析了。现在这个工作，哪怕是全新的系统，也完全可以交给大语言模型完成。

```bash
file M5-frecov.img
./readfat M5-frecov.img | less
M5-frecov.img下载

mkdir mnt
sudo mount M5-frecov.img ./mnt/
open /mnt
sudo umount mnt

# fish shell
strace mkfs.fat M5-frecov.img &| vim -
vim M5-frecov.img
重新挂载
```

**目录树实现：目录文件**
**目录就是个普通文件**
- 但在 metadata 里标记一下 (mode = directory)
    - 操作系统把数据理解成 struct dirent[]
    - Quiz: 为什么不把元数据 (大小、文件名、……) 保存在文件的头部？
- DOS: “8 + 3” 文件名 “AUTOEXEC.BAT”
    - Linux: /etc/xdg/autostart/
    - Windows: shell:startup

**总有一天，8 + 3 文件名会不够用的**
- 那就只能打补丁了 😭

**我们甚至可以直接观察 FAT 文件系统**
**观察 “快速格式化” (mkfs.fat) 是如何工作的**
- 老朋友：strace

**然后，把整个磁盘镜像 mmap 进内存**
- 照抄手册，遍历目录树 (fat-tree demo)，试试镜像

**另一个有趣的问题：文件系统恢复**
- 快速格式化 = FAT 表丢失
    - 所有的文件内容 (包括目录文件) 都还在
    - 只是在数据结构眼里看起来都是 “free block”
- 猜出文件系统的参数 (SecPerClus, BytsPerSec, ...)，恢复 next 关系

**FAT: 性能与可靠性**
**性能**
- ＋ 小文件简直太合适了
- － 但大文件的随机访问就不行了
    - 4 GB 的文件跳到末尾 (4 KB cluster) 有 $2^{20}$ 次 next 操作
    - 缓存能部分解决这个问题
- 在 FAT 时代，磁盘连续访问性能更佳
    - 使用时间久的磁盘会产生碎片 (fragmentation)
        - malloc 也会产生碎片，不过对性能影响不太大

**可靠性**
- 维护若干个 FAT 的副本防止元数据损坏 (轻微写放大)

```bash
lsblk
```

---
## 23.2 UNIX 文件系统
**不要做无脑的优化**

**UNIX 系列文件系统的改进**
**支持 (硬) 链接**
- 树 → 图 (链接)
- 允许一个 “虚拟磁盘” 存在多份引用
    - struct node (数据), struct edge (目录中的文件) 要分开

**支持任意大小文件的随机访问**

**“iNode” (index node)**
- 保存 ls -l 里的各种 metadata
    - Mode, Links, User/Group, Size, Access/Modify/Change Time
    - (Minix1 和 Minix2 的 fs/inode.h 完全一样)
        - 是的，fstat 就直接把数据搬到进程里
- 以及一个用于索引的数据结构
    - map<int,int> (file offset → block id)

```bash
ls
touch a.txt
ln a.txt b.txt
ls -l
chmod 777 a.txt # wsl2 /mnt/修改不了;在/tmp/下试
```

> **Minix**: Minix 是 UNIX 之后的经典教学操作系统，Andrew Tanenbaum 也因此成就了一代计算机系统研究者。代码来自 Minix 1 and 2, Quick and Dirty editions。

```bash
git clone --depth 1 --single-branch -b master https://github.com/davidgiven/minix2

之前就运行fail

面试题：往哪打一枪会把文件系统给毁掉？
inode
# Superblock
```

**ext2: 不过是另一个数据结构**
**“Superblock”：文件系统级的元数据**
- inode 数量，block_per_block (以第一个 superblock 为准), ...

```bash
ls -i # 显示 inode 号
```
**ext2 inode: 联合数据结构 (Fast/Slow Path)**

**ext2 目录文件**
**在 “文件”上的数据结构**
- map<string,int> (name → inode)

**ext2: 性能与可靠性**
**局部性与缓存**
- bitmap, inode 都有 “集中存储” 的局部性
- 通过内存缓存减少读/写放大

**大文件 O(1) 随机读写**
- 支持链接 (一定程度减少空间浪费)
- inode 在磁盘上连续存储，便于缓存/预取
- 依然有碎片的问题

**但可靠性依然是个很大的问题**
- 存储 inode 的数据块损坏是很严重的

---
## 23.3 现代文件系统 🌶️
**文件系统就是数据结构**
**那玩得花活就多了**
- Persistent data structure, filters, learned index, ...

**首先，数据结构可以不用实现在内核**
**FUSE: Filesystem in Userspace**
- 😂 果然是违背祖宗的决定
- FUSE Kernel Module: 负责实现协议 (/dev/fuse)
- libfuse: 用来实现文件系统
    - 没错，是协议，其他人也能实现，例如 macFUSE
```c
struct fuse_operations null_oper = {
    .getattr    = null_getattr,
    .truncate   = null_truncate,
    .open       = null_open,
    .read       = null_read,
    .write      = null_write,
};
```

**其次，任何数据结构都是可以的**
**B-Tree Filesystem (btrfs)**
- 反正只要 “实现文件系统 API”，干脆 “Everything is a B-Tree”，resize、透明压缩、快照……一次性搞定

**各种领域优化的数据结构**
**Flash-Friendly Filesystem (f2fs)**
android 

**Enhanced Read-only Filesystem (erofs)**
haiwei

---
## 23.4 总结
　　***Take-away Messages***: 把文件系统理解成一个 “数据结构”，就不难理解经典和现代文件系统的设计理念——所有人都是在为了合适的硬件、合适的读写 workload 上，用合适的方式组织数据，维护树状 (和链接) 的目录结构和随机访问的文件操作。