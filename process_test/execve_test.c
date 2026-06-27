#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    // 跳转之前
    char *name = "banzhang";
    printf("我是%s 编号%d,我现在还在一楼\n", name, getpid());

    // 执行跳转
    /*
     * const char *__path: 执行程序的路径
     * char *const __argv[]: 传入的参数 -> 对应执行程序main方法的第二个参数
     *     (1): 第一个参数固定是程序的名称 -> 执行程序的路径
     *     (2): 执行程序需要传入的参数
     *     (3): 最后一个参数一定是NULL
     * char *const __envp[]: 传递的环境变量
     *     (1): 环境变量参数: key=value
     *     (2): 最后一个参数一定是NULL
     * return: 成功根本没办法返回   下面的代码也没有意义
     *         失败返回-1
     * int execve (const char *__path, char *const __argv[], char *const __envp[])
     */
 

    char *args[] = {"/home/yhb/process_test/erlou_test", name, NULL};
    char *envs[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin", NULL};
    int re = execve(args[0], args, envs);
    if (re == -1)
    {
        perror("execve");
        return 1;
    }

    // 此处的代码没有意义 因为程序跳转了 不会再往下执行了
    return 0;
}