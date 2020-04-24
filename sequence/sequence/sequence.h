#pragma once

namespace my_namespace {

    template<class T>
    class ISequence {
    public:
        virtual ~ISequence() = default;

        virtual unsigned getLength() const = 0;

        virtual T getFirst() const = 0;

        virtual T getLast() const = 0;

        virtual T get(unsigned index) const = 0;

        virtual T& getRef(unsigned index) = 0;

        virtual T reduce(T (*func)(T, T)) const = 0;

        virtual T reduce(T (*func)(T, T), T initial) const = 0;

        virtual ISequence<T> *clone() const = 0;

        virtual ISequence<T> *map(T (*func)(T)) const = 0;

        virtual ISequence<T> *where(bool (*func)(T)) const = 0;

        virtual ISequence<T> *concat(const ISequence<T> &list) const = 0;

        virtual ISequence<T> *getSubsequence(unsigned startIndex, unsigned endIndex) const = 0;

        virtual ISequence<T> *set(unsigned index, T value) { this[0][index] = value; }

        virtual ISequence<T> *append(T item) = 0;

        virtual ISequence<T> *prepend(T item) = 0;

        virtual ISequence<T> *insertAt(T item, unsigned index) = 0;

        virtual T &operator[](unsigned index) = 0;

        virtual T operator[](unsigned index) const { return get(index); }
    };

// extra

    template<class T>
    bool operator==(const ISequence<T> &sequence1, const ISequence<T> &sequence2) {
        if (sequence1.getLength() != sequence2.getLength()) {
            return false;
        }
        unsigned len = sequence1.getLength();
        for (unsigned i = 0; i < len; ++i) {
            if (sequence1.get(i) != sequence2.get(i)) {
                return false;
            }
        }
        return true;
    }

}