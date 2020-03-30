#include <iostream>
#include "array_sequence.h"
#include "linked_list_sequence.h"


using namespace std;
void show(Sequence<int>* list) {
    int length = list->GetLength();
    cout << "list has length " << length << endl;
    for(int i = 0; i < length; i++) {
        cout << list->Get(i) << " ";
    }
    cout << endl << "-------" << endl;
}


int main() {
    int* items = (int*) malloc(sizeof(int) * 3);
    items[0] = 1;
    items[1] = 2;
    items[2] = 3;
    auto list1 = new ArraySequence<int>();
    list1->Append(1);
    list1->Append(2);
    list1->Append(3);
    list1->Prepend(4);
    show(list1);
    auto list2 = new LinkedListSequence<int>(items, 3);
    show(list2);
    *list1 == *list2;
    cout << (*list1)[0];
    return 0;
}
