#include <iostream>

#include "macro_and_functions_for_tests.h"

#include "../dynamic_array/dynamic_array.h"

using namespace std;
using namespace my_namespace;

template<class T>
bool check_size(const DynamicArray<T> *array, index_type expected_size, int test_num) {
    if (array->GetSize() != expected_size) {
        cout << "TEST " << test_num << ": "<< "FAILED: expected array size " << expected_size << ", but got " << array->GetSize() << endl;
        return false;
    }
#ifdef SHOW_TEST_PASSED
    cout << "TEST " << test_num << ": " << "PASSED: got array size " << array->GetSize() << endl;
#endif
    return true;
}

template<class T>
bool check_item_with_function_Get(const DynamicArray<T> *array, index_type index, T expected_value, int test_num) {
    T value = array->Get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_item_with_subscript_operator(DynamicArray<T> *array, index_type index, T expected_value, int test_num) {
    T value = (*array)[index];
    return check_value(value, expected_value, test_num);
}

int main() {

    DynamicArray<int>* array1 = new DynamicArray<int>();
    ASSERT(check_size(array1, 0, 0));
    print_test_separator();

    DynamicArray<int>* array2 = new DynamicArray<int>(5);
    ASSERT(check_size(array2, 5, 1));
    print_test_separator();

    array1->Resize(10);
    ASSERT(check_size(array1, 10, 2));
    print_test_separator();

    array1->Set(0, 3);
    array1->Set(3, 5);
    array1->Set(5, 0);

    ASSERT(check_item_with_function_Get(array1, 0, 3, 3));
    ASSERT(check_item_with_function_Get(array1, 3, 5, 3));
    ASSERT(check_item_with_function_Get(array1, 5, 0, 3));
    print_test_separator();

    array2->Set(0, 1);
    array2->Set(1, 2);
    array2->Set(2, 3);
    array2->Set(3, 4);
    array2->Set(4, 5);

    ASSERT(check_item_with_subscript_operator(array2, 0, 1, 4));
    ASSERT(check_item_with_subscript_operator(array2, 1, 2, 4));
    ASSERT(check_item_with_subscript_operator(array2, 2, 3, 4));
    ASSERT(check_item_with_subscript_operator(array2, 3, 4, 4));
    ASSERT(check_item_with_subscript_operator(array2, 4, 5, 4));
    print_test_separator();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    DynamicArray<int>* array3 = new DynamicArray<int>(items, 5);

    ASSERT(check_item_with_function_Get(array3, 0, 1, 5));
    ASSERT(check_item_with_function_Get(array3, 1, 2, 5));
    ASSERT(check_item_with_function_Get(array3, 2, 4, 5));
    ASSERT(check_item_with_function_Get(array3, 3, 8, 5));
    ASSERT(check_item_with_function_Get(array3, 4, 16, 5));
    print_test_separator();

    DynamicArray<int>* array4 = array3->Clone();
    ASSERT(check_item_with_function_Get(array4, 0, 1, 6));
    ASSERT(check_item_with_function_Get(array4, 1, 2, 6));
    ASSERT(check_item_with_function_Get(array4, 2, 4, 6));
    ASSERT(check_item_with_function_Get(array4, 3, 8, 6));
    ASSERT(check_item_with_function_Get(array4, 4, 16, 6));
    print_test_separator();

    delete array1;
    delete array2;
    delete array3;
    delete array4;

    DynamicArray<int*>* array5 = new DynamicArray<int*>(3);
    int x = 5;
    int y = 7;
    int z = 6;
    int* p2 = new int();
    int* p3 = new int(z);
    array5->Set(0, &x);
    array5->Set(1, p2);
    array5->Set(2, p3);

    *((*array5)[1]) = y;

    ASSERT( check_value( (*array5)[0], &x, 7 ) );
    ASSERT( check_value(*((*array5)[1]), y, 7) );
    ASSERT( check_value( (*array5)[2], p3, 7 ) );
    print_test_separator();

    DynamicArray<int*>* array6 = new DynamicArray<int*>();
    array6->Resize(5);
    if (array6->GetSize() < 5) {
        array6->Resize(15);
    }
    for(int i = 0; i < 5; i++) {
            array6->Set(i, new int());
    }
    for(int i = 0; i < 5; i++) {
        *((*(array6))[i]) = i;
    }

    delete (*array6)[0];
    delete (*array6)[1];
    delete (*array6)[2];
    delete (*array6)[3];
    delete (*array6)[4];
    delete array6;

    cout << "FINISH";
    return 0;
}
