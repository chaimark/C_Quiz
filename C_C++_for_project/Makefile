# 启用 .ONESHELL 模式
.ONESHELL:

# 定义目标
.PHONY: subMake distclean

# 默认目标：生成可执行文件 main
main: subMake main.o
	gcc -o main main.o -L C_MyLib -lMyLib

# 生成 main.o
main.o: main.c
	gcc -c main.c -o main.o

# 生成 MyLib.a
subMake:
	@echo "Building MyLib.a"
	$(MAKE) -C C_MyLib

# 查找 C_MyLib 目录下的所有 .a 文件
MyLib_a = $(wildcard C_MyLib/*.a)

# 清理目标
distclean:
	@echo "Cleaning up"
	-rm -rf main.o
	@-$(MAKE) distclean -C C_MyLib
	@-rm -rf main
	@-rm -rf main.exe