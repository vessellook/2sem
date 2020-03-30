#include <iostream>
#include "linked_list.h"

using namespace std;


int main() {
    auto list1 = new LinkedList<int>();
    int len = list1->GetLength();
    if (len != 0) {
        cout << "TEST FAILED: expected list length 0, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got list length 0" << endl;

    list1->Append(3);
    list1->Append(2);
    list1->Append(1);
    len = list1->GetLength();
    if (len != 3) {
        cout << "TEST FAILED: expected list length 3, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got list length 3" << endl;

    int value = list1->GetFirst();
    if(value != 1) {
        cout << "TEST FAILED: expected value 1, but got " << value << endl;
        return 0;
    }
    cout << "TEST PASSED: got first item 1" << endl;

    value = list1->GetLast();
    if(value != 3) {
        cout << "TEST FAILED: expected value 3, but got " << value << endl;
        return 0;
    }
    cout << "TEST PASSED: got last item 3" << endl;

    for(int i = 0; i < len; i++) {
        value = list1->Get(i);
        if(value != i+1) {
            cout << "TEST FAILED: expected value " << i+1 <<", but got " << value << endl;
            return 0;
        }
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;

    list1->Prepend(5);
    list1->Prepend(6);
    list1->InsertAt(4, 3);

    len = list1->GetLength();
    if (len != 6) {
        cout << "TEST FAILED: expected list length 6, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got list length 6" << endl;

    for(int i = 0; i < len; i++) {
        value = list1->Get(i);
        if(value != i+1) {
            cout << "TEST FAILED: expected value " << i+1 <<", but got " << value << endl;
            return 0;
        }
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;

    int* items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto list2 = new LinkedList<int>(items, 5);
    len = list2->GetLength();
    if (len != 5) {
        cout << "TEST FAILED: expected list length 5, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got list length 5" << endl;

    for(int i = 0; i < 5; i++) {
        value = list2->Get(i);
        if (value != items[i]) {
            cout << "TEST FAILED: expected value " << items[i] << ", got value " << value << endl;
            return 0;
        }
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;

    auto list3 = new LinkedList<int>(* list2);
    len = list3->GetLength();
    if (len != 5) {
        cout << "TEST FAILED: expected list length 5, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got list length 5" << endl;

    for(int i = 0; i < 5; i++) {
        value = list3->Get(i);
        if (value != items[i]) {
            cout << "TEST FAILED: expected value " << items[i] << ", got value " << value << endl;
            return 0;
        }
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;
    delete(list1);
    delete(list2);
    delete(list3);
    cout << "TEST PASSED: delete(list) don't make errors" << endl;

    return 0;
}