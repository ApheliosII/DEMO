# Linux 常用命令学习指南
>本文档旨在通过分类和示例，便于学习和查阅 Linux 常用命令。

## 如何使用本文档
1. 使用任意 Markdown 阅读器查看本文档
2. 索特定命令：使用阅读器的搜索功能（通常是 Ctrl+F）
3. 将本文档作为速查手册使用

>*以下是为Linux初学者设计的系统学习路径和专业建议，结合高效学习方法和关键技能点：*
>**核心哲学：理解Linux的设计思想**
在死记硬背命令之前，先理解它的设计哲学，你会豁然开朗：
>1. **一切皆文件:** 硬件设备、进程、目录甚至网络连接，在Linux中都被抽象为“文件”来处理。这就是为什么你能用 `cat /proc/cpuinfo` 查看CPU信息。
>2. **小型、单一目的的程序：** 每个命令只做好一件事，并通过管道 (`|`) 将它们组合起来完成复杂任务。例如：`grep` 只负责过滤，`sort` 只负责排序。
>3. **避免使用交互式命令行参数：** 命令通常通过参数(`-a, --all`)和标准输入/输出来工作，便于脚本化和自动化。
>4. **纯文本文件存储配置：** 几乎所有配置都保存在文本文件中（如`/etc`目录下），便于查看、版本控制和用文本工具处理。

### 第一阶段：文件与目录操作 (生存基础)
``` bash
# 查看当前所在目录
pwd

# 改变目录
cd                     # 切换到当前用户的家目录（HOME）
cd /path/to/directory  # 切换到绝对路径
cd ..                  # 切换到上一级目录
cd ~                   # 切换到用户家目录
cd -                   # 切换回上一个所在的目录

cd /                   # 切换到系统根目录
# 切换到你的用户家目录 (Home Directory)，这是你登录后的默认位置
cd /home/hhu  # 或者，更通用的写法是 
cd ~
cd /mnt/e/2025/learn/VS\ Code/Makefile使用  # 切换到 Windows E 盘下的指定目录（这是 WSL 的特殊之处）
#注意：路径中包含空格，必须用反斜杠 \ 转义（如 VS\ Code）或者用引号将整个路径包起来。
# 使用引号处理空格
cd "/mnt/e/2025/learn/VS Code/Makefile使用"

# 假设你当前在 /mnt/e/2025 目录下：
cd learn               # 切换到当前目录下的 learn 子目录
cd ..                  # 切换到当前目录的父目录（即 /mnt/e）
cd ../..               # 切换到上级目录的上级目录（即 /mnt）
cd learn/VS\ Code/Makefile使用      # 切换到当前目录下某个深层次的目录

cd -                   # 切换回上一个所在的目录 在两个最近停留的目录之间快速切换，极其有用！
```
#### 专业人士的方法和建议（让你更高效）
##### 1. 使用 Tab 键自动补全
- 自动补全目录和文件名：输入开头几个字母，按 Tab，系统会自动补全。如果有多项匹配，按两次 Tab 会列出所有可能性。
- 避免拼写错误：尤其是处理长文件名和带空格的目录时。

**示例**：
你想进入 /mnt/e/2025/learn/VS Code/Makefile使用，只需输入：
``` bash
cd /mnt/e/2025/l<Tab> VS<Tab> M<Tab>
```
系统会自动补全为：
``` bash
cd /mnt/e/2025/learn/VS\ Code/Makefile使用
```
>（注意它自动帮你加上了转义符 \）

##### 2. 结合 ls 命令使用
在切换到一个不熟悉的目录之前或之后，用 `ls` 命令查看当前目录的内容，确保你去对了地方。
``` bash
# 先查看当前目录下有什么
ls
learn  projects  documents

# 再切换到 learn 目录
cd learn

# 切换后，再次查看 learn 目录里有什么，确认是否为目标目录
ls
VS Code/  other_folder/
```
##### 3. 使用 pushd 和 popd 进行目录栈管理（高级但强大）
这是一个比 `cd -` 更强大的工具，用于在多个目录之间跳转。
- `pushd <目录>`：将当前目录保存到一个“栈”（堆栈）中，然后切换到目标目录。
- `popd`：将栈顶的目录弹出，并切换回那个目录。

**示例**：
``` bash
# 从家目录开始
~$ pushd /mnt/e/2025/learn
/mnt/e/2025/learn ~  # 栈现在包含 [当前目录, 上一个目录]

/mnt/e/2025/learn$ pushd /tmp
/tmp /mnt/e/2025/learn ~  # 栈现在包含 [当前目录, 上一个, 上上个]

/tmp$ popd  # 弹出 /tmp，跳回到 /mnt/e/2025/learn
/mnt/e/2025/learn$

/mnt/e/2025/learn$ popd  # 再次弹出，跳回到家目录 ~
~$
```
>这对于在项目目录、日志目录、临时目录之间穿梭非常方便。

