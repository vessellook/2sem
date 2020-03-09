#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array_int.h"

typedef struct DynamicArray array;

void* add_2(void* element) {
    int* i = malloc(sizeof(int));
    *i = *((int*) element) + 2;
    return (void*) i;
}
int remove_positive(void* element) {
    if ( *((int*) element) > 0) {
        return 0;
    }
    return 1;
}


int main() {
    char chr;
    array* a = createDynamicArray_int(4);
    if (!a) {
        printf("TEST FAILED: 'createDynamicArray_int(4)' return NULL\n");
        scanf("%c", &chr);
        return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_int(4)' return %p\n", a);
    }
    array* b = createDynamicArray_int(20);
    if (!b) {
        printf("TEST FAILED: 'createDynamicArray_int(20)' return NULL\n");
        scanf("%c", &chr);return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_int(20)' return %p\n", b);
    }
    array* c = createDynamicArray_int(0);
    if (c) {
        printf("TEST FAILED: 'createDynamicArray_int(0)' return %p\n", c);
        scanf("%c", &chr);return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_int(0)' return NULL\n");
    }
    array* d = createDynamicArray_int(-10);
    if (d) {
        printf("TEST FAILED: 'createDynamicArray_int(-10)' return %p\n", d);
        scanf("%c", &chr);return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_int(-10)' return NULL\n");
    }
    destroyDynamicArray_int(b);
    printf("TEST PASSED: 'destroyDinamicArray_int()' executes without fatal error\n");
    destroyDynamicArray_int(c);
    destroyDynamicArray_int(d);
    printf("TEST PASSED: 'destroyDinamicArray_int(NULL)' executes without fatal error\n");
    int x0 = -5;
    int x1 = 1;
    int x2 = 10;
    int x3 = 120;
    setElement_int(a, 0, x0);
    int y0 = getElement_int(a, 0);
    if(y0 != x0) {
        printf("TEST FAILED: after 'setElement_int(a, 0, %d)' 'getElement_int()' return %d", x0, y0);
        scanf("%c", &chr);return 0;
    }
    setElement_int(a, 3, x3);
    int y3 = getElement_int(a, 3);
    if(y3 != x3) {
        printf("TEST FAILED: after 'setElement_int(a, 3, %d)' 'getElement_int()' return %d", x3, y3);
        scanf("%c", &chr);return 0;
    }
    setElement_int(a, 1, x1);
    setElement_int(a, 2, x2);
    int y1 = getElement_int(a, 1);
    if(y1 != x1) {
        printf("TEST FAILED: after 'setElement_int(a, 1, %d)' 'getElement_int()' return %d", x1, y1);
        scanf("%c", &chr);return 0;
    }
    int y2 = getElement_int(a, 2);
    if(y2 != x2) {
        printf("TEST FAILED: after 'setElement_int(a, 2, %d)' 'getElement_int()' return %d", x2, y2);
        scanf("%c", &chr);return 0;
    }
    printf("TEST PASSED: 'getElement_int()' and 'setElement_int()' work without mistake\n");
    array* e = map_int(a, add_2);
    if(a->count != e->count) {
        printf("TEST FAILED: different counts of array before and after 'map_int()'");
        scanf("%c", &chr);return 0;
    }
    if(a->size_of_element != e->size_of_element) {
        printf("TEST FAILED: different size of elements in array before and after 'map_int()'");
        scanf("%c", &chr);return 0;
    }
    int i;
    for(i = 0; i < 4; i++) {
        printf("%d %d\n", getElement_int(a, i), getElement_int(e, i));
        if (getElement_int(a, i) + 2 != getElement_int(e, i)) {
            printf("TEST FAILED: 'map_int()' return wrong value");
            scanf("%c", &chr);return 0;
        }
    }
    printf("TEST PASSED: 'map_int()' return array with right changes\n");
    int count = 0;
    for(i = 0; i < a->count; i++) {
        if (getElement_int(a, i) <= 0) {
            count++;
        }
    }
    e = where_int(a, remove_positive);
    if(count != e->count) {
        printf("TEST FAILED: different count of elements in array after 'where_int()' and count of negative (and 0) elements in array before 'where_int()'");
        scanf("%c", &chr);return 0;
    }
    for(i = a->count - 1; i >= 0; i--) {
        if (getElement_int(a, i) <= 0) {
            if (getElement_int(a, i) != getElement_int(e, count)) {
                printf("TEST FAILED: 'where_int()' return wrong value");
                scanf("%c", &chr);return 0;
            }
            count--;
        }
    }
    destroyDynamicArray_int(a);
    destroyDynamicArray_int(e);
    a = createDynamicArray_int(4);
    b = createDynamicArray_int(3);
    setElement_int(a, 1, 1);
    setElement_int(a, 2, 2);
    setElement_int(a, 3, 3);
    setElement_int(a, 4, 4);
    setElement_int(b, 1, 5);
    setElement_int(b, 2, 66);
    setElement_int(b, 3, 777);
    d = concat_int(a, b);
    if(d->count != a->count + b->count) {
        printf("TEST FAILED: different counts of array before and after 'concat()'");
    }
    for(i = 0; i < 4; i++) {
        if(getElement_int(a, i) != getElement_int(d, i)) {
            printf("TEST FAILED: 'concat_int()' return wrong value");
            scanf("%c", &chr);return 0;
        }
    }
    for(i = 4; i < 7; i++) {
        if(getElement_int(b, i - 4) != getElement_int(d, i)) {
            printf("TEST FAILED: 'concat_int()' return wrong value");
            scanf("%c", &chr);return 0;
        }

    }
    printf("TEST PASSED: 'concat_int()' return array with right changes\n");
    changeDynamicArrayCount_int(d, 12);
    if(d->count != 12) {
        printf("TEST FAILED: 'changeDynamicArrayCount_int()' don't work");
        scanf("%c", &chr);return 0;
    }
    printf("TEST PASSED: 'changeDynamicArrayCount_int()' return array with right changes\n");
    scanf("%c", &chr);return 0;
}