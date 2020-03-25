#include "dynamic_array_structure_definition.h"
#include "complex_structure_definition.h"
#ifndef DYNAMIC_ARRAY_DYNAMIC_ARRAY_COMPLEX_H
#define DYNAMIC_ARRAY_DYNAMIC_ARRAY_COMPLEX_H
struct DynamicArray* createDynamicArray_complex(int count);
void setElement_complex(struct DynamicArray* arr, int index, struct my_complex newValue);
struct my_complex getElement_complex(struct DynamicArray* arr, int index);
struct DynamicArray* map_complex(struct DynamicArray* arr, void* (*func)(void*));
struct DynamicArray* where_complex(struct DynamicArray* arr, int (*func)(void*));
struct DynamicArray* concat_complex(struct DynamicArray *a, struct DynamicArray *b);
void changeDynamicArrayCount_complex(struct DynamicArray* arr, int newCount);
void destroyDynamicArray_complex(struct DynamicArray* a);
#endif //DYNAMIC_ARRAY_DYNAMIC_ARRAY_COMPLEX_H
