#include <stdio.h>
#include <time.h>
#include "array_table.h"   // 包含原来的哈希表和新的无序数组定义

// 生成测试数据量
#define TEST_SIZE 1000

int main() {
    // ========== 无序数组测试 ==========
    array_table_t at;
    array_table_init(&at);

    clock_t start = clock();

    // 插入 TEST_SIZE 条记录
    for (uint64_t i = 1; i <= TEST_SIZE; i++) {
        student_record_t rec;
        rec.student_id = i;
        snprintf(rec.name, MAX_NAME_LEN, "Student%llu", (unsigned long long)i);
        rec.score = (uint32_t)(i % 101);
        array_table_put(&at, i, &rec);
    }

    // 查找 TEST_SIZE 次
    for (uint64_t i = 1; i <= TEST_SIZE; i++) {
        student_record_t *p = array_table_get(&at, i);
        if (p == NULL) {
            printf("Array: 查找失败，不应该发生\n");
        }
    }

    clock_t end = clock();
    double array_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("无序数组：插入和查找 %d 条记录，耗时 %f 秒\n", TEST_SIZE, array_time);

    array_table_destroy(&at);

    // ========== 哈希表测试 ==========

    /*
    hash_table_t ht;
    hash_table_init(&ht);

    start = clock();

    // 插入
    for (uint64_t i = 1; i <= TEST_SIZE; i++) {
        student_record_t rec;
        rec.student_id = i;
        snprintf(rec.name, MAX_NAME_LEN, "Student%llu", (unsigned long long)i);
        rec.score = (uint32_t)(i % 101);

        char key[64];
        snprintf(key, sizeof(key), "%llu", (unsigned long long)i);
        hash_table_put(&ht, key, &rec);
    }

    // 查找
    for (uint64_t i = 1; i <= TEST_SIZE; i++) {
        char key[64];
        snprintf(key, sizeof(key), "%llu", (unsigned long long)i);
        student_record_t *p = hash_table_get(&ht, key);
        if (p == NULL) {
            printf("Hash: 查找失败，不应该发生\n");
        }
    }

    end = clock();
    double hash_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("哈希表：插入和查找 %d 条记录，耗时 %f 秒\n", TEST_SIZE, hash_time);

    hash_table_destroy(&ht);

    // 对比
    if (array_time > 0) {
        printf("哈希表比无序数组快 %.2f 倍\n", array_time / hash_time);
    }

    */
    
    return 0;
}