CC := gcc


create_test:create_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

terminate_test:terminate_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@ 

pthread_detach_test:pthread_detach_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@ 

pthread_cancel_delay:pthread_cancel_delay.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

pthread_cancel_async_test:pthread_cancel_async_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

race_condition_test:race_condition_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

race_condition_revise_test:race_condition_revise_test.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@

rwlock_test_write_unlock:rwlock_test_write_unlock.c
	$(CC) -o $@ $^
	./$@
	-rm ./$@