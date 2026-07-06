#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char sh_name[100] = {0};
    //保证创建的共享内存的唯一性，以/开头并且只能有一个/，后面加上进程号ID也是为了保证唯一性
    sprintf(sh_name,"/my_sh_name%d",getpid());

    //1.创建共享内存
    int fd = shm_open(sh_name,O_RDWR | O_CREAT,0664);//这里读写也不相同
    if(fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    //2.设置共享内存的大小
    ftruncate(fd,1024);

    //3.内存映射,用指针形式
    char *share = mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    /*
    flags：映射类型和特性。MAP_SHARED 表示共享映射，一个进程的修改会立即反映到其他映射同一对象的进程，且会更新到底层对象（共享内存）。另一种常用的是 MAP_PRIVATE（写时复制，不共享修改）。
    */
    if(share == MAP_FAILED)//共享内存返回值不同
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    //相当于是把标识符fd现在映射完成后转成share了直接操作share即可
    close(fd);

    pid_t cpid = fork();
    if(cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(cpid == 0)
    {
        sprintf(share,"你是个好父亲，儿子的编号是%d",getpid());
        printf("儿子回信完成\n");
        //子进程为避免混乱直接运行完成退出
        _exit(0);
    }else{
        //涉及到父子进程就要考虑waitpid()
        waitpid(cpid,NULL,0);
        printf("父亲收到儿子来信:%s,父亲此时ID号是%d\n",share,getpid());

        //5.释放映射区
        int re = munmap(share, 1024);
        if (re == -1)
        {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        //6.释放共享内存对象
        shm_unlink(sh_name);

    }




    return 0;
}


