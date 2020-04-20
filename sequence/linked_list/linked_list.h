#pragma once

#include "../common/my_exceptions.h"

namespace my_namespace {

    template<class T>
    class LinkedList {
    public:
        LinkedList();

        LinkedList(const T *items, int count, bool is_direct_order = true);

        LinkedList(LinkedList<T> const &linked_list, bool is_direct_order = true);

        ~LinkedList();

        int getLength() const { return length_; };

        T getFirst() const;

        T getLast() const;

        T get(int index) const;

        T& getRef(int index);

        T reduce(T (*func)(T, T)) const;

        T reduce(T (*func)(T, T), T initial) const;

        LinkedList<T> *map(T (*func)(T)) const;

        LinkedList<T> *where(bool (*func)(T)) const;

        LinkedList<T> *concat(const LinkedList<T> *list) const;

        LinkedList<T> *getSubList(int startIndex, int endIndex, bool is_direct_order = true) const;

        void append(T item);

        void prepend(T item);

        void set(int index, T item);

        void insertAt(T item, int index);

        bool isPalindrom();

        T &operator[](int index) { return getRef(index); };

    private:
        class Node;

        Node *head_ = nullptr;
        Node *tail_ = nullptr;
        int length_ = 0;

        Node *moveForward(Node *node, int count = 1) const;
    };


    template<class T>
    LinkedList<T>::LinkedList() {
        head_ = nullptr;
        length_ = 0;
        tail_ = nullptr;
    }

    template<class T>
    LinkedList<T>::LinkedList(const T *items, int count, bool is_direct_order) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        for (int index = 0; index < count; index++) {
            if (is_direct_order) {
                this->prepend(items[index]);
            } else {
                this->append(items[index]);
            }
        }
    }

    template<class T>
    LinkedList<T>::LinkedList(LinkedList<T> const &linked_list, bool is_direct_order) {
        int len = linked_list.getLength();
        if (len < 0) {
            return;
        }
        for (int index = 0; index < len; index++) {
            if (is_direct_order) {
                this->prepend(linked_list.get(index));
            } else {
                this->append(linked_list.get(index));
            }
        }
    }

    template<class T>
    LinkedList<T>::~LinkedList() {
        int len = this->getLength();
        Node *node;
        for (int i = 0; i < len; i++) {
            node = head_->getNext();
            delete head_;
            head_ = node;
        }
    }

    template<class T>
    T LinkedList<T>::getFirst() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return head_->getData();
    }

    template<class T>
    T LinkedList<T>::getLast() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return tail_->getData();
    }

    template<class T>
    T LinkedList<T>::get(int index) const {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        auto node = this->moveForward(head_, index);
        return node->getData();
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::getSubList(int startIndex, int endIndex, bool is_direct_order) const {
        if (length_ <= endIndex || startIndex < endIndex || startIndex < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        auto node = this->moveForward(head_, startIndex);
        auto sublist = new LinkedList();
        for (int i = 0; i < endIndex - startIndex; i++) {
            if (is_direct_order) {
                sublist->prepend(node->getData());
            } else {
                sublist->append(node->getData());
            }
            node = this->moveForward(node);
        }
        return sublist;
    }

    template<class T>
    void LinkedList<T>::append(T item) {
        if (tail_ == nullptr) {
            tail_ = new Node(item);
            head_ = tail_;
            length_ = 1;
            return;
        }
        head_ = new Node(item, head_);
        length_++;
        if (tail_ == nullptr) {
            tail_ = head_;
        }
    }

    template<class T>
    void LinkedList<T>::prepend(T item) {
        if (tail_ == nullptr) {
            tail_ = new Node(item);
            head_ = tail_;
            length_ = 1;
            return;
        }
        auto new_tail = new Node(item);
        tail_->setNext(new_tail);
        tail_ = new_tail;
        length_++;
        if (head_ == nullptr) {
            head_ = tail_;
        }
    }

    template<class T>
    void LinkedList<T>::insertAt(T item, int index) {
        if (length_ < index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        if (index == 0) {
            this->append(item);
            return;
        }
        if (index == length_) {
            this->prepend(item);
            return;
        }
        Node *node = this->moveForward(head_, index - 1);
        auto new_node = new Node(item, node->getNext());
        node->setNext(new_node);
        length_++;
    }

    template<class T>
    void LinkedList<T>::set(int index, T item) {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        Node *node = this->moveForward(head_, index);
        node->setData(item);
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::concat(const LinkedList<T> *list) const {
        auto new_list = new LinkedList<T>(*this);
        int len = list->getLength();
        for (int index = 0; index < len; index++) {
            new_list->prepend(list->get(index));
        }
        return new_list;
    }

    template<class T>
    class LinkedList<T>::Node {
    public:
        explicit Node(T data, Node *next = nullptr) {
            this->data_ = data;
            this->next_ = next;
        }

        void setNext(Node *node) {
            this->next_ = node;
        }

        void setData(T d) {
            this->data_ = d;
        }

        Node *getNext() {
            return this->next_;
        }

        T getData() {
            return this->data_;
        }

        T &getDataRef() {
            return this->data_;
        }

    private:
        T data_;
        Node *next_ = nullptr;
    };

    template<class T>
    typename LinkedList<T>::Node *LinkedList<T>::moveForward(LinkedList::Node *node, int count) const {
        for (int i = 0; i < count; i++) {
            node = node->getNext();
        }
        return node;
    }

    template<class T>
    T LinkedList<T>::reduce(T (*func)(T, T)) const {
        int len = this->getLength();
        if (len <= 0) {
            throw MyError("reduce to empty sequence");
        }
        T result = this->getFirst();
        Node *node = head_;
        for (int i = 1; i < len; i++) {
            result = func(node->getData(), result);
            node = moveForward(node);
        }
    }

    template<class T>
    T LinkedList<T>::reduce(T (*func)(T, T), T initial) const {
        T result = initial;
        int len = this->getLength();
        auto node = head_;
        for (int i = 0; i < len; i++) {
            result = func(node->getData(), result);
            node = moveForward(node);
        }
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::map(T (*func)(T)) const {
        auto new_list = new LinkedList<T>();
        auto node = head_;
        int len = this->getLength();
        for (int i = 0; i < len; i++) {
            new_list->prepend(func(node->getData()));
            node = moveForward(node);
        }
        return new_list;
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::where(bool (*func)(T)) const {
        auto new_list = new LinkedList<T>();
        int len = this->getLength();
        auto node = head_;
        T value;
        for (int i = 0; i < len; i++) {
            if (func(node->getData())) {
                new_list->prepend(node->getData());
            }
        }
    }

    template<class T>
    T& LinkedList<T>::getRef(int index) {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        Node *node = this->moveForward(head_, index);
        return node->getDataRef();
    }

    template<class T>
    bool LinkedList<T>::isPalindrom() {
        Node *prevNode = moveForward(head_, (length_ - 1) / 2);
        Node* curNode = prevNode->getNext();
        Node* nextNode;
        for(int i = 0; i < length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }

        Node* forwardNode = head_;
        Node* reverseNode = tail_;
        bool is_palindrom = true;
        for(int i = 0; i < length_ / 2; i++) {
            is_palindrom = is_palindrom and ( forwardNode->getData() != reverseNode->getData() );
            forwardNode = forwardNode->getNext();
            reverseNode = reverseNode->getNext();
        }

        prevNode = nullptr;
        curNode = tail_;
        for(int i = 0; i < length_ / 2; i++) {
            nextNode = curNode->getNext();
            curNode->setNext(prevNode);
            prevNode = curNode;
            curNode = nextNode;
        }

        return is_palindrom;
    }

}