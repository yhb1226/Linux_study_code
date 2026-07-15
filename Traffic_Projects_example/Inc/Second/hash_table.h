#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

#define HASH_TABLE_SIZE 1024   // 哈希桶数量

// 学生记录（和第一阶段一致）
#define MAX_NAME_LEN 32
typedef struct {
    uint64_t student_id;          // 学号，作为哈希表的键
    char     name[MAX_NAME_LEN];
    uint32_t score;
} student_record_t;

// 哈希表节点
typedef struct hash_node {
    char key[64];                // 键的字符串形式（学号转成字符串）
    student_record_t record;     // 值：完整的记录
    struct hash_node *next;      // 链表指针
} hash_node_t;

// 哈希表结构
typedef struct {
    hash_node_t *buckets[HASH_TABLE_SIZE];  // 桶数组
} hash_table_t;

// 初始化哈希表（所有桶置空）
void hash_table_init(hash_table_t *ht);

// 插入或更新记录，key 由调用者传入（学号字符串）
// 返回 0 成功，-1 失败
int hash_table_put(hash_table_t *ht, const char *key, student_record_t *rec);

// 根据 key 查找记录，返回指向记录的指针，未找到返回 NULL
student_record_t *hash_table_get(hash_table_t *ht, const char *key);

// 删除指定 key 的记录，返回 0 成功，-1 未找到
int hash_table_delete(hash_table_t *ht, const char *key);

// 释放整个哈希表内存
void hash_table_destroy(hash_table_t *ht);

#endif