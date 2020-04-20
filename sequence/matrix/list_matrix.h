#pragma once

#include "../ui/simple_ui.h"

#include "matrix.h"
#include "../sequence/array_sequence.h"
#include "../common/my_exceptions.h"
# include "../common/my_functions.h"

using namespace std;

namespace my_namespace {

    template<class T>
    class ListMatrix : public IMatrix<T> {
    public:
        explicit ListMatrix(int size);

        explicit ListMatrix(const IMatrix<T>& matrix);

        int getSize() const;

        T get(int col_index, int row_index) const override;

        T &getRef(int col_index, int row_index) override { return (*this)[col_index][row_index]; }

        ListMatrix<T> *clone() const override;

        ListMatrix<T> *map(T (*func)(T)) const override;

        ListMatrix<T> *transposeNew() const override;

        void mapThis(T (*func)(T)) override;

        void mulRow(int row_index, T scalar) override;

        void mulCol(int col_index, T scalar) override;

        ListMatrix<T> *minorNew(int col_index, int row_index) const override;

        void addToRow(int row_index1, int row_index2, T mul) const override;

        void addToCol(int col_index1, int col_index2, T mul) const override;

        void exchangeRows(int row_index1, int row_index2) override;

        void exchangeCols(int col_index1, int col_index2) override;

        void set(int col_index, int row_index, T value);

        ListMatrix<T> &operator*(T scalar) const override;

        ListMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ListMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ListMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        ISequence<T> &operator[](int col_index) const override;

        ISequence<T> &operator[](int col_index) override;


    private:
        int size_ = 0;
        LinkedListSequence<ISequence<T>*> cols_;
    };


