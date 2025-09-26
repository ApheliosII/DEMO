/* 在 C++ 中，Lambda 表达式是一种匿名函数的语法，用于快速定义临时函数对象。
其语法结构灵活且强大，以下是完整的语法定义和关键组成部分：
*/

// Lambda 表达式语法:
// [capture](parameters) mutable -> return-type { function-body }

// 关键组成部分
// capture: 捕获列表，用于指定 Lambda 表达式内部使用的外部变量。
// parameters: 参数列表，用于指定 Lambda 表达式的参数。
// mutable: 可选，用于指定 Lambda 表达式是否可以修改外部变量。
// return-type: 返回类型，用于指定 Lambda 表达式的返回类型。
// function-body: 函数体，用于指定 Lambda 表达式的实现。

// [捕获列表] (参数列表) mutable(可选) -> 返回类型(可选) {
//     // 函数体
// }

/*
语法组成部分详解
1. 捕获列表 [capture]
定义 Lambda 如何访问外部变量（即作用域外的变量）。
    空捕获列表 []：不捕获任何外部变量。
    值捕获 [x, y]：复制外部变量 x 和 y 的值到 Lambda 内部（默认不可修改，需配合 mutable）。
    引用捕获 [&x, &y]：通过引用访问外部变量 x 和 y，可修改原变量。

    隐式捕获：
        [=]：以值捕获所有外部变量。
        [&]：以引用捕获所有外部变量。

    混合捕获：
        [=, &x]：默认值捕获，但 x 为引用捕获。
        [&, x]：默认引用捕获，但 x 为值捕获。


2. 参数列表 (params)
与普通函数的参数列表类似，支持任意类型（包括 auto，C++14 起支持泛型 Lambda）：
// [](int a, double b) { / ... / }      // 显式类型
// [](auto a, auto b) { / ... / }       // 泛型 Lambda (C++14)

3. 可变规范 mutable（可选）
允许修改值捕获的变量（默认值捕获的变量是 const）：
// int x = 10;
// auto lambda = [x]() mutable { x++; }; // 允许修改 x 的副本
// lambda(); // x 的副本变为 11，但原 x 仍为 10

4. 返回类型 -> ret_type（可选）
显式指定返回类型。若省略，编译器自动推导：
// [](int a, int b) -> int { return a + b; } // 显式返回 int
// [](auto a, auto b) { return a + b; }      // 自动推导返回类型

5. 函数体 { ... }
与普通函数一致，可以使用捕获的变量和参数。

*/

#include <iostream>
#include <vector>
#include <algorithm>

#include <functional> // 必需头文件 //内建函数对象头文件

using namespace std;

void test01()
{
    int x = 10;
    auto lambda = [x]() mutable -> int // 允许修改 x 的副本 ; -> int 显式返回int,可以省略
    {
        x++;
        return x;
    };

    lambda(); // x 的副本变为 11，但原 x 仍为 10

    int result = lambda();                     // 调用 lambda 并返回结果
    cout << "result = " << result << endl;     // 输出 12
    cout << "lambda() = " << lambda() << endl; // 输出 13
    cout << "x = " << x << endl;               // 输出 10
}

// 示例 1：基础用法
void test02()
{

    int offset = 5;

    // Lambda 定义：捕获 offset，接受 int 参数，返回 int
    auto add_offset = [offset](int x) -> int
    {
        return x + offset;
    };
    cout << "offset = " << offset << endl;                 // 输出 5
    cout << "add_offset(10) = " << add_offset(10) << endl; // 输出 15
}

// 示例 2：引用捕获与 mutable
void test03()
{
    int count = 0;

    // 引用捕获 count，允许修改
    auto increment = [&count]() mutable
    {
        count++;
        return count;
    };
    cout << "count = " << count << endl; // 输出 0
    increment();
    cout << "count = " << count << endl; // 输出 1

    cout << "increment() = " << increment() << endl; // 输出 2
    cout << "count = " << count << endl;             // 输出 2

    // 值捕获 count，不可修改
    // auto decrement = [count]()
    // {
    //     count--;
    // };

    // 引用捕获 count，可修改
    count = 0;
    auto decrement = [&count]()
    {
        count--;
        return count;
    };
    cout << "count = " << count << endl;       // 输出 0
    cout << "count = " << decrement() << endl; // 输出 -1
    cout << "count = " << count << endl;       // 输出 -1
}

