#ifndef DYNAMIC_ARRAY_DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_DYNAMIC_ARRAY_H
struct DynamicArray* createDynamicArray(int count, int size_of_element);
struct DynamicArray* concatDynamicArray(struct DynamicArray* a, struct DynamicArray* b);
struct DynamicArray* destroyDynamicArray(struct DynamicArray* a);
void changeDynamicArrayCount(struct DynamicArray* arr, int newCount);
void setElement(struct DynamicArray* arr, int index, void* newValue);
void* getElement(struct DynamicArray* arr, int index);
struct DynamicArray* map(struct DynamicArray* arr, void* (*func)(void*), int size_of_element);
struct DynamicArray* where(struct DynamicArray* arr, void* (*func)(void*));
#endif //DYNAMIC_ARRAY_DYNAMIC_ARRAY_H
