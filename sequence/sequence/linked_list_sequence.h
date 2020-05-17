#pragma once

#include "sequence.h"
#include "../linked_list/singly_linked_list.h"

namespace my_namespace {

    template<class T>
    class LinkedListSequence : public ISequence<T> {
    private:
        SinglyLinkedList<T> *list_ = nullptr;
    public:
        LinkedListSequence();

        LinkedListSequence(const T *, unsigned);

        explicit LinkedListSequence(const ISequence<T> &);

        ~LinkedListSequence() override;

        unsigned getLength() const override;

        T getFirst() const override;

        T getLast() const override;

		LinkedListSequence<T> *set(unsigned index, T value) override { getRef(index) = value; return this; }

        T get(unsigned) const override;

        T& getRef(unsigned) override;

        T getFirstMatch(bool(*check)(T)) const { return this->list_->getFirstMatch(check); }

        T reduce(T (*func)(T, T)) const override;

        T reduce(T (*func)(T, T), T initial) const override { return list_->reduce(func, initial); }

        LinkedListSequence<T> *clone() const override;

        LinkedListSequence<T> *map(T (*func)(T)) override;

        LinkedListSequence<T> *where(bool (*check)(T)) override;

        LinkedListSequence<T> *concat(const ISequence<T> &) override;

        LinkedListSequence<T> *getSubsequence(unsigned, unsigned) const override;

        LinkedListSequence<T> *append(T) override;

        LinkedListSequence<T> *prepend(T) override;

        LinkedListSequence<T> *insertAt(T, unsigned) override;

        T &operator[](unsigned index) override { return getRef(index); };

        T operator[](unsigned index) const override { return get(index); }
    };

    template<class T>
    LinkedListSequence<T>::LinkedListSequence() {
        list_ = new SinglyLinkedList<T>();
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const T *items, unsigned count) {
        list_ = new SinglyLinkedList<T>(items, count);
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const ISequence<T> &list) {
        list_ = new SinglyLinkedList<T>();
        unsigned length = list.getLength();
        for (unsigned i = 0; i < length; ++i) {
            list_->prepend(T(list.get(i)));
        }
    }


    template<class T>
    LinkedListSequence<T>::~LinkedListSequence() {
        delete list_;
    }

    template<class T>
    T LinkedListSequence<T>::getFirst() const {
        return list_->getFirst();
    }

    template<class T>
    T LinkedListSequence<T>::getLast() const {
        return list_->getLast();
    }

    template<class T>
    T LinkedListSequence<T>::get(unsigned index) const {
        return list_->get(index);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::getSubsequence(unsigned startIndex, unsigned endIndex) const {
        auto sublist = list_->getSubList(startIndex, endIndex);
        auto subsequence = new LinkedListSequence<T>();
        unsigned length = sublist->getLength();
        for (unsigned i = 0; i < length; ++i) {
            subsequence->append(sublist->get(i));
        }
        return subsequence;
    }

    template<class T>
    unsigned LinkedListSequence<T>::getLength() const {
        return list_->getLength();
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::append(T item) {
        list_->append(item);
        return this;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::prepend(T item) {
        list_->prepend(item);
        return this;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::insertAt(T item, unsigned index) {
        list_->insertAt(item, index);
        return this;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::concat(const ISequence<T> &list) {
        for(unsigned index = 0; index < list.getLength(); index++) {
            list_->prepend(list.get(index));
            //TODO: заменить тут на использование reduce()
        }
        return this;
    }

    template<class T>
    T LinkedListSequence<T>::reduce(T (*func)(T, T)) const {
        if (!getLength()) {
            throw MyError("Reduce to empty sequence");
        }
        return list_->reduce(func);
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::map(T (*func)(T)) {
        list_->map(func);
        return this;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::where(bool (*func)(T)) {
        list_->where(func);
        return this;
    }

    template<class T>
    LinkedListSequence<T> *LinkedListSequence<T>::clone() const {
        auto* new_sequence = new LinkedListSequence<T>();
        unsigned length = getLength();
        for (unsigned i = 0; i < length; ++i) {
            new_sequence->list_->prepend(T(get(i)));
        }
        return new_sequence;
    }

    template<class T>
    T& LinkedListSequence<T>::getRef(unsigned index) {
        if (getLength() <= index || index < 0) {
            std::string message = "getLength() = " + std::to_string(getLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return list_->getRef(index);
    }


// extra

    template<class F, class T>
    LinkedListSequence<T> *mapNewL(const ISequence<F> &sequence, T (*func)(F)) {
        auto new_sequence = new LinkedListSequence<T>();
        unsigned len = sequence.getLength();
        for (unsigned index = 0; index < len; ++index) {
            new_sequence->prepend(func(sequence[index]));
        }
        return new_sequence;
    }

    template<class F, class T>
    LinkedListSequence<T> *mapNewL(const ISequence<F> &sequence, T (*func)(F, unsigned)) {
        auto new_sequence = new LinkedListSequence<T>();
        unsigned len = sequence.getLength();
        for (unsigned index = 0; index < len; ++index) {
            new_sequence->prepend(func(sequence[index], index));
        }
        return new_sequence;
    }

}
