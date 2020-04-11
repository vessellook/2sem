#pragma once

#include "../config.h"
#include "../sequence/sequence.h"

namespace my_namespace {

    template<class T>
    class IMatrix {
    public:
        virtual ~IMatrix() = default;

        virtual index_type GetSize() const = 0;

        virtual T Get(index_type col_index, index_type row_index) const = 0;

        virtual T getNorm() const {
            index_type len = this->GetSize();
            T result = 0;
            T value;
            for(index_type i = 0; i < len; i++) {
                for(index_type j = 0; j < len; j++) {
                    value = this->Get(i, j);
                    result += value * value;
                }
            }
            return result;
        }

        virtual IMatrix<T> *Clone() const = 0;

        virtual IMatrix<T> *Map(T (*func)(T)) const = 0;

        virtual IMatrix<T> *TransposeNew() const = 0;

        virtual IMatrix<T> *MulRowNew(index_type row_index, T scalar) const = 0;

        virtual IMatrix<T> *MulColNew(index_type col_index, T scalar) const = 0;

        virtual IMatrix<T> *MinorNew(index_type col_index, index_type row_index) const = 0;

        virtual IMatrix<T> *AddToRowNew(index_type row_index1, index_type row_index2) const = 0;

        virtual IMatrix<T> *AddToColNew(index_type col_index1, index_type col_index2) const = 0;

        virtual IMatrix<T> *ExchangeRowsNew(index_type row_index1, index_type row_index2) const = 0;

        virtual IMatrix<T> *ExchangeColsNew(index_type col_index1, index_type col_index2) const = 0;

        virtual void Set(index_type col_index, index_type row_index, T value) = 0;

        virtual IMatrix<T> &operator*(T scalar) const = 0;

        virtual IMatrix<T> &operator*(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator+(const IMatrix<T> &matrix) const = 0;

        virtual IMatrix<T> &operator-(const IMatrix<T> &matrix) const = 0;

        virtual void operator*=(T scalar) = 0;

        virtual void operator*=(const IMatrix<T> &matrix) = 0;

        virtual void operator+=(const IMatrix<T> &matrix) = 0;

        virtual void operator-=(const IMatrix<T> &matrix) = 0;

        virtual ISequence<T> &operator[](index_type index) = 0;
        virtual ISequence<T> &operator[](index_type index) const = 0;
    };

}