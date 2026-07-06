//静态锁用在完自己销毁，动态锁要手动销毁
//静态锁就是“开箱即用”的默认配置锁，无需销毁，伴随进程一生；动态锁则是你需要“手动组装、手动拆卸”的锁，胜在灵活，可以配置属性，也可以即用即弃。
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int share_data = 0;


void *read_lock(void *arg)
{
    pthread_rwlock_wrlock(&rwlock);
    printf("现在读取数据是%d\n",share_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *write_lock(void *arg)
{
    pthread_rwlock_wrlock(&rwlock);
    share_data ++;
    printf("现在写入数据是%d\n",share_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}


int main(int argc, char const *argv[])
{
    //读写锁初始化
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t write1,write2;
    pthread_t read[5];

    //创建两个写线程，更改num的数据
    pthread_create(&write1,NULL,write_lock,NULL);
    pthread_create(&write2,NULL,write_lock,NULL);

    //等待数据写完
    //sleep(2);
    pthread_join(write1,NULL);
    pthread_join(write2,NULL);

    //创建六个读线程，读取num的数据看最终是否准确
    for(int i=0; i<6; i++)
    {
        pthread_create(&read[i],NULL,read_lock,NULL);
    }
    
    for(int i=0; i<6; i++)
    {
        pthread_join(read[i],NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
