#include <stdio.h>
#include <signal.h>
#include <unistd.h>


//类似于中断，但是为什么我的不高不会停止呢
void sigint_handler(int signum){
    printf("\n受到%d信号 停止程序\n",signum);
    exit(signum);
}

int main(int argc, char const *argv[])
{
    if ( signal(SIGINT,sigint_handler) == SIG_ERR)
    {
        perror("signal");
        return 1;
    }

    while (1)
    {
        sleep(1);
        printf("你好,在吗\n");
    }

    return 0;
}

