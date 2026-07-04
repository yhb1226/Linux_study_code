//避免他头竞态条件的方法
//1.避免多线程写入一个地址
//2.加锁
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CONUT_PTHREAD 1000000

void *add_num(void* arg)
{

    int *i = (int *)arg;
    (*i)++;
    return NULL;
}

int main(int argc, char const *argv[])
{
    
    int num=0;
    pthread_t pid[CONUT_PTHREAD];

    for(int i=0;i<CONUT_PTHREAD;i++)
    {
        pthread_create(&pid[i],NULL,add_num,&num);
    }

    for(int i=0;i<CONUT_PTHREAD;i++)
    {
        pthread_join(pid[0],NULL);
    }

    printf("累加结果是：%d",num);

    return 0;
}
