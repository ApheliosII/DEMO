# 定义 TLIB_PATH（根据您的实际路径修改）thread-lib
TLIB_PATH := /mnt/e/2025/learn/VS\ Code/2025\ 南京大学操作系统原理/thread-lib

CFLAGS := -O2 -I$(TLIB_PATH)

main: main.o lockdep.o
	g++ $(CFLAGS) -o $@ $^

main.o: main.c
	gcc $(CFLAGS) -c -o $@ $^

lockdep.o: lockdep.cc
	g++ -std=c++20 $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o main
