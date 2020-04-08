#include <iostream>

#include "macro_for_tests.h"

#include "../matrix/array_matrix.h"

#define TestMatrix ArrayMatrix

//#include "list_matrix.h"
//#define TestMatrix ListMatrix

using namespace std;
using namespace my_namespace;

template<class T>
bool check_size(const TestMatrix<T> *matrix, int expected_size, int test_num) {
    cout << "TEST " << test_num << ": ";
    if (matrix->GetSize() != expected_size) {
        cout << "FAILED: expected matrix size " << expected_size << ", but got " << matrix->GetSize() << endl;
        return false;
    }
    cout << "PASSED: got matrix size " << matrix->GetSize() << endl;
    return true;
}

void show(IMatrix<int> *matrix) {
    int size = matrix->GetSize();
    cout << "matrix has size " << size << endl;
    for (int i = 0; i < size; i++) {
        cout << "|";
        for (int j = 0; j < size; j++) {
            printf("%4d", (*matrix)[j][i]);
        }
        cout << "   |" << endl;
    }
    cout << endl;
}

template<class T>
bool check_value(T got_value, T expected_value, int test_num) {
    cout << "TEST " << test_num << ": ";
    if (got_value != expected_value) {
        cout << "FAILED: expected value " << expected_value << " and got value " << got_value << endl;
        return false;
    }
    cout << "PASSED: expected value and got value are equal" << endl;
    return true;
}

int main() {
    auto matrix1 = new TestMatrix<int>(3);

    ASSERT(check_size(matrix1, 3, 0));
    WHITESPACE();

    (*matrix1)[0][0] = 1;
    (*matrix1)[1][0] = 2;
    (*matrix1)[1][1] = 3;
    (*matrix1)[0][1] = 4;

    ASSERT(check_size(matrix1, 3, 1));
    WHITESPACE();

    ASSERT(check_value(matrix1->Get(0, 0), 1, 2));
    ASSERT(check_value(matrix1->Get(1, 0), 2, 2));
    ASSERT(check_value(matrix1->Get(1, 1), 3, 2));
    ASSERT(check_value(matrix1->Get(0, 1), 4, 2));
    WHITESPACE();

    matrix1->Set(0, 2, 5);
    matrix1->Set(1, 2, 6);
    matrix1->Set(2, 2, 7);
    matrix1->Set(2, 1, 8);
    matrix1->Set(2, 0, 9);

    ASSERT(check_size(matrix1, 3, 3));
    WHITESPACE();

    ASSERT(check_value(matrix1->Get(2, 0), 9, 4));
    ASSERT(check_value(matrix1->Get(2, 1), 8, 4));
    ASSERT(check_value(matrix1->Get(2, 2), 7, 4));
    ASSERT(check_value((*matrix1)[1][2], 6, 4));
    ASSERT(check_value((*matrix1)[0][2], 5, 4));
    WHITESPACE();

    auto matrix2 = matrix1->MinorNew(1, 2);

    ASSERT(check_size(matrix2, 2, 5));
    WHITESPACE();

    ASSERT(check_value(matrix2->Get(0, 0), 1, 6));
    ASSERT(check_value(matrix2->Get(1, 0), 9, 6));
    ASSERT(check_value(matrix2->Get(1, 1), 8, 6));
    ASSERT(check_value(matrix2->Get(0, 1), 4, 6));
    WHITESPACE();

    auto matrix3 = matrix2->TransposeNew();

    ASSERT(check_size(matrix2, 2, 7));
    WHITESPACE();

    ASSERT(check_value(matrix3->Get(0, 0), 1, 8));
    ASSERT(check_value(matrix3->Get(0, 1), 9, 8));
    ASSERT(check_value(matrix3->Get(1, 1), 8, 8));
    ASSERT(check_value(matrix3->Get(1, 0), 4, 8));
    WHITESPACE();


    show(matrix1);
    show(matrix2);
    cout << "FINISH";
    return 0;
}