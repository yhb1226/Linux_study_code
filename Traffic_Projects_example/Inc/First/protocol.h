#include "students_record.h"   // 从这里拿到 MAX_NAME_LEN
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// 魔数：随便取一个4字节值
#define PROTO_MAGIC   0x53545544   // "STUD" 的 ASCII
#define PROTO_VERSION 1

// 消息类型
enum msg_type {
    MSG_SCORE_REPORT = 0x01,  // 成绩上报
    MSG_QUERY_REQ    = 0x02,  // 查询请求
    MSG_QUERY_RESP   = 0x03,  // 查询响应
    MSG_ACK          = 0xFF   // 确认
};

// 定长消息头（取消对齐填充，保证跨平台一致）
typedef struct {
    uint32_t magic;
    uint8_t  version;
    uint8_t  msg_type;
    uint16_t flags;
    uint32_t payload_len;   // 载荷长度（不含头）
} __attribute__((packed)) proto_header_t;

// 成绩上报的载荷结构体（网络传输用）
typedef struct {
    uint64_t student_id;
    char     name[MAX_NAME_LEN];
    uint32_t score;
} score_report_payload_t;

#endif