#pragma once

#include "sequence.h"
#include "linked_list.h"

template <class T>
class LinkedListSequence: public Sequence<T> {
public:
    LinkedListSequence();
    LinkedListSequence(T* items, int count);
    LinkedListSequence(const LinkedListSequence<T> & list);
    ~LinkedListSequence() override;

    int GetLength() const override;
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    T Reduce(T (*func)(T, T)) const override;
    T Reduce(T (*func)(T, T), T initial) const override;
    LinkedListSequence<T>* Map(T (*func)(T)) const override;
    LinkedListSequence<T>* Where(bool (*func)(T)) const override;
    LinkedListSequence<T>* Concat(const Sequence<T> * list) const override;
    LinkedListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override;

    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;


    T& operator[](int index) override;
//    Sequence<T>* operator+(Sequence<T>* sequence) override;
//    Sequence<T>* operator-(Sequence<T>* sequence) override;
//    Sequence<T>* operator*(T scalar) override;
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
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T> & list) {
    this->items = new LinkedList<T>();
    int length = list.GetLength();
    for(int i = 0; i < length; i++) {
        this->items->Prepend(T(list.Get(i)));
    }
}


template<class T>
LinkedListSequence<T>::~LinkedListSequence() {
    delete this->items;
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
LinkedListSequence<T>* LinkedListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
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
LinkedListSequence<T>* LinkedListSequence<T>::Concat(const Sequence<T> * list) const {
    auto new_list = new LinkedListSequence<T>(*this);
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
        std::string message = "this->GetLength() = " + std::to_string(this->GetLength())
                + "; index = " + std::to_string(index);
        throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
    }
    return (*(this->items))[index];
}

//template<class T>
//Sequence<T> *LinkedListSequence<T>::operator+(Sequence<T> *sequence) {
//    if(this->GetLength() != sequence->GetLength()) {
//        throw MyError("DifferentLengthsOfSequencesError");
//    }
//    int len = this->GetLength();
//    auto new_sequence = new LinkedListSequence<T>(len);
//    for(int i = 0; i < len; i++) {
//        new_sequence[i] = this[i] + sequence[i];
//    }
//    return new_sequence;
//}
//
//template<class T>
//Sequence<T> *LinkedListSequence<T>::operator-(Sequence<T> *sequence) {
//    if(this->GetLength() != sequence->GetLength()) {
//        throw MyError("DifferentLengthsOfSequencesError");
//    }
//    int len = this->GetLength();
//    auto new_sequence = new LinkedListSequence<T>(len);
//    for(int i = 0; i < len; i++) {
//        new_sequence[i] = this[i] - sequence[i];
//    }
//    return new_sequence;
//}
//
//template<class T>
//Sequence<T> *LinkedListSequence<T>::operator*(T scalar) {
//    int len = this->GetLength();
//    auto new_sequence = new LinkedListSequence<T>(len);
//    for(int i = 0; i < len; i++) {
//        new_sequence[i] = this[i] * scalar;
//    }
//    return new_sequence;
//}

template <class T>
T LinkedListSequence<T>::Reduce(T (*func)(T, T), T initial) const {
    return this->items->Reduce(func, initial);
}

template <class T>
T LinkedListSequence<T>::Reduce(T (*func)(T, T)) const {
    if(this->GetLength() <= 0) {
        throw MyError("Reduce to empty sequence");
    }
    return this->items->Reduce(func);
}

template<class T>
LinkedListSequence<T> *LinkedListSequence<T>::Map(T (*func)(T)) const {
    auto new_sequence = new LinkedListSequence<T>();
    new_sequence->items = this->items->Map(func);
    return new_sequence;
}

template<class T>
LinkedListSequence<T> *LinkedListSequence<T>::Where(bool (*func)(T)) const {
    auto new_sequence = new LinkedListSequence<T>();
    new_sequence->items = this->items->Where(func);
    return new_sequence;
}


// extra

template <class F, class T>
LinkedListSequence<T>* MapL(T (*func) (T), const Sequence<F> * sequence) {
    auto new_sequence = new LinkedListSequence<T>();
    int len = sequence->GetLength();
    for(int i = 0; i < len; i++) {
        new_sequence->Prepend(func(sequence[i]));
    }
    return new_sequence;
}

template<class T>
LinkedListSequence<T>* WhereL(bool (*func)(T), const Sequence<T> * sequence) {
    auto new_sequence = new LinkedListSequence<T>();
    int len = sequence->GetLength();
    for(int i = 0; i < len; i++) {
        if(func(sequence[i])) {
            new_sequence->Prepend(sequence[i]);
        }
    }
    return new_sequence;
}
