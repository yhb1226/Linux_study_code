//静态锁用在完自己销毁，动态锁要手动销毁
//静态锁就是“开箱即用”的默认配置锁，无需销毁，伴随进程一生；动态锁则是你需要“手动组装、手动拆卸”的锁，胜在灵活，可以配置属性，也可以即用即弃。
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 静态初始化方式（可选，和动态init二选一）
// static pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
//1.创建动态读写锁
pthread_rwlock_t rwlock;
int shared_data = 0;

// 读线程：加读锁读取共享数据（读锁可被多个线程同时持有）
void * read_writer(void * arg){
    pthread_rwlock_rdlock(&rwlock);//2.读线程加锁
    printf("当前是%s, shared_data为%d\n", (char *)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

// 写线程：加写锁修改共享数据（写锁独占，同一时间仅一个写线程）
void * lock_writer(void * arg){
    pthread_rwlock_wrlock(&rwlock);//3.写线程加锁
    int tmp = shared_data + 1;
    sleep(1);
    shared_data = tmp;
    printf("当前是%s, shared_data为%d\n", (char *)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 4.动态初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t writer1, writer2;
    pthread_t reader1, reader2, reader3, reader4, reader5, reader6;

    // 创建2个写线程
    pthread_create(&writer1, NULL, lock_writer, "writer1");
    pthread_create(&writer2, NULL, lock_writer, "writer2");

    // 休眠等待写线程执行
    sleep(3);

    // 创建6个读线程
    pthread_create(&reader1, NULL, read_writer, "reader1");
    pthread_create(&reader2, NULL, read_writer, "reader2");
    pthread_create(&reader3, NULL, read_writer, "reader3");
    pthread_create(&reader4, NULL, read_writer, "reader4");
    pthread_create(&reader5, NULL, read_writer, "reader5");
    pthread_create(&reader6, NULL, read_writer, "reader6");

    // 等待所有子线程执行完毕
    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    // 5.销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}