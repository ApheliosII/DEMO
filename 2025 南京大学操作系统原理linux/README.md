# 2025 南京大学操作系统原理

*本文档为南京大学操作系统原理课程的软件环境配置说明。*

- [视频b站](https://www.bilibili.com/video/BV1XZAbeqEyt/)
- [课程资料](https://jyywiki.cn)

## 环境配置

- **编辑器**：VS Code
- **操作系统wsl2**：Ubuntu 22.04

### WSL2 and Ubuntu 22.04 安装

```bash
# 配置代理
`7897` 端口修改
$env:https_proxy="http://127.0.0.1:7897"
$env:http_proxy="http://127.0.0.1:7897"
Remove-Item Env:\https_proxy
Remove-Item Env:\http_proxy

set http_proxy=http://127.0.0.1:10808
set https_proxy=http://127.0.0.1:10808
set all_proxy=socks5://127.0.0.1:10808

set HTTP_PROXY=http://127.0.0.1:10808
set HTTPS_PROXY=http://127.0.0.1:10808
set ALL_PROXY=socks5://127.0.0.1:10808


wsl --instail --no-distribution
wsl --list --online
wsl --list --verbose
wsl --install -d Ubuntu-24.04
wsl --install -d Ubuntu-22.04
wsl --install -d Ubuntu-20.04

# 重置 WSL 组件：
wsl --unregister Ubuntu-22.04       # 卸载当前损坏的分发
wsl --shutdown                      # 关闭 WSL 后台进程
wsl --install --no-distribution     # 重装 WSL 内核

# 重启后重新安装 Ubuntu
wsl --install -d Ubuntu-22.04
# 首次安装登录需要输入用户名和密码，之后会自动安装必要软件。

# 环境验证：
wsl -l -v                           # 查看 WSL 版本（应为 2）

# 打开WSL终端：在 PowerShell 输入 wsl 直接进入 
wsl                                 # 显示：yourname@DESKTOP-XXXXXX:~$
# 退出WSL终端：输入exit
exit

# 卸载wsl
wsl --shutdown
wsl --list --all
wsl --list --verbose
wsl --unregister <DistributionName>

wsl --uninstall
wsl --list
```

### 软件下载

```bash
sudo apt update                       # 更新软件源（连接Ubuntu官方仓库）
sudo apt install -y build-essential   # 安装编译工具链（GCC/G++/Make等）**
sudo apt install -y git               # 安装 Git

# 安装常用编辑器（选一个即可，Vim 或 Nano）
sudo apt install -y vim               # 推荐 Vim
或
sudo apt install -y nano              # 更简单的 Nano

sudo apt install -y gdb               # 安装调试器 GDB
sudo apt install -y openssh-server    # 安装 SSH 服务器（重要！用于后续 VS Code 连接） 
or 
sudo apt-get install openssh-server   #（可选）

gcc --version                         # 检查编译器，其他软件类似

sudo apt-get install -y fish          # 安装fish
chsh -s $(which fish)                 # 设置默认 shell 为 fish
```

### SSH设置

```bash
ssh localhost                       # 测试 SSH 服务

sudo systemctl enable ssh           # 启用SSH开机自启
sudo systemctl start ssh            # 立即启动服务 == sudo service ssh start
passwd                              # 设置登录密码（云服务器通常用密钥登录）

⚠️ 安全提示：
生产环境建议用密钥登录而非密码，此处为简化流程使用密码登录。
```

- 首次执行 ssh localhost 会提示保存密钥，输入 yes
- 之后会要求输入密码（输入你的 WSL 用户密码）

### VS Code Remote-SSSH 密钥连接 Linux 服务器指南

> 通过SSH密钥连接Linux服务器，既安全又方便，还能免去每次输入密码的麻烦。下面是一份详细的步骤指南，包括每一步的操作位置和作用。

#### 1. 准备工作

- **获取服务器信息**：
  - 服务器 IP 地址
  - 用户名
  - 密码（如果使用密码登录）

```bash
hostname # Host DESKTOP-UUJIN0R
hostname -I # 显示的IP  HostName 172.31.221.21
whoami # 输出的用户名  User hhu 
```

#### 2. 安装必要的VSCode扩展

Microsoft发布的 `Remote-SSH`扩展

#### 3. 生成SSH密钥对

**作用**：创建一对加密密钥（公钥和私钥）。公钥将放置于服务器，私钥保留在本地，用于身份验证，实现免密码登录。

1. 打开终端：本地计算机的终端（Windows系统可使用**PowerShell**、CMD或Git Bash；Linux/macOS系统使用系统终端）。
2. 执行以下命令生成密钥对（推荐使用更现代的Ed25519算法，或使用兼容性更好的RSA算法）：
   **Ed25519 (推荐)**：

   ```bash
   ssh-keygen -t ed25519 -C "你的注释（如邮箱或用途说明）"
   ```

   **RSA (兼容旧系统)**：

   ```bash
   ssh-keygen -t rsa -b 4096 -C "你的注释（如邮箱或用途说明）"
   ```

   参数解释：

   * `-t rsa`：指定密钥类型为RSA
   * `-b 4096`：指定密钥长度为4096位（更安全）
   * `-C`：添加注释（通常用邮箱标识）
3. 系统会提示你选择密钥保存位置。默认是 `C:\Users\你的用户名\.ssh\id_rsa`（Windows）或 `~/.ssh/id_rsa`（Linux/Mac）。**建议直接按回车使用默认位置**。
4. 接着会提示你**设置一个密钥密码**（passphrase），这可以为密钥再加一层保护。

> **为了真正实现“免密”登录，可以直接按两次回车跳过设置**（但出于安全考虑，设置一个密码会更安全）。）。

**密钥口令(passphrase)删除:**
方法：使用 ssh-keygen 命令移除口令
这个过程非常简单，你只需要一个命令。

1. 打开终端

   - 在 Windows 上，你可以使用 PowerShell 或 CMD。
   - 在 macOS 或 Linux（包括 WSL）上，直接打开系统终端。
2. 执行命令
   运行以下命令，将 路径/到/你的/私钥 替换为你的私钥文件的实际路径（例如 C:\Users\YourUserName\.ssh\id_rsa 或 ~/.ssh/id__rsa）。

   ```bash
   ssh-keygen -p -f "路径/到/你的/私钥"
   ```

   - `-p`：表示要求修改私钥的口令。
   - `-f`：用于指定要操作的私钥文件。
3. 按提示操作
   系统会首先提示你输入当前的口令（如果你当前有设置的话）。

   ```bash
   Enter old passphrase:
   ```

   然后，系统会提示你输入新口令。这里直接按两次回车键，输入空密码即可。

   ```bash
   Enter new passphrase (empty for no passphrase):
   Enter same passphrase again:
   ```
4. 完成
   如果看到 `Your identification has been saved with the new passphrase`. 这样的提示，就表示口令已成功移除。

> 更安全的替代方案：强烈推荐使用 ssh-agent + ssh-add 的方式。

生成成功后，你可以在指定保存位置（默认是本地用户目录下的 .ssh 文件夹，例如 `C:\Users\你的用户名\.ssh\`）找到两个文件：

- `id_rsa`：私钥（Private Key），**绝不能泄露**，像你的钥匙一样保管好。
- `id_rsa.pub`：公钥（Public Key），需要放到服务器上，像是你能给别人的门禁卡。

#### 4. 将公钥上传到Linux服务器

**操作位置**：从本地计算机操作，将公钥文件内容添加到远程服务器的指定文件中。
**作用**：让服务器知晓并信任你的公钥，允许持有对应私钥的客户端进行连接。

- [ ] **方法一：使用 `ssh-copy-id` 命令（最简单，推荐）**
  在本地终端中运行：

```bash
ssh-copy-id -i ~/.ssh/id_rsa.pub username@server_ip
```

- 请将 `username` 替换为你的服务器用户名
- `server_ip` 替换为服务器的IP地址或域名
- `id_rsa.pub` 替换为你实际生成的公钥文件名
- `-i ~/.ssh/id_rsa.pub` 指定公钥路径。如果公钥就在默认位置且名称是 `id_rsa.pub`，有时可以省略 `-i` 部分。
- 根据提示输入服务器的用户密码。输入后，公钥会自动追加到服务器对应用户的 `~/.ssh/authorized_keys` 文件中。

- [X] **方法二：手动复制（通用方法）（如果 `ssh-copy-id` 不可用）**

1. **在本地计算机**上查看公钥内容：
   ```bash
   cat ~/.ssh/id_rsa.pub
   ```

   复制终端显示的全部内容。
2. **登录到远程服务器**（使用密码SSH登录或通过其他方式）。
3. 在服务器上，确保存在 `~/.ssh` 目录并设置正确权限，然后将复制的公钥内容追加到 `authorized_keys` 文件中：
   ```bash
   mkdir -p ~/.ssh # 创建 ~/.ssh 目录（如果不存在）
   echo "你复制的公钥内容" >> ~/.ssh/authorized_keys # 将公钥内容追加到 authorized_keys 文件中

   # 下面不一定要设置
   chmod 700 ~/.ssh          # 设置.ssh目录权限为仅用户可读、写、执行
   chmod 600 ~/.ssh/authorized_keys # 设置authorized_keys文件权限为仅用户可读、写
   ```

**重要提示**：千万不能使用 `>`覆盖已有的 `authorized_keys` 文件（如果存在的话），否则其他已配置密钥的用户将无法登录！一定要使用 `>>` 追加或小心地在文件中添加。

> 使用文本编辑器（如 vim）打开 authorized_keys 文件并粘贴进去代码

```bash
ssh your_username@your_server_ip
# 例如： ssh hhu@172.31.221.21
# 然后输入用户密码
cd ~ # 进入用户主目录（可选，但好习惯）
mkdir -p ~/.ssh  # -p 参数确保如果目录已存在也不会报错
vim ~/.ssh/authorized_keys
cat ~/.ssh/authorized_keys # （可选）确认一下文件内容是否正确
```

**vim 编辑器内的操作指令**
这是一个简单的操作流程。进入 vim 后，你会看到（如果是新文件）一个空白窗口或者（如果是已有文件）文件的内容。界面底部会显示文件名和行数等信息。

- 按 i 键：进入插入模式 (Insert Mode)。此时底部会显示 -- INSERT --，表示你可以开始输入或粘贴文本了。
- 粘贴公钥内容：

  - 在你本地电脑上，用记事本或任何文本编辑器打开你的公钥文件 (id_rsa.pub)。
  - 完整地复制其中的所有内容（它应该是一长行文本，以 ssh-rsa AAAAB3NzaC1yc2E... 开头，结尾是你的邮箱注释）。
  - 回到服务器的终端 vim 窗口中，右键单击进行粘贴。或者，对于某些终端，可能需要使用 Shift+Insert 快捷键进行粘贴。
  - 确保粘贴的内容是完整的一行，没有多余的换行或空格。
- 按 Esc 键：退出插入模式，回到命令模式 (Command Mode)。底部的 -- INSERT -- 会消失。
- 保存并退出：

  - 输入 :wq （冒号 : 会激活底部的命令输入，接着输入 wq）
  - 然后按 Enter 键。
  - :w = write (保存)
  - :q = quit (退出)
  - :q! = force quit (强制退出，不保存)
  - :x = 保存并退出 (保存并退出)
  - :w 文件名 = 另存为 (另存为文件名)
    :q
  - :wqa = 保存并退出所有窗口 (保存并退出所有窗口)

#### 5. 配置本地VSCode的SSH配置文件

**作用**：告诉VSCode如何连接你的服务器，以及使用哪个私钥文件进行认证。
**操作位置**：VSCode的设置远程资源管理器（Remote-SSH扩展提供）。

1. 在VSCode中，按 `F1` 或 `Ctrl+Shift+P` 打开命令面板。
2. 输入 **`Remote-SSH: Open SSH Configuration File...`** 并选择。
3. 从列表中选择你的SSH配置文件（通常是 `C:\Users\你的用户名\.ssh\config`**Windows** 或 `~/.ssh/config`**Linux/macOS**）。
4. 在配置文件中添加以下内容（如果文件不存在则创建）：**注意格式，尤其是缩进**
   ```ssh
   Host MyRemoteServer # 自定义一个易记的服务器别名
     HostName your_server_ip # 服务器的IP地址或域名
     User your_username      # 登录服务器的用户名
     IdentityFile ~/.ssh/id_rsa # 本地私钥文件的路径
     # Port 22 # 如果SSH服务不是默认的22端口，取消注释并修改端口号
   ```

   * 将 `MyRemoteServer` 替换为你喜欢的任意别名。
   * 将 `your_server_ip` 和 `your_username` 替换为实际信息。
   * `IdentityFile` 后的路径指向你的**私钥**文件。如果你生成密钥时指定了其他名称或路径，请在这里修改。有时候不需要可能默认位置就行。

#### 6. 在VSCode中连接到远程服务器

**操作位置**：本地计算机上的VSCode。
**作用**：建立VSCode与远程服务器的连接，开始远程开发。
**步骤**：

1. 点击VSCode左下角的**蓝色远程连接按钮**（类似“><”符号）。
2. 在弹出的顶部命令框中，选择 **`Remote-SSH: Connect to Host...`**。
3. - 从列表中选择你刚才在 `config` 文件里设置的**主机别名**（如 `MyRemoteServer`）。
   - 选择“Add New SSH Host...”，然后输入 `ssh username@server_ip` 格式的命令（如果你没有配置config文件）。
4. 如果一切配置正确，VSCode将会在新窗口中打开并连接到你的服务器，**不再需要输入密码**。第一次连接时可能会询问你是否继续连接（验证服务器指纹），选择确认即可。
5. 连接成功后，你可以通过VSCode的**文件管理器**打开服务器上的目录，使用**集成终端**运行命令，就像在本地操作一样。

```ssh
# Host DESKTOP-UUJIN0R  # hostname
#   HostName 172.31.221.21  # 替换为 hostname -I 显示的IP
#   User hhu # 替换为 whoami 输出的用户名

# Host 172.31.221.21 # 自定义别名
#   HostName 172.31.221.21 # WSL2可通过localhost访问
#   User hhu # 你在WSL子系统中的用户名
#   Port 22 # SSH默认端口
#   IdentityFile "C:\Users\Administrator\.ssh\id_rsa" # 私钥路径
#   # 若WSL SSH使用非默认端口，需修改Port项sudo service ssh restart

# 镜像网络模式
Host DESKTOP-UUJIN0R  # hostname
  HostName localhost # 替换为 hostname -I 显示的IP  192.168.3.17
  User hhu # 替换为 whoami 输出的用户名
  Port 22 # SSH默认端口
  IdentityFile "C:\Users\Administrator\.ssh\id_rsa" # 私钥路径
```

#### 7. 故障排查

如果连接失败，可以检查以下几点：

1. **服务器SSH服务配置**：确保服务器上 `/etc/ssh/sshd_config` 中包含以下设置：（似乎不需要）
   ```bash
   PubkeyAuthentication yes
   AuthorizedKeysFile .ssh/authorized_keys
   ```

   修改后需重启SSH服务（如 `sudo systemctl restart sshd`）。
2. **权限检查**：再次确认服务器上 `.ssh` 目录和 `authorized_keys` 文件的权限是否正确。
3. **config文件语法**：确保SSH config文件中`<b style="color:red">`每行缩进使用空格`</b>`，不要用Tab键；`IdentityFile` 后直接跟路径，中间是空格，没有冒号或其他符号。
4. **防火墙**：检查服务器防火墙是否放行了SSH端口（默认22）。

#### 💡 多密钥管理

如果你需要为不同的服务器或服务（如GitHub）使用不同的密钥对，可以在SSH config文件中为每个主机配置不同的 `IdentityFile`：

```ssh
Host ServerA
    HostName 192.168.1.100
    User alice
    IdentityFile ~/.ssh/id_rsa_server_a

Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_rsa_github
    IdentitiesOnly yes # 确保只使用指定的密钥
```

#### 流程概览

```mermaid
flowchart TD
    A[开始: 准备工作] --> B[生成SSH密钥对<br>在本地终端操作]
    B --> C[上传公钥至服务器<br>在本地操作，影响服务器]
    C --> D[配置本地SSH客户端<br>编辑本地~/.ssh/config文件]
    D --> E[通过VSCode连接<br>在VSCode界面操作]
    E --> F{连接成功?}
    F -- 是 --> G[开始远程开发]
    F -- 否 --> H[故障排查]
    H --> H1[检查文件权限]
    H --> H2[检查服务器SSH配置]
    H --> H3[检查防火墙]
    H --> H4[终端测试连接]
    H1 --> E
    H2 --> E
    H3 --> E
    H4 --> E
```

### GIT 仓库克隆 蓝桥

- **克隆仓库**
  git clone https://github.com/your_username/your_repository.git
- **切换分支**
  git checkout -b your_branch_name
- **提交代码**
  git add .
  git commit -m "your_commit_message"
- **推送代码**
  git push origin your_branch_name
- **创建 Pull Request**

#### 在 GitHub 上创建仓库、

1. 首先，申请一个 GitHub 账户。
2. 第二步，我们来新建一个代码仓库。
   - 仓库（repository），可理解为储存代码的场所，点击个人主页的右上角的加号，再点击 New repository，即可创建新的仓库：
   - 然后给你的仓库命名（比如说 Demo），然后点击 Create Repository，无需考虑本页面的其他选项。

#### 添加 SSH 关联授权

- 在终端执行下面命令，每次询问按回车即可。

  ```bash
  ssh-keygen -t ed25519 -C "你的邮箱地址"
  ```
- 终端执行 ssh-keygen 命令按几次回车生成公私钥，公私钥存放在主目录下的隐藏目录 .ssh 中的两个文件中：
- 将 ~/.ssh/id_ed25519.pub 文件中的公钥内容复制出来
- 然后在 GitHub 网页上添加公钥：

  - Title 自定义，把剪切板中的内容粘贴到 Key 中，点击绿色按钮添加 SSH Key 即可：

#### 克隆 GitHub 上的仓库到本地

`git clone + [仓库地址] `

### 挑战：提交我的代码

**介绍**
我们已经有了 Github 账号，现在需要你能新建一个仓库，并向仓库中提交上一个挑战的代码。你需要完整地执行一次对 GitHub 仓库的创建、克隆、提交、推送操作。

**目标**

1. 在自己电脑中的浏览器上打开 GitHub 页面，登录账号后创建 `shiyanlou-code` 仓库。
2. 在实验环境中，克隆你的仓库到 `/home/shiyanlou/Code` 目录下。
3. 进入 `cd /home/shiyanlou/Code/shiyanlou-code` 中，新建 `jump7.py` 文件，并把你上个挑战的通过代码，复制进文件中保存。
4. 将全部修改添加到暂存区、创建提交、推送到自己的 GitHub 远程 `shiyanlou-code` 仓库
   本挑战没有标准答案，完成整个上传仓库的流程即可。

**提示语**

1. `git clone https://github.com/你的Github账号/仓库名称` 克隆仓库
2. `git add .` 添加修改到暂存区
3. `git commit -m 备注信息` 创建新的提交版本
4. `git push` 将提交推送到远程仓库

- [x] **注意事项**
`git push` 第一次记得输入`yes`

`git clone --depth 1 --single-branch -b master https://github.com/davidgiven/minix2`

定期运行git fetch???


---
> DS:windows vscode 怎么从0开始git push 代码到github? 如果你是一位专业人士，有更好的方法和建议吗？尽可能全面。请具体列出详细步骤，操作位置和每一步的作用

在Windows上使用VSCode将代码推送到GitHub是一个高效的工作流。作为专业人士，我建议采用**SSH协议**进行连接，因为它比HTTPS更安全且无需频繁输入凭证。下面是一份从零开始的详细指南，包含专业优化建议。

# 🛠️ Windows VSCode代码推送GitHub专业指南

## 准备工作

1.  **安装Git**
    访问[Git官网](https://git-scm.com/downloads)下载Windows版本。安装时一路默认选项即可，但注意在“Choosing the default editor used by Git”这一步，建议选择**Use Visual Studio Code as Git’s default editor**。

2.  **安装VSCode**
    访问[VSCode官网](https://code.visualstudio.com/download)下载并安装。

3.  **配置Git用户信息（全局）**
    在桌面上右键选择“Git Bash Here”，执行以下命令进行全局基础配置（此配置仅为初始设置，后续可为不同项目设置不同信息）：
    ```bash
    git config --global user.name "Your GitHub Username"
    git config --global user.email "Your GitHub Email"
    ```
    使用 `git config --global --list` 命令验证配置。

## 1. 使用SSH密钥认证（专业推荐）

与需要每次输入密码或使用令牌的HTTPS方式不同，SSH密钥提供了更安全、更便捷的认证方式。

### 生成SSH密钥对
1.  打开 **Git Bash**。
2.  运行以下命令（替换为你的邮箱）：
    ```bash
    ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
    ```
3.  当提示“Enter file in which to save the key”时，直接按回车使用默认路径（`C:\Users\你的用户名\.ssh\id_rsa`）。
4.  你可以为密钥设置一个密码（passphrase），或者直接回车留空（专业人士建议设置密码以增加安全性）。

### 将SSH公钥添加到GitHub
1.  在Git Bash中运行 `cat ~/.ssh/id_rsa.pub`，复制输出的全部内容。
2.  登录GitHub，点击右上角头像 -> **Settings** -> 左侧边栏的 **SSH and GPG keys**。
3.  点击 **New SSH key**，Title可自定义（如`My Windows PC`），将复制的公钥内容粘贴到Key框中，最后点击 **Add SSH key**。

### 验证SSH连接
在Git Bash中运行：
```bash
ssh -T git@github.com
```
如果看到类似“Hi your_username! You've successfully authenticated...”的欢迎信息，说明连接成功。

## 2. 在GitHub上创建远程仓库

1.  登录GitHub，点击右上角“+”号，选择 **New repository**。
2.  填写仓库名称（Repository name），选择公开（Public）或私有（Private）。**重要：先不要勾选“Initialize this repository with a README”**，因为我们将推送一个已存在的本地项目。

## 3. VSCode初始设置与项目准备

### 配置Git路径（如需要）
VSCode通常会自动检测Git安装路径。如果遇到问题，可以手动配置：
1.  在VSCode中按 `Ctrl + ,` 打开设置。
2.  搜索 `git.path`。
3.  在设置中添加项，指向你的git.exe路径，例如：
    ```json
    "git.path": "D:\\Git\\bin\\git.exe"
    ```

### 打开项目文件夹
在VSCode中，通过 `File > Open Folder...` 打开你的项目根目录。

## 4. 初始化本地Git仓库并进行初始提交

以下流程对比了VSCode图形界面操作和终端命令操作，你可以根据喜好选择或结合使用。

| 步骤 | VSCode图形界面操作（可视化） | 终端命令（控制精确度） | 步骤作用解析 |
| :--- | :--- | :--- | :--- |
| **1. 初始化仓库** | 点击左侧源代码管理图标（Ctrl+Shift+G）-> **Initialize Repository** | 在集成终端（Ctrl+`）中执行 `git init` | 在当前项目文件夹中创建一个新的Git本地仓库，生成一个隐藏的`.git`文件夹。 |
| **2. 暂存更改** | 在“源代码管理”面板的“Changes”下，将鼠标悬停在文件上点击“+”号，或点击“Changes”旁的“+”号暂存所有更改。 | `git add .`（暂存所有文件）或 `git add <filename>`（暂存特定文件）。 | 将文件的当前版本快照添加到暂存区（Staging Area），准备进行提交。 |
| **3. 提交更改** | 在“消息”输入框（上方）中输入提交信息（如"Inital commit"），然后按Ctrl+Enter提交，或点击“消息”框上方的√图标。 | `git commit -m "Your commit message here"`。 | 将暂存区的快照永久记录到本地仓库的历史中，并附上描述性信息。 |

## 5. 链接远程仓库并推送代码

### 添加远程仓库地址
你需要告诉本地仓库远程仓库在哪里。在GitHub仓库页面，点击绿色的“Code”按钮，选择 **SSH** 选项卡，复制以 `git@github.com:` 开头的地址。

-   **VSCode方式**：
    1.  打开命令面板（`Ctrl+Shift+P`）。
    2.  输入并选择 **Git: Add Remote**。
    3.  输入一个远程仓库名称（通常为 `origin`），按回车。
    4.  粘贴刚才复制的SSH地址，按回车。

-   **终端命令方式**：
    ```bash
    git remote add origin git@github.com:your_username/your_repository_name.git
    ```

### 推送到远程仓库
最后一步，将本地提交推送到GitHub。

-   **VSCode方式**：
    1.  打开命令面板（`Ctrl+Shift+P`）。
    2.  输入并选择 **Git: Push**，或者点击源代码管理视图右上角的“...”选择 **Push**。
    3.  如果是首次推送，可能会提示你选择上游分支。选择`origin`远程仓库和`main`（或`master`）分支，并选择**OK**进行推送。

-   **终端命令方式**：
    ```bash
    git push -u origin main
    ```
    （如果你的默认分支是`master`，则将命令中的`main`替换为`master`）。`-u` 参数设置上游分支，之后只需简单执行 `git push` 即可。

## 6. 专业人士的进阶配置与建议

### 为不同项目设置独立身份信息
如果你希望为特定项目使用与全局配置不同的用户名和邮箱，可以在项目根目录下执行：
```bash
git config user.name "Your Project Specific Name"
git config user.email "Your_Project_Email@example.com"
```
这会在项目的 `.git/config` 文件中创建局部配置，其优先级高于全局配置。

### 配置凭证存储（如果坚持使用HTTPS）
如果你选择HTTPS方式克隆仓库，可以永久缓存凭证，避免每次推送都输入密码或令牌：
```bash
git config --global credential.helper store
```
首次操作后输入一次凭证，之后就不再需要了。

### 使用 `.gitignore` 文件
在项目根目录创建一个名为 `.gitignore` 的文件，用于指定不需要纳入版本控制的文件或文件夹，如`node_modules/`, `.env`, `*.log`等。在VSCode的源代码管理面板中，右键文件可以选择“添加到 `.gitignore`”。

### 推送代码前先拉取
在团队协作中，推送代码前先执行 `git pull`（或VSCode中的“Pull”操作）是一个好习惯，可以整合队友的提交，避免冲突。

### 使用分支进行功能开发
专业的开发流程不会直接在主分支（`main`/`master`）上修改代码。建议为每个新功能或修复创建新分支：
```bash
git checkout -b feature/awesome-new-feature
```
在VSCode左下角可以方便地查看和切换当前分支。

## 故障排查

-   **推送超时**：可能是网络问题，尝试重新推送。
-   **权限被拒绝**：请检查SSH密钥是否正确配置。可尝试用 `ssh -T git@github.com` 重新测试。
-   **无法创建标签**：可以通过命令面板（`Ctrl+Shift+P`）使用 **Git: Create Tag** 和 **Git: Push (Follow Tags)** 来管理标签。

希望这份全面的指南能帮助你顺利完成代码推送！如果你在具体步骤中遇到问题，可以告诉我具体的错误提示，我能提供更进一步的帮助。

---
> Tencent:windows vscode 怎么从0开始git push 代码到github? 如果你是一位专业人士，有更好的方法和建议吗？尽可能全面。请具体列出详细步骤，操作位置和每一步的作用

在Windows上使用VSCode从零开始将代码推送到GitHub是一个系统性的过程。下面我将为你梳理一份详细步骤和专业人士的建议，旨在提升效率和避免常见陷阱。

# 🚀 Windows VSCode 代码推送GitHub全指南

## 1. 环境准备与配置

在开始推送代码之前，你需要确保系统环境已正确设置，这是所有后续操作的基础。

### 1.1 安装必要软件

首先确保你的Windows系统上已经安装了Git和Visual Studio Code (VSCode)。
*   **Git下载与安装**：访问 https://git-scm.com/downloads 下载Windows版本的Git安装程序。安装过程中，注意选择`Use Git from the Windows Command Prompt`选项，这将允许你在任何终端中使用Git。
*   **VSCode下载与安装**：访问 https://code.visualstudio.com/Download 下载并安装。
*   **验证安装**：安装完成后，打开一个新的命令提示符（CMD）或PowerShell窗口，输入 `git --version` 并回车。如果终端返回了Git的版本号（例如 `git version 2.39.0.windows.1`），说明Git已安装成功并已加入系统环境变量。

### 1.2 配置Git用户信息

安装好Git后，你需要配置全局的用户名和邮箱地址，这样你提交的代码都会带有这些身份信息。
*   **操作位置**：在VSCode中，你可以通过点击菜单栏的“终端(Terminal)” -> “新建终端(New Terminal)”打开集成终端。或者直接使用Windows命令提示符/PowerShell。
*   **执行命令**：
    ```bash
    git config --global user.name "你的GitHub用户名"
    git config --global user.email "你的GitHub注册邮箱"
    ```
*   **作用**：`--global` 参数表示这是全局配置，会应用于你系统上所有的Git仓库。此信息会被记录在你的每一次代码提交中。

## 2. 本地Git仓库操作

现在你可以在本地的项目文件夹中开始进行版本控制了。

### 2.1 初始化Git仓库

这是将你的普通项目文件夹转变为Git可管理仓库的第一步。
*   **操作位置**：在VSCode中，通过菜单“文件(File)” -> “打开文件夹(Open Folder)”打开你的项目根目录。
*   **操作方法**：
    *   **图形界面操作**：在VSCode左侧活动栏点击“源代码管理”(Source Control)图标（或按 `Ctrl+Shift+G`），如果当前文件夹不是Git仓库，通常会看到一个“初始化仓库”(Initialize Repository)的按钮，点击它。
    *   **终端命令**：在VSCode的集成终端中，确保路径在你的项目目录下，然后输入命令：
        ```bash
        git init
        ```
*   **作用**：此命令会在你的项目根目录下创建一个隐藏的 `.git` 文件夹，Git会用这个文件夹来跟踪和管理你项目的所有变更历史。

### 2.2 添加文件到暂存区

Git需要显式地告诉它哪些文件的更改你需要被管理。
*   **操作位置**：VSCode的“源代码管理”视图。
*   **操作方法**：
    *   **图形界面操作**：在“源代码管理”视图下，你会看到“更改”(Changes)列表。将鼠标悬停在文件上，会出现一个“+”号图标，点击即可将该文件添加到“暂存更改”(Staged Changes)区域。你也可以点击“更改”上方的“+”号来一次性添加所有更改的文件。
    *   **终端命令**：
        ```bash
        git add . # 添加当前目录下所有更改的文件和新文件
        git add filename.txt # 添加特定文件
        ```
*   **作用**：`git add` 将你的文件改动“暂存”起来，准备在下一次提交时保存到版本历史中。这是一个准备动作，让你可以精确控制哪些改动要纳入下次提交。

### 2.3 提交更改到本地仓库

提交相当于为你项目的当前状态创建一个快照。
*   **操作位置**：VSCode的“源代码管理”视图。
*   **操作方法**：
    *   **图形界面操作**：在“源代码管理”视图顶部的输入框中，填写本次提交的说明信息（例如“初始化项目”或“修复登录bug”）。然后按 `Ctrl+Enter` (Windows) 或点击输入框旁边的对勾(✓)图标进行提交。
    *   **终端命令**：
        ```bash
        git commit -m "你的提交说明信息"
        ```
*   **作用**：`git commit` 将已在暂存区的文件改动永久性地记录到本地仓库的历史中。提交信息至关重要，它应该清晰扼要地描述这次提交的目的，便于日后查阅。

## 3. 连接与推送到GitHub

本地仓库准备好后，就需要连接到远程的GitHub仓库并推送代码。

### 3.1 在GitHub上创建远程仓库

你需要一个在线的目的地来存放你的代码。
*   **操作位置**：访问 https://github.com/，登录你的账户。
*   **操作方法**：
    1.  点击页面右上角的“+”号，选择“New repository”。
    2.  填写仓库名称（Repository name），最好与本地项目名一致。
    3.  （可选）添加描述（Description）。
    4.  选择仓库可见性（Public 或 Private）。
    5.  **初始化选项**：**不要**勾选“Initialize this repository with a README”，因为你已经有一个本地仓库了，如果勾选可能会导致冲突。
    6.  点击“Create repository”完成创建。

### 3.2 配置SSH密钥（推荐的身份验证方式）

使用SSH密钥可以免去每次推送都输入用户名和密码的麻烦，更加安全便捷。
*   **生成SSH密钥**：
    *   **操作位置**：VSCode集成终端或Git Bash。
    *   **执行命令**：
        ```bash
        ssh-keygen -t rsa -b 4096 -C "你的GitHub邮箱"
        ```
        连续按回车接受默认保存路径和空密码（或设置密码）即可。
*   **将公钥添加到GitHub**：
    1.  在终端中运行命令查看并复制公钥内容：
        ```bash
        type %userprofile%\.ssh\id_rsa.pub # Windows CMD
        cat ~/.ssh/id_rsa.pub # Windows Git Bash / macOS/Linux
        ```
        复制输出的全部文本内容。
    2.  登录GitHub，点击右上角头像 -> “Settings” -> 左侧“SSH and GPG keys”。
    3.  点击“New SSH key”，填写一个易识别的Title（如“My Work Laptop”），并将复制的公钥内容粘贴到“Key”区域。
    4.  点击“Add SSH key”保存。
*   **验证连接**：
    在终端中输入以下命令来测试SSH密钥是否配置成功：
    ```bash
    ssh -T git@github.com
    ```
    如果看到类似 “Hi username! You've successfully authenticated...” 的欢迎信息，说明配置成功。

### 3.3 关联本地与远程仓库并推送

最后一步，告诉你的本地仓库远程地址在哪里，并把代码推上去。
*   **关联远程仓库**：
    *   **操作位置**：VSCode集成终端。
    *   **执行命令**（请将 `你的用户名` 和 `你的仓库名` 替换为实际信息）：
        ```bash
        git remote add origin git@github.com:你的用户名/你的仓库名.git
        ```
        这里的 `origin` 是为远程仓库地址起的一个别名，以后可以用这个别名指代该远程仓库。
*   **推送到GitHub**：
    *   **操作位置**：VSCode集成终端或图形界面。
    *   **操作方法**：
        *   **终端命令**（首次推送需要 `-u` 参数）：
            ```bash
            git push -u origin main
            ```
            **注意**：GitHub现在默认的主分支名是 `main`，早年创建的项目可能是 `master`，请根据你的实际情况修改。`-u` 参数会将本地当前分支与指定的远程分支关联起来，下次只需简单地执行 `git push` 即可。
        *   **图形界面操作**：在VSCode底部状态栏，你可以找到一个同步图标（🔄环形箭头）。点击它，通常会执行“Pull”然后“Push”的操作。或者，在“源代码管理”视图点击“...”更多操作菜单，选择“推送”(Push)。
*   **作用**：`git push` 命令将你本地仓库的提交记录和文件内容上传到名为 `origin` 的远程仓库（GitHub）的 `main` 分支上。

## 4. 专业人士的建议与技巧

掌握了基础操作后，以下建议可以帮助你更高效、专业地使用Git。

*   **SSH vs HTTPS**：**强烈推荐使用SSH协议**（如 `git@github.com:username/repo.git`）进行远程连接，而不是HTTPS（如 `https://github.com/username/repo.git`）。SSH使用密钥对进行认证，无需每次输入密码，更加安全方便。如果你的远程仓库之前是用HTTPS连接的，可以使用命令 `git remote set-url origin git@github.com:用户名/仓库名.git` 来切换。
*   **主分支名称**：GitHub已将新仓库的默认主分支从 `master` 更名为 `main`。如果你希望保持一致，可以使用 `git branch -M main` 命令将你现有的本地主分支重命名为 `main`，然后再执行推送。
*   **有意义的提交信息**：编写提交信息时，**第一行应简要概括提交内容（不超过50字符），空一行后可添加更详细的说明**。好的提交信息能让项目历史清晰易懂。例如：
    ```
    修复用户头像无法上传的问题

    - 修复了在网络延迟时上传接口超时处理逻辑
    - 增加了对图片格式的验证
    ```
*   **使用 `.gitignore`**：在项目根目录创建一个名为 `.gitignore` 的文件。这个文件用于告诉Git哪些文件或目录不需要纳入版本管理，例如系统生成的文件、依赖目录（`node_modules/`）、日志文件、IDE配置文件等。这样可以避免将无关文件提交到仓库。你可以在 https://www.toptal.com/developers/gitignore/ 根据你的开发环境（如Windows, VisualStudioCode, Python, Java等）生成模板。
*   **先拉再推**：在**推送（Push）之前，如果怀疑远程仓库可能有更新（特别是在团队协作中），先执行一次拉取（Pull）**（`git pull origin main`）或使用VSCode的“同步”功能。这可以获取远程的更新并提前合并，避免推送冲突。

下面是整个流程主要步骤和关键操作的总结表：

| 步骤名称             | 关键操作/命令                                      | 主要作用                                             |
| :------------------- | :------------------------------------------------- | :--------------------------------------------------- |
| **1. 环境准备**      | 安装Git、VSCode                                    | 提供版本控制和代码编辑的基础环境                       |
|                      | `git config --global user.name/user.email`         | 设置提交者身份信息                                     |
| **2. 本地仓库初始化** | `git init` 或 VSCode界面"初始化仓库"                 | 将普通文件夹变为Git管理的仓库                         |
| **3. 暂存更改**      | `git add .` 或 VSCode界面"+"号                      | 选择要纳入下次提交的更改                               |
| **4. 提交到本地**    | `git commit -m "message"` 或 VSCode界面输入信息后提交 | 将暂存区的更改创建快照并保存到本地历史记录中             |
| **5. 连接远程仓库**  | 在GitHub创建仓库，获取SSH地址                        | 准备一个远程代码托管位置                               |
|                      | `ssh-keygen`, 将公钥添加到GitHub                    | 配置免密码的安全认证方式                               |
|                      | `git remote add origin git@github.com:user/repo.git` | 为本地仓库关联一个远程地址别名                         |
| **6. 推送到远程**    | `git push -u origin main` 或 VSCode同步/推送按钮    | 将本地提交的历史和内容上传到远程仓库                   |

完成以上所有步骤后，刷新你的GitHub仓库页面，就能看到代码已经成功上传了。之后在日常开发中，你通常只需要重复 **添加 (add) -> 提交 (commit) -> 推送 (push)** 这个循环来管理你的代码迭代。

希望这份详细的指南能帮助你顺利开始使用Git和GitHub！如果你在过程中遇到任何问题，随时可以追问。