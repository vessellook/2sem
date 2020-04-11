#pragma once

#include "../ui/simple_ui.h"

#include "../config.h"
#include "matrix.h"
#include "../sequence/array_sequence.h"
#include "../common/my_exceptions.h"
# include "../common/my_functions.h"

namespace my_namespace {

    template<class T>
    class ArrayMatrix : public IMatrix<T> {
    public:
        explicit ArrayMatrix(index_type size);

        explicit ArrayMatrix(const IMatrix<T>& matrix);

        ~ArrayMatrix() override;

        index_type GetSize() const;

        T Get(index_type col_index, index_type row_index) const override;

        ArrayMatrix<T> *Clone() const override;

        ArrayMatrix<T> *Map(T (*func)(T)) const override;

        ArrayMatrix<T> *TransposeNew() const override;

        ArrayMatrix<T> *MulRowNew(index_type row_index, T scalar) const override;

        ArrayMatrix<T> *MulColNew(index_type col_index, T scalar) const override;

        ArrayMatrix<T> *MinorNew(index_type col_index, index_type row_index) const override;

        ArrayMatrix<T> *AddToRowNew(index_type row_index1, index_type row_index2) const override;

        ArrayMatrix<T> *AddToColNew(index_type col_index1, index_type col_index2) const override;

        ArrayMatrix<T> *ExchangeRowsNew(index_type row_index1, index_type row_index2) const override;

        ArrayMatrix<T> *ExchangeColsNew(index_type col_index1, index_type col_index2) const override;

        void Set(index_type col_index, index_type row_index, T value);

        ArrayMatrix<T> &operator*(T scalar) const override;

        ArrayMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        ISequence<T> &operator[](index_type col_index) const override;

        ISequence<T> &operator[](index_type col_index) override;


    private:
        index_type size_ = 0;
        ISequence<ISequence<T>*> *cols_ = nullptr;

        void MapThis(T (*func)(T));
    };


