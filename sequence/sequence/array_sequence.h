#pragma once
#include <memory>

#include "../common/exceptions.h"
#include "sequence.h"
#include "../dynamic_array/dynamic_array.h"

namespace my_namespace {

    template<class T>
    class ArraySequence : public ISequence<T> {
    private:
        std::shared_ptr<DynamicArray<T>> array_;
        unsigned length_ = 0;
        unsigned buffer_length_ = 10;
    private:
        void resize(unsigned new_size);

    public:
        ArraySequence();

        ArraySequence(const T *items, unsigned count);

        explicit ArraySequence(const ISequence<T> &array);

        unsigned getLength() const override { return length_; };

        T getFirst() const override;

        T getLast() const override;

        T get(unsigned index) const override;

        T reduce(T (*func)(T, T)) const override;

        T reduce(T (*func)(T, T), T initial) const override;

        ArraySequence<T> *clone() const override;

        ArraySequence<T> *map(T (*func)(T)) override;

        T getFirstMatch(bool (*check)(T)) const override;

        ArraySequence<T> *where(bool (*check)(T)) override;

        ArraySequence<T> *concat(const ISequence<T> &sequence) override;

        ArraySequence<T> *getSubsequence(unsigned startIndex, unsigned endIndex) const override;

        ArraySequence<T> *set(unsigned index, T value) override;

        T &getRef(unsigned index) override;

        ArraySequence<T> *append(T item) override;

        ArraySequence<T> *prepend(T item) override;

        ArraySequence<T> *insertAt(T item, unsigned index) override;

        T &operator[](unsigned index) override { return getRef(index); }

        T operator[](unsigned index) const override { return get(index); }
    };

    template<class T>
    ArraySequence<T>::ArraySequence(): array_(new DynamicArray<T>()) {
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const T *items, unsigned count): array_(new DynamicArray<T>()) {
        resize(count);
        for (unsigned i = 0; i < count; ++i) {
            set(i, items[i]);
        }
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ISequence<T> &array) {
        array_ = std::make_shared<DynamicArray<T>>();
        resize(array.getLength());
        for (unsigned index = 0; index < getLength(); ++index) {
            set(index, array[index]);
        }
    }

    template<class T>
    T ArraySequence<T>::getFirst() const {
        if (getLength() <= 0) {
            throw IndexOutOfRangeError("this->getLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return array_->get(0);
    }

    template<class T>
    T ArraySequence<T>::getLast() const {
        unsigned size = getLength();
        if (size <= 0) {
            throw IndexOutOfRangeError("this->getLength() <= 0", __FILE__, __func__, __LINE__);
        }
        return array_->get(size - 1);
    }

    template<class T>
    T ArraySequence<T>::get(unsigned index) const {
        if (getLength() <= index || index < 0) {
            std::string message = "this->getLength() = " + std::to_string(getLength())
                                  + "; index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return array_->get(index);
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::append(T item) {
        unsigned len = getLength();
        resize(len + 1);
        for (unsigned i = len; i > 0; i--) {
            set(i, get(i - 1));
        }
        set(0, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::prepend(T item) {
        unsigned len = getLength();
        resize(len + 1);
        set(len, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::insertAt(T item, unsigned index) {
        unsigned len = getLength();
        resize(len + 1);
        for (unsigned i = len; i > index; i--) {
            set(i, get(i - 1));
        }
        set(index, item);
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::concat(const ISequence<T> &sequence) {
        unsigned start = length_;
        resize(getLength() + sequence.getLength());
        unsigned end = length_;
        for (unsigned index = start; index < end; index++) {

            set(index, sequence[index - start]);
        }
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::getSubsequence(unsigned startIndex, unsigned endIndex) const {
        if (getLength() <= endIndex || startIndex < 0 || startIndex > endIndex) {
            std::string message = "this->getLength() = " +
                                  std::to_string(getLength()) + "; " +
                                  "startIndex = " + std::to_string(startIndex) +
                                  "endIndex = " + std::to_string(endIndex);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        auto subsequence = new ArraySequence<T>();
        subsequence->resize(endIndex - startIndex);
        for (unsigned index = startIndex; index <= endIndex; ++index) {
            (*subsequence)[index] = get(index);
        }
        return subsequence;
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T), T initial) const {
        unsigned len = getLength();
        T result = initial;
        for (unsigned i = 0; i < len; ++i) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    T ArraySequence<T>::reduce(T (*func)(T, T)) const {
        unsigned len = getLength();
        if (len <= 0) {
            throw MyError("Reduce to empty sequence", __FILE__, __func__, __LINE__);
        }
        T result = get(0);
        for (unsigned i = 1; i < len; ++i) {
            result = func(result, get(i));
        }
        return result;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::where(bool (*func)(T)) {
        auto array = DynamicArray<T>(length_);
        unsigned len = length_;
        for (unsigned i = 0; i < len; ++i) {
            if (func(get(i))) array.set(i, get(i));
            else length_--;
        }
        array_ = std::shared_ptr<DynamicArray<T>>(array.clone()->resize(length_));
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::map(T (*func)(T)) {
        unsigned len = getLength();
        for (unsigned i = 0; i < len; ++i) {
            set(i, func(get(i)));
        }
        return this;
    }

    template<class T>
    void ArraySequence<T>::resize(unsigned new_size) {
        if (array_->getSize() < new_size) {
            array_->resize(new_size + buffer_length_);
        }
        length_ = new_size;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::set(unsigned index, T value) {
        this->array_->getRef(index) = value;
        return this;
    }

    template<class T>
    ArraySequence<T> *ArraySequence<T>::clone() const {
        auto new_sequence = new ArraySequence<T>();
        new_sequence->resize(getLength());
        for (unsigned index = 0; index < length_; ++index) {
            new_sequence->array_->set(index, get(index));
        }
        return new_sequence;
    }

	template <class T>
	T ArraySequence<T>::getFirstMatch(bool(*check)(T)) const {
		for (unsigned i = 0; i < this->length_; i++) {
			if (check(array_->get(i))) {
				return array_->get(i);
			}
		}
		throw std::exception();
	}

    template<class T>
    T &ArraySequence<T>::getRef(unsigned index) {
        if (getLength() <= index || index < 0) {
            std::string message = "this->getLength() = " +
                                  std::to_string(getLength()) + "; " +
                                  "index = " + std::to_string(index);
            throw IndexOutOfRangeError(message, __FILE__, __func__, __LINE__);
        }
        return array_->getRef(index);
    }

    // extra

    template<class F, class T>
    ArraySequence<T> *mapNewA(const ISequence<F> &sequence, T (*func)(F)) {
        auto new_sequence = new ArraySequence<T>();
        unsigned len = sequence.getLength();
        for (unsigned index = 0; index < len; ++index) {
            new_sequence->prepend(func(sequence[index]));
        }
        return new_sequence;
    }

    template<class F, class T>
    ArraySequence<T> *mapNewA(const ISequence<F> &sequence, T (*func)(F, unsigned)) {
        auto new_sequence = new ArraySequence<T>();
        unsigned len = sequence.getLength();
        for (unsigned index = 0; index < len; ++index) {
            new_sequence->prepend(func(sequence[index], index));
        }
        return new_sequence;
    }
}
