#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dynamic_array_complex.h"

typedef struct DynamicArray array;
typedef struct my_complex my_complex;

void* add_2(void* element) {
    my_complex* i = malloc(sizeof(int));
    my_complex* j = (my_complex*) element;
    i->re = j->re + 2;
    i->im = j->im + 2;
    return (void*) i;
}
int remove_positive_im(void* element) {
    if (((my_complex*) element)->im > 0) {
        return 0;
    }
    return 1;
}


int main() {
    char chr;
    array* a = createDynamicArray_complex(2);
    if (!a) {
        printf("TEST FAILED: 'createDynamicArray_complex(2)' return NULL\n");
        scanf("%c", &chr);
        return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_complex(2)' return %p\n", a);
    }
    array* b = createDynamicArray_complex(20);
    if (!b) {
        printf("TEST FAILED: 'createDynamicArray_complex(20)' return NULL\n");
        scanf("%c", &chr);
        return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_complex(20)' return %p\n", b);
    }
    array* c = createDynamicArray_complex(0);
    if (c) {
        printf("TEST FAILED: 'createDynamicArray_complex(0)' return %p\n", c);
        scanf("%c", &chr); return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_complex(0)' return NULL\n");
    }
    array* d = createDynamicArray_complex(-10);
    if (d) {
        printf("TEST FAILED: 'createDynamicArray_complex(-10)' return %p\n", d);
        scanf("%c", &chr);
        return 0;
    } else {
        printf("TEST PASSED: 'createDynamicArray_complex(-10)' return NULL\n");
    }
    destroyDynamicArray_complex(b);
    printf("TEST PASSED: 'destroyDinamicArray_complex()' executes without fatal error\n");
    destroyDynamicArray_complex(c);
    destroyDynamicArray_complex(d);
    printf("TEST PASSED: 'destroyDinamicArray_complex(NULL)' executes without fatal error\n");
    my_complex x1;
    x1.re = -5;
    x1.im = 10;
    my_complex x2;
    x2.re = 5;
    x2.im = -10;
    setElement_complex(a, 0, x1);
    my_complex y1 = getElement_complex(a, 0);
    if(fabs(x1.re - y1.re) > 0.0001 || fabs(x1.im - y1.im) > 0.0001) {
        printf("TEST FAILED: after 'setElement_complex()' 'getElement_complex()' return wrong value");
        scanf("%c", &chr);
        return 0;
    }
    setElement_complex(a, 1, x2);
    my_complex y2 = getElement_complex(a, 1);
    if(fabs(x2.re - y2.re) > 0.0001 || fabs(x2.im - y2.im) > 0.0001) {
        printf("TEST FAILED: after 'setElement_complex()' 'getElement_complex()' return wrong value");
        scanf("%c", &chr);
        return 0;
    }
    printf("TEST PASSED: 'getElement_complex()' and 'setElement_complex()' work without mistake");
    scanf("%c", &chr);
    array* e = map_complex(a, add_2);
    if(a->count != e->count) {
        printf("TEST FAILED: different counts of array before and after 'map_complex()'");
        scanf("%c", &chr);
        return 0;
    }
    if(a->size_of_element != e->size_of_element) {
        printf("TEST FAILED: different size of elements in array before and after 'map_complex()'");
        scanf("%c", &chr);
        return 0;
    }
    int i;
    for(i = 0; i < 2; i++) {
        x1 = getElement_complex(a, i);
        y1 = getElement_complex(e, i);
        if ( fabs(x1.re + 2 - y1.re) > 0.0001 || fabs(x1.im + 2 - y1.im) > 0.0001 ) {
            printf("TEST FAILED: 'map_complex()' return wrong value");
            scanf("%c", &chr);
            return 0;
        }
    }
    printf("TEST PASSED: 'map_complex()' return array with right changes");
    scanf("%c", &chr);
    int count = 0;
    for(i = 0; i < a->count; i++) {
        x1 = getElement_complex(a, i);
        if (x1.im <= 0) {
            count++;
        }
    }
    e = where_complex(a, remove_positive_im);
    if(count != e->count) {
        printf("TEST FAILED: different count of elements in array after 'where_complex()' and count of negative (and 0) elements in array before 'where_complex()'");
        scanf("%c", &chr); return 0;
    }
    for(i = a->count - 1; i >= 0; i--) {
        x1 = getElement_complex(a, i);
        if (x1.im <= 0) {
            y1 = getElement_complex(e, count-1);
            if (fabs(x1.re - y1.re) > 0.0001 || fabs(x1.im - y1.im) > 0.0001) {
                printf("TEST FAILED: 'where_complex()' return wrong value");
                scanf("%c", &chr); return 0;
            }
            count--;
        }
    }
    destroyDynamicArray_complex(a);
    destroyDynamicArray_complex(e);
    a = createDynamicArray_complex(1);
    b = createDynamicArray_complex(1);
    setElement_complex(a, 1, x1);
    setElement_complex(b, 1, y2);
    d = concat_complex(a, b);
    if(d->count != a->count + b->count) {
        printf("TEST FAILED: different counts of array before and after 'concat()'");
        scanf("%c", &chr);
        return 0;
    }
    x1 = getElement_complex(a, 0);
    y1 = getElement_complex(d, 0);
    if(fabs(x1.re - y1.re) > 0.0001 || fabs(x1.im - y1.im) > 0.0001) {
        printf("TEST FAILED: 'concat_complex()' return wrong value");
        scanf("%c", &chr);
        return 0;
    }
    x1 = getElement_complex(b, 0);
    y1 = getElement_complex(d, 1);
    if(fabs(x1.re - y1.re) > 0.0001 || fabs(x1.im - y1.im) > 0.0001) {
        printf("TEST FAILED: 'concat_complex()' return wrong value");
        scanf("%c", &chr);
        return 0;
    }
    printf("TEST PASSED: 'concat_complex()' return array with right changes\n");
    changeDynamicArrayCount_complex(d, 12);
    if(d->count != 12) {
        printf("TEST FAILED: 'changeDynamicArrayCount_complex()' don't work");
        scanf("%c", &chr);
        return 0;
    }
    printf("TEST PASSED: 'changeDynamicArrayCount_complex()' return array with right changes\n");
    scanf("%c", &chr);
    return 0;
}