**testkit**: Writing test cases fearlessly! 这是同学们的第一个测试框架：支持单元测试和系统测试，自动注册测试用例并在程序退出后运行。最重要的特点是它使用简单：你只需要包含 testkit.h，并且链接 testkit.c 即可。

## 补充
### 如何使用
- `TK_RUN=1 ./main`:运行测试程序，输出测试结果。
- `TK_VERBOSE=1 ./main`:运行测试程序，输出详细的测试信息。