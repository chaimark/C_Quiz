# 定义编译器和工具
CC = gcc
AR = ar

# 获取所有 .c 文件和对应的 .o 文件
clibs := $(wildcard *.c)
objs := $(clibs:%.c=%.o)

# 默认目标：生成静态库 MyLib.a
libMyLib.a: $(objs)
	$(AR) rcs $@ $^

# 规则：从 .c 文件生成 .o 文件
%.o: %.c
	$(CC) -c $< -o $@

# 清理目标
.PHONY: distclean
distclean:
	-rm -rf *.o libMyLib.a