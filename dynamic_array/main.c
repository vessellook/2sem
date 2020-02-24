#include <stdio.h>
#include "dynamic_array.h"

typedef struct DynamicArray array;

int main() {
    array* p = createDynamicArray(2, sizeof(int));
    int a = 10;
    int b = 2;
    setElement(p, 0, &a);
    setElement(p, 1, &b);
    printf("Hello, World!\n");
    return 0;
}