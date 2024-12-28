#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"

ptrWrapper* alignedMalloc(int dataSize, int alignedSize) {
    void* head = malloc(dataSize);
	memset(head, 0, dataSize);
	uintptr_t addr = (uintptr_t)head;
	void* alignedHead = (void*)((addr + alignedSize - 1) & ~(alignedSize-1));
    return (ptrWrapper*)(&(ptrWrapper){
                                    .unAlignedAddr = head, 
                                    .AlignedAddr = alignedHead
                                    });
}