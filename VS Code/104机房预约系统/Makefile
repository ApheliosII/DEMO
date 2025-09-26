# 用于编译机房预约系统的 Makefile

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