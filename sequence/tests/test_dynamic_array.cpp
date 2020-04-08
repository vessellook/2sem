#include <iostream>

#include "macro_for_tests.h"
#include "../dynamic_array/dynamic_array.h"

using namespace std;
using namespace my_namespace;

template<class T>
bool check_size(const DynamicArray<T> *array, int expected_size, int test_num) {
    cout << "TEST " << test_num << ": ";
    if (array->GetSize() != expected_size) {
        cout << "FAILED: expected array size " << expected_size << ", but got " << array->GetSize() << endl;
        return false;
    }
    cout << "PASSED: got array size " << array->GetSize() << endl;
    return true;
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

template<class T>
bool check_item_with_function_Get(const DynamicArray<T> *array, int index, T expected_value, int test_num) {
    T value = array->Get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_item_with_subscript_operator(DynamicArray<T> *array, int index, T expected_value, int test_num) {
    T value = (*array)[index];
    return check_value(value, expected_value, test_num);
}

int main() {

    auto array1 = new DynamicArray<int>();
    ASSERT(check_size(array1, 0, 0));
    WHITESPACE();

    auto array2 = new DynamicArray<int>(5);
    ASSERT(check_size(array2, 5, 1));
    WHITESPACE();

    array1->Resize(10);
    ASSERT(check_size(array1, 10, 2));
    WHITESPACE();

    array1->Set(0, 3);
    array1->Set(3, 5);
    array1->Set(5, 0);

    ASSERT(check_item_with_function_Get(array1, 0, 3, 3));
    ASSERT(check_item_with_function_Get(array1, 3, 5, 3));
    ASSERT(check_item_with_function_Get(array1, 5, 0, 3));
    WHITESPACE();

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
    WHITESPACE();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto array3 = new DynamicArray<int>(items, 5);

    ASSERT(check_item_with_function_Get(array3, 0, 1, 5));
    ASSERT(check_item_with_function_Get(array3, 1, 2, 5));
    ASSERT(check_item_with_function_Get(array3, 2, 4, 5));
    ASSERT(check_item_with_function_Get(array3, 3, 8, 5));
    ASSERT(check_item_with_function_Get(array3, 4, 16, 5));
    WHITESPACE();

    auto array4 = new DynamicArray<int>(*array3);
    ASSERT(check_item_with_function_Get(array4, 0, 1, 6));
    ASSERT(check_item_with_function_Get(array4, 1, 2, 6));
    ASSERT(check_item_with_function_Get(array4, 2, 4, 6));
    ASSERT(check_item_with_function_Get(array4, 3, 8, 6));
    ASSERT(check_item_with_function_Get(array4, 4, 16, 6));
    WHITESPACE();

    delete array1;
    delete array2;
    delete array3;

    cout << "FINISH";
    return 0;
}
