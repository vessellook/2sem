#pragma once

template <class T>
class Sequence {
public:
//    Sequence();
//    Sequence(T* items, int count);
//    Sequence(const Sequence<T> const &list);
    virtual ~Sequence() = default;
    static bool equal(Sequence<T> sequence1, Sequence<T> sequence2) {
        return true;
    }

    virtual int GetLength() const = 0;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual T Reduce(T (*func)(T, T)) const = 0;
    virtual T Reduce(T (*func)(T, T), T initial) const = 0;
    virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    virtual Sequence<T>* Where(bool (*func)(T)) const = 0;
    virtual Sequence<T>* Concat(const Sequence<T> *list) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;

    virtual T& operator[](int index) = 0;
//    virtual Sequence<T>* operator+(const Sequence<T>* sequence) const = 0;
//    virtual Sequence<T>* operator-(const Sequence<T>* sequence) const = 0;
//    virtual Sequence<T>* operator*(T scalar) = 0;
};

// extra

//template <class T>
//T Reduce(T (*func)(T, T), Sequence<T>* sequence, T initial) {
//    int len = sequence->GetLength();
//    T result = initial;
//    for(int i = 0; i < len; i++) {
//        result = func(result, sequence[i]);
//    }
//    return result;
//}
//
//template <class T>
//T Reduce(T (*func)(T, T), Sequence<T>* sequence) {
//    int len = sequence->GetLength();
//    if(len <= 0) {
//        throw MyError("Reduce to empty sequence");
//    }
//    T result = sequence[0];
//    for(int i = 1; i < len; i++) {
//        result = func(result, sequence[i]);
//    }
//    return result;
//}
