#pragma once
#include "include.h"

struct hashNode {
    char* hash;
    int count;
    hashNode* nextNode;
};

struct hashMap {
    int totalNode;
    hashNode* firstNode;
    hashNode* lastNode;
};

// Ham tao mot hashmap moi.
hashMap* createHashMap();

// Ham tao mot hashnode.
hashNode* createHashNode(const char*);

// Ham tim xem hash co ton tai trong hashmap hay khong.
hashNode* findInHashMap(hashMap*, const char*);

// Ham push mot hash vao hashmap.
void pushToHashMap(hashMap*&, const char*);

// Ham giai phong bo nho hashmap.
void releaseHashMap(hashMap*&);

// Ham xoa node dau hashmap (dung de giai phong hashmap).
void deleteFirstHashmapNode(hashMap*&);