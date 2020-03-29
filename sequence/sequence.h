#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H

template <class T>
class Sequence {
public:
//    Sequence();
//    Sequence(T* items, int count);
//    Sequence(const Sequence<T> const &list);
    virtual Sequence<T> * GetSubsequence(int startIndex, int endIndex) = 0;
    virtual Sequence <T>* Concat(Sequence <T> *list) = 0;
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
};

#endif //SEQUENCE_SEQUENCE_H
