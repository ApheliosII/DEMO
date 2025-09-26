# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

CFLAGS := -O2 -g -I$(TLIB_PATH) -fsanitize=thread

race: race.c Makefile
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f race
