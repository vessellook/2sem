#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array_structure_definition.h"
#include "complex_structure_definition.h"
#include "dynamic_array_int.h"
#include "dynamic_array_complex.h"

typedef struct DynamicArray array;
typedef struct complex complex;
const char* welcomeString = ">>>";

void outputWelcomeText() {
    printf("Menu:\n");
    printf("0. Output this menu\n");
    printf("1. Input array A\n");
    printf("2. Output A\n");
    printf("3. Input array B\n");
    printf("4. Extend B with elements of A\n");
    printf("5. Output B\n");
    printf("6. Make C as concat A and B\n");
    printf("7. Add 2 to each element of C (only for Integer)\n");
    printf("8. Remove elements with positive imaginary part from C (only for Complex)\n");
    printf("9. Output C\n");
    printf("10. Destroy A\n");
    printf("11. Destroy B\n");
    printf("12. Destroy C\n");
    printf("13. Exit\n");
}

void outputElements(array* arr, const char* arr_type) {
    if(!arr) {
        printf("ERROR 1\n");
        return;
    }
    if(!arr->buffer) {
        printf("ERROR 2\n");
        return;
    }
    int i;
    int val_int;
    complex val_complex;
    switch (*arr_type) {
        case 'i':
            for (i = 0; i < arr->count; i++) {
                val_int = getElement_int(arr, i);
                printf("%d ", val_int);
            }
            break;
        case 'c':
            for (i = 0; i < arr->count; i++) {
                val_complex = getElement_complex(arr, i);
                printf("%lf", val_complex.re);
                if (val_complex.im < 0) {
                    printf("-%lfj ", -val_complex.im);
                } else {
                    printf("+%lfj ", val_complex.im);
                }
            }
            break;
        default:
            break;
    }
    printf("\n");
}

void inputElements(char name, array** parr, char* arr_type) {
    printf("Input size of array %c\n", name);
    int count;
    printf("%s", welcomeString);
    scanf("%d", &count);
    switch(*arr_type) {
        case 'i':
            destroyDynamicArray_int(*parr);
            break;
        case 'c':
            destroyDynamicArray_complex(*parr);
    }
    printf("Choose type:\n");
    printf("1. Integer\n");
    printf("2. Complex\n");
    int num;
    printf("%s", welcomeString);
    scanf("%d", &num);
    int i;
    switch (num) {
        case 1:
            *parr = createDynamicArray_int(count);
            *arr_type = 'i';
            printf("Input elements of array %c (%d size of array %c)\n", name, count, name);
            printf("%s", welcomeString);
            int val_int;
            for (i = 0; i < count; i++) {
                scanf("%d", &val_int);
                setElement_int(*parr, i, val_int);
            }
            break;
        case 2:
            *parr = createDynamicArray_complex(count);
            *arr_type = 'c';
            printf("Input elements of array %c as pairs \'re im\' (size of array %c = %d)\n", name, name, count);
            printf("%s", welcomeString);
            complex val_complex;
            double re, im;
            for (i = 0; i < count; i++) {
                scanf("%lf %lf", &re, &im);
                val_complex.re = re;
                val_complex.im = im;
                setElement_complex(*parr, i, val_complex);
            }
            break;
        default:
            break;
    }
}

void concatArrays(array* a, array* b, array** c, const char* a_type, const char* b_type, char* c_type) {
    if (!a || !b) {
        printf("ERROR 4\n");
        return;
    }
    if(*a_type != *b_type || *a_type == 'n') {
        printf("ERROR, different types\n");
        return;
    }
    switch(*c_type) {
        case 'i':
            destroyDynamicArray_int(*c);
            break;
        case 'c':
            destroyDynamicArray_complex(*c);
        default:
            break;
    }
    *c_type = *a_type;
    switch(*c_type) {
        case 'i':
            *c = concat_int(a, b);
            break;
        case 'c':
            *c = concat_complex(a, b);
        default:
            break;
    }
}

void destroyArray(array* arr, char* arr_type) {
    switch(*arr_type) {
        case 'i':
            destroyDynamicArray_int(arr);
            *arr_type = 'n';
            break;
        case 'c':
            destroyDynamicArray_complex(arr);
            *arr_type = 'n';
            break;
        default:
            break;
    }
}

void extendArrayWithArray(array* base, const char* base_type, array* added, const char* added_type) {
    if(*base_type != *added_type || *base_type == 'n') {
        printf("ERROR 3\n");
        return;
    }
    int count = base->count + added->count;
    int old_count = base->count;
    switch (*base_type) {
        case 'i':
            changeDynamicArrayCount_int(base, count);
            break;
        case 'c':
            changeDynamicArrayCount_complex(base, count);
            break;
    }
    int i;
    for(i = 0; i < added->count; i++) {
        switch (*base_type) {
            case 'i':
                setElement_int(base, old_count + i, getElement_int(added, i));
                break;
            case 'c':
                setElement_complex(base, base->count + i, getElement_complex(added, i));
                break;
        }
    }
}

void* add_2(void* element) {
    int* i = malloc(sizeof(int));
    *i = *((int*) element) + 2;
    return i;
}

int remove_positive_im(void* element) {
    if (((complex*) element)->im > 0) {
        return 0;
    }
    return 1;
}


int main() {
    array* a = NULL;
    char a_type = 'n';
    array* b = NULL;
    char b_type = 'n';
    array* c = NULL;
    char c_type = 'n';
    int num = 0;
    outputWelcomeText();
    while(num != 10){
        printf("\nWhat do you want?\n");
        printf("%s", welcomeString);
        scanf("%d", &num);
        switch (num) {
            case 0:
                outputWelcomeText();
                break;
            case 1:
                inputElements('A', &a, &a_type);
                printf("Done\n");
                break;
            case 2:
                outputElements(a, &a_type);
                break;
            case 3:
                inputElements('B', &b, &b_type);
                printf("Done\n");
                break;
            case 4:
                extendArrayWithArray(b, &b_type, a, &a_type);
                printf("Done\n");
                break;
            case 5:
                outputElements(b, &b_type);
                break;
            case 6:
                concatArrays(a, b, &c, &a_type, &b_type, &c_type);
                printf("Done\n");
                break;
            case 7:
                if (c_type == 'i') {
                    map_int(c, &add_2);
                }
                break;
            case 8:
                if (c_type == 'c') {
                    c = where_complex(c, &remove_positive_im);
                }
                break;
            case 9:
                outputElements(c, &c_type);
                break;
            case 10:
                destroyArray(a, &a_type);
                printf("Done\n");
                break;
            case 11:
                destroyArray(b, &b_type);
                printf("Done\n");
                break;
            case 12:
                destroyArray(c, &c_type);
                printf("Done\n");
                break;
            case 13:
                destroyArray(a, &a_type);
                destroyArray(b, &b_type);
                destroyArray(c, &c_type);
                printf("Exit");
                return 0;
            default:
                break;
        }
    }
    return 0;
}