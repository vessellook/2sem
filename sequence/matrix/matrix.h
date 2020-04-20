#pragma once

#include "../sequence/sequence.h"

namespace my_namespace {

    template<class T>
    class IMatrix {
    public:
        virtual ~IMatrix() = default;

        virtual int getSize() const = 0;

        virtual T get(int col_index, int row_index) const = 0;

        virtual T &getRef(int col_index, int row_index) = 0;

        virtual T getNorm() const {
            int len = this->getSize();
            T result = 0;
            T value;
            for(int i = 0; i < len; i++) {
                for(int j = 0; j < len; j++) {
                    value = this->get(i, j);
                    result += value * value;
                }
            }
            return result;
        }

        virtual IMatrix<T> *clone() const = 0;

        virtual IMatrix<T> *map(T (*func)(T)) const = 0;

        virtual IMatrix<T> *transposeNew() const = 0;

        virtual void mapThis(T (*func)(T)) = 0;

        virtual void mulRow(int row_index, T scalar) = 0;

        virtual void mulCol(int col_index, T scalar) = 0;

        virtual IMatrix<T> *minorNew(int col_index, int row_index) const = 0;

        virtual void addToRow(int row_index1, int row_index2, T mul) const = 0;

        virtual void addToCol(int col_index1, int col_index2, T mul) const = 0;

        virtual void exchangeRows(int row_index1, int row_index2) = 0;

        virtual void exchangeCols(int col_index1, int col_index2) = 0;

        virtual void set(int col_index, int row_index, T value) = 0;

        virtual IMatrix<T> &operator*(T scalar) const = 0;

        virtual IMatrix<T> &operator*(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator+(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator-(const IMatrix<T> &matrix) const = 0;

        virtual void operator*=(T scalar) = 0;

        virtual void operator*=(const IMatrix<T> &matrix) = 0;

        virtual void operator+=(const IMatrix<T> &matrix) = 0;

        virtual void operator-=(const IMatrix<T> &matrix) = 0;

        virtual ISequence<T> &operator[](int index) = 0;
        virtual ISequence<T> &operator[](int index) const = 0;
    };

}