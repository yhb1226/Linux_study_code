//此代码具有大问题，当在生产者时候会陷入死循环，互斥锁直接锁住了
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        pthread_mutex_lock(&mutex);

        // ❌ 错误：持有锁的时候忙等条件
        while (count == BUFFER_SIZE) {
            // 什么都不做，就是死等
            // 此时锁没有被释放！
        }

        // 永远不会执行到这里，因为上面死循环了
        buffer[count++] = item++;
        printf("白月光发送了一个幸运数字%d\n", buffer[count - 1]);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // ❌ 错误：持有锁的时候忙等条件
        while (count == 0) {
            // 死等
        }

        printf("我收到白月光的幸运数字为%d\n", buffer[--count]);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t pt, ct;
    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);

    pthread_join(pt, NULL);
    pthread_join(ct, NULL);
    return 0;
}
