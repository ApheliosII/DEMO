# Project: My Awesome App - API Design Notes
## Authentication Module
### JWT Implementation Decisions

## 1.​​标题 (Headers): ​使用`#`#定义不同层级的标题，组织笔记结构。

## 2.​​列表 (Lists): 有序列表 (`1.`) 和无序列表 (`-`或`*`) 
- [x] Implement user registration endpoint
- [ ] Add email verification
- [ ] Write unit tests for auth service
  - [ ] Implement user login endpoint
  - [ ] Implement user logout endpoint
* [ ] Implement user login endpoint
* [ ] Implement user logout endpoint

## 3.​代码块 (Code Blocks):​ ​​最重要！​​ 用 ` ``` `包裹代码片段。可以指定语言以获得语法高亮。
```python

def calculate_sum(a, b):

"""Adds two numbers."""

return a + b

```

```bash

Command to start the dev server
npm run dev

```
## 4.​​行内代码 (Inline Code):​ 用反引号`` ` `` 包裹行内的代码、命令、文件名或变量名。
`The configuration is stored inconfig.yaml.Use the get_user()function.`

## 5.链接(Links): ​使用`[Title](URL)`语法创建链接。
- See the [database schema diagram](./docs/db_schema.png) for details.

- Reference the [official React docs](https://reactjs.org/docs/hooks-intro.html).

  - Reference the [official React docs][参考]


## 6.图片 (Images): ​使用`![Alt Text](URL)`语法插入图片。（通常建议放在项目内的 docs/或 images/目录）。
![Authentication Flow Diagram](./images/auth_flow.png)

## 7.​​表格 (Tables):​​​ ​使用`|`和`-`创建表格。
| Parameter     | Default Value | Description          |
| :------------ | :-----------: | -------------------: |
| `timeout`     |     30s       | Request timeout      |
| `max_retries` |      3        | Maximum API retries |

## 8.块引用 (Blockquotes): ​使用`>`创建块引用。    
> **Important:** This endpoint requires admin privileges.
>> Please make sure to use secure authentication methods such as OAuth 2.0 or JSON Web Tokens (JWT) to ensure the security of your API.
>>> **Note:** This endpoint is rate-limited to prevent abuse.

## 9.​​强调 (Emphasis):​
- ​`**`或`__`加粗: **italic** or __italic__
- ​`*`或`_`斜体: *italic* or _italic_
- `~~`删除线: ~~strikethrough~~

## 10.​​分隔线 (Horizontal Rule): ​使用三个或三个以上的`*`、`-`或`_`创建分隔线。

***
---
___

## 11.​​脚注 (Footnotes): ​使用`[^1]`语法创建脚注。
- This is 1st footnote.[^1]
- This is 2nd footnote.[^2]
- This is 3rd footnote [^research_source]

---

[^1]: This is the first footnote.
[^2]: This is the second footnote.
[^research_source]: Smith, J., & Jones, A. (2023). *The Study of Things*. Academic Press. [Link](https://example.com/study)

## Using Footnotes in Markdown

Markdown is a lightweight markup language.[1](@ref) It allows you to write using an easy-to-read, easy-to-write plain text format, which then converts to structurally valid HTML (or other formats).[2](@ref)

Footnotes are a useful feature for adding supplementary information without cluttering the main text.[3](@ref)


### References

[1](@ref): Created by John Gruber in 2004.
[2](@ref): Many static site generators and documentation tools support Markdown.
[3](@ref): Footnotes appear as superscript numbers in the text and are listed at the bottom of the document or section.

## 12.画图
### 1. Mermaid - 现代 Markdown 绘图的绝对主流
```mermaid
graph TD
    A[开始] --> B{判断}
    B -->|是| C[执行操作]
    B -->|否| D[结束]
    C --> D
```
```mermaid
graph LR
    A[开始] --> B{处理数据}
    B --> C[验证]
    C -->|成功| D[保存结果]
    C -->|失败| E[记录错误]
    D --> F[结束]
    E --> F
```
方法一：使用 <br>标签（最常用）
```mermaid
graph TD
    A[<div>第一行文本</div><div>第二行文本</div>] --> B
    
    Start[开始处理<br>初始化系统] --> Check{数据验证<br>检查完整性}
    Check -->|通过| Process[数据处理<br>转换格式]
    Check -->|失败| Error[错误处理<br>记录日志]
    Process --> Save[保存结果<br>更新数据库]
    Save --> End[流程结束<br>释放资源]
    
    style Start fill:#e1f5fe
    style Check fill:#fff3e0
    style Process fill:#e8f5e9
    style Save fill:#f3e5f5
    style Error fill:#ffebee
    style End fill:#f5f5f5
```

```mermaid
graph LR
    A:::startEnd --> B:::process
    subgraph 子流程 [重要模块]
        B --> C{判断}:::decision
    end
    C -->|是| D[成功]:::success
    C -->|否| E[失败]:::failure

    classDef startEnd fill:#f9f,stroke:#333,stroke-width:2px;
    classDef process fill:#bbf,stroke:#333,stroke-width:1px;
    classDef decision fill:#fc9,stroke:#333,stroke-width:1px;
    classDef success fill:#9f9,stroke:#333;
    classDef failure fill:#f96,stroke:#333;
```

```mermaid
graph LR
    A-->B
    click A "https://www.example.com" "这是提示框"
```

### 2. PlantUML - 专业、强大的图表标准
![我的流程图](http://www.plantuml.com/plantuml/png/SoWkIImgAStDuG8oICrB0N81)

### 3. Graphviz - 关系图和网络图的终极武器
![组织结构图](./org-chart.svg)

### 4. 纯文本草图 - 快速沟通
    +--------+   request   +-------------+
    |        | ----------> |             |
    | Client |             |   Server    |
    |        | <---------- |             |
    +--------+   response  +-------------+

## 导出pdf
***注意: 远程linux没有安装chrome，需要在windows上转pdf。***
- [x] 插件Markdown Preview Enhanced可以将markdown文件导出为pdf文件。


[参考]: https://reactjs.org/docs/hooks-intro.html
