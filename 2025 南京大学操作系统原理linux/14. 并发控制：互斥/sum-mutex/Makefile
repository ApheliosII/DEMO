# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

CFLAGS := -O2 -I$(TLIB_PATH)

all: main.c sum-spin.c sum-mutex.c sum-atomic.c
	gcc $(CFLAGS) -o atomic sum-atomic.c main.c
	gcc $(CFLAGS) -o mutex sum-mutex.c main.c
	gcc $(CFLAGS) -o spin sum-spin.c main.c

clean:
	rm -f atomic mutex spin
