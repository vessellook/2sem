#pragma once

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H

template <class T>
class Sequence {
public:
//    Sequence();
//    Sequence(T* items, int count);
//    Sequence(const Sequence<T> const &list);

    virtual int GetLength() const = 0;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual T Reduce(T (*func)(T, T), T initial) const = 0;
    virtual T Reduce(T (*func)(T, T)) const = 0;
    virtual Sequence<T>* MapNew(T (*func)(T)) const = 0;
    virtual Sequence<T>* WhereNew(bool (*func)(T)) const = 0;
    virtual Sequence<T>* Concat(const Sequence<T> *list) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual void MapThis(T (*func)(T)) = 0;
    virtual void WhereThis(bool (*func)(T)) = 0;

    virtual T& operator[](int index) = 0;
    virtual Sequence<T>* operator+(const Sequence<T>* sequence) const = 0;
    virtual Sequence<T>* operator-(const Sequence<T>* sequence) const = 0;
    virtual Sequence<T>* operator*(T scalar) = 0;
};

template <class T>
bool operator==(const Sequence<T>* sequence1, const Sequence<T>* sequence2) {
    int len = sequence1->GetLength();
    if (sequence2->GetLength() != len) {
        return false;
    }
    for(int i = 0; i < len; i++) {
        if (sequence1->Get(i) != sequence2->Get(i)) {
            return false;
        }
    }
    return true;
}
#endif //SEQUENCE_SEQUENCE_H
