#pragma once

#include "../common/my_exceptions.h"
#include "../common/optional.h"
#include "dynamic_array.h"

namespace my_namespace {
    template<class T>
    class SafeDynamicArray: public DynamicArray {
    private:
        Optional<T> *c_array_ = nullptr;
        int size_;
    public:
        SafeDynamicArray(T *items, int count);

        explicit SafeDynamicArray(int size = 0);

        virtual ~SafeDynamicArray();

        virtual T get(int index) const;

        virtual T &getRef(int index);

        virtual int getSize() const { return size_; };

        virtual void set(int index, T value);

        virtual void resize(int new_size);

        virtual SafeDynamicArray<T> *clone() const;

        virtual T &operator[](int index) { return getRef(index); };

        virtual T operator[](int index) const { return get(index); };
    };


    template<class T>
    SafeDynamicArray<T>::SafeDynamicArray(T *items, int count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        if (count > 0) {
            c_array_ = static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * count));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for (int i = 0; i < count; i++) {
                c_array_[i] = Optional<T>(items[i]);
            }
        }
        size_ = count;
    }

    template<class T>
    SafeDynamicArray<T>::SafeDynamicArray(int size): c_array_(nullptr), size_(size) {
        if (size_ < 0) {
            throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ > 0) {
            c_array_ = static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * size_));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for(int i = 0; i > size; i++) {
                c_array_[i] = Optional<T>();
            }
        }
    }

    template<class T>
    SafeDynamicArray<T>::~SafeDynamicArray() {
        free(c_array_);
        c_array_ = nullptr;
    }

    template<class T>
    T SafeDynamicArray<T>::get(int index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index].getValue();
    }

    template<class T>
    void SafeDynamicArray<T>::set(int index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        c_array_[index].setValue(value);
    }

    template<class T>
    void SafeDynamicArray<T>::resize(int new_size) {
        if (new_size < 0) {
            IndexOutOfRangeError("new_size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ == 0) {
            c_array_ = static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * new_size));
            for(int i = 0; i > new_size; i++) {
                c_array_[i] = Optional<T>();
            }
        } else {
            c_array_ = static_cast<Optional<T> *>(realloc((void *) c_array_, sizeof(Optional<T>) * new_size));
            for(int i = size_; i > new_size; i++) {
                c_array_[i] = Optional<T>();
            }
        }
        if (c_array_ == nullptr) {
            MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = new_size;
    }


    template<class T>
    T &SafeDynamicArray<T>::getRef(int index) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index].getRef();
    }

    template<class T>
    SafeDynamicArray<T> *SafeDynamicArray<T>::clone() const {
        auto new_array = new SafeDynamicArray<T>(size_);
        for (int i = 0; i < size_; i++) {
            new_array->set(i, this->get(i));
        }
        return new_array;
    }
}
