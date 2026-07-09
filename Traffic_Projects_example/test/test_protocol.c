#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pack.h"
#include <arpa/inet.h>

int main() {
    // 准备原始数据
    score_report_payload_t orig;
    orig.student_id = 20210001;
    strcpy(orig.name, "张三");
    orig.score = 95;

    // 测试1：打包再解包，字段应该一致
    uint8_t buf[256];
    int len = pack_score_payload(&orig, buf, sizeof(buf));
    assert(len > 0);

    score_report_payload_t restored;
    memset(&restored, 0, sizeof(restored));
    int ret = unpack_score_payload(buf, len, &restored);
    assert(ret == len);
    assert(orig.student_id == restored.student_id);
    assert(strcmp(orig.name, restored.name) == 0);
    assert(orig.score == restored.score);
    printf("Test1 passed: pack/unpack consistency\n");

    // 测试2：完整消息组装
    uint8_t msg_buf[512];
    int msg_len = pack_message(MSG_SCORE_REPORT, buf, len, msg_buf, sizeof(msg_buf));
    assert(msg_len > 0);
    assert((size_t)msg_len == sizeof(proto_header_t) + len);
    proto_header_t *hdr = (proto_header_t*)msg_buf;
    assert(ntohl(hdr->magic) == PROTO_MAGIC);
    assert(hdr->version == PROTO_VERSION);
    assert(hdr->msg_type == MSG_SCORE_REPORT);
    assert(ntohl(hdr->payload_len) == (uint32_t)len);
    printf("Test2 passed: full message header\n");

    // 测试3：边界条件
    assert(pack_score_payload(&orig, buf, 5) == -1);          // 缓冲区太小
    assert(unpack_score_payload(buf, 10, &restored) == -1);   // 数据不足
    printf("Test3 passed: boundary checks\n");

    printf("All tests passed!\n");
    return 0;
}