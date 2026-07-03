//避免他头竞态条件的方法
//1.避免多线程写入一个地址
//2.加锁
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

// 需要创建的多个线程
void * add_thread(void * arg){
    // 转化传入的参数
    int *p = (int *)arg;
    (*p)++;
    return (void *)0;
}

int main(int argc, char const *argv[])
{
    pthread_t pid[THREAD_COUNT];
    int num = 0;
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        // 创建的线程功能是给传入的参数累加1
        pthread_create(pid + i,NULL,add_thread,&num);
    }

    // 等待所有的线程执行完成
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(pid[i],NULL);
    }

    // 打印最终的累加结果
    printf("累加的结果是%d",num);

    return 0;
}