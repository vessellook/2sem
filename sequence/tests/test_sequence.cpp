#include <iostream>

#include "macro_and_functions_for_tests.h"
#include "../common/my_functions.h"

//#include "../sequence/array_sequence.h"
//#define TestSequence ArraySequence

#include "../sequence/linked_list_sequence.h"
#define TestSequence LinkedListSequence

using namespace std;
using namespace my_namespace;

template <class T>
void show_pointers(ISequence<T>& sequence, const string& name = "") {
    unsigned len = sequence.getLength();
    cout << "start of " << name << endl;
    for(unsigned i = 0; i < len; ++i) {
        cout << &(sequence[i]) << endl;
    }
    cout << "end of " << name << endl;
}

#include "../ui/simple_ui.h"
using simple_ui::show;
template<class T>
bool check_length(const ISequence<T> *sequence, unsigned expected_length, unsigned test_num) {
    if (sequence->getLength() != expected_length) {
        cout << "TEST " << test_num << ": " << "FAILED: expected sequence length " << expected_length << ", but got " << sequence->getLength() << endl;
        return false;
    }
#ifdef SHOW_TEST_PASSED
    cout << "TEST " << test_num << ": " << "PASSED: got sequence length " << sequence->getLength() << endl;
#endif
    return true;
}

template<class T>
bool check_item_with_function_get(const ISequence<T> *sequence, unsigned index, T expected_value, unsigned test_num) {
    T value = sequence->get(index);
    return check_value(value, expected_value, test_num);
}

template<class T>
bool check_value_with_subscript_operator(ISequence<T> *sequence, unsigned index, T expected_value, unsigned test_num) {
    T value = (*sequence)[index];
    return check_value(value, expected_value, test_num);
}

int main() {

    ISequence<int>* sequence1 = new TestSequence<int>();
    unsigned task_num = 0;
    ASSERT(check_length(sequence1, 0, task_num));
    print_test_separator();

    sequence1->append(3);
    sequence1->append(2);
    sequence1->append(1);

    task_num = 1;
    ASSERT(check_length(sequence1, 3, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_value(sequence1->getFirst(), 1, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_value(sequence1->getLast(), 3, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_item_with_function_get(sequence1, 0, 1, task_num));
    ASSERT(check_item_with_function_get(sequence1, 1, 2, task_num));
    ASSERT(check_item_with_function_get(sequence1, 2, 3, task_num));
    print_test_separator();

    sequence1->prepend(5);
    sequence1->prepend(6);
    sequence1->insertAt(4, 3);

    task_num = 5;
    ASSERT(check_length(sequence1, 6, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_item_with_function_get(sequence1, 0, 1, task_num));
    ASSERT(check_item_with_function_get(sequence1, 1, 2, task_num));
    ASSERT(check_item_with_function_get(sequence1, 2, 3, task_num));
    ASSERT(check_item_with_function_get(sequence1, 3, 4, task_num));
    ASSERT(check_item_with_function_get(sequence1, 4, 5, task_num));
    ASSERT(check_item_with_function_get(sequence1, 5, 6, task_num));
    print_test_separator();

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    ISequence<int>* sequence2 = new TestSequence<int>(items, 5);

    task_num = 7;
    ASSERT(check_length(sequence2, 5, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_value_with_subscript_operator(sequence2, 0, 1, task_num));
    ASSERT(check_value_with_subscript_operator(sequence2, 1, 2, task_num));
    ASSERT(check_item_with_function_get(sequence2, 2, 4, task_num));
    ASSERT(check_item_with_function_get(sequence2, 3, 8, task_num));
    ASSERT(check_item_with_function_get(sequence2, 4, 16, task_num));
    print_test_separator();

    ISequence<int>* sequence3 = sequence2->clone();
    show_pointers(*sequence1);
    show_pointers(*sequence2);
    show_pointers(*sequence3);
    delete sequence2;

    task_num = 9;
    ASSERT(check_length(sequence3, 5, ++task_num));
    print_test_separator();

    ASSERT(check_item_with_function_get(sequence3, 0, 1, task_num));
    ASSERT(check_item_with_function_get(sequence3, 1, 2, task_num));
    ASSERT(check_item_with_function_get(sequence3, 2, 4, task_num));
    ASSERT(check_value_with_subscript_operator(sequence3, 3, 8, task_num));
    ASSERT(check_value_with_subscript_operator(sequence3, 4, 16, task_num));
    print_test_separator();

    (*sequence3)[0] = 7;
    (*sequence3)[1] = 8;
    (*sequence3)[2] = 9;
    (*sequence3)[3] = 11;
    (*sequence3)[3] = 10;
    (*sequence3)[4] = 11;

    task_num = 11;
    ASSERT(check_length(sequence3, 5, task_num));
    print_test_separator();

    ++task_num;
    ASSERT(check_item_with_function_get(sequence3, 0, 7, task_num));
    ASSERT(check_item_with_function_get(sequence3, 1, 8, task_num));
    ASSERT(check_item_with_function_get(sequence3, 2, 9, task_num));
    ASSERT(check_item_with_function_get(sequence3, 3, 10, task_num));
    ASSERT(check_item_with_function_get(sequence3, 4, 11, task_num));
    print_test_separator();

    ISequence<int>* sequence4 = sequence1->clone()->concat(*sequence3);
    delete sequence1;
//    show(sequence4);
    task_num = 13;
    ASSERT(check_length(sequence4, 11, ++task_num));
    print_test_separator();

    ASSERT(check_item_with_function_get(sequence4, 0, 1, task_num));
    ASSERT(check_item_with_function_get(sequence4, 1, 2, task_num));
    ASSERT(check_item_with_function_get(sequence4, 2, 3, task_num));
    ASSERT(check_item_with_function_get(sequence4, 3, 4, task_num));
    ASSERT(check_item_with_function_get(sequence4, 4, 5, task_num));
    ASSERT(check_item_with_function_get(sequence4, 5, 6, task_num));
    ASSERT(check_item_with_function_get(sequence4, 6, 7, task_num));
    ASSERT(check_item_with_function_get(sequence4, 7, 8, task_num));
    ASSERT(check_item_with_function_get(sequence4, 8, 9, task_num));
    ASSERT(check_item_with_function_get(sequence4, 9, 10, task_num));
    ASSERT(check_item_with_function_get(sequence4, 10, 11, ++task_num));
    print_test_separator();
    delete sequence3;
    delete sequence4;

    ISequence<int>* sequence5 = new TestSequence<int>();
    sequence5->append(2);

    MulWrapper<int>::setValue(3);
    ISequence<int>* sequence6 = sequence5->map(MulWrapper<int>::Mul);
//    show(sequence6);
    delete sequence6;

    TestSequence<shared_ptr<TestSequence<int>>> sequence7;
    cout << "FINISH";
    return 0;
}