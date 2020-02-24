//
// Created by vesse on 24.02.2020.
//

#ifndef DINAMIC_ARRAY_DINAMIC_ARRAY_H
struct DynamicArray;
struct DynamicArray* createDynamicArray(int count, int size_of_element);
void setElement(struct DynamicArray* arr, int index, void* newValue);
void* getElement(struct DynamicArray* arr, int index);
struct DynamicArray* map(struct DynamicArray* arr, void* (*func)(void*), int size_of_element);
struct DynamicArray* where(struct DynamicArray* arr, bool (*func)(void*), int size_of_element);
struct DynamicArray* concatenate(struct DynamicArray* a, struct DynamicArray* b);

#define DINAMIC_ARRAY_DINAMIC_ARRAY_H

#endif //DINAMIC_ARRAY_DINAMIC_ARRAY_H
