#include <iostream>
#include <memory>

#include "macro_and_functions_for_tests.h"

#include "asserts.h"

#include "../dynamic_array/dynamic_array.h"
#define TestDynamicArray DynamicArray

//#include "../dynamic_array/safe_dynamic_array.h"
//#define TestDynamicArray SafeDynamicArray

using namespace std;
using namespace my_namespace;
using tests::assert_equal;

template<class T>
bool check_size(const TestDynamicArray<T> *array, unsigned expected_size, unsigned test_num) {
    if (array->getSize() != expected_size) {
        cout << "TEST " << test_num << ": " << "FAILED: expected array size " << expected_size << ", but got "
             << array->getSize() << endl;
        return false;
    }
    cout << "TEST " << test_num << ": " << "PASSED: got array size " << array->getSize() << endl;
    return true;
}

template<class T>
bool check_item_with_function_get(const TestDynamicArray<T> *array, unsigned index, T expected_value, unsigned test_num) {
    T value = array->get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_item_with_subscript_operator(TestDynamicArray<T> *array, unsigned index, T expected_value, unsigned test_num) {
    T value = (*array)[index];
    return check_value(value, expected_value, test_num);
}

bool check_constructor_and_size() {
    auto array1 = TestDynamicArray<int>();
    assert_equal(array1.getSize(), (unsigned)0);
    auto array2 = TestDynamicArray<double>();
    assert_equal(array1.getSize(), (unsigned)0);
    auto array3 = TestDynamicArray<shared_ptr<int>>();
    assert_equal(array1.getSize(), (unsigned)0);
    auto array4 = TestDynamicArray<shared_ptr<double>>();
    assert_equal(array4.getSize(), (unsigned)0);
    auto array5 = TestDynamicArray<shared_ptr<TestDynamicArray<int>>>();
    assert_equal(array5.getSize(), (unsigned)0);
    auto array6 = TestDynamicArray<shared_ptr<TestDynamicArray<shared_ptr<int>>>>();
    assert_equal(array6.getSize(), (unsigned)0);

    auto array11 = TestDynamicArray<int>(5);
    assert_equal(array11.getSize(), (unsigned)5);
    auto array12 = TestDynamicArray<double>(5);
    assert_equal(array12.getSize(), (unsigned)5);
    auto array13 = TestDynamicArray<shared_ptr<int>>(5);
    assert_equal(array13.getSize(), (unsigned)5);
    auto array14 = TestDynamicArray<shared_ptr<double>>(5);
    assert_equal(array14.getSize(), (unsigned)5);
    auto array15 = TestDynamicArray<shared_ptr<TestDynamicArray<int>>>(5);
    assert_equal(array15.getSize(), (unsigned)5);
    auto array16 = TestDynamicArray<shared_ptr<TestDynamicArray<shared_ptr<int>>>>(5);
    assert_equal(array16.getSize(), (unsigned)5);

    int* int_array = new int[5];
    auto array21 = TestDynamicArray<int>(int_array, 5);
    assert_equal(array21.getSize(), (unsigned)5);
    auto* double_array = new double[5];
    auto array22 = TestDynamicArray<double>(double_array, 5);
    assert_equal(array22.getSize(), (unsigned)5);
    delete[] int_array;
    delete[] double_array;
    return true;
}

bool check_set_and_get() {
    auto array1 = TestDynamicArray<int>(10);
    array1.set(0, 3);
    array1.set(1, 5);
    array1.set(2, 0);
    assert_equal(array1.get(0), 3, __FILE__, __LINE__);
    assert_equal(array1.get(1), 5, __FILE__, __LINE__);
    assert_equal(array1.get(2), 0, __FILE__, __LINE__);
    array1.getRef(0) = 1;
    array1.getRef(1) = 2;
    array1.getRef(2) = 3;
    assert_equal(array1.get(0), 1, __FILE__, __LINE__);
    assert_equal(array1.get(1), 2, __FILE__, __LINE__);
    assert_equal(array1.get(2), 3, __FILE__, __LINE__);
    auto array3 = make_shared<TestDynamicArray<int>>(5);
    array3->set(0, 1);
    array3->set(1, 2);
    array3->set(2, 3);
    auto array4 = TestDynamicArray<shared_ptr<TestDynamicArray<int>>>(10);
    array4.set(5, array3);
    assert_equal(array4.get(5)->get(2), 3, __FILE__, __LINE__);
    array3->set(2, 4);
    assert_equal(array4.get(5)->get(2), 4, __FILE__, __LINE__);
    return true;
}

bool check_subscript_operator() {
    auto array1 = TestDynamicArray<int>(10);
    array1[0] = 3;
    array1[1] = 5;
    array1[2] = 0;
    assert_equal(array1[0], 3, __FILE__, __LINE__);
    assert_equal(array1[1], 5, __FILE__, __LINE__);
    assert_equal(array1[2], 0, __FILE__, __LINE__);
    array1[0] = 1;
    array1[1] = 2;
    array1[2] = 3;
    assert_equal(array1[0], 1, __FILE__, __LINE__);
    assert_equal(array1[1], 2, __FILE__, __LINE__);
    assert_equal(array1[2], 3, __FILE__, __LINE__);
    auto array3 = make_shared<TestDynamicArray<int>>(5);
    (*array3)[0] = 1;
    (*array3)[1] = 2;
    (*array3)[2] = 3;
    auto array4 = TestDynamicArray<shared_ptr<TestDynamicArray<int>>>(10);
    array4[5] = array3;
    assert_equal((*(array4[5]))[2], 3, __FILE__, __LINE__);
    (*array3)[2] = 4;
    assert_equal((*(array4[5]))[2], 4, __FILE__, __LINE__);
    return true;
}

bool check_resize() {
    auto array1 = TestDynamicArray<int>();
    array1.resize(3);
    assert_equal(array1.getSize(), (unsigned)3);
    array1.set(0, 1);
    array1.set(1, 2);
    array1.set(2, 3);
    assert_equal(array1.get(0), 1);
    assert_equal(array1.get(1), 2);
    assert_equal(array1.get(2), 3);
    array1.resize(5);
    array1.set(3, 4);
    array1.set(4, 5);
    assert_equal(array1.get(3), 4);
    assert_equal(array1.get(4), 5);
    return true;
}

int main() {
    check_constructor_and_size();
    cout << "constructor TEST PASSED" << endl;

    check_set_and_get();
    cout << "set&get TEST PASSED" << endl;
    check_subscript_operator();
    cout << "operator[] TEST PASSED" << endl;
    check_resize();
    cout << "resize TEST PASSED" << endl;

    auto *array1 = new TestDynamicArray<int>();
    ASSERT(check_size(array1, 0, 0));
    print_test_separator();

    auto *array2 = new TestDynamicArray<int>(5);
    ASSERT(check_size(array2, 5, 1));
    print_test_separator();

    array1->resize(10);
    ASSERT(check_size(array1, 10, 2));
    print_test_separator();

    array1->set(0, 3);
    array1->set(3, 5);
    array1->set(5, 0);

    ASSERT(check_item_with_function_get(array1, 0, 3, 3));
    ASSERT(check_item_with_function_get(array1, 3, 5, 3));
    ASSERT(check_item_with_function_get(array1, 5, 0, 3));
    print_test_separator();

    array2->set(0, 1);
    array2->set(1, 2);
    array2->set(2, 3);
    array2->set(3, 4);
    array2->set(4, 5);

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

    auto *array3 = new TestDynamicArray<int>(items, 5);

    ASSERT(check_item_with_function_get(array3, 0, 1, 5));
    ASSERT(check_item_with_function_get(array3, 1, 2, 5));
    ASSERT(check_item_with_function_get(array3, 2, 4, 5));
    ASSERT(check_item_with_function_get(array3, 3, 8, 5));
    ASSERT(check_item_with_function_get(array3, 4, 16, 5));
    print_test_separator();

    auto *array4 = array3->clone();
    ASSERT(check_item_with_function_get(array4, 0, 1, 6));
    ASSERT(check_item_with_function_get(array4, 1, 2, 6));
    ASSERT(check_item_with_function_get(array4, 2, 4, 6));
    ASSERT(check_item_with_function_get(array4, 3, 8, 6));
    ASSERT(check_item_with_function_get(array4, 4, 16, 6));
    print_test_separator();

    delete array1;
    delete array2;
    delete array3;
    delete array4;

    auto *array5 = new TestDynamicArray<int *>(3);
    int x = 5;
    int y = 7;
    int z = 6;
    int *p2 = new int();
    int *p3 = new int(z);
    array5->set(0, &x);
    array5->set(1, p2);
    array5->set(2, p3);

    *(array5->getRef(1)) = y;

    ASSERT(check_value(array5->getRef(0), &x, 7));
    ASSERT(check_value(*(array5->getRef(1)), y, 7));
    ASSERT(check_value(array5->getRef(2), p3, 7));
    print_test_separator();

    auto *array6 = new TestDynamicArray<int *>();
    array6->resize(5);
    if (array6->getSize() < 5) {
        array6->resize(15);
    }
    for (int i = 0; i < 5; ++i) {
        array6->set(i, new int());
    }
    for (int i = 0; i < 5; ++i) {
        *(array6->getRef(i)) = i;
    }

    delete array6->getRef(0);
    delete array6->getRef(1);
    delete array6->getRef(2);
    delete array6->getRef(3);
    delete array6->getRef(4);
    delete array6;

    cout << "FINISH";
    return 0;
}
