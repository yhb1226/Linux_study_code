# Makefile内容组成
#<目标名称>：<前置依赖>
#    他\t<需要执行的命令>
#目标: 依赖文件1 依赖文件2 ...
#	命令（必须以Tab开头）

#宏定义
objects := hello.o main.o

main: $(objects)          # 最终目标 main 依赖两个 .o 文件
	gcc $(objects) -o main  # 链接成可执行文件

#可以省略main.c
main.o: main.c hello.h        # main.o 依赖 main.c 和 hello.h
	gcc -c main.c               # 只编译 main.c,生成 main.o
#可以省略hello.c
hello.o: hello.c hello.h      # hello.o 依赖 hello.c 和 hello.h
	gcc -c hello.c              # 只编译 hello.c,生成 hello.o

clean:
	-rm $(objects)           # 清理中间文件







