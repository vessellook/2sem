#include "dynamic_array_structure_definition.h"
#ifndef DYNAMIC_ARRAY_DYNAMIC_ARRAY_INT_H
#define DYNAMIC_ARRAY_DYNAMIC_ARRAY_INT_H
struct DynamicArray* createDynamicArray_int(int count);
void destroyDynamicArray_int(struct DynamicArray* a);
void setElement_int(struct DynamicArray* arr, int index, int newValue);
int getElement_int(struct DynamicArray* arr, int index);
struct DynamicArray* map_int(struct DynamicArray* arr, void* (*func)(void*));
struct DynamicArray* where_int(struct DynamicArray* arr, int (*func)(void*));
struct DynamicArray* concat_int(struct DynamicArray *a, struct DynamicArray *b);
void changeDynamicArrayCount_int(struct DynamicArray* arr, int newCount);
#endif //DYNAMIC_ARRAY_DYNAMIC_ARRAY_INT_H