// 示例 3：泛型 Lambda（C++14）
void test04()
{
    // 泛型 Lambda，支持任意类型参数
    auto multiply = [](auto a, auto b)
    {
        return a * b;
    };

    cout << multiply(3, 4) << endl // 输出 12
         << multiply(2.5, 4.0);    // 输出 10.0
}
/* 关键注意事项
1.捕获变量的生命周期
    引用捕获的变量需确保在 Lambda 执行时仍然有效（避免悬空引用）。
    值捕获的变量是 Lambda 对象的成员，生命周期与 Lambda 一致。

2.默认 const 行为
    值捕获的变量默认不可修改（除非使用 mutable）。

3.性能与闭包
    Lambda 会生成一个闭包对象，捕获的变量会成为其成员。
    简单的 Lambda 可能被编译器内联优化。
*/

/* Lambda 与 STL 算法的结合
Lambda 常用于 std::sort、std::for_each 等算法： */

void testSTL()
{
    vector<int> nums = {3, 1, 4, 1, 5};

    // 使用 Lambda 自定义排序规则
    sort(nums.begin(), nums.end(), [](int a, int b)
         {
             return a > b; // 降序排序
         });

    // 使用 Lambda 遍历元素
    for_each(nums.begin(), nums.end(), [](int x)
             {
                 cout << x << " "; // 输出 5 4 3 1 1
             });
}
// 通过灵活组合捕获列表、参数和返回类型，Lambda 表达式可以高效地替代传统函数对象（如 functor），成为 C++ 中函数式编程的核心工具。

/*
 Lambda表达式与递归的写法，c++写法
在 C++ 中，Lambda 表达式与递归的结合需要特殊处理，因为 Lambda 无法直接通过 auto 类型捕获自身。以下是两种常见实现方式及示例：
 */
void testRecursion()
{
    // 方法 1：通过 std::function 和引用捕获
    // 需要显式定义 std::function 类型，并通过引用捕获自身来实现递归：
    // #include <functional> // 必需头文件
    // 定义递归 Lambda
    function<int(int)> factorial;
    factorial = [&factorial](int n) -> int
    {
        return (n <= 1) ? 1 : n * factorial(n - 1); // 递归调用
    };
    cout << factorial(5) << endl; // 输出 120 5*4*3*2*1 = 120
    /* 注意事项：
    1.引用捕获的必要性：必须通过 [&] 或显式捕获 [&factorial] 来确保 Lambda 能引用自身。
    2.初始化顺序：先声明 std::function 变量，再为其赋值 Lambda，避免未初始化问题。
    3.生命周期风险：若 Lambda 被拷贝或移动，引用可能失效，需确保 std::function 对象存活。 */

    // 方法 2：将自身作为参数传递（C++14+）
    // 通过泛型 Lambda 将自身作为参数传递，避免捕获：

    // 泛型 Lambda，接受自身作为参数
    auto factorialself = [](auto &&self, int n) -> int
    {
        return (n <= 1) ? 1 : n * self(self, n - 1); // 递归时传递自身
    };
    cout << factorialself(factorialself, 5) << endl; // 输出 120
    // 递归参数 self：Lambda想要递归调用自身，必须显式将自身作为参数传入。auto&& self 是一个通用引用（universal reference），可以接受任意类型的参数（包括Lambda自身）。
    /* 特点：
    无需捕获：通过参数传递自身，避免引用捕获的潜在问题。
    显式调用：每次递归需传递自身（如 self(self, args)），语法稍显冗余。 */
    
    // 3.C++20 递归 lambda 技术
    // this auto&& self：显式对象参数（explicit object parameter），声明 lambda 自身实例的引用
    // 无需类型擦除：直接通过 self 进行递归调用，无需 std::function 包装
    // 隐式传递实例：调用时 self(node->left, s) 会自动传递当前 lambda 实例，无需手动添加参数
    auto dfs = [](this auto &&self, int n) -> int
    {
        return (n <= 1) ? 1 : n * self(n - 1); // 递归时传递自身
    };
    cout << dfs(5) << endl; // 输出 120

}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // testSTL();
    testRecursion();
    return 0;
}