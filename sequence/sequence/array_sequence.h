#pragma once

#include "../config.h"
#include "../common/my_exceptions.h"
#include "sequence.h"
#include "../dynamic_array/dynamic_array.h"

namespace my_namespace {

    template<class T>
    class ArraySequence : public ISequence<T> {
    public:
        ArraySequence();

        ArraySequence(const T *items, int count);

        ArraySequence(const ISequence<T> &array);

        ~ArraySequence() override;

        int GetLength() const override { return length_; };

        T GetFirst() const override;

        T GetLast() const override;

        T Get(int index) const override;

        T Reduce(T (*func)(T, T)) const override;

        T Reduce(T (*func)(T, T), T initial) const override;

        ArraySequence<T> *Clone() const override;

        ArraySequence<T> *Map(T (*func)(T)) const override;

        ArraySequence<T> *Where(bool (*func)(T)) const override;

        ArraySequence<T> *Concat(const ISequence<T> &sequence) const override;

        ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) const override;

        void Set(int index, T value) override;

        void Append(T item) override;

        void Prepend(T item) override;

        void InsertAt(T item, int index) override;

        T &operator[](int index) override;

        T operator[](int index) const override;
    private:
        void Resize(int new_size);

        int length_ = 0;
        int buffer_length_ = 10;
        DynamicArray<T>* items_ = nullptr;
    };

    template<class T>
    ArraySequence<T>::ArraySequence() {
        items_ = new DynamicArray<T>();
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const T *items, int count) {
        items_ = new DynamicArray<T>();
        Resize(count);
        for (int i = 0; i < count; i++) {
            Set(i, items[i]);
        }
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ISequence<T> &array) {
        items_ = new DynamicArray<T>();
        Resize(array.GetLength());
        for (int index = 0; index < GetLength(); index++) {
            Set(index, array[index]);
        }
    }

    template<class T>
    ArraySequence<T>::~ArraySequence() {
        if (items_ == nullptr) {
            return;
        }
        delete items_;
    }

    template<class T>
    T ArraySequence<T>::GetFirst() const {
        if (GetLength() <= 0) {
            throw IndexOutOfRangeError("this->GetLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return (*items_)[0];
    }

    template<class T>
    T ArraySequence<T>::GetLast() const {
        int size = GetLength();
        if (size <= 0) {
            throw IndexOutOfRangeError("this->GetLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return (*items_)[size - 1];
    }

    template<class T>
    T ArraySequence<T>::Get(int index) const {
        if (GetLength() <= index || index < 0) {
            std::string message = "this->GetLength() = " + std::to_string(GetLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return (*items_)[index];
    }

    template<class T>
    void ArraySequence<T>::Append(T item) {
        int len = GetLength();
        Resize(len + 1);
        for (int i = len; i > 0; i--) {
            Set(i, Get(i-1));
        }
        Set(0, item);
    }

    template<class T>
    void ArraySequence<T>::Prepend(T item) {
        int len = GetLength();
        Resize(len + 1);
        Set(len, item);
    }

    template<class T>
    void ArraySequence<T>::InsertAt(T item, int index) {
        int len = GetLength();
        Resize(len + 1);
        for (int i = len; i > index; i--) {
            Set(i, Get(i-1));
        }
        Set(index, item);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Concat(const ISequence<T> &sequence) const {
        ArraySequence<T>* new_sequence = this->Clone();
        new_sequence->Resize(GetLength() + sequence.GetLength());
        int start = GetLength();
        int end = start + sequence.GetLength();
        for (int index = start; index < end; index++) {

            (*new_sequence)[index] = sequence[index - start];
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
        if (GetLength() <= endIndex || startIndex < 0 || startIndex > endIndex) {
            std::string message = "this->GetLength() = " +
                                  std::to_string(GetLength()) + "; " +
                                  "startIndex = " + std::to_string(startIndex) +
                                  "endIndex = " + std::to_string(endIndex);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        auto subsequence = new ArraySequence<T>();
        subsequence->Resize(endIndex - startIndex);
        for (int index = startIndex; index <= endIndex; index++) {
            (*subsequence)[index] = Get(index);
        }
        return subsequence;
    }

    template<class T>
    T &ArraySequence<T>::operator[](int index) {
        if (GetLength() <= index || index < 0) {
            std::string message = "this->GetLength() = " +
                                  std::to_string(GetLength()) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return (*items_)[index];
    }

    template<class T>
    T ArraySequence<T>::Reduce(T (*func)(T, T), T initial) const {
        int len = GetLength();
        T result = initial;
        for (int i = 0; i < len; i++) {
            result = func(result, Get(i));
        }
        return result;
    }

    template<class T>
    T ArraySequence<T>::Reduce(T (*func)(T, T)) const {
        int len = GetLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence", __FILE__, __func__, __LINE__);
        }
        T result = Get(0);
        for (int i = 1; i < len; i++) {
            result = func(result, Get(i));
        }
        return result;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Where(bool (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = new_array->GetLength();
        for (int i = 0; i < len; i++) {
            if (func(Get(i))) {
                new_array->Prepend(Get(i));
            }
        }
        return new_array;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Map(T (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = GetLength();
        for (int i = 0; i < len; i++) {
            new_array->Prepend(func(Get(i)));
        }
        return new_array;
    }

    template<class T>
    void ArraySequence<T>::Resize(int new_size) {
        if (new_size < 0) {
            std::string message = "new_size = " + std::to_string(new_size);
            throw ResizeToNegativeSizeError(message, __FILE__, __func__, __LINE__);
        }
        if (items_->GetSize() < new_size) {
            items_->Resize(new_size + buffer_length_);
        }
        length_ = new_size;
    }

    template<class T>
    void ArraySequence<T>::Set(int index, T value) {
        (*this)[index] = value;
    }

    template<class T>
    T ArraySequence<T>::operator[](int index) const {
        return Get(index);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Clone() const {
        auto new_sequence = new ArraySequence<T>();
        new_sequence->Resize(GetLength());
        for (int index = 0; index < length_; index++) {
            new_sequence->items_->Set(index, Get(index));
        }
        return new_sequence;
    }

// extra

    template<class F, class T>
    ArraySequence<T> *MapA(T (*func)(F), const ISequence<F> *sequence) {
        auto new_sequence = new ArraySequence<T>();
        int len = sequence->GetLength();
        for (int i = 0; i < len; i++) {
            new_sequence->Prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    ArraySequence<T> *WhereA(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new ArraySequence<T>();
        int len = sequence->GetLength();
        for (int i = 0; i < len; i++) {
            if (func(sequence[i])) {
                new_sequence->Prepend(sequence[i]);
            }
        }
        return new_sequence;
    }
}