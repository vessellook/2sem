#pragma once

#include "my_exceptions.h"

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T* items, int count, bool is_direct_order = true);
    LinkedList(LinkedList<T> const & linked_list, bool is_direct_order = true);
    ~LinkedList();

    int GetLength() const;
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    T Reduce(T (*func)(T, T)) const;
    T Reduce(T (*func)(T, T), T initial) const;
    LinkedList<T>* Map(T (*func)(T)) const;
    LinkedList<T>* Where(bool (*func)(T)) const;
    LinkedList<T>* Concat(const LinkedList<T> *list) const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex, bool is_direct_order = true) const;

    void Append(T item);
    void Prepend(T item);
    void Set(int index, T item);
    void InsertAt(T item, int index);

    T& operator[](int index);
private:
    class Node;
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
    Node* MoveForward(Node* node, int count = 1) const;
};


template <class T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->length = 0;
    this->tail = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(T* items, int count, bool is_direct_order) {
    if (count < 0) {
        throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
    }
    for(int index = 0; index < count; index++) {
        if(is_direct_order) {
            this->Prepend(items[index]);
        } else {
            this->Append(items[index]);
        }
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T> const &linked_list, bool is_direct_order) {
    int len = linked_list.GetLength();
    if (len < 0) {
        return;
    }
    for(int index = 0; index < len; index++) {
        if (is_direct_order) {
            this->Prepend(linked_list.Get(index));
        } else {
            this->Append(linked_list.Get(index));
        }
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    int len = this->GetLength();
    Node* node;
    for(int i = 0; i < len; i++) {
        node = this->head->GetNext();
        delete this->head;
        this->head = node;
    }
}

template <class T>
T LinkedList<T>::GetFirst() const {
    if(this->length == 0) {
        throw MyError("IndexOutOfRangeError");
    }
    return this->head->GetData();
}

template <class T>
T LinkedList<T>::GetLast() const {
    if(this->length == 0) {
        throw MyError("IndexOutOfRangeError");
    }
    return this->tail->GetData();
}

template <class T>
T LinkedList<T>::Get(int index) const {
    if(this->length <= index || index < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    auto node = this->MoveForward(this->head, index);
    return node->GetData();
}

template <class T>
int LinkedList<T>::GetLength() const {
    return this->length;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex, bool is_direct_order) const {
    if(this->length <= endIndex || startIndex < endIndex || startIndex < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    auto node = this->MoveForward(this->head, startIndex);
    auto sublist = new LinkedList();
    for(int i = 0; i < endIndex - startIndex; i++) {
        if(is_direct_order) {
            sublist->Prepend(node->GetData());
        } else {
            sublist->Append(node->GetData());
        }
        node = this->MoveForward(node);
    }
    return sublist;
}

template  <class T>
void LinkedList<T>::Append(T item) {
    if (this->tail == nullptr) {
        this->tail = new Node(item);
        this->head = this->tail;
        this->length = 1;
        return;
    }
    this->head = new Node(item, this->head);
    length++;
    if (this->tail == nullptr) {
        this->tail = this->head;
    }
}

template <class T>
void LinkedList<T>::Prepend(T item) {
    if (this->tail == nullptr) {
        this->tail = new Node(item);
        this->head = this->tail;
        this->length = 1;
        return;
    }
    auto new_tail = new Node(item);
    this->tail->SetNext(new_tail);
    this->tail = new_tail;
    this->length++;
    if (this->head == nullptr) {
        this->head = this->tail;
    }
}

template  <class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if(this->length < index || index < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    if (index == 0) {
        this->Append(item);
        return;
    }
    if (index == this->length) {
        this->Prepend(item);
        return;
    }
    Node* node = this->MoveForward(this->head, index-1);
    auto new_node = new Node(item, node->GetNext());
    node->SetNext(new_node);
    this->length++;
}

template <class T>
void LinkedList<T>::Set(int index, T item) {
    if(this->length <= index || index < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    Node* node = this->MoveForward(this->head, index);
    node->SetData(item);
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T> *list) const {
    auto new_list = new LinkedList<T>(*this);
    int len = list->GetLength();
    for(int index = 0; index < len; index++) {
        new_list->Prepend(list->Get(index));
    }
    return new_list;
}

template <class T>
class LinkedList<T>::Node {
public:
    explicit Node(T data, Node* next = nullptr) {
        this->data_ = data;
        this->next_ = next;
    }
    void SetNext(Node* node) {
        this->next_ = node;
    }
    void SetData(T d) {
        this->data_ = d;
    }
    Node* GetNext() {
        return this->next_;
    }
    T GetData() {
        return this->data_;
    }
    T& GetDataRef() {
        return this->data_;
    }
private:
    T data_;
    Node* next_ = nullptr;
};

template <class T>
T& LinkedList<T>::operator[](int index) {
    if(this->length <= index || index < 0) {
        throw MyError("IndexOutOfRangeError");
    }
    Node* node = this->MoveForward(this->head, index);
    return node->GetDataRef();
}

template<class T>
typename LinkedList<T>::Node *LinkedList<T>::MoveForward(LinkedList::Node *node, int count) const {
    for(int i = 0; i < count; i++) {
        node = node->GetNext();
    }
    return node;
}

template<class T>
T LinkedList<T>::Reduce(T (*func)(T, T)) const {
    int len = this->GetLength();
    if(len <= 0) {
        throw MyError("Reduce to empty sequence");
    }
    T result = this->GetFirst();
    Node* node = this->head;
    for(int i = 1; i < len; i++) {
        result = func(node->GetData(), result);
        node = MoveForward(node);
    }
}

template<class T>
T LinkedList<T>::Reduce(T (*func)(T, T), T initial) const {
    T result = initial;
    int len = this->GetLength();
    auto node = this->head;
    for(int i = 0; i < len; i++) {
        result = func(node->GetData(), result);
        node = MoveForward(node);
    }
}

template<class T>
LinkedList<T> *LinkedList<T>::Map(T (*func)(T)) const {
    auto new_list = new LinkedList<T>();
    auto node = this->head;
    int len = this->GetLength();
    for(int i = 0; i < len; i++) {
        new_list->Prepend(func(node->GetData()));
        node = MoveForward(node);
    }
    return new_list;
}

template<class T>
LinkedList<T> *LinkedList<T>::Where(bool (*func)(T)) const {
    auto new_list = new LinkedList<T>();
    int len = this->GetLength();
    auto node = this->head;
    T value;
    for(int i = 0; i < len; i++) {
        if(func(node->GetData())) {
            new_list->Prepend(node->GetData());
        }
    }
}