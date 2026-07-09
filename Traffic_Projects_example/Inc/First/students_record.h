#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include <stdint.h>

#define MAX_NAME_LEN 32

typedef struct {
    uint64_t student_id;          // 学号
    char     name[MAX_NAME_LEN];  // 姓名
    uint32_t score;               // 分数
} student_record_t;

#endif