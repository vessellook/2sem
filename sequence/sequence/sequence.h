#pragma once

#include "../config.h"

namespace my_namespace {

    template<class T>
    class ISequence {
    public:
        virtual ~ISequence() = default;

        virtual int GetLength() const = 0;

        virtual T GetFirst() const = 0;

        virtual T GetLast() const = 0;

        virtual T Get(int index) const = 0;

        virtual T Reduce(T (*func)(T, T)) const = 0;

        virtual T Reduce(T (*func)(T, T), T initial) const = 0;

        virtual ISequence<T> *Clone() const = 0;

        virtual ISequence<T> *Map(T (*func)(T)) const = 0;

        virtual ISequence<T> *Where(bool (*func)(T)) const = 0;

        virtual ISequence<T> *Concat(const ISequence<T> &list) const = 0;

        virtual ISequence<T> *GetSubsequence(int startIndex, int endIndex) const = 0;

        virtual void Set(int index, T value) { this[0][index] = value; }

        virtual void Append(T item) = 0;

        virtual void Prepend(T item) = 0;

        virtual void InsertAt(T item, int index) = 0;

        virtual T &operator[](int index) = 0;

        virtual T operator[](int index) const { return Get(index); }
    };

// extra

    template<class T>
    bool operator==(const ISequence<T> &sequence1, const ISequence<T> &sequence2) {
        if (sequence1.GetLength() != sequence2.GetLength()) {
            return false;
        }
        int len = sequence1.GetLength();
        for (int i = 0; i < len; i++) {
            if (sequence1.Get(i) != sequence2.Get(i)) {
                return false;
            }
        }
        return true;
    }

}