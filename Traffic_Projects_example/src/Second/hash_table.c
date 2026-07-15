#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 简单的字符串哈希函数（DJB2）
static unsigned int hash(const char *key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_TABLE_SIZE;
}

void hash_table_init(hash_table_t *ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

int hash_table_put(hash_table_t *ht, const char *key, student_record_t *rec) {
    unsigned int idx = hash(key);
    hash_node_t *cur = ht->buckets[idx];

    // 检查是否已存在相同 key，存在则更新
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            // 更新记录
            cur->record = *rec;
            return 0;
        }
        cur = cur->next;
    }

    // 不存在，创建新节点插入链表头部
    hash_node_t *node = (hash_node_t*)malloc(sizeof(hash_node_t));
    if (node == NULL) return -1;

    strncpy(node->key, key, sizeof(node->key) - 1);
    node->key[sizeof(node->key) - 1] = '\0';
    node->record = *rec;
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
    return 0;
}

student_record_t *hash_table_get(hash_table_t *ht, const char *key) {
    unsigned int idx = hash(key);
    hash_node_t *cur = ht->buckets[idx];
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            return &cur->record;
        }
        cur = cur->next;
    }
    return NULL;
}

int hash_table_delete(hash_table_t *ht, const char *key) {
    unsigned int idx = hash(key);
    hash_node_t *cur = ht->buckets[idx];
    hash_node_t *prev = NULL;

    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            if (prev == NULL) {
                ht->buckets[idx] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1; // 未找到
}

void hash_table_destroy(hash_table_t *ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_node_t *cur = ht->buckets[i];
        while (cur != NULL) {
            hash_node_t *next = cur->next;
            free(cur);
            cur = next;
        }
        ht->buckets[i] = NULL;
    }
}