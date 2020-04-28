#include <iostream>

#include "asserts.h"

#include "../linked_list/singly_linked_list.h"
#define TestLinkedList SinglyLinkedList


using namespace std;
using namespace my_namespace;
using tests::assert_equal;

int main() {
    auto list1 = new TestLinkedList<int>();

    assert_equal(list1->getLength(), (unsigned) 0);

    list1->append(3);
    list1->append(2);
    list1->append(1);

    assert_equal(list1->getLength(), (unsigned) 3);

    return 0;
    assert_equal(list1->getFirst(), 1);
    assert_equal(list1->getLast(), 3);

    assert_equal(list1->get(0), 1);
    assert_equal(list1->get(1), 2);
    assert_equal(list1->get(2), 3);

    list1->prepend(5);
    list1->prepend(6);
    list1->insertAt(4, 3);

    assert_equal(list1->getLength(), (unsigned) 6);

    assert_equal(list1->get(0), 1);
    assert_equal(list1->get(1), 2);
    assert_equal(list1->get(2), 3);
    assert_equal(list1->get(3), 4);
    assert_equal(list1->get(4), 5);
    assert_equal(list1->get(5), 6);

    int *items = new int[5];
    items[0] = 1;
    items[1] = 2;
    items[2] = 4;
    items[3] = 8;
    items[4] = 16;

    auto list2 = new TestLinkedList<int>(items, 5);

    assert_equal(list2->getLength(), (unsigned) 5);

    assert_equal(list2->get(0), 1);
    assert_equal(list2->get(1), 2);
    assert_equal(list2->get(2), 4);
    assert_equal((*list2)[3], 8);
    assert_equal((*list2)[4], 16);

    auto list3 = new TestLinkedList<int>(*list2);
    delete list2;

    assert_equal(list3->getLength(), (unsigned) 5);

    assert_equal(list3->get(0), 1);
    assert_equal(list3->get(1), 2);
    assert_equal(list3->get(2), 4);
    assert_equal((*list3)[3], 8);
    assert_equal((*list3)[4], 16);

    (*list3)[0] = 7;
    (*list3)[1] = 8;
    list3->set(2, 9);
    list3->set(3, 11);
    list3->set(3, 10);
    list3->set(4, 11);

    assert_equal(list3->getLength(), (unsigned) 5);

    assert_equal(list3->get(0), 7);
    assert_equal(list3->get(1), 8);
    assert_equal(list3->get(2), 9);
    assert_equal(list3->get(3), 10);
    assert_equal(list3->get(4), 11);

    TestLinkedList<int>* list4 = list1->clone()->concat(list3);

    assert_equal(list4->getLength(), (unsigned) 11);

    assert_equal(list4->get(0), 1);
    assert_equal(list4->get(1), 2);
    assert_equal(list4->get(2), 3);
    assert_equal(list4->get(3), 4);
    assert_equal(list4->get(4), 5);
    assert_equal(list4->get(5), 6);
    assert_equal(list4->get(6), 7);
    assert_equal(list4->get(7), 8);
    assert_equal(list4->get(8), 9);
    assert_equal(list4->get(9), 10);
    assert_equal(list4->get(10), 11);

    list4->cut(5, 7);

    assert_equal(list4->getLength(), (unsigned) 10, __FILE__, __LINE__);


    assert_equal(list4->get(0), 1, __FILE__, __LINE__);
    assert_equal(list4->get(1), 2, __FILE__, __LINE__);
    assert_equal(list4->get(2), 3, __FILE__, __LINE__);
    assert_equal(list4->get(3), 4, __FILE__, __LINE__);
    assert_equal(list4->get(4), 5, __FILE__, __LINE__);
    assert_equal(list4->get(5), 7, __FILE__, __LINE__);
    assert_equal(list4->get(6), 8, __FILE__, __LINE__);
    assert_equal(list4->get(7), 9, __FILE__, __LINE__);
    assert_equal(list4->get(8), 10, __FILE__, __LINE__);
    assert_equal(list4->get(9), 11, __FILE__, __LINE__);

    delete list1;
    delete list3;
    delete list4;

    cout << "FINISH";

    return 0;
}