# 该Makefile用于编译C++程序，使用g++编译器。

#注意：不同系统的命令行命令可能不同，如Windows下用del，文件名必需为.exe结尾，如test.exe。类Unix系统用rm。
# 检测操作系统
# ifeq ($(OS),Windows_NT)
#     # Windows系统
#     RM = del /Q
# #    TARGET = test.exe
# else
#     # 类Unix系统（Linux、macOS等）
#     # rm是linux/mac下的文件删除命令，-f表示强制删除，test是要删除的文件名
#     RM = rm -f
# #    TARGET = test
# endif

# test: test.cpp
# 	g++ -o $(TARGET) test.cpp

# clean:
# 	$(RM) $(TARGET)




# Linux下编译：
# make
# # 或者
# make -f Makefile

# #VERSION 1
# hello : main.cpp print_hello.cpp factorial.cpp
# 	g++ -o hello main.cpp print_hello.cpp factorial.cpp

# clean:
# 	$(RM) hello

# #VERSION 2
# CXX = g++
# TARGET = hello
# OBJ = main.o print_hello.o factorial.o
# RM = rm -f

# $(TARGET) : $(OBJ)
# 	$(CXX) -o $(TARGET) $(OBJ)

# main.o : main.cpp
# 	$(CXX) -c main.cpp

# print_hello.o : print_hello.cpp
# 	$(CXX) -c print_hello.cpp

# factorial.o : factorial.cpp
# 	$(CXX) -c factorial.cpp

# clean:
# 	$(RM) $(OBJ) $(TARGET)

#VERSION 3
# CXX = g++
# TARGET = hello
# OBJ = main.o print_hello.o factorial.o
# RM = rm -f 
# # rm -f 表示强制删除文件，不管是否存在

# CXXFLAGS = -c -Wall #编译选项，显示所有警告信息

# $(TARGET) : $(OBJ)
# 	$(CXX) -o $@ $^ 
# # $@表示目标文件名，$^表示所有依赖文件名

# %.o : %.cpp
# 	$(CXX) $(CXXFLAGS) $< -o $@  
# # == g++ -c -Wall main.cpp -o main.o 只编译不链接,生成指定文件名的.o文件
# # -o $@ 可以不要，默认就是目标文件名
# # $@表示目标文件名，$<表示第一个依赖文件名，这里只有一个 等价于下面三条语句

# # main.o : main.cpp
# # 	$(CXX) -c main.cpp

# # print_hello.o : print_hello.cpp
# # 	$(CXX) -c print_hello.cpp

# # factorial.o : factorial.cpp
# # 	$(CXX) -c factorial.cpp

# .PHONY: clean # 定义一个PHONY目标，表示这个目标不需要依赖文件，只要执行make clean命令就行,防止 'clean' is up to date.的错误
# clean:
# 	$(RM) *.o $(TARGET)

# Version 4
CXX = g++
TARGET = hello
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
#OBJ = $(patsubst %.cpp,%.o,$(SRC))
RM = rm -f

CXXFLAGS = -c -Wall

$(TARGET) : $(OBJ)
	$(CXX) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(TARGET)

# Version 5
# 复杂的 Makefile 通常会包含很多变量和模式规则，但基本的结构和规则是固定的。
# 编译器设置
CXX := g++
# CXXFLAGS := -Wall -Wextra -pedantic -std=c++11 -g
CXXFLAGS := -Wall -g
# -Wall：开启所有警告
# -Wextra：提供额外的警告信息
# -pedantic：严格要求符合 ANSI 标准
# -std=c++11：使用 C++11 标准
# -g：在可执行文件中包含调试信息

# 项目设置
TARGET := 机房预约系统
# 最终生成的可执行文件名
SRC_DIR := .
# 源代码目录（当前目录）
BUILD_DIR := build
# 构建目录，存放编译过程中的中间文件

# 自动获取所有.cpp文件
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# 生成对应的.o文件列表
# OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# 获取所有.txt文件（用于数据文件依赖）
DATA_FILES := $(wildcard $(SRC_DIR)/*.txt)

# 主目标：构建可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 模式规则：编译.cpp到.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# 模式规则：告诉 make 如何从 .cpp 文件编译出 .o 文件
# $< 表示第一个依赖文件
# | $(BUILD_DIR) 表示 $(BUILD_DIR) 是顺序先决条件（order-only prerequisite）
# 表示目录必须存在，但如果目录时间戳更新，不会导致重新编译

# 确保构建目录存在
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
# 如果 build 目录不存在，则创建它

# 数据文件处理（复制.txt到构建目录）
$(BUILD_DIR)/%.txt: $(SRC_DIR)/%.txt | $(BUILD_DIR)
	cp $< $@

# 伪目标声明
.PHONY: all clean data

# 默认目标（包含数据文件）
all: data $(TARGET)

# 复制所有数据文件
# data: $(patsubst $(SRC_DIR)/%.txt,$(BUILD_DIR)/%.txt,$(DATA_FILES))
data: $(DATA_FILES: $(SRC_DIR)/%.txt=$(BUILD_DIR)/%.txt)

# 清理构建
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# 包含自动生成的依赖关系（可选）
-include $(OBJS:.o=.d)

# 自动生成依赖规则（可选）
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
# 这部分用于自动生成头文件依赖关系
# -include 尝试包含依赖文件，如果不存在则忽略错误
# 下面的规则用于生成 .d 文件（依赖文件）
# 这段代码比较复杂，初学者可以先忽略，等熟悉基础后再学习

##执行命令：
# make
# make -f Makefile
# make clean
# make && ./机房预约系统