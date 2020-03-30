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
    T operator[](int index);
};

template <class T>
bool operator==(Sequence<T> & sequence1, Sequence<T> & sequence2) {
    int len = sequence1.GetLength();
    if (sequence2.GetLength() != len) {
        return false;
    }
    for(int i = 0; i < len; i++) {
        if (sequence1.Get(i) != sequence2.Get(i)) {
            return false;
        }
    }
    return true;
}

template <class T>
T Sequence<T>::operator[](int index) {
    return this->Get(index);
}

#endif //SEQUENCE_SEQUENCE_H