    template<class T>
    ArrayMatrix<T>::ArrayMatrix(index_type size) {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + std::to_string(size), __FILE__, __func__, __LINE__);
        }
        size_ = size;
        cols_ = new ArraySequence<ISequence<T>*>();
        ArraySequence<T> *col;
        T value;
        for (index_type i = 0; i < size; i++) {

            col = new ArraySequence<T>();
            for (index_type j = 0; j < size; j++) {
                col->Prepend(T());
            }
            cols_->Prepend(col);
        }
    }

    template<class T>
    ArrayMatrix<T>::ArrayMatrix(const IMatrix<T>& matrix) {
        cols_ = new ArraySequence<ISequence<T>*>();
        index_type len = matrix.GetSize();
        for (index_type i = 0; i < len; i++) {
            cols_->Prepend(new ArraySequence<T>());
            const ISequence<T> &sequence = matrix[i];
            for (index_type j = 0; j < len; j++) {
                (*cols_)[i]->Prepend(sequence[j]);
            }
        }
        size_ = matrix.GetSize();
    }

    template<class T>
    ArrayMatrix<T>::~ArrayMatrix() {
        delete cols_;
        cols_ = nullptr;
    }

    template<class T>
    index_type ArrayMatrix<T>::GetSize() const {
        return size_;
    }

    template<class T>
    T ArrayMatrix<T>::Get(index_type col_index, index_type row_index) const {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        return (*(*cols_)[col_index])[row_index];
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::Map(T (*func)(T)) const {
        auto new_matrix = this->Clone();
        new_matrix->MapThis(func);
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::TransposeNew() const {
        index_type len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        for (index_type i = 0; i < len; i++) {
            for (index_type j = 0; j < len; j++) {
                new_matrix->Set(i, j, this->Get(j, i));
            }
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MulRowNew(index_type row_index, T scalar) const {
        index_type len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(*this);
        for (index_type i = 0; i < len; i++) {
            new_matrix->Set(i, row_index, new_matrix->Get(i, row_index) * scalar);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MulColNew(index_type col_index, T scalar) const {
        index_type len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(*this);
        for (index_type i = 0; i < len; i++) {
            new_matrix->Set(col_index, i, new_matrix->Get(col_index, i) * scalar);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MinorNew(index_type col_index, index_type row_index) const {
        index_type len = size_;
        if (col_index < 0 || len <= col_index ||
            row_index < 0 || len <= row_index) {
            throw MyError("Wrong indeces of matrix");
        }
        auto minor = new ArrayMatrix<T>(len - 1);
        index_type x = 0;
        index_type y;
        for (index_type i = 0; i < len; i++) {
            if (i != col_index) {
                y = 0;
                for (index_type j = 0; j < len; j++) {
                    if (j != row_index) {
                        (*minor)[x][y] = this->Get(i, j);
                        y++;
                    }
                }
                x++;
            }

        }
        return minor;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::AddToRowNew(index_type row_index1, index_type row_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            (*new_matrix)[i][row_index1] += this->Get(i, row_index2);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::AddToColNew(index_type col_index1, index_type col_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            (*new_matrix)[col_index1][i] += this->Get(col_index2, i);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::ExchangeRowsNew(index_type row_index1, index_type row_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            (*new_matrix)[i][row_index1] = this->Get(i, row_index2);
            (*new_matrix)[i][row_index2] = this->Get(i, row_index1);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::ExchangeColsNew(index_type col_index1, index_type col_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            (*new_matrix)[col_index1][i] = this->Get(col_index2, i);
            (*new_matrix)[col_index2][i] = this->Get(col_index1, i);
        }
        return new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::Set(index_type col_index, index_type row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
         (*((*(cols_))[col_index]))[row_index] = value;
    }

    template<class T>
    ISequence<T> &ArrayMatrix<T>::operator[](index_type col_index) {
        return *((*(cols_))[col_index]);
    }

    template<class T>
    ISequence<T> &ArrayMatrix<T>::operator[](index_type col_index) const {
        return *((*(cols_))[col_index]);
    }

    template<class T>
    void ArrayMatrix<T>::MapThis(T (*func)(T)) {
        ISequence<T> *col;
        for (index_type i = 0; i < size_; i++) {
            col = cols_[0][i]->Map(func);
            delete cols_[0][i];
            cols_[0][i] = col;
        }
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator+(const IMatrix<T> &matrix) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        *new_matrix += matrix;
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator-(const IMatrix<T> &matrix) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        *new_matrix -= matrix;
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator*(const IMatrix<T> &matrix) const {
        index_type len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(this->GetSize());
        T value1;
        T value2;
        for (index_type col_index = 0; col_index < len; col_index++) {
            for (index_type row_index = 0; row_index < len; row_index++) {
                (*new_matrix)[col_index][row_index] = T();
                for (index_type k = 0; k < len; k++) {
                    value1 = this->Get(col_index, k);
                    value2 = matrix.Get(k, row_index);
//                    std::cout << "value1 = " << value1 << "; value2 = " << value2 << "; col_index = " << col_index << "; row_index = " << row_index << "; k = " << k << std::endl;
                    (*new_matrix)[col_index][row_index] += value1 * value2;
                }
            }
        }
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator*(T scalar) const {
        MulWrapper<T>::setValue(scalar);
        T (*func)(T) = MulWrapper<T>::Mul;
        ArrayMatrix<T> *new_matrix = Map(func);
        return *new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::operator+=(const IMatrix<T> &matrix) {
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            for (index_type j = 0; j < len; j++) {
                this->Set(i, j, this->Get(i, j) + matrix.Get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator-=(const IMatrix<T> &matrix) {
        index_type len = this->GetSize();
        for (index_type i = 0; i < len; i++) {
            for (index_type j = 0; j < len; j++) {
                this->Set(i, j, this->Get(i, j) - matrix.Get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(const IMatrix<T> &matrix) {
        auto new_matrix = (*this) * matrix;
        delete this->cols_;
        this->cols_ = new_matrix.cols_;
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(T scalar) {
        MulWrapper<T>::setValue(scalar);
        this->MapThis(MulWrapper<T>::Mul);
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::Clone() const {
        auto new_matrix = new ArrayMatrix<T>(this->GetSize());
        for (index_type i = 0; i < size_; i++) {
            for (index_type j = 0; j < size_; j++) {
                new_matrix->Set(i, j, this->Get(i, j));
            }
        }
        return new_matrix;
    }

}