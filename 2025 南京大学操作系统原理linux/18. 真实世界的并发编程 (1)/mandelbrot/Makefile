# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

CFLAGS := -O2 -fopenmp -I$(TLIB_PATH)

mandelbrot: mandelbrot.c
	gcc $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f mandelbrot *.jpg *.ppm
