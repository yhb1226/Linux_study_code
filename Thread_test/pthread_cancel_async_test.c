//异步取消非常危险，一般来说使用取消点函数进行取消子线程，并且异步取消时候是不等某一行代码运行完成的
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * task(void * arg){
    printf("thread started\n");
    // 默认取消类型是延迟
    /*
        pthread_setcanceltype 用于设置当前线程的取消类型（cancelability type）。它有两个参数：

        第一个参数是取消类型常量：

        PTHREAD_CANCEL_DEFERRED（默认）：延迟取消，取消请求只在线程到达取消点时才生效。

        PTHREAD_CANCEL_ASYNCHRONOUS：异步取消，取消请求可立即中断线程，无论线程执行到何处。

        第二个参数（通常传 NULL）用于保存之前的取消类型，一般不需要。
    */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    printf("working...\n");
    sleep(1);
    // 人为调用取消点函数
    pthread_testcancel();
    printf("after cancelled\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 取消子线程
    if (pthread_cancel(tid) != 0)
    {
        perror("pthread_cancel");
    }
    
    void * res;
    // pthread_cancel只是发出一个停止的命令
    pthread_join(tid,&res);

    if (res == PTHREAD_CANCELED)
    {
        printf("线程被取消\n");
    }else {
        printf("线程还没有被取消 exit code %ld",(long)res);
    }

    return 0;
}