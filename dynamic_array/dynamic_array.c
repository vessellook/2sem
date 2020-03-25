#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dynamic_array.h"


struct DynamicArray* createDynamicArray(int count, int size_of_element) {
// проверка на дурака
    if (count <= 0 || size_of_element <= 0) {
        return NULL;
    }
    struct DynamicArray* arr = (struct DynamicArray*) malloc(sizeof(struct DynamicArray));
// проверка выделения памяти
    arr->buffer = (void*) malloc(count * size_of_element);
    if (!arr->buffer) {
        return NULL;
    }
    arr->count = count;
    arr->size_of_element = size_of_element;
    return arr;
}

void setElement( struct DynamicArray* arr, int index, void* newValue ) {
// проверка на дурака
    if (!arr->buffer || arr->count <= index || index < 0 || arr->size_of_element <= 0) {
        return;
    }
    memcpy((void*) ((char*) arr->buffer + index * arr->size_of_element), newValue, arr->size_of_element);
}

void* getElement(struct DynamicArray* arr, int index) {
// проверка на дурака
    if (!arr->buffer || arr->count <= index || index < 0 || arr->size_of_element <= 0) {
        return NULL;
    }
    return (void*) ((char*) arr->buffer + index * arr->size_of_element);
}

struct DynamicArray* map(struct DynamicArray* arr, void* (*func)(void*), int size_of_element) {
// проверка на дурака
    if (!arr->buffer || arr->count <= 0 || arr->size_of_element <= 0 || size_of_element <= 0) {
        return NULL;
    }
    struct DynamicArray* newArr = createDynamicArray(arr->count, size_of_element);
// проверка создания массива
    if(newArr) {
// запись в созданный массив
        int i;
        for (i = 0; i < arr->count; i++) {
            void* res = func((void*)((char*) arr->buffer + i * arr->size_of_element));
            memcpy((void*) ((char*) newArr->buffer + i * newArr->size_of_element), res, newArr->size_of_element);
            free(res);
        }
    }
    return newArr;
}

struct DynamicArray* where(struct DynamicArray* arr, int (*func)(void*)) {
// проверка на дурака
    if (!arr->buffer || arr->count <= 0 || arr->size_of_element <= 0) {
        return NULL;
    }
// наверное, не самое эффективное решение:
// - посчитаю количество подходящих элементов
// - создам массив нужного размера
// - второй раз пройдусь по исходному массиву
    int count = 0;
    for(int i = 0; i < arr->count; i++) {
        void* ptr = (void*) ((char*) arr->buffer + i * arr->size_of_element);
        if (func(ptr) == 1) {
            count++;
        }
    }
    struct DynamicArray* newArr = createDynamicArray(count, arr->size_of_element);
    count = 0;
    if(newArr) {
        for(int i = 0; i < arr->count; i++) {
            void* ptr = (void*) ((char*) arr->buffer + i * arr->size_of_element);
            if (func(ptr) == 1) {
                setElement(newArr, count, getElement(arr, i));
                count++;
            }
        }
    }
    return newArr;
}

struct DynamicArray* concatDynamicArray(struct DynamicArray *a, struct DynamicArray *b) {
    if (!a || !b) {
        return NULL;
    }
    if (!a->buffer || a->count <= 0 || a->size_of_element <= 0) {
        return NULL;
    }
    if (!b->buffer || b->count <= 0 || b->size_of_element <= 0) {
        return NULL;
    }
    if (a->size_of_element != b->size_of_element) {
        return NULL;
    }
    struct DynamicArray *newArr = createDynamicArray(a->count + b->count, a->size_of_element);
    for (int i = 0; i < a->count; i++) {
        setElement(newArr, i, getElement(a, i));
    }
    for (int j = 0; j < b->count; j++) {
        setElement(newArr, a->count + j, getElement(b, j));
    }
    return newArr;
}


void changeDynamicArrayCount(struct DynamicArray* arr, int newCount) {
    if(!arr->buffer) {
        if(arr->size_of_element > 0){
            arr->buffer = (void*) malloc(newCount * arr->size_of_element);
            arr->count = newCount;
        } else {
            printf("ERROR: EMPTY buffer AND INVALID size_of_element");
        }
        return;
    }
    arr->buffer = realloc(arr->buffer, newCount*arr->size_of_element);
    arr->count = newCount;
}

void destroyDynamicArray(struct DynamicArray* arr) {
    if(!arr) {
        return;
    } else if(!arr->buffer) {
        free((void*) arr);
        return;
    }
    free(arr->buffer);
    free((void*) arr);
}
