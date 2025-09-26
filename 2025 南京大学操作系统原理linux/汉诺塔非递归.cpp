#include <stdio.h>
#include <assert.h> // 添加assert.h头文件:  用于错误检测（assert宏）

// 定义栈帧结构体，用于模拟函数调用栈
typedef struct
{
    int pc, n;          // 程序计数器（跟踪当前执行步骤）// 当前要移动的盘子数量
    char from, to, via; // 盘子的初始位置、目标位置、中转位置
} Frame;

// 宏定义：模拟函数调用（压栈操作）
#define call(...) ({ *(++top) = (Frame){.pc = 0, __VA_ARGS__}; }) // 修正：使用双下划线
// 宏定义：模拟函数返回（弹栈操作）
#define ret() ({ top--; })
// 宏定义：跳转到指定程序位置
#define goto(loc) ({ f->pc = (loc) - 1; })

// 汉诺塔非递归实现
void hanoi(int n, char from, char to, char via)
{
    Frame stk[64], *top = stk - 1; // 创建栈空间（最大64层递归）// 栈顶指针初始化为栈底前一个位置
    call(n, from, to, via);        // 初始调用：将主问题压栈

    // 模拟CPU执行：只要栈非空就继续执行
    for (Frame *f; (f = top) >= stk; f->pc++)
    {
        switch (f->pc) // 根据程序计数器选择操作
        {
        case 0:            // 第一步：检查基本情况
            if (f->n == 1) // 只剩一个盘子时直接移动
            {
                printf("%c -> %c\n", f->from, f->to); // 打印移动步骤
                goto(4);                              // 直接跳转到返回操作
            }
            break;
        case 1: // 第二步：模拟递归调用（移动n-1个盘子到中转柱）
            call(f->n - 1, f->from, f->via, f->to);
            break;
        case 2: // 第三步：移动最底下的盘子
            call(1, f->from, f->to, f->via);
            break;
        case 3: // 第四步：模拟递归调用（移动n-1个盘子到目标柱）
            call(f->n - 1, f->via, f->to, f->from);
            break;
        case 4:    // 第五步：当前帧完成，返回
            ret(); // 弹出当前栈帧
            break;
        default:       // 错误处理
            assert(0); // 遇到未知pc值触发断言错误
        }
    }
}

int main()
{
    hanoi(3, 'A', 'C', 'B'); // 移动3个盘从A到C，用B中转
    return 0;
}

/*
// n = 2 ,输出：
A -> B
A -> C
B -> C

// n = 3 ,输出：
A -> C
A -> B
C -> B
A -> C
B -> A
B -> C
A -> C
*/

/*关键概念解释：

栈帧(Frame)：模拟函数调用的上下文
pc：记录当前执行位置（类似程序计数器）
n/from/to/via：保存当前递归状态的参数

宏操作：
call()：模拟函数调用（创建新帧压栈）
ret()：模拟函数返回（弹出当前帧）
goto()：跳转到指定位置（修改当前帧的pc值）

递归模拟原理：
每个递归调用转化为一个栈帧
程序计数器(pc)跟踪执行阶段
栈帧按后进先出(LIFO)顺序处理
*/

/* 宏定义解释：
#define call(...) ({ *(++top) = (Frame){.pc = 0, __VA_ARGS__}; })

1. call(...)
call 是宏的名称（可以理解为函数名）
... 表示宏接受可变数量参数（类似函数中的可变参数）

2. __VA_ARGS__ 这是预处理器专用标识符作用：原样替换调用时传入的所有参数

3. (Frame){.pc = 0, __VA_ARGS__}
这是C99引入的复合字面量(Compound Literal)
作用：创建一个临时的Frame结构体实例
初始化方式：
.pc = 0：显式设置pc成员为0
__VA_ARGS__：用传入的参数初始化其他成员

4. *(++top) = ...
top 是指向栈顶的指针
++top：先将栈顶指针上移（为新的栈帧腾出空间）
*(++top)：获取新栈顶位置的引用
= ...：将创建的Frame实例赋值给新栈顶位置

5. ({ ... })
这是GCC的语句表达式(Statement Expression)扩展
作用：将多个语句组合成一个表达式
特点：有返回值（最后一个语句的值）

完整工作流程：
当代码中出现：
call(n-1, from, via, to);

预处理器会将其展开为：
({ 
    *(++top) = (Frame){.pc = 0, n-1, from, via, to}; 
})
    
这相当于执行了：
// 1. 栈顶上移
top = top + 1;

// 2. 初始化新栈帧
Frame new_frame = {
    .pc = 0,        // 程序计数器初始为0
    .n = n-1,       // 第一个参数
    .from = from,   // 第二个参数
    .to = via,      // 第三个参数（注意顺序！）
    .via = to       // 第四个参数
};

// 3. 将新帧放入栈顶
*top = new_frame;
*/