#include "dynamic_array.h"
#include "dynamic_array_complex.h"
#include <stdlib.h>
#include <stdio.h>
struct DynamicArray* createDynamicArray_complex( int count ) {
    struct DynamicArray* arr = createDynamicArray( count, sizeof(struct my_complex) / sizeof(char) );
    if ( !arr ) {
        return NULL;
    }
    return arr;
}

void setElement_complex(struct DynamicArray* arr, int index, struct my_complex newValue) {
    setElement( arr, index, (void*) &newValue );
}

struct my_complex getElement_complex(struct DynamicArray* arr, int index) {
    return *((struct my_complex*) getElement(arr, index));
}

void destroyDynamicArray_complex(struct DynamicArray* a) {
    destroyDynamicArray(a);
}

struct DynamicArray* concat_complex(struct DynamicArray *a, struct DynamicArray *b) {
    return concatDynamicArray(a, b);
}

void changeDynamicArrayCount_complex(struct DynamicArray* arr, int newCount) {
    changeDynamicArrayCount(arr, newCount);
};

struct DynamicArray* map_complex(struct DynamicArray* arr, void* (*func)(void*)) {
    return map(arr, func, sizeof(struct my_complex));
}

struct DynamicArray* where_complex(struct DynamicArray* arr, int (*func)(void*)) {
    return where(arr, func);
}