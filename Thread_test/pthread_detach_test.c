//pthread_detach不会像pthread_join一样阻塞等待，让子线程可以独立回收，的那时如果主线程先于子线程结束也会杀死子线程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * task(void * arg){ 
    printf("thread started\n");
    sleep(2);
    printf("thread finished\n");
    return NULL;
}

//主线程需要等待子线程的版本
int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 使用detach标记会等待线程完成之后回收相关资源
    pthread_detach(tid);

    // 主线程运行完成比创建的子线程慢
    printf("main thread continues\n");

    sleep(3);// 因为主线程不会在pthread_detach等待 如果父线程先结束 会强制杀死子线程

    printf("main thread ending");

    return 0;
}