#include <stdlib.h>
#include <stdio.h>

struct Animal {
    char name;
    int age;
};
typedef struct Animal Animal;

Animal createAnimal(char name, int age) {
    Animal a;
    a.name = name;
    a.age = age;
    return a;
}

Animal rise_age(Animal item) {
    item.age += 1;
    return item;
}

int is_age_not_zero(Animal item) {
    return item.age != 0;
}


void where(Animal** array, unsigned size, int(*check)(Animal), unsigned* new_size) {
    unsigned index1 = 0;
    for(unsigned index2 = 0; index2 < size; index2++) {
        if(check((*array)[index2])) {

            Animal temp = (*array)[index1];
            (*array)[index1] = (*array)[index2];
            (*array)[index2] = temp;

            index1++;
        }
    }
    *array = (Animal*)(realloc(*array, sizeof(Animal)*(index1 + 1)));
    *new_size = index1 + 1;
}

void show(Animal* array, unsigned size) {
    for(int i = 0; i < size; i++) {
        printf("(%c, %d)", array[i].name, array[i].age);
    }
    printf("\n");
}



int main() {
    unsigned int size = 10;
    Animal* items = (Animal*) (malloc(sizeof(Animal) * size));
//    for(unsigned i = 0; i < size * sizeof(Animal)/ sizeof(char); i++) {
//        *((char*)items+i) = (char)0;
//    }
    printf("1");
    for(int i = 0; i < size; i++) {
        printf("2");
        *(items + i) = createAnimal((char)(i+'a'), i % 2);
    }
    printf("3");
    unsigned new_size;
    where(&items, size, is_age_not_zero, &new_size);
    show(items, new_size);
    return 0;
}