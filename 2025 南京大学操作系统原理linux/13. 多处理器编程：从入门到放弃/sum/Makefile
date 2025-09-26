# 定义 TLIB_PATH（根据您的实际路径修改）makefile
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/13.\ 多处理器编程：从入门到放弃/thread-lib

all: sum

CFLAGS := -I$(TLIB_PATH) -O2

sum: sum.c Makefile
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f sum
