#pragma once

#include "../common/exceptions.h"
#include "sequence.h"
#include "../dynamic_array/dynamic_array.h"

namespace my_namespace {

    template<class T>
    class ArraySequence : public ISequence<T> {
    private:
        DynamicArray<T> items_;
        unsigned length_ = 0;
        unsigned buffer_length_ = 10;
    private:
        void resize(unsigned new_size);
    public:
        ArraySequence();

        ArraySequence(const T *items, unsigned count);

        explicit ArraySequence(const ISequence<T> &array);

        unsigned getLength() const override { return length_; };

        T getFirst() const override;

        T getLast() const override;

        T get(unsigned index) const override;

        T reduce(T (*func)(T, T)) const override;

        T reduce(T (*func)(T, T), T initial) const override;

        ArraySequence<T> *clone() const override;

        ArraySequence<T> *map(T (*func)(T)) const override;

        ArraySequence<T> *where(bool (*func)(T)) const override;

        ArraySequence<T> *concat(const ISequence<T> &sequence) const override;

        ArraySequence<T> *getSubsequence(unsigned startIndex, unsigned endIndex) const override;

        ArraySequence<T> *set(unsigned index, T value) override;

        T& getRef(unsigned index) override;

        ArraySequence<T> *append(T item) override;

        ArraySequence<T> *prepend(T item) override;

        ArraySequence<T> *insertAt(T item, unsigned index) override;

        T &operator[](unsigned index) override;

        T operator[](unsigned index) const override;
    };

    template<class T>
    ArraySequence<T>::ArraySequence(): items_() {
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const T *items, unsigned count): items_() {
        resize(count);
        for (unsigned i = 0; i < count; ++i) {
            set(i, items[i]);
        }
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ISequence<T> &array) {
        items_ = DynamicArray<T>();
        resize(array.getLength());
        for (unsigned index = 0; index < getLength(); ++index) {
            set(index, array[index]);
        }
    }

    template<class T>
    T ArraySequence<T>::getFirst() const {
        if (getLength() <= 0) {
            throw IndexOutOfRangeError("this->getLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return items_[0];
    }

    template<class T>
    T ArraySequence<T>::getLast() const {
        unsigned size = getLength();
        if (size <= 0) {
            throw IndexOutOfRangeError("this->getLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return items_[size - 1];
    }

    template<class T>
    T ArraySequence<T>::get(unsigned index) const {
        if (getLength() <= index || index < 0) {
            std::string message = "this->getLength() = " + std::to_string(getLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return items_[index];
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::append(T item) {
        unsigned len = getLength();
        resize(len + 1);
        for (unsigned i = len; i > 0; i--) {
            set(i, get(i - 1));
        }
        set(0, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::prepend(T item) {
        unsigned len = getLength();
        resize(len + 1);
        set(len, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::insertAt(T item, unsigned index) {
        unsigned len = getLength();
        resize(len + 1);
        for (unsigned i = len; i > index; i--) {
            set(i, get(i - 1));
        }
        set(index, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::concat(const ISequence<T> &sequence) const {
        ArraySequence<T> *new_sequence = this->clone();
        new_sequence->resize(getLength() + sequence.getLength());
        unsigned start = getLength();
        unsigned end = start + sequence.getLength();
        for (unsigned index = start; index < end; ++index) {

            (*new_sequence)[index] = sequence[index - start];
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::getSubsequence(unsigned startIndex, unsigned endIndex) const {
        if (getLength() <= endIndex || startIndex < 0 || startIndex > endIndex) {
            std::string message = "this->getLength() = " +
                                  std::to_string(getLength()) + "; " +
                                  "startIndex = " + std::to_string(startIndex) +
                                  "endIndex = " + std::to_string(endIndex);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        auto subsequence = new ArraySequence<T>();
        subsequence->resize(endIndex - startIndex);
        for (unsigned index = startIndex; index <= endIndex; ++index) {
            (*subsequence)[index] = get(index);
        }
        return subsequence;
    }

    template<class T>
    T &ArraySequence<T>::operator[](unsigned index) {
        return getRef(index);
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T), T initial) const {
        unsigned len = getLength();
        T result = initial;
        for (unsigned i = 0; i < len; ++i) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T)) const {
        unsigned len = getLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence", __FILE__, __func__, __LINE__);
        }
        T result = get(0);
        for (unsigned i = 1; i < len; ++i) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::where(bool (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        unsigned len = new_array->getLength();
        for (unsigned i = 0; i < len; ++i) {
            if (func(get(i))) {
                new_array->prepend(get(i));
            }
        }
        return new_array;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::map(T (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        unsigned len = getLength();
        for (unsigned i = 0; i < len; ++i) {
            new_array->prepend(func(get(i)));
        }
        return new_array;
    }

    template<class T>
    void ArraySequence<T>::resize(unsigned new_size) {
        if (new_size < 0) {
            std::string message = "new_size = " + std::to_string(new_size);
            throw resizeToNegativeSizeError(message, __FILE__, __func__, __LINE__);
        }
        if (items_.getSize() < new_size) {
            items_.resize(new_size + buffer_length_);
        }
        length_ = new_size;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::set(unsigned index, T value) {
        this->items_[index] = value;
        return this;
    }

    template<class T>
    T ArraySequence<T>::operator[](unsigned index) const {
        return get(index);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::clone() const {
        auto new_sequence = new ArraySequence<T>();
        new_sequence->resize(getLength());
        for (unsigned index = 0; index < length_; ++index) {
            new_sequence->items_.set(index, get(index));
        }
        return new_sequence;
    }

    template<class T>
    T& ArraySequence<T>::getRef(unsigned index) {
        if (getLength() <= index || index < 0) {
            std::string message = "this->getLength() = " +
                                  std::to_string(getLength()) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return items_[index];
    }

// extra

    template<class F, class T>
    ArraySequence<T> *mapA(T (*func)(F), const ISequence<F> *sequence) {
        auto new_sequence = new ArraySequence<T>();
        unsigned len = sequence->getLength();
        for (unsigned i = 0; i < len; ++i) {
            new_sequence->prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *whereA(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new ArraySequence<T>();
        unsigned len = sequence->getLength();
        for (unsigned i = 0; i < len; ++i) {
            if (func(sequence[i])) {
                new_sequence->prepend(sequence[i]);
            }
        }
        return new_sequence;
    }
}