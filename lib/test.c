#include <assert.h>
#include <string.h>
#include "vector.h"

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
    void* vector = createVector(10, 300);
    assert(vector);
    printf("malloc addr is %p\n", ((vectorHeader*)vector) -> mallocHead);
    printf("vector addr is %p\n", vector);
    printf("data addr is %p\n", vector + sizeof(vectorHeader));
    printf("vector capacity is %d\n", ((vectorHeader*)vector) -> capacity);
    printf("vectorHeader size is %d\n", sizeof(vectorHeader));
    printf("data 0 addr is %p\n", (((vectorHeader*)vector) -> funcs[INDEX]).index(vector, 0));
    printf("data 1 addr is %p\n", (((vectorHeader*)vector) -> funcs[INDEX]).index(vector, 1));
    *(uint8_t*)(((vectorHeader*)vector) -> funcs[INDEX]).index(vector, 0) = 2;
    *(uint8_t*)(((vectorHeader*)vector) -> funcs[INDEX]).index(vector, 1) = 4;
    *(uint8_t*)(((vectorHeader*)vector) -> funcs[INDEX]).index(vector, 6) = 7;
    for (int i = 0; i < 10; i++)
        printf("id %d stores %d\n", i, *(uint8_t*)(((vectorHeader*)vector) -> funcs[INDEX]).index(vector, i));
    ((vectorHeader*)vector) -> funcs[FREE].free(vector);
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