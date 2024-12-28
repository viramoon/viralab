#include <assert.h>
#include <string.h>
#include "utils.h"
#include "vector.h"
#define VECTOR_MAX_LENGTH 1024

static void freeVector(vectorHeader* this) {
	free(this -> mallocHead);
}

static void* indexVector(vectorHeader* this, int index) {
	return (void*)this + sizeof(vectorHeader) + index * this -> elementSize;
}

func funcs[] = {
	{.index = indexVector},
	{.free = freeVector}
};

void* createVector(int elesize, int length) {
	vectorHeader* ptr;
	uint16_t capcity = 32;
	uint16_t elesz = 1;
	assert(elesize);
	if (elesize <= CACHE_LINE_SIZE)
		for (; elesz < elesize; elesz <<= 1);
	else
		for (elesz = CACHE_LINE_SIZE; elesz < elesize; elesz += CACHE_LINE_SIZE);
	for (; capcity < length; capcity <<= 1);
	if (capcity > VECTOR_MAX_LENGTH)
		goto error;
	int totalLength = capcity * elesz + sizeof(vectorHeader);

	ptrWrapper* ptrs = alignedMalloc(totalLength, CACHE_LINE_SIZE);
	ptr = ptrs -> AlignedAddr;
	ptr -> funcs = funcs;
	ptr -> mallocHead = ptrs -> unAlignedAddr;
	ptr -> capacity = capcity;
	ptr -> size = length;
	ptr -> elementSize = elesz;
	return (void*)ptr;

	error:
		return NULL;
}

