
#include "config.h"
#include <iostream>
#include <cstdio>

#include "sequence/array_sequence.h"
#include "sequence/linked_list_sequence.h"
#include "matrix/array_matrix.h"
#include "matrix/list_matrix.h"
#include "ui/text_block.h"

using namespace std;
using namespace my_namespace;

#include "ui/simple_ui.h"
using simple_ui::show;

int main() {

    int *items = (int *) malloc(sizeof(int) * 3);
    items[0] = 1;
    items[1] = 2;
    items[2] = 3;

    auto list1 = new ArraySequence<int>();
    list1->Append(3);
    list1->Append(1);
    list1->InsertAt(2, 1);
    list1->Prepend(4);
    show(list1, "list1");

    auto list2 = new LinkedListSequence<int>(items, 3);
    show(list2, "list2");

    auto matrix1 = new ArrayMatrix<int>(2);
    auto matrix2 = new ArrayMatrix<int>(2);

    show(matrix1, "empty1");
    show(matrix2, "empty2");

    matrix1->Set(0, 0, 1);
    matrix1->Set(0, 1, 0);
    matrix1->Set(1, 1, 1);
    matrix1->Set(1, 0, 0);

    matrix2->Set(0, 0, 1);
    matrix2->Set(0, 1, 5);
    matrix2->Set(1, 1, 3);
    matrix2->Set(1, 0, 7);

    show(matrix1, "1");
    *matrix1 *= 2;
    show(matrix1, "2");
    show(matrix2, "matrix2");

    auto sum = &(*matrix1 * *matrix2);

    show(sum, "sum");

    return 0;
}
