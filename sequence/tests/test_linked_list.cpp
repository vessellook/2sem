#include <iostream>

#include "macro_for_tests.h"
#include "../linked_list/linked_list.h"

using namespace std;
using namespace my_namespace;

template<class T>
bool check_length(const LinkedList<T> *list, int expected_length, int test_num) {
    cout << "TEST " << test_num << ": ";
    if (list->GetLength() != expected_length) {
        cout << "FAILED: expected list length " << expected_length << ", but got " << list->GetLength() << endl;
        return false;
    }
    cout << "PASSED: got list length " << list->GetLength() << endl;
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
bool check_item_with_Get(const LinkedList<T> *list, int index, T expected_value, int test_num) {
    T value = list->Get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_item_with_subscript_operator(LinkedList<T> *list, int index, T expected_value, int test_num) {
    T value = (*list)[index];
    return check_value(value, expected_value, test_num);
}

int main() {
    auto list1 = new LinkedList<int>();
    ASSERT(check_length(list1, 0, 0));
    WHITESPACE();

    list1->Append(3);
    list1->Append(2);
    list1->Append(1);

    ASSERT(check_length(list1, 3, 1));
    WHITESPACE();

    ASSERT(check_value(list1->GetFirst(), 1, 2));
    WHITESPACE();

    ASSERT(check_value(list1->GetLast(), 3, 3));
    WHITESPACE();

    ASSERT(check_item_with_Get(list1, 0, 1, 4));
    ASSERT(check_item_with_Get(list1, 1, 2, 4));
    ASSERT(check_item_with_Get(list1, 2, 3, 4));
    WHITESPACE();

    list1->Prepend(5);
    list1->Prepend(6);
    list1->InsertAt(4, 3);

    ASSERT(check_length(list1, 6, 5));
    WHITESPACE();

    ASSERT(check_item_with_Get(list1, 0, 1, 6));
    ASSERT(check_item_with_Get(list1, 1, 2, 6));
    ASSERT(check_item_with_Get(list1, 2, 3, 6));
    ASSERT(check_item_with_Get(list1, 3, 4, 6));
    ASSERT(check_item_with_Get(list1, 4, 5, 6));
    ASSERT(check_item_with_Get(list1, 5, 6, 6));
    WHITESPACE();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto list2 = new LinkedList<int>(items, 5);

    ASSERT(check_length(list2, 5, 7));
    WHITESPACE();

    ASSERT(check_item_with_subscript_operator(list2, 0, 1, 8));
    ASSERT(check_item_with_subscript_operator(list2, 1, 2, 8));
    ASSERT(check_item_with_Get(list2, 2, 4, 8));
    ASSERT(check_item_with_Get(list2, 3, 8, 8));
    ASSERT(check_item_with_Get(list2, 4, 16, 8));
    WHITESPACE();

    auto list3 = new LinkedList<int>(*list2);
    delete list2;

    ASSERT(check_length(list3, 5, 9));
    WHITESPACE();

    ASSERT(check_item_with_Get(list3, 0, 1, 9));
    ASSERT(check_item_with_Get(list3, 1, 2, 9));
    ASSERT(check_item_with_Get(list3, 2, 4, 9));
    ASSERT(check_item_with_subscript_operator(list3, 3, 8, 9));
    ASSERT(check_item_with_subscript_operator(list3, 4, 16, 9));
    WHITESPACE();

    (*list3)[0] = 7;
    (*list3)[1] = 8;
    list3->Set(2, 9);
    list3->Set(3, 11);
    list3->Set(3, 10);
    list3->Set(4, 11);

    ASSERT(check_length(list3, 5, 10));
    WHITESPACE();

    ASSERT(check_item_with_Get(list3, 0, 7, 11));
    ASSERT(check_item_with_Get(list3, 1, 8, 11));
    ASSERT(check_item_with_Get(list3, 2, 9, 11));
    ASSERT(check_item_with_Get(list3, 3, 10, 11));
    ASSERT(check_item_with_Get(list3, 4, 11, 11));
    WHITESPACE();

    auto list4 = list1->Concat(list3);

    ASSERT(check_length(list4, 11, 12));
    WHITESPACE();

    ASSERT(check_item_with_Get(list4, 0, 1, 13));
    ASSERT(check_item_with_Get(list4, 1, 2, 13));
    ASSERT(check_item_with_Get(list4, 2, 3, 13));
    ASSERT(check_item_with_Get(list4, 3, 4, 13));
    ASSERT(check_item_with_Get(list4, 4, 5, 13));
    ASSERT(check_item_with_Get(list4, 5, 6, 13));
    ASSERT(check_item_with_Get(list4, 6, 7, 13));
    ASSERT(check_item_with_Get(list4, 7, 8, 13));
    ASSERT(check_item_with_Get(list4, 8, 9, 13));
    ASSERT(check_item_with_Get(list4, 9, 10, 13));
    ASSERT(check_item_with_Get(list4, 10, 11, 13));
    WHITESPACE();

    delete list1;
    delete list3;
    delete list4;

    cout << "FINISH";

    return 0;
}