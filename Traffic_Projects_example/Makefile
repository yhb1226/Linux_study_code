CC       = gcc
# 头文件路径：分别指定第一阶段和第二阶段头文件目录
CFLAGS   = -Wall -Wextra -g -IInc/First -IInc/Second

# 所有自定义头文件，方便追踪依赖
HEADERS  = Inc/First/pack.h Inc/First/protocol.h Inc/First/students_record.h \
           Inc/Second/hash_table.h

# 两个测试可执行文件
TARGET1  = test_protocol
TARGET2  = test_hash_table

# 第一阶段需要的目标文件
OBJS1    = pack.o test_protocol.o
# 第二阶段需要的目标文件（包含 hash_table 和测试文件，以及可能需要的 pack）
OBJS2    = hash_table.o test_hash_table.o pack.o

.PHONY: all clean

all: $(TARGET1) $(TARGET2)

# ===== 第一阶段：协议测试 =====
$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^

pack.o: src/First/pack.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

test_protocol.o: test/test_protocol.c Inc/First/pack.h Inc/First/protocol.h
	$(CC) $(CFLAGS) -c -o $@ $<

# ===== 第二阶段：哈希表测试 =====
$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^

hash_table.o: src/Second/hash_table.c Inc/Second/hash_table.h
	$(CC) $(CFLAGS) -c -o $@ $<

test_hash_table.o: test/test_hash_table.c Inc/Second/hash_table.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS1) $(OBJS2) $(TARGET1) $(TARGET2)