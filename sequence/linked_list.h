#ifndef SEQUENCE_LINKED_LIST_H
#define SEQUENCE_LINKED_LIST_H

template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T* items, int count, bool is_direct_order = true);
    LinkedList(LinkedList<T> const & linked_list, bool is_direct_order = true);
    ~LinkedList();
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    int GetLength() const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex, bool is_direct_order = true) const;
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, int index);
    void Set(int index, T item);
    LinkedList<T>* Concat(const LinkedList<T> *list) const;
    T& operator[](int index);
private:
    class Node;
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
    Node* MoveForward(Node* node, int count = 1);
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
        throw MyError("IndexOutOfRangeError");
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
        if (is_direct_order) {
            this->Prepend(linked_list->Get(index));
        } else {
            this->Append(linked_list->Get(index));
        }
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    int len = this->GetLength();
    Node* node;
    for(int i = 0; i < len; i++) {
        node = this->head->next;
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
    Node* node = this->MoveForward(this->head, index);
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
    Node* node = this->MoveForward(this->head, startIndex);
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
    Node* new_node = new Node(item, node->GetNext());
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
    auto new_list = new LinkedList<T>(this);
    int len = list->GetLength();
    if (len < 0) {
        return;
    }
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
        return & this->data_;
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
typename LinkedList<T>::Node *LinkedList<T>::MoveForward(LinkedList::Node *node, int count) {
    for(int i = 0; i < count; i++) {
        node = node->GetNext();
    }
    return node;
}

#endif //SEQUENCE_LINKED_LIST_H
