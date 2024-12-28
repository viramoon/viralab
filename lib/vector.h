#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define CACHE_LINE_SIZE 64
//#define FUNC_SIZE 16

typedef struct vectorHeader {
    uint16_t size;
    uint16_t capacity;
    uint64_t elementSize;
    void* mallocHead;
    void (*free)(struct vectorHeader*);
} __attribute__((aligned(CACHE_LINE_SIZE))) vectorHeader;

void* createVector(int elesize, int length);