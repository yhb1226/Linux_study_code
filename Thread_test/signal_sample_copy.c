//计数例子，如果需要改成互斥则直接把它变成每次只允许进一个即可
//信号量主要的目的是两个：1.互斥、2.计数、3.同步
//sem_init()0表示线程，1表示进程
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;//全局信号量

void *signal_test(void *arg)
{
    int num = (int)(long)arg;
    sem_wait(&sem);
    printf("线程%d开始工作\n",num);
    sleep(2);
    printf("线程%d结束工作\n",num);
    sem_post(&sem);
    return NULL;
}


int main(int argc, char const *argv[])
{
    sem_init(&sem,0,4);
    //使用十个线程
    pthread_t pid[10];

    for(int i=0;i<10;i++)
    {   //int 4字节，void*8字节，先转成long这种八字节保证安全
        pthread_create(&pid[i],NULL,signal_test,(void*)(long)i);
    }

    for(int i=0;i<10;i++)
    {
        pthread_join(pid[i],NULL);
    }
    
    sem_destroy(&sem);

    return 0;
}
