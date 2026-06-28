#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char *name = "班长";
    printf("我是%s,我的编号是%d,我现在在一楼\n",name,getpid());

    pid_t pid = fork();
    if(pid == -1)
    {
        //报错退出
        perror("fork");
    }else if(pid == 0){
        //子进程
        char *args[] = {"/home/yhb/process_test/erlou_test",name,NULL};
        char *envs[] = {NULL};
        execve(args[0],args,envs);
        printf("我还是%s,我的编号是%d,我现在还是在子进程中\n",name,getppid());

    }else{
        //父进程
        printf("我还是%s,我的编号是%d,我现在还是在一楼\n",name,getpid());

    }
    
    return 0;
}
