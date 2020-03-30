#ifndef SEQUENCE_LINKED_LIST_H
#define SEQUENCE_LINKED_LIST_H

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T* items, int count, bool is_direct_order = true);
    LinkedList(LinkedList<T> const & linked_list, bool is_direct_order = true);
    T GetFirst();
    T GetLast();
    T Get(int index);
    int GetLength();
    LinkedList<T>* GetSubList(int startIndex, int endIndex, bool is_direct_order = true);
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, int index);
    LinkedList<T>* Concat(LinkedList<T> *list);
private:
    class Node;
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
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
        throw IndexOutOfRange();
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
    int len = linked_list->GetLength();
    if (len < 0) {
        return;
    }
    for(int index = 0; index < len; index++) {
        if(is_direct_order) {
            this->Prepend(linked_list->Get(index));
        } else {
            this->Append(linked_list->Get(index));
        }
    }
    //TODO
}

template <class T>
T LinkedList<T>::GetFirst() {
    if(this->length == 0) {
        throw IndexOutOfRange();
    }
    return this->head->GetData();
}

template <class T>
T LinkedList<T>::GetLast() {
    if(this->length == 0) {
        throw IndexOutOfRange();
    }
    return this->tail->GetData();
}

template <class T>
T LinkedList<T>::Get(int index) {
    if(this->length <= index || index < 0) {
        throw IndexOutOfRange();
    }
    Node* node = this->head;
    for(int i = 0; i < index; i++) {
        node = node->GetNext();
    }
    return node->GetData();
}

template <class T>
int LinkedList<T>::GetLength() {
    return this->length;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex, bool is_direct_order) {
    if(this->length <= endIndex || startIndex < endIndex || startIndex < 0) {
        throw IndexOutOfRange();
    }
    Node* node = this->head;
    for(int i = 0; i < startIndex; i++) {
        node = node->GetNext();
    }
    auto sublist = new LinkedList();
    for(int i = 0; i < endIndex - startIndex; i++) {
        if(is_direct_order) {
            sublist->Prepend(node->GetData());
        } else {
            sublist->Append(node->GetData());
        }
        node = node->GetNext();
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
    Node* new_tail = new Node(item);
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
        throw IndexOutOfRange();
    }
    if (index == 0) {
        this->Append(item);
        return;
    }
    if (index == this->length) {
        this->Prepend(item);
        return;
    }
    Node* node = this->head;
    for(int i = 0; i < index-1; i++) {
        node = node->GetNext();
    }
    Node* new_node = new Node(item, node->GetNext());
    node->SetNext(new_node);
    this->length++;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) {
    int len = list->GetLength();
    if (len < 0) {
        return;
    }
    for(int index = 0; index < len; index++) {
        this->prepend(list->Get(index));
    }
}

template <class T>
class LinkedList<T>::Node {
public:
    explicit Node(T data, Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
    void SetNext(Node* node) {
        this->next = node;
    }
    Node* GetNext() {
        return this->next;
    }
    T GetData() {
        return this->data;
    }
private:
    T data;
    Node* next = nullptr;
};
#endif //SEQUENCE_LINKED_LIST_H
