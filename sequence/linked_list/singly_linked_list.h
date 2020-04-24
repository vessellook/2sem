#pragma once

#include <memory>

#include "singly_linked_node.h"
#include "../common/exceptions.h"

namespace my_namespace {

    template<class T>
    class SinglyLinkedList {
    private:
        unsigned length_;
        // sentinel_ будет содержать ссылку на голову и данные хвоста
        // хвост будет указывать на sentinel_
        std::shared_ptr<SinglyLinkedNode<T>> sentinel_;
    private:
        std::shared_ptr<SinglyLinkedNode<T>> moveForward(std::shared_ptr<SinglyLinkedNode<T>> node, unsigned count = 1) const;

        std::shared_ptr<SinglyLinkedNode<T>> getNode(unsigned index) const;
    public:
        SinglyLinkedList(): sentinel_(new SinglyLinkedNode<T>()), length_(0) {
            sentinel_->setNext(sentinel_);
        }

        SinglyLinkedList(const T *items, unsigned count, bool is_direct_order = true);

        SinglyLinkedList(SinglyLinkedList<T> const &other, bool is_direct_order = true);

        ~SinglyLinkedList() { sentinel_.reset(); }

        unsigned getLength() const { return length_; };

        T getFirst() const;

        T getLast() const;

        T get(unsigned index) const;

        T& getRef(unsigned index);

        std::shared_ptr<SinglyLinkedNode<T>> getHandle() const { return sentinel_->getNext(); }

        T reduce(T (*func)(T, T)) const;

        T reduce(T (*func)(T, T), T initial) const;

        T reduce(T (*func)(T, T, unsigned)) const;

        T reduce(T (*func)(T, T, unsigned), T initial) const;

        SinglyLinkedList<T> *clone(bool is_direct_order = true) const;

        SinglyLinkedList<T> *map(T (*func)(T)) const;

        SinglyLinkedList<T> *map(T (*func)(T, unsigned)) const;

        SinglyLinkedList<T> *where(bool (*func)(T)) const;

        SinglyLinkedList<T> *where(bool (*func)(T, unsigned)) const;

        SinglyLinkedList<T> *concat(const SinglyLinkedList<T> *list) const;

        SinglyLinkedList<T> *getSubList(unsigned startIndex, unsigned endIndex, bool is_direct_order = true) const;

        SinglyLinkedList<T> *append(T item);

        SinglyLinkedList<T> *prepend(T item);

        SinglyLinkedList<T> *set(unsigned index, T item);

        SinglyLinkedList<T> *insertAt(T item, unsigned index);

        SinglyLinkedList<T> *remove(unsigned index);

        bool isPalindrom();

        T &operator[](unsigned index) { return getRef(index); };
    };

    template<class T>
    SinglyLinkedList<T>::SinglyLinkedList(const T *items, unsigned count, bool is_direct_order): sentinel_(new SinglyLinkedNode<T>()), length_(0) {
        sentinel_->setNext(sentinel_);
        for (unsigned index = 0; index < count; index++) {
            if (is_direct_order) {
                this->prepend(items[index]);
            } else {
                this->append(items[index]);
            }
        }
        if (count > 0) {
            sentinel_->setData(items[count-1]);
        }
    }

