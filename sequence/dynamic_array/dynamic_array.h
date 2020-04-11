#pragma once

#include "../config.h"
#include "../common/my_exceptions.h"

namespace my_namespace {
    template<class T>
    class DynamicArray {
    public:
        DynamicArray(T *items, index_type count);

        explicit DynamicArray(index_type size = 0);

        ~DynamicArray();

        T Get(index_type index) const;

        int GetSize() const { return size_; };

        void Set(index_type index, T value);

        void Resize(index_type new_size);

        DynamicArray<T> *Clone() const;

        T &operator[](index_type index) { return GetRef(index); };

        T operator[](index_type index) const { return Get(index); };

    private:

        T &GetRef(index_type index);

        T *c_array_ = nullptr;
        index_type size_;
    };


    template<class T>
    DynamicArray<T>::DynamicArray(T *items, index_type count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        if (count > 0) {
            c_array_ = static_cast<T *>(malloc(sizeof(T) * count));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for (index_type i = 0; i < count; i++) {
                c_array_[i] = items[i];
            }
        }
        size_ = count;
    }

    template<class T>
    DynamicArray<T>::DynamicArray(int size): c_array_(nullptr), size_(size) {
        if (size_ < 0) {
            throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ > 0) {
            c_array_ = static_cast<T *>(malloc(sizeof(T) * size_));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
        }
    }

    template<class T>
    DynamicArray<T>::~DynamicArray() {
        free(c_array_);
        c_array_ = nullptr;
    }

    template<class T>
    T DynamicArray<T>::Get(index_type index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        T &result = c_array_[index];
        return result;
    }

    template<class T>
    void DynamicArray<T>::Set(index_type index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        c_array_[index] = value;
    }

    template<class T>
    void DynamicArray<T>::Resize(index_type new_size) {
        if (new_size < 0) {
            IndexOutOfRangeError("new_size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ == 0) {
            c_array_ = static_cast<T *>(malloc(sizeof(T) * new_size));
        } else {
            c_array_ = static_cast<T *>(realloc((void *) c_array_, sizeof(T) * new_size));
        }
        if (c_array_ == nullptr) {
            MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = new_size;
    }


    template<class T>
    T &DynamicArray<T>::GetRef(index_type index) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index];
    }

    template<class T>
    DynamicArray<T> *DynamicArray<T>::Clone() const {
        auto new_array = new DynamicArray<T>(size_);
        for (index_type i = 0; i < size_; i++) {
            new_array->Set(i, this->Get(i));
        }
        return new_array;
    }
}
