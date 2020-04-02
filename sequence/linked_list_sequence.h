#pragma once

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

    int GetLength() const override;
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    T Reduce(T (*func)(T), T initial) const override;
    T Reduce(T (*func)(T)) const override;
    Sequence<T>* MapNew(T (*func)(T)) const override;
    Sequence<T>* WhereNew(bool (*func)(T)) const override;
    Sequence<T>* Concat(const Sequence<T> * list) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;

    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    void MapThis(T (*func)(T)) override;
    void WhereThis(bool (*func)(T)) override;


    T& operator[](int index) override;
    Sequence<T>* operator+(Sequence<T>* sequence) override;
    Sequence<T>* operator-(Sequence<T>* sequence) override;
    Sequence<T>* operator*(T scalar) override;
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
T LinkedListSequence<T>::GetFirst() const {
    return this->items->GetFirst();
}

template <class T>
T LinkedListSequence<T>::GetLast() const {
    return this->items->GetLast();
}

template <class T>
T LinkedListSequence<T>::Get(int index) const {
    return this->items->Get(index);
}

template <class T>
Sequence<T>* LinkedListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    auto sublist = this->items->GetSubList(startIndex, endIndex);
    auto subsequence = new LinkedListSequence<T>();
    int length = sublist->GetLength();
    for(int i = 0; i < length; i++) {
        subsequence->Append(sublist->Get(i));
    }
    return subsequence;
}

template <class T>
int LinkedListSequence<T>::GetLength() const {
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
void LinkedListSequence<T>::MapThis(T(*func)(T)) {
    int len = this->items->GetLength();
    T value;
    for(int i = 0; i < len; i++) {
        value = this->items->Get(i);
        value = func(value);
        this->items->Set(i, value);
    }
}

template <class T>
void LinkedListSequence<T>::WhereThis(bool (*func)(T)) {
    int len = this->items->GetLength();
    auto new_items = new LinkedList<T>();
    T item;
    for(int i = 0; i < len; i++) {
        item = this->items[i];
        if(func(item)) {
            new_items->Prepend(item);
        }
    }
    delete this->items;
    this->items = new_items;
}

template <class T>
Sequence<T>* LinkedListSequence<T>::Concat(const Sequence<T> * list) const {
    auto new_list = new LinkedListSequence<T>(* this);
    int start = this->GetLength();
    int end = start + list->GetLength();
    for(int index = start; index < end; index++) {
        new_list->Prepend(list->Get(index - start));
    }
    return new_list;
}

template <class T>
T& LinkedListSequence<T>::operator[](int index) {
    if(this->GetLength() <= index || index < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    return this->items[index];
}

template<class T>
Sequence<T> *LinkedListSequence<T>::operator+(Sequence<T> *sequence) {
    if(this->GetLength() != sequence->GetLength()) {
        throw MyError("DifferentLengthsOfSequencesError");
    }
    int len = this->GetLength();
    auto new_sequence = new LinkedListSequence<T>(len);
    for(int i = 0; i < len; i++) {
        new_sequence[i] = this[i] + sequence[i];
    }
    return new_sequence;
}

#endif //SEQUENCE_LINKED_LIST_SEQUENCE_H
