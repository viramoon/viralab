#pragma once

typedef struct {
    void* unAlignedAddr;
    void* AlignedAddr;
} ptrWrapper;

ptrWrapper* alignedMalloc(int dataSize, int alignedSize);