``` bash
# 列出目录内容
ls                     # 简单列出
ls -l                  # 长格式列表（显示详细信息）
ls -la                 # 长格式列表，并显示所有文件（包括隐藏文件.）
ls -lh                 # 长格式列表，以人类易读方式显示文件大小

ll                     # 同 ls -l
ll -a  # 本质是 'ls -la'  # 显示所有文件，包括隐藏文件（以 . 开头的文件）
ll -h  # 本质是 'ls -lh'  # 以人类易读的形式显示文件大小（如用 K, M, G 显示）
ll -ah # 本质是 'ls -lah' # 组合使用：显示所有文件（包括隐藏文件）的详细信息，并以易读格式显示大小

# 创建与删除
mkdir my_dir           # 创建目录
rmdir my_dir           # 删除空目录
rm -r my_dir           # 递归删除目录及其内容（危险！）
touch file.txt         # 创建空文件或更新文件时间戳

# 复制与移动
cp file1.txt file2.txt # 复制文件
cp -r dir1/ dir2/      # 递归复制目录
mv file1.txt file2.txt # 重命名文件
mv file1.txt /new/path/ # 移动文件
mv [选项] <原文件名> <新文件名>
-i交互模式（覆盖前确认）
-n禁止覆盖已存在文件
-v显示操作详情

# 删除
rm file.txt            # 删除文件
rm -f file.txt         # 强制删除，不提示
rm -rf somedir/        # 强制递归删除目录（极其危险！慎用！）

# 查看文件内容
cat file.txt           # 一次性输出整个文件内容（适合小文件）
less file.txt          # 分页查看文件（可前后翻页，推荐）
head -n 10 file.txt    # 查看文件头10行
tail -n 10 file.txt    # 查看文件尾10行
tail -f /var/log/syslog # 实时追踪日志文件末尾的更新
```

```bash
ww
ls -i # 显示inode号，可以用来判断两个文件是否是同一个文件
```

