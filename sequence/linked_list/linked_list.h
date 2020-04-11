#pragma once

#include "../config.h"
#include "../common/my_exceptions.h"

namespace my_namespace {

    template<class T>
    class LinkedList {
    public:
        LinkedList();

        LinkedList(T *items, index_type count, bool is_direct_order = true);

        LinkedList(LinkedList<T> const &linked_list, bool is_direct_order = true);

        ~LinkedList();

        index_type GetLength() const;

        T GetFirst() const;

        T GetLast() const;

        T Get(index_type index) const;

        T Reduce(T (*func)(T, T)) const;

        T Reduce(T (*func)(T, T), T initial) const;

        LinkedList<T> *Map(T (*func)(T)) const;

        LinkedList<T> *Where(bool (*func)(T)) const;

        LinkedList<T> *Concat(const LinkedList<T> *list) const;

        LinkedList<T> *GetSubList(index_type startIndex, index_type endIndex, bool is_direct_order = true) const;

        void Append(T item);

        void Prepend(T item);

        void Set(index_type index, T item);

        void InsertAt(T item, index_type index);

        T &operator[](index_type index);

    private:
        class Node;

        Node *head_ = nullptr;
        Node *tail_ = nullptr;
        index_type length_ = 0;

        Node *MoveForward(Node *node, index_type count = 1) const;
    };


    template<class T>
    LinkedList<T>::LinkedList() {
        head_ = nullptr;
        length_ = 0;
        tail_ = nullptr;
    }

    template<class T>
    LinkedList<T>::LinkedList(T *items, index_type count, bool is_direct_order) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        for (index_type index = 0; index < count; index++) {
            if (is_direct_order) {
                this->Prepend(items[index]);
            } else {
                this->Append(items[index]);
            }
        }
    }

    template<class T>
    LinkedList<T>::LinkedList(LinkedList<T> const &linked_list, bool is_direct_order) {
        index_type len = linked_list.GetLength();
        if (len < 0) {
            return;
        }
        for (index_type index = 0; index < len; index++) {
            if (is_direct_order) {
                this->Prepend(linked_list.Get(index));
            } else {
                this->Append(linked_list.Get(index));
            }
        }
    }

    template<class T>
    LinkedList<T>::~LinkedList() {
        index_type len = this->GetLength();
        Node *node;
        for (index_type i = 0; i < len; i++) {
            node = head_->GetNext();
            delete head_;
            head_ = node;
        }
    }

    template<class T>
    T LinkedList<T>::GetFirst() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return head_->GetData();
    }

    template<class T>
    T LinkedList<T>::GetLast() const {
        if (length_ == 0) {
            throw MyError("IndexOutOfRangeError");
        }
        return tail_->GetData();
    }

    template<class T>
    T LinkedList<T>::Get(index_type index) const {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        auto node = this->MoveForward(head_, index);
        return node->GetData();
    }

    template<class T>
    index_type LinkedList<T>::GetLength() const {
        return length_;
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::GetSubList(index_type startIndex, index_type endIndex, bool is_direct_order) const {
        if (length_ <= endIndex || startIndex < endIndex || startIndex < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        auto node = this->MoveForward(head_, startIndex);
        auto sublist = new LinkedList();
        for (index_type i = 0; i < endIndex - startIndex; i++) {
            if (is_direct_order) {
                sublist->Prepend(node->GetData());
            } else {
                sublist->Append(node->GetData());
            }
            node = this->MoveForward(node);
        }
        return sublist;
    }

    template<class T>
    void LinkedList<T>::Append(T item) {
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
    void LinkedList<T>::Prepend(T item) {
        if (tail_ == nullptr) {
            tail_ = new Node(item);
            head_ = tail_;
            length_ = 1;
            return;
        }
        auto new_tail = new Node(item);
        tail_->SetNext(new_tail);
        tail_ = new_tail;
        length_++;
        if (head_ == nullptr) {
            head_ = tail_;
        }
    }

    template<class T>
    void LinkedList<T>::InsertAt(T item, index_type index) {
        if (length_ < index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        if (index == 0) {
            this->Append(item);
            return;
        }
        if (index == length_) {
            this->Prepend(item);
            return;
        }
        Node *node = this->MoveForward(head_, index - 1);
        auto new_node = new Node(item, node->GetNext());
        node->SetNext(new_node);
        length_++;
    }

    template<class T>
    void LinkedList<T>::Set(index_type index, T item) {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        Node *node = this->MoveForward(head_, index);
        node->SetData(item);
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::Concat(const LinkedList<T> *list) const {
        auto new_list = new LinkedList<T>(*this);
        index_type len = list->GetLength();
        for (index_type index = 0; index < len; index++) {
            new_list->Prepend(list->Get(index));
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

        void SetNext(Node *node) {
            this->next_ = node;
        }

        void SetData(T d) {
            this->data_ = d;
        }

        Node *GetNext() {
            return this->next_;
        }

        T GetData() {
            return this->data_;
        }

        T &GetDataRef() {
            return this->data_;
        }

    private:
        T data_;
        Node *next_ = nullptr;
    };

    template<class T>
    T &LinkedList<T>::operator[](index_type index) {
        if (length_ <= index || index < 0) {
            throw MyError("IndexOutOfRangeError");
        }
        Node *node = this->MoveForward(head_, index);
        return node->GetDataRef();
    }

    template<class T>
    typename LinkedList<T>::Node *LinkedList<T>::MoveForward(LinkedList::Node *node, index_type count) const {
        for (index_type i = 0; i < count; i++) {
            node = node->GetNext();
        }
        return node;
    }

    template<class T>
    T LinkedList<T>::Reduce(T (*func)(T, T)) const {
        index_type len = this->GetLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence");
        }
        T result = this->GetFirst();
        Node *node = head_;
        for (index_type i = 1; i < len; i++) {
            result = func(node->GetData(), result);
            node = MoveForward(node);
        }
    }

    template<class T>
    T LinkedList<T>::Reduce(T (*func)(T, T), T initial) const {
        T result = initial;
        index_type len = this->GetLength();
        auto node = head_;
        for (index_type i = 0; i < len; i++) {
            result = func(node->GetData(), result);
            node = MoveForward(node);
        }
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::Map(T (*func)(T)) const {
        auto new_list = new LinkedList<T>();
        auto node = head_;
        index_type len = this->GetLength();
        for (index_type i = 0; i < len; i++) {
            new_list->Prepend(func(node->GetData()));
            node = MoveForward(node);
        }
        return new_list;
    }

    template<class T>
    LinkedList<T> *LinkedList<T>::Where(bool (*func)(T)) const {
        auto new_list = new LinkedList<T>();
        index_type len = this->GetLength();
        auto node = head_;
        T value;
        for (index_type i = 0; i < len; i++) {
            if (func(node->GetData())) {
                new_list->Prepend(node->GetData());
            }
        }
    }

}