    template<class T>
    SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> const &other, bool is_direct_order): sentinel_(new SinglyLinkedNode<T>()), length_(0) {
        sentinel_->setNext(sentinel_);
        auto node = other.sentinel_->getNext();
        unsigned len = other.getLength();
        for (unsigned index = 0; index < len; index++) {
            if (is_direct_order) {
                this->prepend(node->getData());
            } else {
                this->append(node->getData());
            }
            node = node->getNext();
        }
        sentinel_->setData(other.getLast());
    }

    template<class T>
    T SinglyLinkedList<T>::getFirst() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return sentinel_->getNext()->getData();
    }

    template<class T>
    T SinglyLinkedList<T>::getLast() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return sentinel_->getData();
    }

    template<class T>
    T SinglyLinkedList<T>::get(unsigned index) const {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return getNode(index)->getData();
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::getSubList(unsigned startIndex, unsigned endIndex, bool is_direct_order) const {
        if (length_ <= endIndex || startIndex < endIndex || startIndex < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        auto node = getNode(startIndex);
        auto sublist = new SinglyLinkedList();
        for (unsigned i = 0; i < endIndex - startIndex; i++) {
            if (is_direct_order) {
                sublist->prepend(node->getData());
            } else {
                sublist->append(node->getData());
            }
            node = node->getNext();
        }
        return sublist;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::append(T item) {
        sentinel_->setNext(std::make_shared<SinglyLinkedNode<T>>(item, sentinel_->getNext()));
        if(!length_) {
            sentinel_->setData(item);
        }
        length_++;
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::prepend(T item) {
        sentinel_->setNext(std::make_shared<SinglyLinkedNode<T>>(item, sentinel_->getNext()));
        sentinel_->setData(item);
        sentinel_ = sentinel_->getNext();
        length_++;
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::insertAt(T item, unsigned index) {
        if (length_ < index) {
            throw MyError("IndexOutOfRangeError");
        }
        if(index == 0) {
            append(item);
            return this;
        }
        if(index == length_ - 1) {
            prepend(item);
            return this;
        }
        auto node = getNode(index-1);
        node->setNext(std::make_shared<SinglyLinkedNode<T>>(item, node->getNext()));
        length_++;
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::set(unsigned index, T item) {
        if (length_ <= index) {
            throw MyError("IndexOutOfRangeError");
        }
        getNode(index)->setData(item);
        return this;
    }

    template <class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::remove(unsigned index) {
        auto node = moveForward(sentinel_, index);
        auto next_node = node->getNext()->getNext();
        node->getNext()->clearNext();// вообще этот шаг необязателен
        node->setNext(next_node);
        return this;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::concat(const SinglyLinkedList<T> *list) const {
        auto new_list = new SinglyLinkedList<T>(*this);
        for (unsigned index = 0; index < list->length_; index++) {
            new_list->prepend(list->get(index));
        }
        return new_list;
    }

    template<class T>
    typename std::shared_ptr<SinglyLinkedNode<T>> SinglyLinkedList<T>::moveForward(std::shared_ptr<SinglyLinkedNode<T>> node, unsigned count) const {
        // небезопасная функция — не проверяется, индекс превышает длину
        for (unsigned i = 0; i < count; i++) {
            node = node->getNext();
        }
        return node;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T)) const {
        if (!length_) {
            throw MyError("reduce to empty sequence");
        }
        T result = getFirst();
        auto node = sentinel_;
        for (unsigned i = 1; i < length_; i++) {
            node = node->getNext();
            result = func(node->getData(), result);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T), T initial) const {
        T result = initial;
        auto node = sentinel_;
        for (unsigned index = 0; index < length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T, unsigned)) const {
        if (!length_) {
            throw MyError("reduce to empty sequence");
        }
        T result = getFirst();
        auto node = sentinel_;
        for (unsigned index = 0; index < length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result, index);
        }
        return result;
    }

    template<class T>
    T SinglyLinkedList<T>::reduce(T (*func)(T, T, unsigned), T initial) const {
        T result = initial;
        auto node = sentinel_;
        for (unsigned index = 0; index < length_; index++) {
            node = node->getNext();
            result = func(node->getData(), result, index);
        }
        return result;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::map(T (*func)(T)) const {
        auto new_list = new SinglyLinkedList<T>();
        auto node = sentinel_;
        for (unsigned index = 0; index < length_; index++) {
            node = node->getNext();
            new_list->prepend(func(node->getData()));
        }
        return new_list;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::map(T (*func)(T, unsigned)) const {
        auto new_list = new SinglyLinkedList<T>();
        auto node = sentinel_;
        for (unsigned index = 0; index < length_; index++) {
            node = node->getNext();
            new_list->prepend(func(node->getData(), index));
        }
        return new_list;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::where(bool (*func)(T)) const {
        auto new_list = new SinglyLinkedList<T>();
        auto node = sentinel_;
        T value;
        for (unsigned i = 0; i < length_; i++) {
            node = node->getNext();
            if (func(node->getData())) {
                new_list->prepend(node->getData());
            }
        }
        return new_list;
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::where(bool (*func)(T, unsigned)) const {
        auto new_list = new SinglyLinkedList<T>();
        auto node = sentinel_;
        T value;
        for (unsigned i = 0; i < length_; i++) {
            node = node->getNext();
            if (func(node->getData())) {
                new_list->prepend(node->getData());
            }
        }
        return new_list;
    }

    template<class T>
    T& SinglyLinkedList<T>::getRef(unsigned index) {
        if (length_ <= index) {
            throw MyError("IndexOutOfRangeError");
        }
        return getNode(index)->getDataRef();
    }

    template<class T>
    bool SinglyLinkedList<T>::isPalindrom() {
        if(length_ < 2) {
            return true;
        }

        std::shared_ptr<SinglyLinkedNode<T>> prevNode = getNode((length_ + 1) / 2);
        std::shared_ptr<SinglyLinkedNode<T>> curNode = prevNode->getNext();
        std::shared_ptr<SinglyLinkedNode<T>> nextNode;
        for(unsigned i = 0; i < length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }// в curNode останется хвост, в prevNode останется sentinel_

        auto forwardNode = sentinel_->getNext();
        auto backwardNode = curNode;
        bool is_palindrom = true;
        unsigned index = 0;
        while(is_palindrom && index < length_/2) {
            is_palindrom = forwardNode->getData() == backwardNode->getData();
            forwardNode = forwardNode->getNext();
            backwardNode = backwardNode->getNext();
            index++;
        }

        // prevNode всё ещё содержит sentinel_
        // curNode всё ещё содержит хвост
        for(unsigned i = 0; i < length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }

        return is_palindrom;
    }

    template<class T>
    std::shared_ptr<SinglyLinkedNode<T>> SinglyLinkedList<T>::getNode(unsigned index) const {
        return moveForward(sentinel_, index + 1);
    }

    template<class T>
    SinglyLinkedList<T> *SinglyLinkedList<T>::clone(bool is_direct_order) const {
        auto list = new SinglyLinkedList<T>();
        auto node = sentinel_->getNext();
        for (unsigned index = 0; index < length_; index++) {
            if (is_direct_order) {
                list->prepend(node->getData());
            } else {
                list->append(node->getData());
            }
            node = node->getNext();
        }
        list->sentinel_->setData(getLast());
        return list;
    }

}