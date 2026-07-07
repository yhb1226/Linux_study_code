#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main() {
    // 1. 打开同一个有名信号量（不创建，等待进程A创建）
    sem_t *sem = sem_open("/init_sem", 0);  // 0 表示只打开已有
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // 2. 等待进程 A 发出初始化完成的信号
    printf("进程 B：等待初始化完成...\n");
    sem_wait(sem);   // 阻塞直到 sem_post
    printf("进程 B：收到就绪信号，开始工作！\n");

    // 3. 读取进程 A 准备好的数据
    int fd = open("data.txt", O_RDONLY);
    if (fd >= 0) {
        char buf[100];
        ssize_t n = read(fd, buf, sizeof(buf)-1);
        if (n > 0) {
            buf[n] = '\0';
            printf("进程 B 读到数据：%s", buf);
        }
        close(fd);
    }

    // 4. 清理信号量（最后一个进程负责删除）
    sem_close(sem);
    sem_unlink("/init_sem");  // 销毁有名信号量
    return 0;
}