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

    char *avgs[] = {"/home/yhb/process_test/erlou_test",name,NULL};
    char *envs[] = {NULL};

    int exr = execve(avgs[0],avgs,envs);

    if(exr == -1)
    {
        perror("execve");
        return 1;
    }

    
    return 0;
}

