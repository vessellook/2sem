#pragma once

#include <memory>

#include "../linked_list/singly_linked_node.h"
#include "singly_linked_list_base.h"
#include "../common/exceptions.h"

namespace my_namespace {

    template<class T>
    class SinglyLinkedList : public SinglyLinkedListBase<T> {
        // простой список, большое количество вспомогательных функций
    public:
        SinglyLinkedList() : SinglyLinkedListBase<T>() {}

        SinglyLinkedList(const T *items, unsigned count) : SinglyLinkedListBase<T>(items, count) {}

        SinglyLinkedList(const SinglyLinkedList<T> &other) : SinglyLinkedListBase<T>(other) {}

        T getFirst() const { return this->get(0); }

        T getLast() const { return this->get(this->length_ - 1); }

        T reduce(T (*)(T, T)) const;

        T reduce(T (*)(T, T), T) const;

        T reduce(T (*)(T, T, unsigned)) const;

        T reduce(T (*)(T, T, unsigned), T) const;

        SinglyLinkedList<T> *map(T (*)(T));

        SinglyLinkedList<T> *map(T (*)(T, unsigned));

        SinglyLinkedList<T> *where(bool (*)(T));

        SinglyLinkedList<T> *where(bool (*)(T, unsigned));

        SinglyLinkedList<T> *concat(const SinglyLinkedList<T> *);

        SinglyLinkedList<T> *getSubList(unsigned, unsigned) const;

        SinglyLinkedList<T> *append(T item) {
            this->insertAt(item, 0);
            return this;
        }

        SinglyLinkedList<T>* clone() const;

        SinglyLinkedList<T> *cut(unsigned, unsigned);

        bool isPalindrom();

        T &operator[](unsigned index) { return this->getRef(index); };
    };

    template<class T>
    SinglyLinkedList<T> *
    SinglyLinkedList<T>::getSubList(unsigned startIndex, unsigned endIndex) const {
        if (this->length_ <= endIndex || startIndex < endIndex) {
            throw IndexOutOfRangeError("length_ <= endIndex || startIndex < endIndex", __FILE__, __func__, __LINE__);
        }
        auto node = this->moveForward(this->sentinel_, startIndex + 1);
        auto sublist = new SinglyLinkedList();
        for (unsigned i = 0; i < endIndex - startIndex; i++) {
            sublist->prepend(node->getData());
            node = node->getNext();
        }
        return sublist;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::concat(const SinglyLinkedList<T> *list) {
        for (unsigned index = 0; index < list->length_; index++) {
            this->prepend(list->get(index));
        }
        return this;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T)) const {
        if (!this->length_) {
            throw IndexOutOfRangeError("length_ == 0", __FILE__, __func__, __LINE__);
        }
        T result = getFirst();
        auto node = this->sentinel_;
        for (unsigned i = 1; i < this->length_; i++) {
            node = node->getNext();
            result = func(node->getData(), result);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T), T initial) const {
        T result = initial;
        auto node = this->sentinel_;
        for (unsigned index = 0; index < this->length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T, unsigned)) const {
        if (!this->length_) {
            throw IndexOutOfRangeError("length_ == 0", __FILE__, __func__, __LINE__);
        }
        T result = getFirst();
        auto node = this->sentinel_;
        for (unsigned index = 0; index < this->length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result, index);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T, unsigned), T initial) const {
        T result = initial;
        auto node = this->sentinel_;
        for (unsigned index = 0; index < this->length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result, index);
        }
        return result;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::map(T (*func)(T)) {
        auto node = this->sentinel_;
        for (unsigned index = 0; index < this->length_; index++) {
            node = node->getNext();
            node->setData(func(node->getData()));
        }
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::map(T (*func)(T, unsigned)) {
        auto node = this->sentinel_;
        for (unsigned index = 0; index < this->length_; index++) {
            node = node->getNext();
            node->setData(func(node->getData(), index));
        }
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::where(bool (*func)(T)) {
        if(this->length_ == 0) return this;
        unsigned index = 0;
        auto node = this->sentinel_;
        while(index < this->length_ - 1) {
            if(!func(node->getNext()->getData())) {
                this->skipNext(node);
            } else {
                node = node->getNext();
                index++;
            }
        }
        if(!func(this->tail_->getData())) {
            this->tail_ = node;
            this->tail_->clearNext();
            this->length_--;
        }
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::where(bool (*func)(T, unsigned)) {
        if(this->length_ == 0) return this;
        unsigned index = 0;
        unsigned prev_index = 0;
        auto node = this->sentinel_;
        while(index < this->length_ - 1) {
            if(!func(node->getNext()->getData(), prev_index)) {
                this->skipNext(node);
            } else {
                node = node->getNext();
                index++;
            }
            prev_index++;
        }
        if(!func(this->tail_->getData(), prev_index)) {
            this->tail_ = node;
            this->tail_->clearNext();
            this->length_--;
        }
        return this;
    }

    template<class T>
    bool SinglyLinkedList<T>::isPalindrom() {
        if (this->length_ < 2) {
            return true;
        }

        std::shared_ptr<SinglyLinkedNode<T>>
                prevNode = getNode((this->length_ + 1) / 2);
        std::shared_ptr<SinglyLinkedNode<T>>
                curNode = prevNode->getNext();
        std::shared_ptr<SinglyLinkedNode<T>>
                nextNode;
        for (unsigned i = 0; i < this->length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }// в curNode останется хвост, в prevNode останется sentinel_

        auto forwardNode = this->sentinel_->getNext();
        auto backwardNode = curNode;
        bool is_palindrom = true;
        unsigned index = 0;
        while (is_palindrom && index < this->length_ / 2) {
            is_palindrom = forwardNode->getData() == backwardNode->getData();
            forwardNode = forwardNode->getNext();
            backwardNode = backwardNode->getNext();
            index++;
        }

        // prevNode всё ещё содержит sentinel_
        // curNode всё ещё содержит хвост
        for (unsigned i = 0; i < this->length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }

        return is_palindrom;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::cut(unsigned start_index, unsigned end_index) {
        if (this->length_ < end_index || end_index < start_index) {
            throw IndexOutOfRangeError("length_ < end_index || end_index < start_index", __FILE__, __func__, __LINE__);
        }
        if(end_index == this->length_ - 1) {
            this->tail_ = this->moveForward(this->sentinel_, start_index);
            this->tail_->clearNext();
        } else {
            auto start_node = this->moveForward(this->sentinel_, start_index);
            start_node->setNext(this->moveForward(start_node, end_index - start_index + 2));
        }
        this->length_ = this->length_ - end_index + start_index - 1;
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::clone() const {
        auto list = new SinglyLinkedList<T>();
        auto node = this->sentinel_->getNext();
        for (unsigned index = 0; index < this->length_; index++) {
            list->prepend(node->getData());
            node = node->getNext();
        }
        return list;
    }

}