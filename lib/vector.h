#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define CACHE_LINE_SIZE 64
#define FUNC_SIZE 16

struct vectorHeader;

typedef void* (*func1)(struct vectorHeader*, int index);
typedef void (*func2)(struct vectorHeader*);
typedef enum {
    INDEX = 0,
    FREE
} funcType;

typedef union {
    func1 index;
    func2 free;
} func;

typedef struct vectorHeader{
    uint16_t size;
    uint16_t capacity;
    uint64_t elementSize;
    void* mallocHead;
    func* funcs;
} __attribute__((aligned(CACHE_LINE_SIZE))) vectorHeader;

void* createVector(int elesize, int length);