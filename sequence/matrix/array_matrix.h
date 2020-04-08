#pragma once

#include "matrix.h"
#include "../sequence/array_sequence.h"
#include "../common/my_exceptions.h"
# include "../common/my_functions.h"

namespace my_namespace {

    template<class T>
    class ArrayMatrix : public IMatrix<T> {
    public:
        explicit ArrayMatrix(int size);

        explicit ArrayMatrix(const IMatrix<T> &matrix);

        ~ArrayMatrix() override;

        int GetSize() const;

        T Get(int col_index, int row_index) const override;

        ArrayMatrix<T> *Map(T (*func)(T)) const override;

        ArrayMatrix<T> *TransposeNew() const override;

        ArrayMatrix<T> *MulRowNew(int row_index, T scalar) const override;

        ArrayMatrix<T> *MulColNew(int col_index, T scalar) const override;

        ArrayMatrix<T> *MinorNew(int col_index, int row_index) const override;

        ArrayMatrix<T> *AddToRowNew(int row_index1, int row_index2) const override;

        ArrayMatrix<T> *AddToColNew(int col_index1, int col_index2) const override;

        ArrayMatrix<T> *ExchangeRowsNew(int row_index1, int row_index2) const override;

        ArrayMatrix<T> *ExchangeColsNew(int col_index1, int col_index2) const override;

        void Set(int col_index, int row_index, T value);

        ArrayMatrix<T> &operator*(T scalar) const override;

        ArrayMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        ArraySequence<T> &operator[](int col_index) override;

    private:
        int size_ = 0;
        ArraySequence<ArraySequence<T> *> *cols_ = nullptr;

        void MapThis(T (*func)(T));
    };


    template<class T>
    ArrayMatrix<T>::ArrayMatrix(int size) {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + std::to_string(size), __FILE__, __func__, __LINE__);
        }
        size_ = size;
        cols_ = new ArraySequence<ArraySequence<T> *>();
        ArraySequence<T> *col;
        T value;
        for (int i = 0; i < size; i++) {
            col = new ArraySequence<T>();
            for (int j = 0; j < size; j++) {
                col->Prepend(T());
            }
            cols_->Prepend(col);
        }
    }

    template<class T>
    ArrayMatrix<T>::ArrayMatrix(const IMatrix<T> &matrix) {
        cols_ = new ArraySequence<ArraySequence<T> *>();
        ArraySequence<T> *sequence;
        int len = matrix.GetSize();
        for (int i = 0; i < len; i++) {
            cols_[i] = new ArraySequence<T>();
            sequence = matrix[i];
            for (int j = 0; j < len; j++) {
                this->Set(i, j, sequence[j]);
            }
        }
    }

    template<class T>
    ArrayMatrix<T>::~ArrayMatrix() {
        delete cols_;
    }

    template<class T>
    int ArrayMatrix<T>::GetSize() const {
        return size_;
    }

    template<class T>
    T ArrayMatrix<T>::Get(int col_index, int row_index) const {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw MyError("IndexOutOfRangeError");
        }
        return (*((*(cols_))[col_index]))[row_index];
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::Map(T (*func)(T)) const {
        int len = size_;
        auto new_matrix = new ArrayMatrix<T>(len);
        new_matrix->MapThis(func);
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::TransposeNew() const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                new_matrix->Set(i, j, this->Get(j, i));
            }
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MulRowNew(int row_index, T scalar) const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(*this);
        for (int i = 0; i < len; i++) {
            new_matrix->Set(i, row_index, new_matrix->Get(i, row_index) * scalar);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MulColNew(int col_index, T scalar) const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(*this);
        for (int i = 0; i < len; i++) {
            new_matrix->Set(col_index, i, new_matrix->Get(col_index, i) * scalar);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::MinorNew(int col_index, int row_index) const {
        int len = size_;
        if (col_index < 0 || len <= col_index ||
            row_index < 0 || len <= row_index) {
            throw MyError("Wrong indeces of matrix");
        }
        auto minor = new ArrayMatrix<T>(len - 1);
        int x = 0;
        int y;
        for (int i = 0; i < len; i++) {
            if (i != col_index) {
                y = 0;
                for (int j = 0; j < len; j++) {
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
    ArrayMatrix<T> *ArrayMatrix<T>::AddToRowNew(int row_index1, int row_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*new_matrix)[i][row_index1] += this->Get(i, row_index2);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::AddToColNew(int col_index1, int col_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*new_matrix)[col_index1][i] += this->Get(col_index2, i);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::ExchangeRowsNew(int row_index1, int row_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*new_matrix)[i][row_index1] = this->Get(i, row_index2);
            (*new_matrix)[i][row_index2] = this->Get(i, row_index1);
        }
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::ExchangeColsNew(int col_index1, int col_index2) const {
        auto new_matrix = new ArrayMatrix<T>(*this);
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*new_matrix)[col_index1][i] = this->Get(col_index2, i);
            (*new_matrix)[col_index2][i] = this->Get(col_index1, i);
        }
        return new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::Set(int col_index, int row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw MyError("IndexOutOfRangeError");
        }
        (*((*(cols_))[col_index]))[row_index] = value;
    }

    template<class T>
    ArraySequence<T> &ArrayMatrix<T>::operator[](int col_index) {
        return *((*(cols_))[col_index]);
    }

    template<class T>
    void ArrayMatrix<T>::MapThis(T (*func)(T)) {
        int len = size_;
        ArraySequence<T> *col;
        for (int i = 0; i < len; i++) {
            col = (*cols_)[i]->Map(func);
            delete &cols_[i];
            (*(cols_))[i] = col;
        }
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator+(const IMatrix<T> &matrix) const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        *new_matrix += matrix;
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator-(const IMatrix<T> &matrix) const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        *new_matrix -= matrix;
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator*(const IMatrix<T> &matrix) const {
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        *new_matrix *= matrix;
        return *new_matrix;
    }

    template<class T>
    ArrayMatrix<T> &ArrayMatrix<T>::operator*(T scalar) const {
        MulWrapper<T>::setValue(scalar);
        T (*func)(T) = MulWrapper<T>::Mul;
        ArrayMatrix<T> *new_matrix = this->Map(func);
        return *new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::operator+=(const IMatrix<T> &matrix) {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                this->Set(i, j, this->Get(i, j) + matrix.Get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator-=(const IMatrix<T> &matrix) {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                this->Set(i, j, this->Get(i, j) - matrix.Get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(const IMatrix<T> &matrix) {
        int len = this->GetSize();
        auto new_cols = new ArraySequence<ArraySequence<T> *>(*(cols_));
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                new_cols[i][j] = 0;
                for (int k = 0; k < len; k++) {
                    (*(*(new_cols))[i])[j] += this->Get(i, k) * matrix.Get(k, j);
                }
            }
        }
        delete cols_;
        cols_ = new_cols;
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(T scalar) {
        MulWrapper<T>::setValue(scalar);
        this->MapThis(MulWrapper<T>::Mul);
    }

}