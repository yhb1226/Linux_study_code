#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int pipefd[2];
    pid_t cpid ;
    if(argc != 2)
    {
        return 1;
        exit(EXIT_FAILURE);
    }


    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if(cpid == -1)
    {
    perror("fork");
    exit(EXIT_FAILURE);
    }else if(cpid == 0)
    {
        //子进程读取数据
        close(pipefd[1]);
        char str; 
        printf("我是子进程，下面是我接收到的数据\n");

        while(read(pipefd[0],&str,1)>0)
        {
            write(STDOUT_FILENO,&str,1);
        }
        printf("\n");
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    }else{
        //父进程写入数据
        close(pipefd[0]);
        char *sentence = "这是我给你子进程的数据";
        write(pipefd[1],sentence,strlen(sentence));
        close(pipefd[1]);
        waitpid(cpid,NULL,0);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
