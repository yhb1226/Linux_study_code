//用信号量实现交替进行

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

sem_t *full;
sem_t *empty;

int shard_num;

int rand_num(){
    srand(time(NULL));
    return rand();
}

void * producer(void * arg){
    for (size_t i = 0; i < 5; i++)
    {
        // 获取信号量
        sem_wait(empty);
        printf("\n第%ld轮数据传输\n", i + 1);
        sleep(1);
        shard_num = rand_num();
        // 释放信号量
        sem_post(full);
    }
}

void * consumer(void * arg){
    for (size_t i = 0; i < 5; i++)
    {
        // 获取信号量
        sem_wait(full);
        printf("\n第%ld轮消费者开始读取数据\n", i + 1);
        sleep(1);
        printf("接收到的数字是%d", shard_num);
        // 释放信号量
        sem_post(empty);
    }
}

int main(int argc, char const *argv[])
{
    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));

    // 初始化信号量
    sem_init(empty, 0, 1);//最开始可以减1
    sem_init(full, 0, 0);//最开始不可以减1

    // 创建生产者和消费者的线程
    pthread_t producer_id, consumer_id;
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);

    // 等待线程全部执行完成
    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);

    // 代码最后摧毁信号量
    sem_destroy(empty);
    sem_destroy(full);

    return 0;
}