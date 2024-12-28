#include "vector.h"
#include <string.h>
#define VECTOR_MAX_LENGTH 1024

static void freeVector(vectorHeader* this) {
	free(this -> mallocHead);
}

void* createVector(int elesize, int length) {
	vectorHeader* ptr;
	uint16_t capcity = 32;
	for (; capcity < length; capcity <<= 1);
	if (capcity > VECTOR_MAX_LENGTH)
		goto error;
	int totalLength = capcity * elesize + sizeof(vectorHeader);

	void* head = malloc(CACHE_LINE_SIZE + totalLength - 1);
	memset(head, 0, CACHE_LINE_SIZE + totalLength - 1);
	uintptr_t addr = (uintptr_t)head;
	ptr = (vectorHeader*)((addr + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE-1));

	ptr -> mallocHead = head;
	ptr -> capacity = capcity;
	ptr -> elementSize = length;
	ptr -> free = freeVector;
	return ptr;

	error:
		return NULL;
}