### 第二阶段：查看、编辑与权限管理
``` bash
# 文件编辑器 (Vim 基础)
# vim file.txt          # 用vim打开文件
# 按 `i` 进入插入模式 (Insert mode) 进行编辑
# 按 `ESC` 退出插入模式
# 输入 `:wq` 保存并退出 (write & quit)
# 输入 `:q!` 不保存强制退出

# 权限管理
# 查看权限：ls -l 输出的第一列，如 -rwxr--r--
chmod +x script.sh     # 为script.sh文件添加可执行权限
chmod 755 script.sh    # 用数字模式设置权限 (rwxr-xr-x)
chown user:group file.txt # 改变文件的所有者和所属组
```
### 第三阶段：系统管理与进程管理
``` bash
# 系统状态监控
ps aux                 # 查看当前所有进程的详细信息
top                    # 动态、交互式查看系统进程和资源占用（类似任务管理器）
htop                   # top的增强版（需安装，更直观）
free -h                # 显示内存使用情况 (-h 人类可读格式)
df -h                  # 显示磁盘空间使用情况 (-h 人类可读格式)
uname -a               # 显示系统内核信息

# 进程控制
kill 1234              # 终止进程ID为1234的进程
kill -9 1234           # 强制终止进程
pkill process_name     # 根据进程名终止进程
Ctrl + C               # 终止当前前台进程
Ctrl + Z               # 挂起当前前台进程
bg                     # 将最近挂起的进程在后台继续运行
fg                     # 将后台进程切换到前台运行
jobs                   # 查看当前shell中后台运行的任务列表
```
``` bash
# ww
^c              # 终止当前命令
^d              # 退出当前 shell

^z              # 挂起当前进程
^\              # 关闭当前窗口
jobs -l         # 列出后台任务详细信息
fg %job_id      # 切换到后台任务
```
### 第四阶段：文本处理与管道 (PowerShell的精髓)
``` bash
# 管道符 | ：将前一个命令的输出，作为后一个命令的输入

# 搜索文本
grep "pattern" file.txt               # 在file.txt中搜索包含"pattern"的行
grep -r "pattern" /path/to/dir/       # 递归地在目录中搜索
grep -i "pattern" file.txt            # 忽略大小写进行搜索

# 文本分析处理
awk '{print $1}' file.txt             # 打印file.txt每一行的第一个字段（默认以空格分隔）
awk -F "," '{print $2}' data.csv      # 指定逗号为分隔符，打印第二个字段

sed 's/foo/bar/g' file.txt            # 将文件中所有的"foo"替换为"bar"
sed -i 's/foo/bar/g' file.txt         # 直接修改文件内容（原地替换）

sort file.txt                         # 对文件的行进行排序
uniq file.txt                         # 报告或忽略重复的行（常先sort）
sort file.txt | uniq                  # 先排序再去重，是标准用法

wc -l file.txt                        # 统计文件的行数

# 组合示例：
# 统计包含"ERROR"的日志行数
grep -c "ERROR" /var/log/syslog
# 或
grep "ERROR" /var/log/syslog | wc -l

# 查看占用CPU最高的前10个进程
ps aux --sort=-%cpu | head -n 10
```
### 第五阶段：网络操作
``` bash
# 远程连接
ssh username@host_ip                  # 通过SSH连接到远程服务器

# 文件传输
scp file.txt user@host:/remote/path/  # 将本地文件复制到远程服务器
scp user@host:/remote/file.txt .      # 将远程文件复制到本地当前目录
rsync -avz /local/dir/ user@host:/remote/dir/ # 更高效的同步工具

# 网络诊断
ping example.com                      # 检查与目标主机的网络连通性
curl http://example.com               # 获取URL的内容（常用于API测试）
wget http://example.com/file.tar.gz   # 下载文件

# 网络状态查看
ss -tuln                              # 查看所有监听的TCP和UDP端口
netstat -tuln                         # 旧版命令，功能类似ss
```
### 第六阶段：压缩与解压
``` bash
# 打包与压缩
tar -czvf archive_name.tar.gz /path/to/dir   # 创建gzip压缩包 (.tar.gz 或 .tgz)
tar -cjvf archive_name.tar.bz2 /path/to/dir  # 创建bzip2压缩包 (.tar.bz2)

# 解压
tar -xzvf archive_name.tar.gz          # 解压gzip压缩包到当前目录
tar -xjvf archive_name.tar.bz2         # 解压bzip2压缩包到当前目录

# Zip格式
zip -r archive_name.zip /path/to/dir   # 创建zip压缩包
unzip archive_name.zip                 # 解压zip压缩包
```
## 实用技巧与快捷键
``` bash
# 命令历史
history                # 查看命令历史记录
Ctrl + R              # 反向搜索历史命令（输入关键词）
!!                    # 重新执行上一条命令 (常用 sudo !!)
!$                    # 代表上一条命令的最后一个参数

# 补全与中断
Tab                   # 命令/文件名补全（按一次补全，按两次显示选项）
Ctrl + C              # 中断当前正在运行的命令
Ctrl + D              # 结束终端输入（EOF）或退出当前Shell会话

# 重定向
command > file.txt    # 将标准输出重定向到文件（覆盖）
command >> file.txt   # 将标准输出重定向到文件（追加）
command 2> error.log  # 将标准错误重定向到文件（覆盖）
command &> output.log # 将标准输出和标准错误都重定向到文件（覆盖）
```
## 学习建议
1. 抛弃图形界面（GUI），拥抱终端（Terminal）：强迫自己所有操作都在终端中完成
2. 使用命令自带的帮助系统：`man <command>`是最权威、最全面的命令手册
3. 使用Tab键补全：提高效率并防止拼写错误
4. 熟练使用历史记录：`history, Ctrl + R, !!, !$` 等技巧
5. 在安全环境中练习：使用虚拟机或云服务器搭建实验环境
6. 学习Shell脚本编程：将命令组合成脚本来自动化重复性任务

## 思维转变
1. **命令行思维：** 思考如何用命令组合（管道）解决问题
2. **自动化思维：** 任何需要重复操作两次以上的任务，考虑写脚本自动化
3. **日志思维：** 出问题第一时间看日志（通常在 `/var/log/` 目录下）
4. **配置思维：** 学会阅读和修改 `/etc` 下的配置文件

>*注意：本文档只是一个命令参考，并非可执行脚本。请在实际环境中练习这些命令。*

---

## linux命令---touch、vim、cat、echo
你提到的这四个命令（`touch`、`vim`、`cat`、`echo`）是 Linux 中处理文件时非常常用的命令，它们的功能和用途各有不同。下面我用一个表格来对比它们的特点，然后详细解释：

