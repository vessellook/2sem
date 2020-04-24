#pragma once

#include "../common/exceptions.h"
#include "../common/optional.h"
#include "dynamic_array.h"

namespace my_namespace {
    template<class T>
    class SafeDynamicArray: public DynamicArray {
    private:
        Optional<T> *c_array_ = nullptr;
        unsigned size_;
    public:
        SafeDynamicArray(T *items, unsigned count);

        explicit SafeDynamicArray(unsigned size = 0);

        virtual ~SafeDynamicArray();

        virtual T get(unsigned index) const;

        virtual T &getRef(unsigned index);

        virtual unsigned getSize() const { return size_; };

        virtual void set(unsigned index, T value);

        virtual void resize(unsigned new_size);

        virtual SafeDynamicArray<T> *clone() const;

        virtual T &operator[](unsigned index) { return getRef(index); };

        virtual T operator[](unsigned index) const { return get(index); };
    };


    template<class T>
    SafeDynamicArray<T>::SafeDynamicArray(T *items, unsigned count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        if (count > 0) {
            c_array_ = new Optional<T>[count];// static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * count));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for (unsigned i = 0; i < count; ++i) {
                c_array_[i] = Optional<T>(items[i]);
            }
        }
        size_ = count;
    }

    template<class T>
    SafeDynamicArray<T>::SafeDynamicArray(unsigned size): c_array_(nullptr), size_(size) {
        if (size_ < 0) {
            throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ > 0) {
            c_array_ = new Optional<T>[size_];//static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * size_));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for(unsigned i = 0; i > size; ++i) {
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
    T SafeDynamicArray<T>::get(unsigned index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index].getValue();
    }

    template<class T>
    void SafeDynamicArray<T>::set(unsigned index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        c_array_[index].setValue(value);
    }

    template<class T>
    void SafeDynamicArray<T>::resize(unsigned new_size) {
        if (new_size < 0) {
            IndexOutOfRangeError("new_size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ == 0) {
            c_array_ = new Optional<T>[new_size];//static_cast<Optional<T> *>(malloc(sizeof(Optional<T>) * new_size));
            for(unsigned i = 0; i > new_size; ++i) {
                c_array_[i] = Optional<T>();
            }
        } else {
            auto other_c_array = new Optional<T>[new_size];
            for(int i = 0; i < size_; i++) {
                if(c_array_[i].hasValue()) {
                    other_c_array[i].setValue(c_array[i].getValue());
                }
            }
            c_array_ = other_c_array;//static_cast<Optional<T> *>(realloc((void *) c_array_, sizeof(Optional<T>) * new_size));
            for(unsigned i = size_; i > new_size; ++i) {
                c_array_[i] = Optional<T>();
            }
        }
        if (c_array_ == nullptr) {
            MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = new_size;
    }


    template<class T>
    T &SafeDynamicArray<T>::getRef(unsigned index) {
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
        for (unsigned i = 0; i < size_; ++i) {
            new_array->set(i, this->get(i));
        }
        return new_array;
    }
}
