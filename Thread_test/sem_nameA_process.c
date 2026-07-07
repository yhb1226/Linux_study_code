#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main() {
    // 1. 创建/打开有名信号量，初值设为 0（进程间共享）
    sem_t *sem = sem_open("/init_sem", O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // 2. 模拟初始化工作（例如创建配置文件）
    printf("进程 A：开始初始化...\n");
    sleep(3);  // 模拟耗时操作
    int fd = open("data.txt", O_WRONLY | O_CREAT, 0644);
    if (fd >= 0) {
        write(fd, "重要数据\n", 10);
        close(fd);
    }
    printf("进程 A：初始化完成！\n");

    // 3. 发出“就绪”信号
    sem_post(sem);
    printf("进程 A：已通知进程 B\n");

    // 4. 清理
    sem_close(sem);
    return 0;
}