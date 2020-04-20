#pragma once

namespace my_namespace {

    template<class T>
    class ISequence {
    public:
        virtual ~ISequence() = default;

        virtual int getLength() const = 0;

        virtual T getFirst() const = 0;

        virtual T getLast() const = 0;

        virtual T get(int index) const = 0;

        virtual T& getRef(int index) = 0;

        virtual T reduce(T (*func)(T, T)) const = 0;

        virtual T reduce(T (*func)(T, T), T initial) const = 0;

        virtual ISequence<T> *clone() const = 0;

        virtual ISequence<T> *map(T (*func)(T)) const = 0;

        virtual ISequence<T> *where(bool (*func)(T)) const = 0;

        virtual ISequence<T> *concat(const ISequence<T> &list) const = 0;

        virtual ISequence<T> *getSubsequence(int startIndex, int endIndex) const = 0;

        virtual void set(int index, T value) { this[0][index] = value; }

        virtual void append(T item) = 0;

        virtual void prepend(T item) = 0;

        virtual void insertAt(T item, int index) = 0;

        virtual T &operator[](int index) = 0;

        virtual T operator[](int index) const { return get(index); }
    };

// extra

    template<class T>
    bool operator==(const ISequence<T> &sequence1, const ISequence<T> &sequence2) {
        if (sequence1.getLength() != sequence2.getLength()) {
            return false;
        }
        int len = sequence1.getLength();
        for (int i = 0; i < len; i++) {
            if (sequence1.get(i) != sequence2.get(i)) {
                return false;
            }
        }
        return true;
    }

}