#ifndef PACK_H
#define PACK_H

#include <stdint.h>
#include "protocol.h"

// 打包成绩上报载荷到 buf，返回写入字节数，不够返回 -1
int pack_score_payload(score_report_payload_t *p, uint8_t *buf, int max_len);

// 从 buf 解包到 p，返回消耗字节数，数据错误返回 -1
int unpack_score_payload(uint8_t *buf, int buf_len, score_report_payload_t *p);

// 组装完整消息（头 + 载荷），返回完整消息长度，不够返回 -1
int pack_message(uint8_t msg_type, uint8_t *payload, int payload_len,
                 uint8_t *out_buf, int max_len);

#endif