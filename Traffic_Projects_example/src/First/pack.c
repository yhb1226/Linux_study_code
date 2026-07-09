#include "pack.h"
#include <string.h>
#include <arpa/inet.h>   // htons, htonl
#include <endian.h>      // htobe64, be64toh (Linux)

int pack_score_payload(score_report_payload_t *p, uint8_t *buf, int max_len) {
    // 计算所需长度：8 + 32 + 4 = 44 字节
    int need = sizeof(uint64_t) + MAX_NAME_LEN + sizeof(uint32_t);
    if (max_len < need) return -1;

    int offset = 0;

    // 写入 student_id (64位，转网络字节序)
    uint64_t id_be = htobe64(p->student_id);
    memcpy(buf + offset, &id_be, sizeof(id_be));
    offset += sizeof(id_be);

    // 写入 name（定长数组，直接拷贝）
    memcpy(buf + offset, p->name, MAX_NAME_LEN);
    offset += MAX_NAME_LEN;

    // 写入 score (32位，转网络字节序)
    uint32_t score_be = htonl(p->score);
    memcpy(buf + offset, &score_be, sizeof(score_be));
    offset += sizeof(score_be);

    return offset;   // 实际写入长度
}

int unpack_score_payload(uint8_t *buf, int buf_len, score_report_payload_t *p) {
    int need = sizeof(uint64_t) + MAX_NAME_LEN + sizeof(uint32_t);
    if (buf_len < need) return -1;

    int offset = 0;

    // 读取 student_id
    uint64_t id_be;
    memcpy(&id_be, buf + offset, sizeof(id_be));
    p->student_id = be64toh(id_be);
    offset += sizeof(id_be);

    // 读取 name
    memcpy(p->name, buf + offset, MAX_NAME_LEN);
    p->name[MAX_NAME_LEN - 1] = '\0'; // 确保结束符
    offset += MAX_NAME_LEN;

    // 读取 score
    uint32_t score_be;
    memcpy(&score_be, buf + offset, sizeof(score_be));
    p->score = ntohl(score_be);
    offset += sizeof(score_be);

    return offset;
}

int pack_message(uint8_t msg_type, uint8_t *payload, int payload_len,
                 uint8_t *out_buf, int max_len) {
    int total_len = sizeof(proto_header_t) + payload_len;
    if (max_len < total_len) return -1;

    // 填充头部
    proto_header_t hdr;
    hdr.magic       = htonl(PROTO_MAGIC);   // 网络字节序
    hdr.version     = PROTO_VERSION;
    hdr.msg_type    = msg_type;
    hdr.flags       = 0;                   // 暂无标志
    hdr.payload_len = htonl(payload_len);

    memcpy(out_buf, &hdr, sizeof(hdr));
    memcpy(out_buf + sizeof(hdr), payload, payload_len);

    return total_len;
}