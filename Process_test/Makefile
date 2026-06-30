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

fifo_read_test:fifo_read_test.c
	$(CC) -o $@ $^

clean:
	-rm $(objects)           # 清理中间文件