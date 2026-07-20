#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash_table.h"

int main() {
    hash_table_t ht;
    hash_table_init(&ht);

    // 准备几条学生记录
    student_record_t s1 = { .student_id = 1001, .name = "Alice", .score = 90 };
    student_record_t s2 = { .student_id = 1002, .name = "Bob",   .score = 85 };
    student_record_t s3 = { .student_id = 1003, .name = "Carol", .score = 95 };

    // 测试1：插入和查找
    char key1[64], key2[64], key3[64];
    snprintf(key1, sizeof(key1), "%llu", (unsigned long long)s1.student_id);
    snprintf(key2, sizeof(key2), "%llu", (unsigned long long)s2.student_id);
    snprintf(key3, sizeof(key3), "%llu", (unsigned long long)s3.student_id);

    assert(hash_table_put(&ht, key1, &s1) == 0);
    assert(hash_table_put(&ht, key2, &s2) == 0);
    assert(hash_table_put(&ht, key3, &s3) == 0);

    student_record_t *found = hash_table_get(&ht, key2);
    assert(found != NULL);
    assert(found->student_id == 1002);
    assert(strcmp(found->name, "Bob") == 0);
    assert(found->score == 85);
    printf("Test1 passed: insert and find\n");

    // 测试2：查找不存在的 key 返回 NULL
    assert(hash_table_get(&ht, "9999") == NULL);
    printf("Test2 passed: non-existent key returns NULL\n");

    // 测试3：更新已存在的记录
    student_record_t s2_updated = { .student_id = 1002, .name = "Bob", .score = 99 };
    assert(hash_table_put(&ht, key2, &s2_updated) == 0);
    found = hash_table_get(&ht, key2);
    assert(found->score == 99);
    printf("Test3 passed: update existing record\n");

    // 测试4：删除记录
    assert(hash_table_delete(&ht, key1) == 0);
    assert(hash_table_get(&ht, key1) == NULL);
    printf("Test4 passed: delete record\n");

    // 测试5：删除不存在记录返回 -1
    assert(hash_table_delete(&ht, "9999") == -1);
    printf("Test5 passed: delete non-existent key\n");

    // 清理
    hash_table_destroy(&ht);
    printf("All tests passed!\n");







    
    //额外测试程序
    // // 1. 打包一条学生记录（发送方做的事）
    // uint8_t buf[256];
    // int len = pack_score_payload(&s1, buf, sizeof(buf));

    // // 2. 模拟网络传输... 然后接收方解包
    // student_record_t received;
    // unpack_score_payload(buf, len, &received);

    // // 3. 存入哈希表
    // hash_table_put(&ht, key1, &received);

    // // 4. 查询出来验证
    // student_record_t *p = hash_table_get(&ht, key1);
    // assert(p->score == 90);


    
    return 0;
}