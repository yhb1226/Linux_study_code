CC       = gcc
CFLAGS   = -Wall -Wextra -g -IInc/First   # 让编译器找到头文件
TARGET   = test_protocol

# 中间文件会生成在当前目录（根目录）
OBJS     = pack.o test_protocol.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# pack.o 的依赖文件路径
pack.o: src/First/pack.c Inc/First/pack.h Inc/First/protocol.h Inc/First/students_record.h
	$(CC) $(CFLAGS) -c -o $@ $<

# test_protocol.o 的依赖文件路径
test_protocol.o: test/test_protocol.c Inc/First/pack.h Inc/First/protocol.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)