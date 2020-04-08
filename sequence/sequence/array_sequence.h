#pragma once

#include "../common/my_exceptions.h"
#include "sequence.h"
#include "../dynamic_array/dynamic_array.h"

namespace my_namespace {

    template<class T>
    class ArraySequence : public ISequence<T> {
    public:
        ArraySequence();

        ArraySequence(T *items, int count);

        ArraySequence(const ArraySequence<T> &array);

        ~ArraySequence() override;

        int GetLength() const override;

        T GetFirst() const override;

        T GetLast() const override;

        T Get(int index) const override;

        T Reduce(T (*func)(T, T)) const override;

        T Reduce(T (*func)(T, T), T initial) const override;

        ArraySequence<T> *Map(T (*func)(T)) const override;

        ArraySequence<T> *Where(bool (*func)(T)) const override;

        ArraySequence<T> *Concat(const ISequence<T> *list) const override;

        ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) const override;

        void Append(T item) override;

        void Prepend(T item) override;

        void InsertAt(T item, int index) override;

        T &operator[](int index) override;

    protected:
        void Resize(int new_size);

        int length_ = 0;
        DynamicArray<T> *items_ = nullptr;
    };

    template<class T>
    ArraySequence<T>::ArraySequence() {
        this->items_ = new DynamicArray<T>();
    }

    template<class T>
    ArraySequence<T>::ArraySequence(T *items, int count) {
        this->items_ = new DynamicArray<T>(items, count);
        this->length_ = count;
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ArraySequence<T> &array) {
        this->length_ = array.GetLength();
        this->items_ = new DynamicArray<T>(this->length_ + 10);
        for (int i = 0; i < this->length_; i++) {
            this->items_->Set(i, T(array.Get(i)));
        }
    }

    template<class T>
    ArraySequence<T>::~ArraySequence() {
        delete this->items_;
    }

    template<class T>
    T ArraySequence<T>::GetFirst() const {
        if (this->GetLength() <= 0) {
            throw IndexOutOfRangeError("this->GetLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return this->items_->Get(0);
    }

    template<class T>
    T ArraySequence<T>::GetLast() const {
        int size = this->GetLength();
        if (size <= 0) {
            throw IndexOutOfRangeError("this->GetLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return this->items_->Get(size - 1);
    }

    template<class T>
    T ArraySequence<T>::Get(int index) const {
        if (this->GetLength() <= index || index < 0) {
            std::string message = "this->GetLength() = " + std::to_string(this->GetLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return this->items_->Get(index);
    }

    template<class T>
    int ArraySequence<T>::GetLength() const {
        return this->length_;
    }

    template<class T>
    void ArraySequence<T>::Append(T item) {
        int len = this->GetLength();
        this->Resize(len + 1);
        for (int i = len; i > 0; i--) {
            (*this)[i] = (*this)[i - 1];
        }
        this->items_->Set(0, item);
    }

    template<class T>
    void ArraySequence<T>::Prepend(T item) {
        int len = this->GetLength();
        this->Resize(len + 1);
        this->items_->Set(len, item);
    }

    template<class T>
    void ArraySequence<T>::InsertAt(T item, int index) {
        int len = this->GetLength();
        this->Resize(len + 1);
        for (int i = len; i > index; i--) {
            this->items_->Set(i, this->items_->Get(i - 1));
        }
        this->items_->Set(index, item);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Concat(const ISequence<T> *list) const {
        auto new_list = new ArraySequence(*this);
        int start = this->GetLength();
        int end = start + list->GetLength();
        for (int index = start; index < end; index++) {
            new_list->Prepend(list->Get(index - start));
        }
        return new_list;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
        if (this->GetLength() <= endIndex || startIndex < 0 || startIndex > endIndex) {
            throw MyError("IndexOutOfRangeError");
        }
        auto subsequence = new ArraySequence<T>();
        for (int i = startIndex; i <= endIndex; i++) {
            subsequence->Append(this->items_->Get(i));
        }
        return subsequence;
    }

    template<class T>
    T &ArraySequence<T>::operator[](int index) {
        if (this->GetLength() <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return (*(this->items_))[index];
    }

    template<class T>
    T ArraySequence<T>::Reduce(T (*func)(T, T), T initial) const {
        int len = this->GetLength();
        T result = initial;
        for (int i = 0; i < len; i++) {
            result = func(result, this->Get(i));
        }
        return result;
    }

    template<class T>
    T ArraySequence<T>::Reduce(T (*func)(T, T)) const {
        int len = this->GetLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence");
        }
        T result = this->Get(0);
        for (int i = 1; i < len; i++) {
            result = func(result, this->Get(i));
        }
        return result;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Where(bool (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = new_array->GetLength();
        for (int i = 0; i < len; i++) {
            if (func((*new_array)[i])) {
                new_array->Prepend((*new_array)[i]);
            }
        }
        return new_array;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::Map(T (*func)(T)) const {
        auto new_array = new ArraySequence<T>();
        int len = this->GetLength();
        for (int i = 0; i < len; i++) {
            if (func(this->items_->Get(i))) {
                new_array->Prepend(this->items_->Get(i));
            }
        }
        return new_array;
    }

    template<class T>
    void ArraySequence<T>::Resize(int new_size) {
        if (new_size < 0) {
            std::string message = "new_size = " + std::to_string(new_size);
            throw ResizeToNegativeSizeError(message, __FILE__, __func__, __LINE__);
        }
        if (this->items_->GetSize() < new_size) {
            this->items_->Resize(new_size + 10);
        }
        this->length_ = new_size;
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