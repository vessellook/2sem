#include <iostream>

#include "macro_and_functions_for_tests.h"

#include "../matrix/array_matrix.h"
#define TestMatrix ArrayMatrix

//#include "../matrix/list_matrix.h"
//#define TestMatrix ListMatrix

using namespace std;
using namespace my_namespace;

#include "../ui/simple_ui.h"
using simple_ui::show;

template <class T>
void show_pointers(IMatrix<T>& matrix, const std::string& name = "") {
    unsigned len = matrix.getSize();
    cout<<"start show pointer of " << name << std::endl;
    for(unsigned i = 0; i < len; ++i) {
        for(unsigned j = 0; j < len; ++j) {
            cout << &(matrix[i][j]) << std::endl;
        }
    }
    cout<<"end show pointer of " << name << std::endl;

}


template<class T>
bool check_size(const IMatrix<T> *matrix, unsigned expected_size, unsigned test_num) {
    if (matrix->getSize() != expected_size) {
        cout << "TEST " << test_num << ": "
             << "FAILED: expected matrix size " << expected_size
             << ", but got " << matrix->getSize() << endl;
        return false;
    }
#ifdef SHOW_TEST_PASSED
    cout << "TEST " << test_num << ": " << "PASSED: got matrix size " << matrix->getSize() << endl;
#endif
    return true;
}

int main() {
    unsigned test_num = 0;

    IMatrix<int>* matrix1 = new TestMatrix<int>(3);

    test_num = 0;
    ASSERT(check_size(matrix1, 3, test_num++));
    print_test_separator();

    (*matrix1)[0][0] = 1;
    (*matrix1)[1][0] = 2;
    (*matrix1)[1][1] = 3;
    (*matrix1)[0][1] = 4;

    ASSERT(check_size(matrix1, 3, test_num++));
    print_test_separator();

    ASSERT(check_value((*matrix1)[0][0], 1, test_num));
    ASSERT(check_value((*matrix1)[1][0], 2, test_num));
    ASSERT(check_value(matrix1->get(1, 1), 3, test_num));
    ASSERT(check_value(matrix1->get(0, 1), 4, test_num++));
    print_test_separator();

    matrix1->set(0, 2, 5);
    matrix1->set(1, 2, 6);
    matrix1->set(2, 2, 7);
    matrix1->set(2, 1, 8);
    matrix1->set(2, 0, 9);

    ASSERT(check_size(matrix1, 3, test_num++));
    print_test_separator();

    ASSERT(check_value(matrix1->get(2, 0), 9, test_num));
    ASSERT(check_value(matrix1->get(2, 1), 8, test_num));
    ASSERT(check_value(matrix1->get(2, 2), 7, test_num));
    ASSERT(check_value((*matrix1)[1][2], 6, test_num));
    ASSERT(check_value((*matrix1)[0][2], 5, test_num++));
    print_test_separator();

    IMatrix<int>* matrix2 = matrix1->getMinor(1, 2);

    test_num = 5;
    ASSERT(check_size(matrix2, 2, test_num++));
    print_test_separator();

    ASSERT(check_value(matrix2->get(0, 0), 1, test_num));
    ASSERT(check_value(matrix2->get(1, 0), 9, test_num));
    ASSERT(check_value(matrix2->get(1, 1), 8, test_num));
    ASSERT(check_value(matrix2->get(0, 1), 4, test_num++));
    print_test_separator();

    IMatrix<int>* matrix3 = matrix2->clone()->transpose();

    test_num = 7;
    ASSERT(check_size(matrix2, 2, test_num++));
    print_test_separator();

    ASSERT(check_value(matrix3->get(0, 0), 1, test_num));
    ASSERT(check_value(matrix3->get(0, 1), 9, test_num));
    ASSERT(check_value(matrix3->get(1, 1), 8, test_num));
    ASSERT(check_value(matrix3->get(1, 0), 4, test_num++));
    print_test_separator();


    IMatrix<int>* matrix4 = matrix2->clone();

    test_num = 9;
    ASSERT(check_size(matrix4, 2, test_num++));
    print_test_separator();
    matrix4[0][0];
    ASSERT(check_value(matrix4->get(0, 0), 1, test_num));
    ASSERT(check_value(matrix4->get(1, 0), 9, test_num));
    ASSERT(check_value(matrix4->get(1, 1), 8, test_num));
    ASSERT(check_value(matrix4->get(0, 1), 4, test_num++));
    print_test_separator();

    show(matrix1, "matrix1");
    show(matrix2, "matrix2");
    show(matrix3, "matrix3");

    show(&(*matrix2 + *matrix3), "matrix2+3");
    show(matrix2, "matrix2");
    show(matrix3, "matrix3");

    show(matrix4, "matrix4");
    *matrix4 *= 2;
    show(matrix4, "matrix4");

    delete matrix1;
    matrix1 = nullptr;
    delete matrix2;
    matrix2 = nullptr;
    delete matrix3;
    matrix3 = nullptr;

    IMatrix<int>* matrix5 = &(*matrix4 * 2);
    show(matrix5, "matrix5");
    cout << "FINISH";
    return 0;
}
