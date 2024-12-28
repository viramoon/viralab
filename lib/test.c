#include "vector.h"
#include <string.h>
#include <assert.h>

char Buff[50];
typedef enum functions {
    enumVector = 0,
    enumMap
} functions;

int isInFunctions(char* input) {
    if (strcmp(input, "vector") == 0)
        return enumVector;
    if (strcmp(input, "map") == 0)
        return enumMap;
    return -1;
}

int testVector() {
    void* vector = createVector(8, 300);
    assert(vector);
    printf("malloc addr is %p\n", ((vectorHeader*)vector) -> mallocHead);
    printf("vector addr is %p\n", vector);
    printf("data addr is %p\n", vector + sizeof(vectorHeader));
    printf("vector capacity is %d\n", ((vectorHeader*)vector) -> capacity);
    printf("vectorHeader size is %d\n", sizeof(vectorHeader));
    uint8_t* ptr = (uint8_t*)(vector + sizeof(vectorHeader));
    ptr[0] = 2;
    ptr[1] = 6;
    ptr[6] = 10;
    for (int i = 0; i < 10; i++)
        printf("id %d stores %d\n", i, ptr[i]);
    ((vectorHeader*)vector) -> free(vector);
}

void getHelp() {
    fprintf(stdout, "avaiable options: vector map\n");
}

int main() {
    fprintf(stdout, "-------------------------------Test is starting---------------------------------\n");
    fprintf(stdout, "Please enter the function you want to test:\n");
    int funcId = -1;
    int ret = 0;
    while(funcId == -1) {
        getHelp();
        fgets(Buff, sizeof(Buff), stdin);
        if (Buff[strlen(Buff) - 1] == '\n')
            Buff[strlen(Buff) - 1] = '\0';
        else {
            fprintf(stdout, "too long!\n");
            continue;
        }
        funcId = isInFunctions(Buff);
    }

    switch (funcId) {
        case enumVector:
            ret = testVector();
            break;
        case enumMap:
            break;
        default:
            goto error;
    }

    return ret;

    error:
        return -1;
}