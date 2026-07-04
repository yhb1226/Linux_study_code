#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

//定义将结构体为了返回接收两个线程函数的参数
typedef struct RESULT{
    char *serial;
    int lens;
}RESULT;

void *red_flower_pthread(void *arg)
{
    RESULT *result = malloc(sizeof(RESULT));
    //arg 的类型是 void *（通用指针），它只保存地址，但编译器不知道它指向什么类型的数据，因此人为规定成char类型数据
    char code = *((char *)arg);
    char *ans = malloc(100);
    /*
    * 功能：读取一行字符串
    * char *s：存放读取结果的字符数组地址
    * int size：最多读取的字符数（含结尾 '\0'）
    * FILE *stream：输入流，键盘用 stdin
    * return：成功返回 s，失败或读到文件尾返回 NULL
    */

    fgets(ans,100,stdin);
    
    if(ans[0] == code)
    {
        free (ans);
        printf("红玫瑰离开了\n");
        char *readen = strdup("红玫瑰去了巴黎\n");//readen是一个字符指针，保存字符串的首地址，并在后面的代码当中把它复制给serial
        result->lens = strlen(readen);
        result->serial = readen;
        //返回故事结果
        pthread_exit((void *)result);

    }else{

        printf("红玫瑰还在等你\n");

    }

}

void *white_flower_pthread(void *arg)
{
    //配置结构体变量
    RESULT *result = malloc(sizeof(RESULT));
    char code = *((char *)arg);
    char *ans = malloc(100);

    fgets(ans,100,stdin);

    if(ans[0] == code)
    {
        free(ans);
        printf("白玫瑰离开了\n");
        char *readen = strdup("白玫瑰去了巴黎\n");
        result->lens = strlen(readen);
        result->serial = readen;
        pthread_exit((void *)result);
    }else{

        printf("白玫瑰还在等你\n");
    }

}

int main(int argc, char const *argv[])
{
    //声明线程ID
    pthread_t red_flower;
    pthread_t white_flower;
    char red_code = 'r';
    char white_code = 'w';
    //接收返回变量的指针
    RESULT *red_result = NULL;
    RESULT *white_result = NULL;

    pthread_create(&red_flower,NULL,red_flower_pthread,&red_code);
    pthread_create(&white_flower,NULL,white_flower_pthread,&white_code);


    pthread_join(red_flower,(void**)&red_result);
    printf("红玫瑰故事的结局%d是:%s", red_result->lens, red_result->serial);
    free(red_result->serial);
    free(red_result);

    pthread_join(white_flower,(void**)&white_result);
    printf("白玫瑰故事的结局%d是:%s", white_result->lens, white_result->serial);
    free(white_result->serial);
    free(white_result);



    return 0;
}