    template<class T>
    ListMatrix<T>::ListMatrix(int size) {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + to_string(size), __FILE__, __func__, __LINE__);
        }
        size_ = size;
        cols_ = LinkedListSequence<ISequence<T>*>();
        LinkedListSequence<T> *col;
        T value;
        for (int i = 0; i < size; i++) {

            col = new LinkedListSequence<T>();
            for (int j = 0; j < size; j++) {
                col->prepend(T());
            }
            cols_.prepend(col);
        }
    }

    template<class T>
    ListMatrix<T>::ListMatrix(const IMatrix<T>& matrix) {
        cols_ = LinkedListSequence<ISequence<T>*>();
        int len = matrix.getSize();
        for (int i = 0; i < len; i++) {
            cols_.prepend(new LinkedListSequence<T>());
            const ISequence<T> &sequence = matrix[i];
            for (int j = 0; j < len; j++) {
                cols_.getRef(i)->prepend(sequence[j]);
            }
        }
        size_ = matrix.getSize();
    }

    template<class T>
    int ListMatrix<T>::getSize() const {
        return size_;
    }

    template<class T>
    T ListMatrix<T>::get(int col_index, int row_index) const {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        return cols_[col_index]->get(row_index);
    }

    template<class T>
    ListMatrix<T> *ListMatrix<T>::map(T (*func)(T)) const {
        auto new_matrix = this->clone();
        new_matrix->mapThis(func);
        return new_matrix;
    }

    template<class T>
    ListMatrix<T> *ListMatrix<T>::transposeNew() const {
        int len = this->getSize();
        auto new_matrix = new ListMatrix<T>(len);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                new_matrix->set(i, j, this->get(j, i));
            }
        }
        return new_matrix;
    }

    template<class T>
    void ListMatrix<T>::mulRow(int row_index, T scalar) {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            (*this)[i][row_index] *= scalar;
        }
    }

    template<class T>
    void ListMatrix<T>::mulCol(int col_index, T scalar) {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            (*this)[col_index][i] *= scalar;
        }
    }

    template<class T>
    ListMatrix<T> *ListMatrix<T>::minorNew(int col_index, int row_index) const {
        int len = size_;
        if (col_index < 0 || len <= col_index ||
            row_index < 0 || len <= row_index) {
            throw MyError("Wrong indeces of matrix");
        }
        auto minor = new ListMatrix<T>(len - 1);
        int x = 0;
        int y;
        for (int i = 0; i < len; i++) {
            if (i != col_index) {
                y = 0;
                for (int j = 0; j < len; j++) {
                    if (j != row_index) {
                        (*minor)[x][y] = this->get(i, j);
                        y++;
                    }
                }
                x++;
            }

        }
        return minor;
    }

    template<class T>
    void ListMatrix<T>::addToRow(int row_index1, int row_index2, T mul) const {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            (*this)[i][row_index1] += mul * this->get(i, row_index2);
        }
    }

    template<class T>
    void ListMatrix<T>::addToCol(int col_index1, int col_index2, T mul) const {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            (*this)[col_index1][i] += mul * this->get(col_index2, i);
        }
    }

    template<class T>
    void ListMatrix<T>::exchangeRows(int row_index1, int row_index2) {
        int len = this->getSize();
        T value;
        for (int i = 0; i < len; i++) {
            value = (*this)[i][row_index1];
            (*this)[i][row_index1] = (*this)[i][row_index2];
            (*this)[i][row_index2] = value;
        }
    }

    template<class T>
    void ListMatrix<T>::exchangeCols(int col_index1, int col_index2) {
        int len = this->getSize();
        T value;
        for (int i = 0; i < len; i++) {
            value = (*this)[col_index1][i];
            (*this)[col_index1][i] = (*this)[col_index2][i];
            (*this)[col_index2][i] = value;
        }
    }

    template<class T>
    void ListMatrix<T>::set(int col_index, int row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        cols_[col_index]->getRef(row_index) = value;
    }

    template<class T>
    ISequence<T> &ListMatrix<T>::operator[](int col_index) {
        return *(cols_[col_index]);
    }

    template<class T>
    ISequence<T> &ListMatrix<T>::operator[](int col_index) const {
        return *(cols_[col_index]);
    }

    template<class T>
    void ListMatrix<T>::mapThis(T (*func)(T)) {
        ISequence<T> *col;
        for (int i = 0; i < size_; i++) {
            col = cols_[i]->map(func);
            delete cols_[i];
            cols_[i] = col;
        }
    }

    template<class T>
    ListMatrix<T> &ListMatrix<T>::operator+(const IMatrix<T> &matrix) const {
        auto new_matrix = new ListMatrix<T>(*this);
        *new_matrix += matrix;
        return *new_matrix;
    }

    template<class T>
    ListMatrix<T> &ListMatrix<T>::operator-(const IMatrix<T> &matrix) const {
        auto new_matrix = new ListMatrix<T>(*this);
        *new_matrix -= matrix;
        return *new_matrix;
    }

    template<class T>
    ListMatrix<T> &ListMatrix<T>::operator*(const IMatrix<T> &matrix) const {
        int len = this->getSize();
        auto new_matrix = new ListMatrix<T>(this->getSize());
        T value1;
        T value2;
        for (int col_index = 0; col_index < len; col_index++) {
            for (int row_index = 0; row_index < len; row_index++) {
                (*new_matrix)[col_index][row_index] = T();
                for (int k = 0; k < len; k++) {
                    value1 = this->get(col_index, k);
                    value2 = matrix.get(k, row_index);
//                    cout << "value1 = " << value1 << "; value2 = " << value2 << "; col_index = " << col_index << "; row_index = " << row_index << "; k = " << k << endl;
                    (*new_matrix)[col_index][row_index] += value1 * value2;
                }
            }
        }
        return *new_matrix;
    }

    template<class T>
    ListMatrix<T> &ListMatrix<T>::operator*(T scalar) const {
        MulWrapper<T>::setValue(scalar);
        T (*func)(T) = MulWrapper<T>::Mul;
        ListMatrix<T> *new_matrix = map(func);
        return *new_matrix;
    }

    template<class T>
    void ListMatrix<T>::operator+=(const IMatrix<T> &matrix) {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                this->set(i, j, this->get(i, j) + matrix.get(i, j));
            }
        }
    }

    template<class T>
    void ListMatrix<T>::operator-=(const IMatrix<T> &matrix) {
        int len = this->getSize();
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                this->set(i, j, this->get(i, j) - matrix.get(i, j));
            }
        }
    }

    template<class T>
    void ListMatrix<T>::operator*=(const IMatrix<T> &matrix) {
        auto new_matrix = (*this) * matrix;
        this->cols_ = new_matrix.cols_;
    }

    template<class T>
    void ListMatrix<T>::operator*=(T scalar) {
        MulWrapper<T>::setValue(scalar);
        this->mapThis(MulWrapper<T>::Mul);
    }

    template<class T>
    ListMatrix<T> *ListMatrix<T>::clone() const {
        auto new_matrix = new ListMatrix<T>(this->getSize());
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                new_matrix->set(i, j, this->get(i, j));
            }
        }
        return new_matrix;
    }

}