#include "array_table.h"   // 你头文件名字也可以改成 array_table.h，这里为了衔接暂且包含原来的
#include <string.h>
#include <stdlib.h>

void array_table_init(array_table_t *at) {
    at->count = 0;
}

int array_table_put(array_table_t *at, uint64_t student_id, student_record_t *rec) {
    // 1. 先遍历数组，看是否已存在相同学号
    for (int i = 0; i < at->count; i++) {
        if (at->records[i].student_id == student_id) {
            // 找到了，更新
            at->records[i] = *rec;
            return 0;
        }
    }

    // 2. 不存在，检查数组是否满了
    if (at->count >= MAX_RECORDS) {
        return -1;  // 数组已满，无法插入
    }

    // 3. 追加到数组末尾
    at->records[at->count] = *rec;
    at->count++;
    return 0;
}

student_record_t *array_table_get(array_table_t *at, uint64_t student_id) {
    // 遍历整个数组，逐个比对学号
    for (int i = 0; i < at->count; i++) {
        if (at->records[i].student_id == student_id) {
            return &at->records[i];  // 返回指向该记录的指针
        }
    }
    return NULL;  // 没找到
}

int array_table_delete(array_table_t *at, uint64_t student_id) {
    // 找到要删除的记录的位置
    for (int i = 0; i < at->count; i++) {
        if (at->records[i].student_id == student_id) {
            // 把最后一个元素搬到当前位置，覆盖掉要删除的记录
            at->records[i] = at->records[at->count - 1];
            at->count--;
            return 0;
        }
    }
    return -1;  // 没找到
}

void array_table_destroy(array_table_t *at) {
    // 数组版不需要释放动态内存，置零即可
    at->count = 0;
}