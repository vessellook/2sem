#include <iostream>
#include "dynamic_array.h"

using namespace std;

int main() {
    auto array1 = new DynamicArray<int>();

    int len = array1->GetSize();
    if (len != 0) {
        cout << "TEST FAILED: expected array size 0, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got array size 0" << endl;

    auto array2 = new DynamicArray<int>(5);
    len = array2->GetSize();
    if(len != 5) {
        cout << "TEST FAILED: expected array size 5, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got array size 5" << endl;

    array1->Resize(10);
    len = array1->GetSize();
    if(len != 10) {
        cout << "TEST FAILED: expected array size 10, but got " << len << endl;
        return 0;
    }
    cout << "TEST PASSED: got array size 10" << endl;

    array1->Set(0, 3);
    array1->Set(3, 5);
    array1->Set(5, 0);
    int value = array1->Get(0);
    if (value != 3) {
        cout << "TEST FAILED: set value 3 and got value " << value << endl;
        return 0;
    }
    value = array1->Get(3);
    if (value != 5) {
        cout << "TEST FAILED: set value 5 and got value " << value << endl;
        return 0;
    }
    value = array1->Get(5);
    if (value != 0) {
        cout << "TEST FAILED: set value 0 and got value " << value << endl;
        return 0;
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;


    array2->Set(0, 1);
    array2->Set(1, 2);
    array2->Set(2, 3);
    array2->Set(3, 4);
    array2->Set(4, 5);
    cout << "TEST PASSED: real array size not less than got array size" << endl;
    for(int i = 0; i < 5; i++) {
        value = array2->Get(i);
        if (value != i + 1) {
            cout << "TEST FAILED: expected value " << i+1 << ", got value " << value << endl;
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

    auto array3 = new DynamicArray<int>(items, 5);
    for(int i = 0; i < 5; i++) {
        value = array3->Get(i);
        if (value != items[i]) {
            cout << "TEST FAILED: expected value " << items[i] << ", got value " << value << endl;
            return 0;
        }
    }
    cout << "TEST PASSED: set values and got values are equal" << endl;
    delete array1;
    delete array2;
    delete array3;
    cout << "TEST PASSED: delete array don't make errors" << endl;
    return 0;
}


