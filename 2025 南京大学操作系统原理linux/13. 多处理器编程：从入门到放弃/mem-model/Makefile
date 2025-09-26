# 定义 TLIB_PATH（根据您的实际路径修改）makefile
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/13.\ 多处理器编程：从入门到放弃/thread-lib

CFLAGS := -O2 -g -I$(TLIB_PATH)

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=)

# Default target
all: $(OBJS)

%: %.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
