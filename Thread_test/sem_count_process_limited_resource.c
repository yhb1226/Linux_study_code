#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "用法: %s <进程名>\n", argv[0]);
        exit(1);
    }
    char *name = argv[1];

    // 1. 打开或创建有名信号量，初值设为 3（最多允许 3 个进程同时使用）
    sem_t *sem = sem_open("/db_conn_sem", O_CREAT, 0644, 3);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // 2. 模拟每个进程尝试连接 2 次
    for (int i = 0; i < 2; i++) {
        printf("[%s] 尝试获取数据库连接（第%d次）...\n", name, i+1);
        sem_wait(sem);   // 获取一个令牌，若没有则阻塞

        // --- 临界区（最多 3 个进程同时在这里）---
        printf("[%s] ✓ 获得连接，开始使用数据库...\n", name);
        sleep(2);   // 模拟执行查询等操作
        printf("[%s] 使用完毕，释放连接\n", name);
        // --- 临界区结束 ---

        sem_post(sem);   // 归还令牌
        sleep(1);   // 模拟两次连接之间的间隔
    }

    // 3. 清理（最后一个进程退出后应由外部删除信号量，这里简单处理）
    sem_close(sem);
    // 注意：通常由第一个创建的进程负责 sem_unlink，这里为了简便略过
    return 0;
}