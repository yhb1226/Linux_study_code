//自旋锁，用在线程执行代码极短的情况
#include <stdio.h>
#include <pthread.h>

pthread_spinlock_t spinlock;   // 自旋锁变量
int shared_counter = 0;

void *worker(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_spin_lock(&spinlock);    // 获取自旋锁
        shared_counter++;                // 临界区（极短）
        pthread_spin_unlock(&spinlock);  // 释放自旋锁
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);  // 初始化自旋锁

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("最终计数: %d\n", shared_counter);  // 输出 200000

    pthread_spin_destroy(&spinlock);
    return 0;
}