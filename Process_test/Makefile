CC := gcc

system_test:system_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

fork_test:fork_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

fork1_test:fork1_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

erlou_test:erlou_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

execve_test:execve_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@
execve1_test:execve1_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@
fork_execve_test:fork_execve_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

fork_execve_test1:fork_execve_test1.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

unnamed_pipe_test:unnamed_pipe_test.c
	$(CC) -o $@ $^
	./$@ test
	-rm ./$@

unnamed_pipe_test_copy:unnamed_pipe_test_copy.c
	$(CC) -o $@ $^
	./$@ test
	-rm ./$@


fifo_write_test:fifo_write_test.c
	$(CC) -o $@ $^

fifo_write_test_copy:fifo_write_test_copy.c
	$(CC) -o $@ $^



fifo_read_test:fifo_read_test.c
	$(CC) -o $@ $^


fifo_read_test_copy:fifo_read_test_copy.c
	$(CC) -o $@ $^



shared_memory:shared_memory.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

shared_memory_copy:shared_memory_copy.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@


mq_test:mq_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

signal_test:signal_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@	

producer:producer.c
	$(CC) -o $@ $^

consumer:consumer.c
	$(CC) -o $@ $^

clean:
	-rm $(objects)           # 清理中间文件