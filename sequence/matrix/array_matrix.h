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
        explicit ArrayMatrix(int size);

        explicit ArrayMatrix(const IMatrix<T>& matrix);

        ~ArrayMatrix() override;

        int GetSize() const;

        T Get(int col_index, int row_index) const override;

        ArrayMatrix<T> *Clone() const override;

        ArrayMatrix<T> *Map(T (*func)(T)) const override;

        ArrayMatrix<T> *TransposeNew() const override;

        void MulRow(int row_index, T scalar) override;

        void MulCol(int col_index, T scalar) override;

        ArrayMatrix<T> *MinorNew(int col_index, int row_index) const override;

        void AddToRow(int row_index1, int row_index2, T mul) const override;

        void AddToCol(int col_index1, int col_index2, T mul) const override;

        void ExchangeRows(int row_index1, int row_index2) override;

        void ExchangeCols(int col_index1, int col_index2) override;

        void Set(int col_index, int row_index, T value);

        ArrayMatrix<T> &operator*(T scalar) const override;

        ArrayMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        ISequence<T> &operator[](int col_index) const override;

        ISequence<T> &operator[](int col_index) override;


    private:
        int size_ = 0;
        ISequence<ISequence<T>*> *cols_ = nullptr;

        void MapThis(T (*func)(T));
    };


    template<class T>
    ArrayMatrix<T>::ArrayMatrix(int size) {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + std::to_string(size), __FILE__, __func__, __LINE__);
        }
        size_ = size;
        cols_ = new ArraySequence<ISequence<T>*>();
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
    ArrayMatrix<T>::ArrayMatrix(const IMatrix<T>& matrix) {
        cols_ = new ArraySequence<ISequence<T>*>();
        int len = matrix.GetSize();
        for (int i = 0; i < len; i++) {
            cols_->Prepend(new ArraySequence<T>());
            const ISequence<T> &sequence = matrix[i];
            for (int j = 0; j < len; j++) {
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
    int ArrayMatrix<T>::GetSize() const {
        return size_;
    }

    template<class T>
    T ArrayMatrix<T>::Get(int col_index, int row_index) const {
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
    void ArrayMatrix<T>::MulRow(int row_index, T scalar) {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*this)[i][row_index] *= scalar;
        }
    }

    template<class T>
    void ArrayMatrix<T>::MulCol(int col_index, T scalar) {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*this)[col_index][i] *= scalar;
        }
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
    void ArrayMatrix<T>::AddToRow(int row_index1, int row_index2, T mul) const {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*this)[i][row_index1] += mul * this->Get(i, row_index2);
        }
    }

    template<class T>
    void ArrayMatrix<T>::AddToCol(int col_index1, int col_index2, T mul) const {
        int len = this->GetSize();
        for (int i = 0; i < len; i++) {
            (*this)[col_index1][i] += mul * this->Get(col_index2, i);
        }
    }

    template<class T>
    void ArrayMatrix<T>::ExchangeRows(int row_index1, int row_index2) {
        int len = this->GetSize();
        T value;
        for (int i = 0; i < len; i++) {
            value = (*this)[i][row_index1];
            (*this)[i][row_index1] = (*this)[i][row_index2];
            (*this)[i][row_index2] = value;
        }
    }

    template<class T>
    void ArrayMatrix<T>::ExchangeCols(int col_index1, int col_index2) {
        int len = this->GetSize();
        T value;
        for (int i = 0; i < len; i++) {
            value = (*this)[col_index1][i];
            (*this)[col_index1][i] = (*this)[col_index2][i];
            (*this)[col_index2][i] = value;
        }
    }

    template<class T>
    void ArrayMatrix<T>::Set(int col_index, int row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
         (*((*(cols_))[col_index]))[row_index] = value;
    }

    template<class T>
    ISequence<T> &ArrayMatrix<T>::operator[](int col_index) {
        return *((*(cols_))[col_index]);
    }

    template<class T>
    ISequence<T> &ArrayMatrix<T>::operator[](int col_index) const {
        return *((*(cols_))[col_index]);
    }

    template<class T>
    void ArrayMatrix<T>::MapThis(T (*func)(T)) {
        ISequence<T> *col;
        for (int i = 0; i < size_; i++) {
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
        int len = this->GetSize();
        auto new_matrix = new ArrayMatrix<T>(this->GetSize());
        T value1;
        T value2;
        for (int col_index = 0; col_index < len; col_index++) {
            for (int row_index = 0; row_index < len; row_index++) {
                (*new_matrix)[col_index][row_index] = T();
                for (int k = 0; k < len; k++) {
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
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                new_matrix->Set(i, j, this->Get(i, j));
            }
        }
        return new_matrix;
    }

}