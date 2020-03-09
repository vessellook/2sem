#include "dynamic_array.h"
#include "dynamic_array_int.h"
#include <stdio.h>
#
struct DynamicArray* createDynamicArray_int( int count ) {
    struct DynamicArray* arr = createDynamicArray( count, sizeof(int)/sizeof(char) );
    if ( !arr ) {
        return NULL;
    }
    return arr;
}

void setElement_int(struct DynamicArray* arr, int index, int newValue) {
    setElement( arr, index, (void*) &newValue );
}

int getElement_int(struct DynamicArray* arr, int index) {
    int* p = (int*) getElement(arr, index);
    if (!p) {
        return 0;
    }
    return *p;
}

void destroyDynamicArray_int(struct DynamicArray* a) {
    destroyDynamicArray(a);
};

struct DynamicArray* concat_int(struct DynamicArray *a, struct DynamicArray *b) {
    return concatDynamicArray(a, b);
}

void changeDynamicArrayCount_int(struct DynamicArray* arr, int newCount) {
    changeDynamicArrayCount(arr, newCount);
};

struct DynamicArray* map_int(struct DynamicArray* arr, void* (*func)(void*)) {
    return map(arr, func, sizeof(int));
}

struct DynamicArray* where_int(struct DynamicArray* arr, int (*func)(void*)) {
    return where(arr, func);
}