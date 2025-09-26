# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

all: join-1 join-2

CFLAGS := -O2 -I$(TLIB_PATH)

join-1: join-1.c main.c
	gcc $(CFLAGS) -o $@ $^

join-2: join-2.c main.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f join-1 join-2
