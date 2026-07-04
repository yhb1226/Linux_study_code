#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define BUF_LEN  1024

volatile int has_data = 0;   // 0：无新数据   1：有新数据待处理
char *buf;

void *input(void *arg)
{
    char local_buf[BUF_LEN];

    while(1)
    {
        
        memset(local_buf,0,100);
        //输入线程阻塞等待读取
        ssize_t read_num = read(STDIN_FILENO,local_buf,BUF_LEN -1);
        //读取结果判断
        if(read_num == -1)
        {   
            perror("read");
            exit(EXIT_FAILURE);
            
        }else if(read_num == 0){
            
            printf("写入线程准备结束退出\n");
            has_data = 2;
            break;

        }else{
            local_buf[read_num] = '\0';
            strncpy(buf,local_buf,BUF_LEN -1);
            buf[BUF_LEN - 1] = '\0'; //数组是到1023的不到1024
            has_data = 1;
            printf("输入线程已写入消息\n");
            while(has_data) 
            usleep(100);
        }
    }
    return NULL;
}

void *output(void *arg)
{   

    while(1)
    {
        if(has_data == 1)
        {
            write(STDOUT_FILENO,buf,BUF_LEN);
            printf("输出端已接收数据并输出\n");
            has_data = 0;
        }else if(has_data == 2){

            printf("输出端准备退出");
            has_data = 0;
            break;

        }else{

            usleep(100);

        }
 
    }  

    return NULL;
}


int main(int argc, char const *argv[])
{
    buf = calloc(BUF_LEN,1);

    //线程ID
    pthread_t pid_input;
    pthread_t pid_output;

    /*
        int pthread_create(
        pthread_t *thread,          // 第1个：存放新线程ID的变量地址
        const pthread_attr_t *attr, // 第2个：线程属性，一般填 NULL
        void *(*start_routine)(void *), // 第3个：线程要执行的函数名
        void *arg                   // 第4个：传给线程函数的参数
        );
    */
   //读线程
    pthread_create(&pid_input,NULL,input,NULL);
    //写线程
    pthread_create(&pid_output,NULL,output,NULL);

    //等待线程结束
    pthread_join(pid_input,NULL);
    pthread_join(pid_output,NULL);

    free(buf);

    return 0;
}
