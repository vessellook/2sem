#pragma once

#include "../sequence/sequence.h"

namespace my_namespace {

    template<class T>
    class IMatrix {
    public:
        virtual ~IMatrix() = default;

        virtual unsigned getSize() const = 0;

        virtual T get(unsigned col_index, unsigned row_index) const = 0;

        virtual T &getRef(unsigned col_index, unsigned row_index) = 0;

        virtual T getNorm() const {
            unsigned len = this->getSize();
            T result = 0;
            T value;
            for(unsigned i = 0; i < len; ++i) {
                for(unsigned j = 0; j < len; ++j) {
                    value = this->get(i, j);
                    result += value * value;
                }
            }
            return result;
        }

        virtual IMatrix<T> *clone() const = 0;

        virtual IMatrix<T> *transpose() = 0;

        virtual IMatrix<T> *map(T (*func)(T)) = 0;

        virtual IMatrix<T> *mulRow(unsigned row_index, T scalar) = 0;

        virtual IMatrix<T> *mulCol(unsigned col_index, T scalar) = 0;

        virtual IMatrix<T> *getMinor(unsigned col_index, unsigned row_index) const = 0;

        virtual IMatrix<T> *addToRow(unsigned row_index1, unsigned row_index2, T mul) = 0;

        virtual IMatrix<T> *addToCol(unsigned col_index1, unsigned col_index2, T mul) = 0;

        virtual IMatrix<T> *exchangeRows(unsigned row_index1, unsigned row_index2) = 0;

        virtual IMatrix<T> *exchangeCols(unsigned col_index1, unsigned col_index2) = 0;

        virtual IMatrix<T> *set(unsigned col_index, unsigned row_index, T value) = 0;

        virtual IMatrix<T> &operator*(T scalar) const = 0;

        virtual IMatrix<T> &operator*(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator+(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator-(const IMatrix<T> &matrix) const = 0;

        virtual void operator*=(T scalar) = 0;

        virtual void operator*=(const IMatrix<T> &matrix) = 0;

        virtual void operator+=(const IMatrix<T> &matrix) = 0;

        virtual void operator-=(const IMatrix<T> &matrix) = 0;

        virtual ISequence<T> &operator[](unsigned index) = 0;
        virtual ISequence<T> &operator[](unsigned index) const = 0;
    };

}