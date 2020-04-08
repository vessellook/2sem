#pragma once

#include "sequence.h"
#include "../linked_list/linked_list.h"

namespace my_namespace {

    template<class T>
    class LinkedListSequence : public ISequence<T> {
    public:
        LinkedListSequence();

        LinkedListSequence(T *items, int count);

        LinkedListSequence(const LinkedListSequence<T> &list);

        ~LinkedListSequence() override;

        int GetLength() const override;

        T GetFirst() const override;

        T GetLast() const override;

        T Get(int index) const override;

        T Reduce(T (*func)(T, T)) const override;

        T Reduce(T (*func)(T, T), T initial) const override;

        LinkedListSequence<T> *Map(T (*func)(T)) const override;

        LinkedListSequence<T> *Where(bool (*func)(T)) const override;

        LinkedListSequence<T> *Concat(const ISequence<T> *list) const override;

        LinkedListSequence<T> *GetSubsequence(int startIndex, int endIndex) const override;

        void Append(T item) override;

        void Prepend(T item) override;

        void InsertAt(T item, int index) override;


        T &operator[](int index) override;

    protected:
        LinkedList<T> *items_ = nullptr;
    };

    template<class T>
    LinkedListSequence<T>::LinkedListSequence() {
        this->items_ = new LinkedList<T>();
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(T *items, int count) {
        this->items_ = new LinkedList<T>(items, count);
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T> &list) {
        this->items_ = new LinkedList<T>();
        int length = list.GetLength();
        for (int i = 0; i < length; i++) {
            this->items_->Prepend(T(list.Get(i)));
        }
    }


    template<class T>
    LinkedListSequence<T>::~LinkedListSequence() {
        delete this->items_;
    }

    template<class T>
    T LinkedListSequence<T>::GetFirst() const {
        return this->items_->GetFirst();
    }

    template<class T>
    T LinkedListSequence<T>::GetLast() const {
        return this->items_->GetLast();
    }

    template<class T>
    T LinkedListSequence<T>::Get(int index) const {
        return this->items_->Get(index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
        auto sublist = this->items_->GetSubList(startIndex, endIndex);
        auto subsequence = new LinkedListSequence<T>();
        int length = sublist->GetLength();
        for (int i = 0; i < length; i++) {
            subsequence->Append(sublist->Get(i));
        }
        return subsequence;
    }

    template<class T>
    int LinkedListSequence<T>::GetLength() const {
        return this->items_->GetLength();
    }

    template<class T>
    void LinkedListSequence<T>::Append(T item) {
        this->items_->Append(item);
    }

    template<class T>
    void LinkedListSequence<T>::Prepend(T item) {
        this->items_->Prepend(item);
    }

    template<class T>
    void LinkedListSequence<T>::InsertAt(T item, int index) {
        this->items_->InsertAt(item, index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Concat(const ISequence<T> *list) const {
        auto new_list = new LinkedListSequence<T>(*this);
        int start = this->GetLength();
        int end = start + list->GetLength();
        for (int index = start; index < end; index++) {
            new_list->Prepend(list->Get(index - start));
        }
        return new_list;
    }

    template<class T>
    T &LinkedListSequence<T>::operator[](int index) {
        if (this->GetLength() <= index || index < 0) {
            std::string message = "this->GetLength() = " + std::to_string(this->GetLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return (*(this->items_))[index];
    }

    template<class T>
    T LinkedListSequence<T>::Reduce(T (*func)(T, T), T initial) const {
        return this->items_->Reduce(func, initial);
    }

    template<class T>
    T LinkedListSequence<T>::Reduce(T (*func)(T, T)) const {
        if (this->GetLength() <= 0) {
            throw MyError("Reduce to empty sequence");
        }
        return this->items_->Reduce(func);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Map(T (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = this->items_->Map(func);
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::Where(bool (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = this->items_->Where(func);
        return new_sequence;
    }


// extra

    template<class F, class T>
    LinkedListSequence<T> *MapL(T (*func)(T), const ISequence<F> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        int len = sequence->GetLength();
        for (int i = 0; i < len; i++) {
            new_sequence->Prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *WhereL(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        int len = sequence->GetLength();
        for (int i = 0; i < len; i++) {
            if (func(sequence[i])) {
                new_sequence->Prepend(sequence[i]);
            }
        }
        return new_sequence;
    }

}