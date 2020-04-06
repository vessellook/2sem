#pragma once

#include "my_exceptions.h"

template <class T>
class DynamicArray {
public:
    DynamicArray(T* items, int count);
    explicit DynamicArray(int size = 0);
    DynamicArray(DynamicArray<T> const &dynamic_array);
    ~DynamicArray();
    T Get(int index) const;
    int GetSize() const;
    void Set(int index, T value);
    void Resize(int new_size);
    T & operator[](int index);
private:
    T* items = nullptr;
    int size = 0;
};


template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    if (count < 0) {
        throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
    }
    this->items = new T[count];
    if (this->items == nullptr) {
        throw MemoryAllocationError("this->items == nullptr", __FILE__, __func__, __LINE__);
    }
    for (int i = 0; i < count; i++) {
        this->items[i] = items[i];
    }
    this->size = count;
}

template  <class T>
DynamicArray<T>::DynamicArray(int size) {
    if(size < 0) {
        throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
    }
    if(size == 0) {
        this->size = 0;
        this->items = nullptr;
    } else {
        this->items = new T[size];
        if (this->items == nullptr) {
            throw MemoryAllocationError("this->items == nullptr", __FILE__, __func__, __LINE__);
        }
        this->size = size;
    }
}

template  <class T>
DynamicArray<T>::~DynamicArray() {
    delete this->items;
}

template  <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> const &dynamic_array) {
    size = dynamic_array.GetSize();
    if(size < 0) {
        IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
    }
    if(size == 0) {
        this->size = 0;
        this->items = nullptr;
        return;
    }
    this->items = new T[size];
    if (this->items == nullptr) {
        throw MemoryAllocationError("this->items == nullptr", __FILE__, __func__, __LINE__);
    }
    this->size = size;
    for(int index = 0; index < size; index++) {
        this->Set(index, dynamic_array.Get(index));
    }
}

template <class T>
T DynamicArray<T>::Get(int index) const {
    if(this->size <= index || index < 0) {
        std::string message = "this->size = " + std::to_string(this->size)
                              + "; index = " + std::to_string(index);
        throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
    }
    return items[index];
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return this->size;
}

template <class T>
void DynamicArray<T>::Set(int index, T value) {
    if(this->size <= index || index < 0) {
        std::string message = "this->size = " + std::to_string(this->size)
                              + "; index = " + std::to_string(index);
        throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
    }
    this->items[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int new_size) {
    if(new_size < 0) {
        IndexOutOfRangeError("new_size < 0", __FILE__, __func__, __LINE__);
    }
    if(this->size == 0) {
        this->items = new T[size];
    } else {
        this->items = (T*) realloc((void *) this->items, sizeof(T) * new_size);
    }
    if (this->items == nullptr) {
        MemoryAllocationError("this->items == nullptr", __FILE__, __func__, __LINE__);
    }
    this->size = new_size;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    if(this->size <= index || index < 0) {
        std::string message = "this->size = " + std::to_string(this->size)
                              + "; index = " + std::to_string(index);
        throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
    }
    return (this->items)[index];
}
