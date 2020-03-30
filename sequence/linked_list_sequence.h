#ifndef SEQUENCE_LINKED_LIST_SEQUENCE_H
#define SEQUENCE_LINKED_LIST_SEQUENCE_H

#include "sequence.h"
#include "linked_list.h"

template <class T>
class LinkedListSequence: public Sequence<T> {
public:
    LinkedListSequence();
    LinkedListSequence(T* items, int count);
    LinkedListSequence(LinkedListSequence<T> & list);
    T GetFirst() override;
    T GetLast() override;
    T Get(int index) override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override;
    int GetLength() override;
    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> * list) override;
protected:
    LinkedList<T>* items = nullptr;
};

template <class T>
LinkedListSequence<T>::LinkedListSequence() {
    this->items = new LinkedList<T>();
}

template <class T>
LinkedListSequence<T>::LinkedListSequence(T* items, int count) {
    this->items = new LinkedList<T>(items, count);
}

template <class T>
LinkedListSequence<T>::LinkedListSequence(LinkedListSequence<T> & list) {
    this->items = new LinkedList<T>();
    int length = list.GetLength();
    for(int i = 0; i < length; i++) {
        this->items->Prepend(list.Get(i));
    }
}

template <class T>
T LinkedListSequence<T>::GetFirst() {
    return this->items->GetFirst();
}

template <class T>
T LinkedListSequence<T>::GetLast() {
    return this->items->GetLast();
}

template <class T>
T LinkedListSequence<T>::Get(int index) {
    return this->items->Get(index);
}

template <class T>
Sequence<T>* LinkedListSequence<T>::GetSubsequence(int startIndex, int endIndex) {
    auto sublist = this->items->GetSubList(startIndex, endIndex);
    auto subsequence = new LinkedListSequence<T>();
    int length = sublist->GetLength();
    for(int i = 0; i < length; i++) {
        subsequence->Append(sublist->Get(i));
    }
    return subsequence;
}

template <class T>
int LinkedListSequence<T>::GetLength() {
    return this->items->GetLength();
}

template <class T>
void LinkedListSequence<T>::Append(T item) {
    this->items->Append(item);
}

template <class T>
void LinkedListSequence<T>::Prepend(T item) {
    this->items->Prepend(item);
}

template <class T>
void LinkedListSequence<T>::InsertAt(T item, int index) {
    this->items->InsertAt(item, index);
}

template <class T>
Sequence<T>* LinkedListSequence<T>::Concat(Sequence<T> * list) {
    auto new_list = new LinkedListSequence<T>(* this);
    int start = this->GetLength();
    int end = start + list->GetLength();
    for(int index = start; index < end; index++) {
        new_list->Prepend(list->Get(index - start));
    }
    return new_list;
}
#endif //SEQUENCE_LINKED_LIST_SEQUENCE_H
