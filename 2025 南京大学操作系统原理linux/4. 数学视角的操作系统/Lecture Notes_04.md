# 2025 南京大学操作系统原理
> 操作系统原理课程学习笔记
包括*软件安装，环境配置，运行命令，专有名词，基本概念*等。

## 4. 数学视角的操作系统
==mosaic==
```bash
./mosaic.py examples/intro/hello.py  
./mosaic.py -c examples/intro/hello.py | less 
./mosaic.py -c examples/intro/hello.py | ./collect.py
```
1. 执行当前目录下的名为`mosaic.py`的 Python 脚本，并将 `examples/intro/hello.py`作为参数传递给这个脚本。

2. 
    - 执行 `mosaic.py` 脚本，并传递两个参数：一个选项`-c`和 一个文件路径 `examples/intro/hello.py`。
    - 将 `mosaic.py` 的标准输出（stdout）通过管道（`|`）传递给 `less`命令。
    - `less`是一个分页器，允许你上下翻页查看长篇内容。

3. 
    - 执行 `mosaic.py`脚本（带 `-c`参数和文件路径）。
    - 将其标准输出通过管道传递给另一个脚本 `collect.py`的标准输入。

==在 `less` 中你可以==
- 按 `Space`空格键 或 `Page Down` 向下翻一页。
- 按 `Page Up` 向上翻一页。
- 按 `/` 然后输入文字来搜索内容（例如 `/hello`）。
- 按 `q` 键退出 `less`，回到正常的命令行界面。

==主要问题：缺少 rich模块==
```bash
pip3 install --user rich # 需要先安装pip

sudo apt update        # 首先更新软件源列表，确保获取到最新的包信息
sudo apt install -y python3-rich

sudo apt update && sudo apt install -y python3-rich
#说明​​：&&是"逻辑与"操作符。只有当前面的命令成功执行（返回退出状态码为0），后面的命令才会执行。这是最安全的方式，确保只有在更新成功后才会尝试安装
sudo apt update ; sudo apt install -y python3-rich
#说明​​：分号 ;简单地分隔命令，无论前一个命令是否成功，后面的命令都会执行。
# 添加 -y 参数来自动确认安装，避免中途需要手动输入 Y 确认。
```