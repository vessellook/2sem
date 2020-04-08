#include <iostream>

#include "macro_for_tests.h"

#include "../sequence/array_sequence.h"

#define TestSequence ArraySequence

//#include "linked_list_sequence.h"
//#define TestSequence LinkedListSequence

using namespace std;
using namespace my_namespace;

template<class T>
bool check_length(const TestSequence<T> *sequence, int expected_length, int test_num) {
    cout << "TEST " << test_num << ": ";
    if (sequence->GetLength() != expected_length) {
        cout << "FAILED: expected sequence length " << expected_length << ", but got " << sequence->GetLength() << endl;
        return false;
    }
    cout << "PASSED: got sequence length " << sequence->GetLength() << endl;
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
bool check_item_with_function_Get(const TestSequence<T> *sequence, int index, T expected_value, int test_num) {
    T value = sequence->Get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_value_with_subscript_operator(TestSequence<T> *sequence, int index, T expected_value, int test_num) {
    T value = (*sequence)[index];
    return check_value(value, expected_value, test_num);
}

int main() {

    auto sequence1 = new TestSequence<int>();
    ASSERT(check_length(sequence1, 0, 0));
    WHITESPACE();

    sequence1->Append(3);
    sequence1->Append(2);
    sequence1->Append(1);

    ASSERT(check_length(sequence1, 3, 1));
    WHITESPACE();

    ASSERT(check_value(sequence1->GetFirst(), 1, 2));
    WHITESPACE();

    ASSERT(check_value(sequence1->GetLast(), 3, 3));
    WHITESPACE();

    ASSERT(check_item_with_function_Get(sequence1, 0, 1, 4));
    ASSERT(check_item_with_function_Get(sequence1, 1, 2, 4));
    ASSERT(check_item_with_function_Get(sequence1, 2, 3, 4));
    WHITESPACE();

    sequence1->Prepend(5);
    sequence1->Prepend(6);
    sequence1->InsertAt(4, 3);

    ASSERT(check_length(sequence1, 6, 5));
    WHITESPACE();

    ASSERT(check_item_with_function_Get(sequence1, 0, 1, 6));
    ASSERT(check_item_with_function_Get(sequence1, 1, 2, 6));
    ASSERT(check_item_with_function_Get(sequence1, 2, 3, 6));
    ASSERT(check_item_with_function_Get(sequence1, 3, 4, 6));
    ASSERT(check_item_with_function_Get(sequence1, 4, 5, 6));
    ASSERT(check_item_with_function_Get(sequence1, 5, 6, 6));
    WHITESPACE();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto sequence2 = new TestSequence<int>(items, 5);


    ASSERT(check_length(sequence2, 5, 7));
    WHITESPACE();

    ASSERT(check_value_with_subscript_operator(sequence2, 0, 1, 8));
    ASSERT(check_value_with_subscript_operator(sequence2, 1, 2, 8));
    ASSERT(check_item_with_function_Get(sequence2, 2, 4, 8));
    ASSERT(check_item_with_function_Get(sequence2, 3, 8, 8));
    ASSERT(check_item_with_function_Get(sequence2, 4, 16, 8));
    WHITESPACE();

    auto sequence3 = new TestSequence<int>(*sequence2);
    delete sequence2;

    ASSERT(check_length(sequence3, 5, 9));
    WHITESPACE();

    ASSERT(check_item_with_function_Get(sequence3, 0, 1, 9));
    ASSERT(check_item_with_function_Get(sequence3, 1, 2, 9));
    ASSERT(check_item_with_function_Get(sequence3, 2, 4, 9));
    ASSERT(check_value_with_subscript_operator(sequence3, 3, 8, 9));
    ASSERT(check_value_with_subscript_operator(sequence3, 4, 16, 9));
    WHITESPACE();

    (*sequence3)[0] = 7;
    (*sequence3)[1] = 8;
    (*sequence3)[2] = 9;
    (*sequence3)[3] = 11;
    (*sequence3)[3] = 10;
    (*sequence3)[4] = 11;

    ASSERT(check_length(sequence3, 5, 10));
    WHITESPACE();

    ASSERT(check_item_with_function_Get(sequence3, 0, 7, 11));
    ASSERT(check_item_with_function_Get(sequence3, 1, 8, 11));
    ASSERT(check_item_with_function_Get(sequence3, 2, 9, 11));
    ASSERT(check_item_with_function_Get(sequence3, 3, 10, 11));
    ASSERT(check_item_with_function_Get(sequence3, 4, 11, 11));
    WHITESPACE();

    auto sequence4 = sequence1->Concat(sequence3);
    delete sequence1;

    ASSERT(check_length(sequence4, 11, 12));
    WHITESPACE();

    ASSERT(check_item_with_function_Get(sequence4, 0, 1, 13));
    ASSERT(check_item_with_function_Get(sequence4, 1, 2, 13));
    ASSERT(check_item_with_function_Get(sequence4, 2, 3, 13));
    ASSERT(check_item_with_function_Get(sequence4, 3, 4, 13));
    ASSERT(check_item_with_function_Get(sequence4, 4, 5, 13));
    ASSERT(check_item_with_function_Get(sequence4, 5, 6, 13));
    ASSERT(check_item_with_function_Get(sequence4, 6, 7, 13));
    ASSERT(check_item_with_function_Get(sequence4, 7, 8, 13));
    ASSERT(check_item_with_function_Get(sequence4, 8, 9, 13));
    ASSERT(check_item_with_function_Get(sequence4, 9, 10, 13));
    ASSERT(check_item_with_function_Get(sequence4, 10, 11, 13));
    WHITESPACE();

    delete sequence3;
    delete sequence4;

    cout << "FINISH";
    return 0;
}