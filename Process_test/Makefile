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

clean:
	-rm $(objects)           # 清理中间文件