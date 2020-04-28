#pragma once

#include "../common/exceptions.h"

namespace my_namespace {
    template<class T>
    class DynamicArray {
    private:
        unsigned size_;
        T *c_array_ = nullptr;
    public:
        DynamicArray(T *items, unsigned count);

        explicit DynamicArray(unsigned size = 0);

        virtual ~DynamicArray();

        virtual T get(unsigned index) const;

        virtual T &getRef(unsigned index);

        virtual unsigned getSize() const { return size_; };

        virtual DynamicArray<T>* set(unsigned index, T value);

        virtual DynamicArray<T>* resize(unsigned new_size);

        virtual DynamicArray<T> *clone() const;

        virtual T &operator[](unsigned index) { return getRef(index); };

        virtual T operator[](unsigned index) const { return get(index); };
    };


    template<class T>
    DynamicArray<T>::DynamicArray(T *items, unsigned count): size_(count) {
        if (count < 0) {
            throw IndexOutOfRangeError("count < 0", __FILE__, __func__, __LINE__);
        }
        if (count > 0) {
            c_array_ = new T[count];//static_cast<T *>(malloc(sizeof(T) * count));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
            for (unsigned i = 0; i < count; ++i) {
                c_array_[i] = items[i];
            }
        }
    }

    template<class T>
    DynamicArray<T>::DynamicArray(unsigned size): c_array_(nullptr), size_(size) {
        if (size_ < 0) {
            throw IndexOutOfRangeError("size < 0", __FILE__, __func__, __LINE__);
        }
        if (size_ > 0) {
            c_array_ = new T[size_];//static_cast<T *>(malloc(sizeof(T) * size_));
            if (c_array_ == nullptr) {
                throw MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
            }
        }
        for (unsigned i = 0; i < size_; ++i) {
            c_array_[i] = T();
        }
    }

    template<class T>
    DynamicArray<T>::~DynamicArray() {
        if(c_array_ != nullptr) {
            delete[] c_array_;//free(c_array_);
            c_array_ = nullptr;
        }
    }

    template<class T>
    T DynamicArray<T>::get(unsigned index) const {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return c_array_[index];
    }

    template<class T>
    DynamicArray<T>* DynamicArray<T>::set(unsigned index, T value) {
        if (size_ <= index || index < 0) {
            std::string message = "size_ = " + std::to_string(size_)
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        c_array_[index] = value;
        return this;
    }

    template<class T>
    DynamicArray<T>* DynamicArray<T>::resize(unsigned new_size) {
        if (new_size == 0) {
            size_ = 0;
            if(c_array_ != nullptr) {
                delete[] c_array_;
            }
        }
        if (size_ == 0) {
            c_array_ = new T[new_size];//static_cast<T *>(malloc(sizeof(T) * new_size));
        } else {
            auto other_c_array = new T[new_size];
            for(int i = 0; i < size_; i++) {
                other_c_array[i] = c_array_[i];
            }
            c_array_ = other_c_array;
            //c_array_ = static_cast<T *>(realloc((void *) c_array_, sizeof(T) * new_size));
        }
        if (c_array_ == nullptr) {
            MemoryAllocationError("c_array_ == nullptr", __FILE__, __func__, __LINE__);
        }
        size_ = new_size;
        return this;
    }


    template<class T>
    T &DynamicArray<T>::getRef(unsigned index) {
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
        for (unsigned i = 0; i < size_; ++i) {
            new_array->set(i, this->get(i));
        }
        return new_array;
    }
}
