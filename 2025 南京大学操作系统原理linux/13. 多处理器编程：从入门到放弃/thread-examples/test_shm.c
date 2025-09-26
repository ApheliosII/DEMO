#include <thread.h>
#include <unistd.h>

int x = 0, y = 0;

void inc_x() { while (1) { x++; sleep(1); } } // 休眠1秒
void inc_y() { while (1) { y++; sleep(2); } } // 休眠2秒

int main() {
    spawn(inc_x);
    spawn(inc_y);
    while (1) {
        printf("\033[2J\033[H");// ANSI转义序列：清屏并移动光标到左上角
        printf("x = %d, y = %d", x, y);
        fflush(stdout);// 强制刷新输出缓冲区
        usleep(100000);
    }
}
