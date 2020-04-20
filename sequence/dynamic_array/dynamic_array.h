#pragma once

#include "../common/my_exceptions.h"

namespace my_namespace {
    template<class T>
    class DynamicArray {
    private:
        T *c_array_ = nullptr;
        int size_;
    public:
        DynamicArray(T *items, int count);

        explicit DynamicArray(int size = 0);

        virtual ~DynamicArray();

        virtual T get(int index) const;

        virtual T &getRef(int index);

        virtual int getSize() const { return size_; };

        virtual void set(int index, T value);

        virtual void resize(int new_size);

        virtual DynamicArray<T> *clone() const;

        virtual T &operator[](int index) { return getRef(index); };

        virtual T operator[](int index) const { return get(index); };
    };


    template<class T>
    DynamicArray<T>::DynamicArray(T *items, int count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        if (count > 0) {
            c_array_ = static_cast<T *>(malloc(sizeof(T) * count));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for (int i = 0; i < count; i++) {
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
    T DynamicArray<T>::get(int index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        T &result = c_array_[index];
        return result;
    }

    template<class T>
    void DynamicArray<T>::set(int index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        c_array_[index] = value;
    }

    template<class T>
    void DynamicArray<T>::resize(int new_size) {
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
    T &DynamicArray<T>::getRef(int index) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index];
    }

    template<class T>
    DynamicArray<T> *DynamicArray<T>::clone() const {
        auto new_array = new DynamicArray<T>(size_);
        for (int i = 0; i < size_; i++) {
            new_array->set(i, this->get(i));
        }
        return new_array;
    }
}
