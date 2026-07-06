#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t ready_sem;   // 信号量：初值为0，用于通知“准备工作已完成”

void *thread_A(void *arg) {
    printf("线程A:开始初始化资源...\n");
    sleep(2);                       // 模拟耗时的初始化工作
    printf("线程A:初始化完成！\n");
    sem_post(&ready_sem);           // V操作：发出“准备就绪”信号
    return NULL;
}

void *thread_B(void *arg) {
    printf("线程B:等待初始化完成...\n");
    sem_wait(&ready_sem);           // P操作：等待信号，若还未就绪则阻塞
    printf("线程B:收到就绪信号，开始工作！\n");
    // 执行依赖初始化的操作...
    return NULL;
}

int main() {
    pthread_t ta, tb;
    sem_init(&ready_sem, 0, 0);     // 初值为0，表示“尚未就绪”

    pthread_create(&ta, NULL, thread_A, NULL);
    pthread_create(&tb, NULL, thread_B, NULL);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    sem_destroy(&ready_sem);
    return 0;
}