#pragma once

#include "../common/my_exceptions.h"

namespace my_namespace {

    template<class T>
    class DynamicArray {
    public:
        DynamicArray(T *items, int count);

        explicit DynamicArray(int size = 0);

        DynamicArray(DynamicArray<T> const &dynamic_array);

        ~DynamicArray();

        T Get(int index) const;

        int GetSize() const;

        void Set(int index, T value);

        void Resize(int new_size);

        T &operator[](int index);

    private:
        T *items_ = nullptr;
        int size_ = 0;
    };


    template<class T>
    DynamicArray<T>::DynamicArray(T *items, int count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        items_ = new T[count];
        if (items_ == nullptr) {
            throw MemoryAllocationError("items_ == nullptr", __FILE__, __func__, __LINE__);
        }
        for (int i = 0; i < count; i++) {
            items_[i] = items[i];
        }
        size_ = count;
    }

    template<class T>
    DynamicArray<T>::DynamicArray(int size) {
        if (size < 0) {
            throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size == 0) {
            size_ = 0;
            items_ = nullptr;
        } else {
            items_ = new T[size];
            if (items_ == nullptr) {
                throw MemoryAllocationError("items_ == nullptr", __FILE__, __func__, __LINE__);
            }
            size_ = size;
        }
    }

    template<class T>
    DynamicArray<T>::~DynamicArray() {
        delete items_;
    }

    template<class T>
    DynamicArray<T>::DynamicArray(DynamicArray<T> const &dynamic_array) {
        size_ = dynamic_array.GetSize();
        if (size_ < 0) {
            IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ == 0) {
            size_ = 0;
            items_ = nullptr;
            return;
        }
        items_ = new T[size_];
        if (items_ == nullptr) {
            throw MemoryAllocationError("items_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = size_;
        for (int index = 0; index < size_; index++) {
            this->Set(index, dynamic_array.Get(index));
        }
    }

    template<class T>
    T DynamicArray<T>::Get(int index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return items_[index];
    }

    template<class T>
    int DynamicArray<T>::GetSize() const {
        return size_;
    }

    template<class T>
    void DynamicArray<T>::Set(int index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        items_[index] = value;
    }

    template<class T>
    void DynamicArray<T>::Resize(int new_size) {
        if (new_size < 0) {
            IndexOutOfRangeError("new_size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ == 0) {
            items_ = new T[size_];
        } else {
            items_ = (T *) realloc((void *) items_, sizeof(T) * new_size);
        }
        if (items_ == nullptr) {
            MemoryAllocationError("items_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = new_size;
    }

    template<class T>
    T &DynamicArray<T>::operator[](int index) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return (items_)[index];
    }

}