| 命令                 | 核心功能                                     | 是否改变文件内容 | 是否改变文件时间戳 | 主要用途                                     | 特点                                     |
| :------------------- | :------------------------------------------- | :--------------- | :----------------- | :------------------------------------------- | :--------------------------------------- |
| `touch /tmp/test.txt` | 创建空文件或更新文件时间戳 | 否（若文件存在） | 是                 | 创建空文件；更新文件访问和修改时间。           | 简单快速；文件不存在则创建，存在则更新时间戳。 |
| `vim /tmp/test.txt`  | 交互式文本编辑器             | 是               | 是（保存时）       | 创建、编辑文件内容。                           | 功能强大；学习曲线稍陡峭；支持多种编辑模式。   |
| `cat /tmp/test.txt`  | 连接文件并输出内容到标准输出     | 否               | 否                 | 查看**较小**文件内容；文件合并；创建文件。     | 直接输出全部内容；适合查看内容不多的文件。   |
| `echo /tmp/test.txt` | 输出字符串                     | 否               | 否                 | 输出文本或变量内容；**常与重定向配合**写入文件。 | 简单直接；脚本中常用；输出重定向可创建文件。 |

下面是这些命令的详细说明：

### 📝 命令详解

1.  **`touch /tmp/test.txt`**
    *   **作用**：如果 `/tmp/test.txt` 文件不存在，**创建一个新的空文件**；如果文件已存在，则**更新该文件的访问时间和修改时间**为当前系统时间，但**不会改变文件内容**。
    *   **适用场景**：快速创建空文件（例如占位文件、日志文件初始化）、强制更新文件时间戳（例如在脚本中触发某些基于时间的操作）。

2.  **`vim /tmp/test.txt`**
    *   **作用**：启动 `vim` 文本编辑器来**创建或编辑** `/tmp/test.txt` 文件。`vim` 功能强大，支持插入、删除、复制、粘贴、查找替换等多种文本操作。
    *   **特点**：
        *   如果文件不存在，`vim` 会在你第一次保存时创建它。
        *   操作是**交互式**的，你需要进入插入模式（按 `i`）才能输入内容，编辑完成后需要保存（命令模式下输入 `:wq`）并退出。
        *   `vim` 的学习曲线相对陡峭，但熟练掌握后编辑效率很高。

3.  **`cat /tmp/test.txt`**
    *   **作用**：在终端中**显示** `/tmp/test.txt` 文件的**全部内容**。
    *   **特点**：
        *   仅用于**查看**文件内容，**不会修改**文件本身。
        *   适合查看内容较少的文本文件。如果文件很大，内容会快速滚动显示，你可能更想用 `less` 或 `more` 命令来分页查看。
        *   `cat` 命令还可用于**文件合并**（`cat file1 file2 > combined_file`）或**创建包含内容的文件**（结合重定向和输入结束符，如 `cat > file.txt << EOF`）。

4.  **`echo /tmp/test.txt`**
    *   **作用**：将字符串 `/tmp/test.txt` **输出到终端（标准输出）**。
    *   **特点**：
        *   它只是简单地打印参数字符串，**不会直接读取或操作文件**。
        *   常与**输出重定向**（`>` 或 `>>`）结合使用来**创建文件或向文件追加内容**：
            *   `echo "Hello" > /tmp/test.txt`：创建文件并写入 "Hello"（如果文件已存在则**覆盖**原有内容）。
            *   `echo "World" >> /tmp/test.txt`：向文件**追加**一行 "World"（保留原有内容）。

### 🔍 组合使用示例

这些命令经常组合使用：
1.  用 `touch` 快速创建一个空文件：`touch /tmp/test.txt`
2.  用 `echo` 向文件写入内容：`echo "Hello World" > /tmp/test.txt` (覆盖) 或 `echo "New line" >> /tmp/test.txt` (追加)
3.  用 `cat` 查看刚写入的内容：`cat /tmp/test.txt`
4.  用 `vim` 对文件进行更复杂的编辑：`vim /tmp/test.txt`

### 💡 使用建议

*   **权限问题**：如果对 `/tmp` 目录没有写权限，在这些命令前加 `sudo`。
*   **文件已存在**：使用 `echo >` 和 `vim` 保存时会**覆盖**原有文件内容，务必小心。`echo >>` 是追加。
*   **学习 `vim`**：`vim` 初学者可以先记住几个基本操作：按 `i` 进入插入模式开始编辑；按 `Esc` 退出插入模式；在非插入模式下输入 `:wq` 保存并退出，输入 `:q!` 不保存强制退出。
*   **查看大文件**：避免直接用 `cat` 查看大文件，改用 `less /tmp/test.txt` 或 `more /tmp/test.txt` 可以分页浏览。

---
