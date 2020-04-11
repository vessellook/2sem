#pragma once

#include "../config.h"
#include "sequence.h"
#include "../linked_list/linked_list.h"

namespace my_namespace {

    template<class T>
    class LinkedListSequence : public ISequence<T> {
    public:
        LinkedListSequence();

        LinkedListSequence(T *items, index_type count);

        explicit LinkedListSequence(const ISequence<T> &list);

        ~LinkedListSequence() override;

        index_type GetLength() const override;

        T GetFirst() const override;

        T GetLast() const override;

        T Get(index_type index) const override;

        T Reduce(T (*func)(T, T)) const override;

        T Reduce(T (*func)(T, T), T initial) const override;

        LinkedListSequence<T> *Clone() const override;

        LinkedListSequence<T> *Map(T (*func)(T)) const override;

        LinkedListSequence<T> *Where(bool (*func)(T)) const override;

        LinkedListSequence<T> *Concat(const ISequence<T> &list) const override;

        LinkedListSequence<T> *GetSubsequence(index_type startIndex, index_type endIndex) const override;

        void Append(T item) override;

        void Prepend(T item) override;

        void InsertAt(T item, index_type index) override;


        T &operator[](index_type index) override;

        T operator[](index_type index) const override { return Get(index); }

    protected:
        LinkedList<T> *items_ = nullptr;
    };

    template<class T>
    LinkedListSequence<T>::LinkedListSequence() {
        items_ = new LinkedList<T>();
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(T *items, index_type count) {
        items_ = new LinkedList<T>(items, count);
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const ISequence<T> &list) {
        items_ = new LinkedList<T>();
        index_type length = list.GetLength();
        for (index_type i = 0; i < length; i++) {
            items_->Prepend(T(list.Get(i)));
        }
    }


    template<class T>
    LinkedListSequence<T>::~LinkedListSequence() {
        delete items_;
    }

    template<class T>
    T LinkedListSequence<T>::GetFirst() const {
        return items_->GetFirst();
    }

    template<class T>
    T LinkedListSequence<T>::GetLast() const {
        return items_->GetLast();
    }

    template<class T>
    T LinkedListSequence<T>::Get(index_type index) const {
        return items_->Get(index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::GetSubsequence(index_type startIndex, index_type endIndex) const {
        auto sublist = items_->GetSubList(startIndex, endIndex);
        auto subsequence = new LinkedListSequence<T>();
        index_type length = sublist->GetLength();
        for (index_type i = 0; i < length; i++) {
            subsequence->Append(sublist->Get(i));
        }
        return subsequence;
    }

    template<class T>
    index_type LinkedListSequence<T>::GetLength() const {
        return items_->GetLength();
    }

    template<class T>
    void LinkedListSequence<T>::Append(T item) {
        items_->Append(item);
    }

    template<class T>
    void LinkedListSequence<T>::Prepend(T item) {
        items_->Prepend(item);
    }

    template<class T>
    void LinkedListSequence<T>::InsertAt(T item, index_type index) {
        items_->InsertAt(item, index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Concat(const ISequence<T> &list) const {
        auto new_list = this->Clone();
        index_type start = GetLength();
        index_type end = start + list.GetLength();
        for (index_type index = start; index < end; index++) {
            new_list->Prepend(list.Get(index - start));
        }
        return new_list;
    }

    template<class T>
    T &LinkedListSequence<T>::operator[](index_type index) {
        if (GetLength() <= index || index < 0) {
            std::string message = "GetLength() = " + std::to_string(GetLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return (*(items_))[index];
    }

    template<class T>
    T LinkedListSequence<T>::Reduce(T (*func)(T, T), T initial) const {
        return items_->Reduce(func, initial);
    }

    template<class T>
    T LinkedListSequence<T>::Reduce(T (*func)(T, T)) const {
        if (GetLength() <= 0) {
            throw MyError("Reduce to empty sequence");
        }
        return items_->Reduce(func);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Map(T (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = items_->Map(func);
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Where(bool (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = items_->Where(func);
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Clone() const {
        auto* new_sequence = new LinkedListSequence<T>();
        index_type length = GetLength();
        for (index_type i = 0; i < length; i++) {
            new_sequence->items_->Prepend(T(Get(i)));
        }
        return new_sequence;
    }


// extra

    template<class F, class T>
    LinkedListSequence<T> *MapL(T (*func)(T), const ISequence<F> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        index_type len = sequence->GetLength();
        for (index_type i = 0; i < len; i++) {
            new_sequence->Prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *WhereL(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        index_type len = sequence->GetLength();
        for (index_type i = 0; i < len; i++) {
            if (func(sequence[i])) {
                new_sequence->Prepend(sequence[i]);
            }
        }
        return new_sequence;
    }

}