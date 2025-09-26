# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

all: pc-1 pc-2 pc-cv pc-cv-broadcast

CFLAGS := -O2 -I$(TLIB_PATH)

pc-1: pc-1.c main.c
	gcc $(CFLAGS) -o $@ $^

pc-2: pc-2.c main.c
	gcc $(CFLAGS) -o $@ $^

pc-cv: pc-cv.c main.c
	gcc $(CFLAGS) -o $@ $^

pc-cv-broadcast: pc-cv-broadcast.c main.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f pc-1 pc-2 pc-cv
