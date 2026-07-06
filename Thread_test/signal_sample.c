//信号量主要的目的是两个：1.互斥、2.同步
//两个信号量：1.二进制信号量(互斥)  2.计数信号量(有顺序)
//sem_init()0表示线程，1表示进程
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_THREADS 10
#define MAX_CONCURRENT 3

sem_t sem;  // 全局信号量

void* worker(void* arg) {
    long id = (long)arg;
    
    sem_wait(&sem);  // P操作：尝试获取一个许可（计数减1），若计数为0则阻塞
    
    // --- 临界区（最多 MAX_CONCURRENT 个线程同时执行）---
    printf("线程 %ld 开始工作...\n", id);
    sleep(2);  // 模拟耗时操作
    printf("线程 %ld 工作结束。\n", id);
    // --- 临界区结束 ---
    
    sem_post(&sem);  // V操作：释放许可（计数加1），唤醒一个等待线程
    return NULL;
}

int main() {
    pthread_t threads[TOTAL_THREADS];
    
    // 初始化信号量：线程间共享（第二个参数0），初始计数为 MAX_CONCURRENT
    sem_init(&sem, 0, MAX_CONCURRENT);
    
    // 创建 10 个线程
    for (long i = 0; i < TOTAL_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)i);
    }
    
    // 等待所有线程结束
    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&sem);  // 销毁信号量
    return 0;
}