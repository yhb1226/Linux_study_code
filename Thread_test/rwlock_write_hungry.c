//当一直在读取的时候是写入不了的，因此出现了写饥饿，本次代码为了避免写饥饿
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int turn = 1;   // 1 表示线程 A，2 表示线程 B
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


/*  写饥饿代码，一旦greedy强到之后就会死循环霸占
    void *greedy_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        shared++;
        pthread_mutex_unlock(&mutex);
        // 注释掉下面这行，饥饿更容易发生
        // usleep(1);  // 如果稍微休眠，给其他线程机会，饥饿会缓解
    }
    return NULL;
}

void *starving_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("我终于拿到锁了！\n");
        shared++;
        pthread_mutex_unlock(&mutex);
        sleep(1);  // 每次执行后睡眠，但依然很难拿到锁
    }
    return NULL;
}
*/

//改成条件变量+标志位交替进行

void *thread_A(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (turn != 1)
            pthread_cond_wait(&cond, &mutex);   // 等待轮到自己
        // 临界区
        turn = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void *thread_B(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (turn != 2)
            pthread_cond_wait(&cond, &mutex);
        // 临界区
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_A, NULL);
    pthread_create(&t2, NULL, thread_B, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}