#include <iostream>

#include "macro_and_functions_for_tests.h"
#include "../linked_list/singly_linked_list.h"

#define TestLinkedList SinglyLinkedList

using namespace std;
using namespace my_namespace;

template<class T>
bool check_length(const TestLinkedList<T> *list, unsigned expected_length, unsigned test_num) {
    if (list->getLength() != expected_length) {
        cout << "TEST " << test_num << ": " << "FAILED: expected list length " << expected_length << ", but got " << list->getLength() << endl;
        return false;
    }
#ifdef SHOW_TEST_PASSED
    cout << "TEST " << test_num << ": " << "PASSED: got list length " << list->getLength() << endl;
#endif
    return true;
}

template<class T>
bool check_item_with_get(const TestLinkedList<T> *list, unsigned index, T expected_value, unsigned test_num) {
    T value = list->get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_item_with_subscript_operator(TestLinkedList<T> *list, unsigned index, T expected_value, unsigned test_num) {
    T value = (*list)[index];
    return check_value(value, expected_value, test_num);
}

int main() {
    auto list1 = new TestLinkedList<int>();
    ASSERT(check_length(list1, 0, 0));
    print_test_separator();

    list1->append(3);
    list1->append(2);
    list1->append(1);

    ASSERT(check_length(list1, 3, 1));
    print_test_separator();

    ASSERT(check_value(list1->getFirst(), 1, 2));
    print_test_separator();

    ASSERT(check_value(list1->getLast(), 3, 3));
    print_test_separator();

    ASSERT(check_item_with_get(list1, 0, 1, 4));
    ASSERT(check_item_with_get(list1, 1, 2, 4));
    ASSERT(check_item_with_get(list1, 2, 3, 4));
    print_test_separator();

    list1->prepend(5);
    list1->prepend(6);
    list1->insertAt(4, 3);

    ASSERT(check_length(list1, 6, 5));
    print_test_separator();

    ASSERT(check_item_with_get(list1, 0, 1, 6));
    ASSERT(check_item_with_get(list1, 1, 2, 6));
    ASSERT(check_item_with_get(list1, 2, 3, 6));
    ASSERT(check_item_with_get(list1, 3, 4, 6));
    ASSERT(check_item_with_get(list1, 4, 5, 6));
    ASSERT(check_item_with_get(list1, 5, 6, 6));
    print_test_separator();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto list2 = new TestLinkedList<int>(items, 5);

    ASSERT(check_length(list2, 5, 7));
    print_test_separator();

    ASSERT(check_item_with_subscript_operator(list2, 0, 1, 8));
    ASSERT(check_item_with_subscript_operator(list2, 1, 2, 8));
    ASSERT(check_item_with_get(list2, 2, 4, 8));
    ASSERT(check_item_with_get(list2, 3, 8, 8));
    ASSERT(check_item_with_get(list2, 4, 16, 8));
    print_test_separator();

    auto list3 = new TestLinkedList<int>(*list2);
    delete list2;

    ASSERT(check_length(list3, 5, 9));
    print_test_separator();

    ASSERT(check_item_with_get(list3, 0, 1, 9));
    ASSERT(check_item_with_get(list3, 1, 2, 9));
    ASSERT(check_item_with_get(list3, 2, 4, 9));
    ASSERT(check_item_with_subscript_operator(list3, 3, 8, 9));
    ASSERT(check_item_with_subscript_operator(list3, 4, 16, 9));
    print_test_separator();

    (*list3)[0] = 7;
    (*list3)[1] = 8;
    list3->set(2, 9);
    list3->set(3, 11);
    list3->set(3, 10);
    list3->set(4, 11);

    ASSERT(check_length(list3, 5, 10));
    print_test_separator();

    ASSERT(check_item_with_get(list3, 0, 7, 11));
    ASSERT(check_item_with_get(list3, 1, 8, 11));
    ASSERT(check_item_with_get(list3, 2, 9, 11));
    ASSERT(check_item_with_get(list3, 3, 10, 11));
    ASSERT(check_item_with_get(list3, 4, 11, 11));
    print_test_separator();

    auto list4 = list1->concat(list3);

    ASSERT(check_length(list4, 11, 12));
    print_test_separator();

    ASSERT(check_item_with_get(list4, 0, 1, 13));
    ASSERT(check_item_with_get(list4, 1, 2, 13));
    ASSERT(check_item_with_get(list4, 2, 3, 13));
    ASSERT(check_item_with_get(list4, 3, 4, 13));
    ASSERT(check_item_with_get(list4, 4, 5, 13));
    ASSERT(check_item_with_get(list4, 5, 6, 13));
    ASSERT(check_item_with_get(list4, 6, 7, 13));
    ASSERT(check_item_with_get(list4, 7, 8, 13));
    ASSERT(check_item_with_get(list4, 8, 9, 13));
    ASSERT(check_item_with_get(list4, 9, 10, 13));
    ASSERT(check_item_with_get(list4, 10, 11, 13));
    print_test_separator();

    delete list1;
    delete list3;
    delete list4;

    cout << "FINISH";

    return 0;
}