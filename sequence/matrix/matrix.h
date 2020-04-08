#pragma once

#include "../sequence/sequence.h"

namespace my_namespace {

    template<class T>
    class IMatrix {
    public:
        virtual ~IMatrix() = default;

        virtual int GetSize() const = 0;

        virtual T Get(int col_index, int row_index) const = 0;

        virtual T getNorm() const {
            int len = this->GetSize();
            T result = 0;
            T value;
            for(int i = 0; i < len; i++) {
                for(int j = 0; j < len; j++) {
                    value = this->Get(i, j);
                    result += value * value;
                }
            }
            return result;
        }

        virtual IMatrix<T> *Map(T (*func)(T)) const = 0;

        virtual IMatrix<T> *TransposeNew() const = 0;

        virtual IMatrix<T> *MulRowNew(int row_index, T scalar) const = 0;

        virtual IMatrix<T> *MulColNew(int col_index, T scalar) const = 0;

        virtual IMatrix<T> *MinorNew(int col_index, int row_index) const = 0;

        virtual IMatrix<T> *AddToRowNew(int row_index1, int row_index2) const = 0;

        virtual IMatrix<T> *AddToColNew(int col_index1, int col_index2) const = 0;

        virtual IMatrix<T> *ExchangeRowsNew(int row_index1, int row_index2) const = 0;

        virtual IMatrix<T> *ExchangeColsNew(int col_index1, int col_index2) const = 0;

        virtual void Set(int col_index, int row_index, T value) = 0;

        virtual IMatrix<T> &operator*(T scalar) const = 0;

        virtual IMatrix<T> &operator*(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator+(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator-(const IMatrix<T> &matrix) const = 0;

        virtual void operator*=(T scalar) = 0;

        virtual void operator*=(const IMatrix<T> &matrix) = 0;

        virtual void operator+=(const IMatrix<T> &matrix) = 0;

        virtual void operator-=(const IMatrix<T> &matrix) = 0;

        virtual ISequence<T> &operator[](int index) = 0;
    };

}