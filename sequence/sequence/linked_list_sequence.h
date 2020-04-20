#pragma once

#include "sequence.h"
#include "../linked_list/linked_list.h"

namespace my_namespace {

    template<class T>
    class LinkedListSequence : public ISequence<T> {
    public:
        LinkedListSequence();

        LinkedListSequence(const T *items, int count);

        explicit LinkedListSequence(const ISequence<T> &list);

        ~LinkedListSequence() override;

        int getLength() const override;

        T getFirst() const override;

        T getLast() const override;

        T get(int index) const override;

        T& getRef(int index) override;

        T reduce(T (*func)(T, T)) const override;

        T reduce(T (*func)(T, T), T initial) const override;

        LinkedListSequence<T> *clone() const override;

        LinkedListSequence<T> *map(T (*func)(T)) const override;

        LinkedListSequence<T> *where(bool (*func)(T)) const override;

        LinkedListSequence<T> *concat(const ISequence<T> &list) const override;

        LinkedListSequence<T> *getSubsequence(int startIndex, int endIndex) const override;

        void append(T item) override;

        void prepend(T item) override;

        void insertAt(T item, int index) override;


        T &operator[](int index) override;

        T operator[](int index) const override { return get(index); }

    protected:
        LinkedList<T> *items_ = nullptr;
    };

    template<class T>
    LinkedListSequence<T>::LinkedListSequence() {
        items_ = new LinkedList<T>();
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const T *items, int count) {
        items_ = new LinkedList<T>(items, count);
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const ISequence<T> &list) {
        items_ = new LinkedList<T>();
        int length = list.getLength();
        for (int i = 0; i < length; i++) {
            items_->prepend(T(list.get(i)));
        }
    }


    template<class T>
    LinkedListSequence<T>::~LinkedListSequence() {
        delete items_;
    }

    template<class T>
    T LinkedListSequence<T>::getFirst() const {
        return items_->getFirst();
    }

    template<class T>
    T LinkedListSequence<T>::getLast() const {
        return items_->getLast();
    }

    template<class T>
    T LinkedListSequence<T>::get(int index) const {
        return items_->get(index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::getSubsequence(int startIndex, int endIndex) const {
        auto sublist = items_->getSubList(startIndex, endIndex);
        auto subsequence = new LinkedListSequence<T>();
        int length = sublist->getLength();
        for (int i = 0; i < length; i++) {
            subsequence->append(sublist->get(i));
        }
        return subsequence;
    }

    template<class T>
    int LinkedListSequence<T>::getLength() const {
        return items_->getLength();
    }

    template<class T>
    void LinkedListSequence<T>::append(T item) {
        items_->append(item);
    }

    template<class T>
    void LinkedListSequence<T>::prepend(T item) {
        items_->prepend(item);
    }

    template<class T>
    void LinkedListSequence<T>::insertAt(T item, int index) {
        items_->insertAt(item, index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::concat(const ISequence<T> &list) const {
        auto new_list = this->clone();
        int start = getLength();
        int end = start + list.getLength();
        for (int index = start; index < end; index++) {
            new_list->prepend(list.get(index - start));
        }
        return new_list;
    }

    template<class T>
    T &LinkedListSequence<T>::operator[](int index) {
        return getRef(index);
    }

    template<class T>
    T LinkedListSequence<T>::reduce(T (*func)(T, T), T initial) const {
        return items_->reduce(func, initial);
    }

    template<class T>
    T LinkedListSequence<T>::reduce(T (*func)(T, T)) const {
        if (getLength() <= 0) {
            throw MyError("Reduce to empty sequence");
        }
        return items_->reduce(func);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::map(T (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = items_->map(func);
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::where(bool (*func)(T)) const {
        auto new_sequence = new LinkedListSequence<T>();
        new_sequence->items_ = items_->where(func);
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::clone() const {
        auto* new_sequence = new LinkedListSequence<T>();
        int length = getLength();
        for (int i = 0; i < length; i++) {
            new_sequence->items_->prepend(T(get(i)));
        }
        return new_sequence;
    }

    template<class T>
    T& LinkedListSequence<T>::getRef(int index) {
        if (getLength() <= index || index < 0) {
            std::string message = "getLength() = " + std::to_string(getLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return items_->getRef(index);
    }


// extra

    template<class F, class T>
    LinkedListSequence<T> *mapL(T (*func)(T), const ISequence<F> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        int len = sequence->getLength();
        for (int i = 0; i < len; i++) {
            new_sequence->prepend(func(sequence[i]));
        }
        return new_sequence;
    }

    template<class T>
    LinkedListSequence<T> *whereL(bool (*func)(T), const ISequence<T> *sequence) {
        auto new_sequence = new LinkedListSequence<T>();
        int len = sequence->getLength();
        for (int i = 0; i < len; i++) {
            if (func(sequence[i])) {
                new_sequence->prepend(sequence[i]);
            }
        }
        return new_sequence;
    }

}