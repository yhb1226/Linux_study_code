#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

// 数组最大容量
#define MAX_RECORDS 1024

// 学生记录（保持不变）
#define MAX_NAME_LEN 32
typedef struct {
    uint64_t student_id;
    char     name[MAX_NAME_LEN];
    uint32_t score;
} student_record_t;

// 无序数组存储结构
typedef struct {
    student_record_t records[MAX_RECORDS];  // 存放记录的数组
    int count;                              // 当前已存了多少条记录
} array_table_t;

// 初始化
void array_table_init(array_table_t *at);

// 插入或更新
int array_table_put(array_table_t *at, uint64_t student_id, student_record_t *rec);

// 查找（按学号）
student_record_t *array_table_get(array_table_t *at, uint64_t student_id);

// 删除
int array_table_delete(array_table_t *at, uint64_t student_id);

// 销毁（数组版本什么都不用做，这里保留接口统一）
void array_table_destroy(array_table_t *at);

#endif