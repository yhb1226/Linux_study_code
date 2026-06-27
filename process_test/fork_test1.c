#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("父进程的ID号是%d\n",getpid());

    pid_t pid = fork();

    if(pid < 0)
    {
        perror(pid);

    }else if(pid == 0)//子进程
    {
        printf("我在子进程里面,我的子进程ID号是%d,我的父进程ID号是%d\n",getpid(),getppid());
        //在哪个进程里面，就是用的getpid返回的是哪个进程的ID号，如果要在子进程的代码里面返回父进程的ID号就是需要用pp

    }else{

        printf("我在父进程里面,我的子进程ID号是%d,我的父进程ID号是%d\n",fork(),getpid());


    }

    return 0;
}
