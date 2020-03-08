#include "dynamic_array_structure_definition.h"
#include "dynamic_array.h"
#include "complex_structure_definition.h"
#include <stdlib.h>
struct DynamicArray* createDynamicArray_complex( int count ) {
    struct DynamicArray* arr = createDynamicArray( count, sizeof(int)/sizeof(char) );
    if ( !arr ) {
        return NULL;
    }
    return arr;
}

void setElement_complex(struct DynamicArray* arr, int index, int newValue) {
    setElement( arr, index, (void*) &newValue );
}

int getElement_complex(struct DynamicArray* arr, int index) {
    int* p = (int*) getElement(arr, index);
    if (!p) {
        return 0;
    }
    return *p;
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
    return map(arr, func, sizeof(struct complex));
}

struct DynamicArray* where_complex(struct DynamicArray* arr, int (*func)(void*)) {
    return where(arr, func);
}