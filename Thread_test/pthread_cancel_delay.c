//取消函数pthread_cancel(),向子线程发送取消消息，当子线程运行到规定的取消消息函数pthread_testcancel()时候才会真正的取消子线程
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * task(void * arg){
    printf("thread started\n");
    // 默认取消类型是延迟
    printf("working...");
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
    //取消子线程是否成功的标志位
    if (res == PTHREAD_CANCELED)
    {
        printf("线程被取消\n");
    }else {
        printf("线程还没有被取消 exit code %ld",(long)res);
    }

    return 0;
}