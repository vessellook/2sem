#include <iostream>
#include <cstdlib>

#include "animal.h"
#include "sequence/array_sequence.h"
#include "sequence/linked_list_sequence.h"
#include "matrix/array_matrix.h"
#include "matrix/list_matrix.h"

using namespace std;
using namespace my_namespace;

#include "ui/simple_ui.h"
using simple_ui::show;


void where(Animal** array, unsigned size, bool(*check)(Animal), unsigned& new_size) {
    unsigned index1 = 0;
    for(unsigned index2 = 0; index2 < size; index2++) {
        if(check((*array)[index2])) {

            Animal temp = (*array)[index1];
            (*array)[index1] = (*array)[index2];
            (*array)[index2] = temp;

            index1++;
        }
    }
    *array = static_cast<Animal*>(realloc(*array, sizeof(Animal)*(index1 + 1)));
    new_size = index1 + 1;
}

void show(Animal* array, unsigned size) {
    for(unsigned i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {

    unsigned int size = 10;
    Animal* items = (Animal*) (malloc(sizeof(Animal) * size));
    cout << 0;
    for(unsigned i = 0; i < size; i++) {
        cout << 0.5;
        *(items + i) = Animal(to_string(i+1), i % 2);
    }
    unsigned new_size;
    cout << 1;
    where(&items, size, is_age_not_zero, new_size);
    cout << 2;
    show(items, new_size);


    return 0;
//    auto sequence1 = new LinkedListSequence<int>();
//    sequence1->append(3);
//    sequence1->append(1);
//    sequence1->insertAt(2, 1);
//    sequence1->prepend(4);
//    show(sequence1, "sequence1");
//
//    int *items = (int *) malloc(sizeof(int) * 5);
//    items[0] = 1;
//    items[1] = 2;
//    items[2] = 3;
//    items[3] = 4;
//    items[4] = 5;
//
//    auto sequence2 = new LinkedListSequence<int>(items, 3);
//    show(sequence2, "sequence2");
//
//    auto list = new SinglyLinkedList<int>(items, 5);
//    show(list, "list");
//    cout << list->isPalindrom();
//
//    return 0;
//    auto matrix1 = new ArrayMatrix<int>(2);
//    auto matrix2 = new ArrayMatrix<int>(2);
//
//    show(matrix1, "empty1");
//    show(matrix2, "empty2");
//
//    matrix1->set(0, 0, 1);
//    matrix1->set(0, 1, 0);
//    matrix1->set(1, 1, 1);
//    matrix1->set(1, 0, 0);
//
//    matrix2->set(0, 0, 1);
//    matrix2->set(0, 1, 5);
//    matrix2->set(1, 1, 3);
//    matrix2->set(1, 0, 7);
//
//    show(matrix1, "1");
//    *matrix1 *= 2;
//    show(matrix1, "2");
//    show(matrix2, "matrix2");
//
//    auto sum = &(*matrix1 * *matrix2);
//
//    show(sum, "sum");
//
//    return 0;
}
