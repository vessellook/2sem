#include <stdlib.h>
#include <string.h>

/*
struct DynamicArray {
void* buffer;
int count;
int size_of_element;
};

struct DynamicArray* createDynamicArray(int count, int size_of_element) {
// проверка на дурака
if (count <= 0 || size_of_element <= 0) {
return NULL;
}

// тут проверка выделения памяти излишняя
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
memcpy((void*) ((char*) arr->buffer + index), newValue, arr->size_of_element);
}

void* getElement( struct DynamicArray* arr, int index ) {
// проверка на дурака
if (!arr->buffer || arr->count <= index || index < 0 || arr->size_of_element <= 0) {
return NULL;
}

return (void*) ( (char*) arr->buffer + index * size_of_element );
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
int res = func(getElement(arr, i));
setElement(newArr, i, res);
}
}
return newArr;
}
struct DynamicArray* where(struct DynamicArray* arr, bool (*func)(void*)) {
// проверка на дурака
if (!arr->buffer || arr->count <= 0 || arr->size_of_element <= 0 || size_of_element <= 0) {
return NULL;
}
// наверное, не самое эффективное решение:
// - посчитаю количество подходящих элементов
// - создам массив нужного размера
// - второй раз пройдусь по исходному массиву
int count = 0;
for(int i = 0; i < arr->count; i++) {
void* ptr = (void*) ((char*) arr->buffer + i * arr->size_of_element);
if (where(ptr)) {
count++;
}
}
struct DynamicArray* newArr = createDynamicArray(count, arr->size_of_element);
if(newArr) {
for(int i = 0; i < arr->count; i++) {
void* ptr = (void*) ((char*) arr->buffer + i * arr->size_of_element);
if (where(ptr)) {
setElement(newArr, count, getElement(newArr, i));
count++;
}
}
}
return newArr;
}

struct DynamicArray* concatenate( struct DynamicArray* a, struct DynamicArray* b) {
// несколько проверок на дурака
if ( !a || !b ) {
return NULL;
}
if (!a->buffer || a->count <= 0 || a->size_of_element <= 0) {
return NULL;
}
if (!b->buffer || b->count <= 0 || b->size_of_element <= 0) {
return NULL;
}
if (a->size_of_element != b->sise_of_element) {
return NULL;
}

struct DynamicArray* newArr = createDynamicArray( a->count + b->count, a->size_of_element);
if(newArr) {
for(int i = 0; i < a->count; i++) {
setElement( newArr, i, getElement(a, i) );
}
for(int j = 0; j < b->count; j++) {
setElement( newArr, a->count + j, getElement(b, j) );
}
}
return newArr;
}

// обёртка для целых чисел
struct DynamicArray* createDynamicArray_int( int count ) {
struct DynamicArray* arr = createDynamicArray( count, sizeof(int)/sizeof(char) );
if ( !arr ) {
printf("ERROR 401");
}
return NULL;
}

void setElement_int( struct DynamicArray* arr, int index, int newValue) {
setElement( arr, index, (void*) &newValue );
}

int* getElement_int( struct DynamicArray* arr, int index) {
void* p = getElement( arr, index );
if ( !p ) {
printf("ERROR 402");
}
return (int*) p;
}

struct DynamicArray* map( struct DynamicArray* arr, void* (*func)(void*), int size_of_element) {
}
 */

struct DynamicArray {
    void *buffer;
    int count;
    int size_of_element;
};

struct DynamicArray *createDynamicArray(int count, int size_of_element) {
    if (count <= 0 || size_of_element <= 0) {
        return NULL;
    }
    struct DynamicArray *arr = (struct DynamicArray *) malloc(sizeof(struct DynamicArray));
    arr->buffer = (void *) malloc(count * size_of_element);
    if (!arr->buffer) {
        return NULL;
    }
    arr->count = count;
    arr->size_of_element = size_of_element;
    return arr;
}

void setElement(struct DynamicArray *arr, int index, void *newValue) {
    if (!arr->buffer || arr->count <= index || index < 0 || arr->size_of_element <= 0) {
        return;
    }
    memcpy((void *) ((char *) arr->buffer + index), newValue, arr->size_of_element);
}

void *getElement(struct DynamicArray *arr, int index) {
    if (!arr->buffer || arr->count <= index || index < 0 || arr->size_of_element <= 0) {
        return NULL;
    }
    return (void *) ((char *) arr->buffer + index * arr->size_of_element);
}

struct DynamicArray *map(struct DynamicArray *arr, void *(*func)(void *), int size_of_element) {
    if (!arr->buffer || arr->count <= 0 || arr->size_of_element <= 0 || size_of_element <= 0) {
        return NULL;
    }
    struct DynamicArray *newArr = createDynamicArray(arr->count, size_of_element);
    for (int i = 0; i < arr->count; i++) {
        void *res = func(getElement(arr, i));
        setElement(newArr, i, res);
    }
    return newArr;
}

struct DynamicArray *where(struct DynamicArray *arr, int (*func)(void *), int size_of_element) {
    if (!arr->buffer || arr->count <= 0 || arr->size_of_element <= 0 || size_of_element <= 0) {
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < arr->count; i++) {
        void *ptr = (void *) ((char *) arr->buffer + i * arr->size_of_element);
        if (func(ptr)) {
            count++;
        }
    }
    count = 0;
    struct DynamicArray *newArr = createDynamicArray(count, arr->size_of_element);
    for (int i = 0; i < arr->count; i++) {
        void *ptr = (void *) ((char *) arr->buffer + i * arr->size_of_element);
        if (func(ptr)) {
            setElement(newArr, count, getElement(newArr, i));
            count++;
        }
    }
    return newArr;
}

struct DynamicArray *concatenate(struct DynamicArray *a, struct DynamicArray *b) {
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
