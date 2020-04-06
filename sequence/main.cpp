#include <iostream>
#include <stdio.h>
#include "array_sequence.h"
#include "linked_list_sequence.h"
#include "matrix_a.h"
//#include "matrix_l.h"

using namespace std;
void show(Sequence<int>* list) {
    int length = list->GetLength();
    cout << "list has length " << length << endl;
    for(int i = 0; i < length; i++) {
        cout << list->Get(i) << " ";
    }
    cout << endl << endl;
}

void show(Matrix<int>* matrix1, Matrix<int>* matrix2) {
    int length = matrix1->GetSize();
    cout << "matrix has length " << length << endl;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            printf("%4d", (*matrix1)[i][j] + (*matrix2)[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    int* items = (int*) malloc(sizeof(int) * 3);
    items[0] = 1;
    items[1] = 2;
    items[2] = 3;

    auto list1 = new ArraySequence<int>();
    list1->Append(3);
    list1->Append(1);
    list1->InsertAt(2, 1);
    list1->Prepend(4);
    show(list1);

    auto list2 = new LinkedListSequence<int>(items, 3);
    show(list2);

    auto matrix1 = new MatrixA<int>(3);
    auto matrix2 = new MatrixA<int>(3);

    show(matrix1, matrix2);
    return 0;
}
