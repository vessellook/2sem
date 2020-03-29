#ifndef SEQUENCE_ARRAY_SEQUENCE_H
#define SEQUENCE_ARRAY_SEQUENCE_H

#include "my_exceptions.h"
#include "sequence.h"
#include "dynamic_array.h"

template <class T>
class ArraySequence: public Sequence<T> {
public:
    ArraySequence();
    ArraySequence(T* items, int count);
    ArraySequence(ArraySequence<T> & array);
    T GetFirst() override;
    T GetLast() override;
    T Get(int index) override;
    int GetLength() override;
    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T> * list) override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex);
protected:
    DynamicArray<T>* items;
};

template <class T>
ArraySequence<T>::ArraySequence() {
    this->items = new DynamicArray<T>() ;
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    this->items = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(ArraySequence<T> & array) {
    this->items = new DynamicArray<T>();
    int length = array.GetLength();
    for(int i = 0; i < length; i++) {
        this->items->Set(i, array.Get(i));
    }
}

template <class T>
T ArraySequence<T>::GetFirst() {
    return this->items->Get(0);
}

template <class T>
T ArraySequence<T>::GetLast() {
    int size = this->items->GetSize();
    if(size <= 0) {
        throw IndexOutOfRange();
    }
    return this->items->Get(size - 1);
}

template  <class T>
T ArraySequence<T>::Get(int index) {
return this->items->Get(index);
}

template <class T>
int ArraySequence<T>::GetLength() {
    return this->items->GetSize();
}

template <class T>
void ArraySequence<T>::Append(T item) {
    int len = this->items->GetSize();
    this->items->Resize(len + 1);
    for(int i = len; i > 0; i--) {
        this->items->Set(i, this->items->Get(i-1));
    }
    this->items->Set(0, item);
}

template <class T>
void ArraySequence<T>::Prepend(T item) {
    int len = this->items->GetSize();
    this->items->Resize(len + 1);
    this->items->Set(len, item);
}

template <class T>
void ArraySequence<T>::InsertAt(T item, int index) {
    int len = this->items->GetSize();
    this->items->Resize(len + 1);
    for(int i = len; i > index - 1; i--) {
        this->items->Set(i+1, this->items->Get(i));
    }
    this->items->Set(index, item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T> * list) {
    auto new_list = new ArraySequence(* this);
    int start = this->GetLength();
    int end = start + list->GetLength();
    for(int index = start; index < end; index++) {
        new_list->Prepend(list->Get(index - start));
    }
    return new_list;
}

template <class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) {
    if (this->items->GetSize() <= endIndex || startIndex < 0 || startIndex > endIndex) {
        throw IndexOutOfRange();
    }
    auto subsequence = new ArraySequence<T>();
    for(int i = startIndex; i <= endIndex; i++) {
        subsequence->Append(this->items->Get(i));
    }
    return subsequence;
}
#endif //SEQUENCE_ARRAY_SEQUENCE_H
