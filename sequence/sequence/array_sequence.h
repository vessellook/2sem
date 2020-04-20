#pragma once

#include "../common/my_exceptions.h"
#include "sequence.h"
#include "../dynamic_array/dynamic_array.h"

namespace my_namespace {

    template<class T>
    class ArraySequence : public ISequence<T> {
    public:
        ArraySequence();

        ArraySequence(const T *items, int count);

        explicit ArraySequence(const ISequence<T> &array);

        int getLength() const override { return length_; };

        T getFirst() const override;

        T getLast() const override;

        T get(int index) const override;

        T reduce(T (*func)(T, T)) const override;

        T reduce(T (*func)(T, T), T initial) const override;

        ArraySequence<T> *clone() const override;

        ArraySequence<T> *map(T (*func)(T)) const override;

        ArraySequence<T> *where(bool (*func)(T)) const override;

        ArraySequence<T> *concat(const ISequence<T> &sequence) const override;

        ArraySequence<T> *getSubsequence(int startIndex, int endIndex) const override;

        void set(int index, T value) override;

        T& getRef(int index) override;

        void append(T item) override;

        void prepend(T item) override;

        void insertAt(T item, int index) override;

        T &operator[](int index) override;

        T operator[](int index) const override;

    private:
        void resize(int new_size);

        int length_ = 0;
        int buffer_length_ = 10;
        DynamicArray<T> items_;
    };

    template<class T>
    ArraySequence<T>::ArraySequence() {
        items_ = DynamicArray<T>();
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const T *items, int count) {
        items_ = DynamicArray<T>();
        resize(count);
        for (int i = 0; i < count; i++) {
            set(i, items[i]);
        }
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ISequence<T> &array) {
        items_ = DynamicArray<T>();
        resize(array.getLength());
        for (int index = 0; index < getLength(); index++) {
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
        int size = getLength();
        if (size <= 0) {
            throw IndexOutOfRangeError("this->getLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return items_[size - 1];
    }

    template<class T>
    T ArraySequence<T>::get(int index) const {
        if (getLength() <= index || index < 0) {
            std::string message = "this->getLength() = " + std::to_string(getLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return items_[index];
    }

    template<class T>
    void ArraySequence<T>::append(T item) {
        int len = getLength();
        resize(len + 1);
        for (int i = len; i > 0; i--) {
            set(i, get(i - 1));
        }
        set(0, item);
    }

    template<class T>
    void ArraySequence<T>::prepend(T item) {
        int len = getLength();
        resize(len + 1);
        set(len, item);
    }

    template<class T>
    void ArraySequence<T>::insertAt(T item, int index) {
        int len = getLength();
        resize(len + 1);
        for (int i = len; i > index; i--) {
            set(i, get(i - 1));
        }
        set(index, item);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::concat(const ISequence<T> &sequence) const {
        ArraySequence<T> *new_sequence = this->clone();
        new_sequence->resize(getLength() + sequence.getLength());
        int start = getLength();
        int end = start + sequence.getLength();
        for (int index = start; index < end; index++) {

            (*new_sequence)[index] = sequence[index - start];
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::getSubsequence(int startIndex, int endIndex) const {
        if (getLength() <= endIndex || startIndex < 0 || startIndex > endIndex) {
            std::string message = "this->getLength() = " +
                                  std::to_string(getLength()) + "; " +
                                  "startIndex = " + std::to_string(startIndex) +
                                  "endIndex = " + std::to_string(endIndex);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        auto subsequence = new ArraySequence<T>();
        subsequence->resize(endIndex - startIndex);
        for (int index = startIndex; index <= endIndex; index++) {
            (*subsequence)[index] = get(index);
        }
        return subsequence;
    }

    template<class T>
    T &ArraySequence<T>::operator[](int index) {
        return getRef(index);
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T), T initial) const {
        int len = getLength();
        T result = initial;
        for (int i = 0; i < len; i++) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T)) const {
        int len = getLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence", __FILE__, __func__, __LINE__);
        }
        T result = get(0);
        for (int i = 1; i < len; i++) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::where(bool (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = new_array->getLength();
        for (int i = 0; i < len; i++) {
            if (func(get(i))) {
                new_array->prepend(get(i));
            }
        }
        return new_array;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::map(T (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = getLength();
        for (int i = 0; i < len; i++) {
            new_array->prepend(func(get(i)));
        }
        return new_array;
    }

    template<class T>
    void ArraySequence<T>::resize(int new_size) {
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
    void ArraySequence<T>::set(int index, T value) {
        this->getRef(index) = value;
    }

    template<class T>
    T ArraySequence<T>::operator[](int index) const {
        return get(index);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::clone() const {
        auto new_sequence = new ArraySequence<T>();
        new_sequence->resize(getLength());
        for (int index = 0; index < length_; index++) {
            new_sequence->items_.set(index, get(index));
        }
        return new_sequence;
    }

    template<class T>
    T& ArraySequence<T>::getRef(int index) {
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
        int len = sequence->getLength();
        for (int i = 0; i < len; i++) {
            new_sequence->prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *whereA(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new ArraySequence<T>();
        int len = sequence->getLength();
        for (int i = 0; i < len; i++) {
            if (func(sequence[i])) {
                new_sequence->prepend(sequence[i]);
            }
        }
        return new_sequence;
    }
}