#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"a.py", NULL};
    extern char **environ;

    execve(args[0], args, environ);

    // 如果execve失败，执行到这里
    perror("execve");
    return 1;
}