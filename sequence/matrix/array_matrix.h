#pragma once

#include <string>

#include "../ui/simple_ui.h"

#include "matrix.h"
#include "../sequence/array_sequence.h"
#include "../common/exceptions.h"
# include "../common/my_functions.h"

using namespace std;

namespace my_namespace {

    template<class T>
    class ArrayMatrix : public IMatrix<T> {
    private:
        ArraySequence<shared_ptr<ArraySequence<T>>> cols_;
        unsigned size_ = 0;
    public:
        explicit ArrayMatrix(unsigned size);

        explicit ArrayMatrix(const IMatrix<T>& matrix);

        unsigned getSize() const { return size_; }

        T get(unsigned col_index, unsigned row_index) const override;

        T &getRef(unsigned col_index, unsigned row_index) override { return (*this)[col_index][row_index]; }

        ArrayMatrix<T> *clone() const override;

        ArrayMatrix<T> *map(T (*func)(T)) const override;

        ArrayMatrix<T> *transposeNew() const override;

        void mapThis(T (*func)(T)) override;

        void mulRow(unsigned row_index, T scalar) override;

        void mulCol(unsigned col_index, T scalar) override;

        ArrayMatrix<T> *minorNew(unsigned col_index, unsigned row_index) const override;

        void addToRow(unsigned row_index1, unsigned row_index2, T mul) const override;

        void addToCol(unsigned col_index1, unsigned col_index2, T mul) const override;

        void exchangeRows(unsigned row_index1, unsigned row_index2) override;

        void exchangeCols(unsigned col_index1, unsigned col_index2) override;

        void set(unsigned col_index, unsigned row_index, T value);

        ArrayMatrix<T> &operator*(T scalar) const override;

        ArrayMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ArrayMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        ArraySequence<T> &operator[](unsigned col_index) const override;

        ArraySequence<T> &operator[](unsigned col_index) override;
    };


    template<class T>
    ArrayMatrix<T>::ArrayMatrix(unsigned size): size_(size), cols_() {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + to_string(size), __FILE__, __func__, __LINE__);
        }
        shared_ptr<ArraySequence<T>> col;
        T value;
        for (unsigned i = 0; i < size; ++i) {

            col = std::make_shared<ArraySequence<T>>();
            for (unsigned j = 0; j < size; ++j) {
                col->prepend(T());
            }
            cols_.prepend(col);
        }
    }

    template<class T>
    ArrayMatrix<T>::ArrayMatrix(const IMatrix<T>& matrix): size_(matrix.getSize()), cols_() {
        auto len = matrix.getSize();
        for (unsigned i = 0; i < len; ++i) {
            cols_.prepend(std::make_shared<ArraySequence<T>>());
            const ISequence<T> &sequence = matrix[i];
            for (unsigned j = 0; j < len; ++j) {
                cols_.getRef(i)->prepend(sequence[j]);
            }
        }
    }

    template<class T>
    T ArrayMatrix<T>::get(unsigned col_index, unsigned row_index) const {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        return cols_[col_index]->get(row_index);
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::map(T (*func)(T)) const {
        auto new_matrix = this->clone();
        new_matrix->mapThis(func);
        return new_matrix;
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::transposeNew() const {
        unsigned len = this->getSize();
        auto new_matrix = new ArrayMatrix<T>(len);
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
                new_matrix->set(i, j, this->get(j, i));
            }
        }
        return new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::mulRow(unsigned row_index, T scalar) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[i][row_index] *= scalar;
        }
    }

    template<class T>
    void ArrayMatrix<T>::mulCol(unsigned col_index, T scalar) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[col_index][i] *= scalar;
        }
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::minorNew(unsigned col_index, unsigned row_index) const {
        unsigned len = size_;
        if (col_index < 0 || len <= col_index ||
            row_index < 0 || len <= row_index) {
            throw MyError("Wrong indeces of matrix");
        }
        auto minor = new ArrayMatrix<T>(len - 1);
        unsigned x = 0;
        unsigned y;
        for (unsigned i = 0; i < len; ++i) {
            if (i != col_index) {
                y = 0;
                for (unsigned j = 0; j < len; ++j) {
                    if (j != row_index) {
                        (*minor)[x][y] = this->get(i, j);
                        ++y;
                    }
                }
                ++x;
            }

        }
        return minor;
    }

    template<class T>
    void ArrayMatrix<T>::addToRow(unsigned row_index1, unsigned row_index2, T mul) const {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[i][row_index1] += mul * this->get(i, row_index2);
        }
    }

    template<class T>
    void ArrayMatrix<T>::addToCol(unsigned col_index1, unsigned col_index2, T mul) const {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[col_index1][i] += mul * this->get(col_index2, i);
        }
    }

    template<class T>
    void ArrayMatrix<T>::exchangeRows(unsigned row_index1, unsigned row_index2) {
        unsigned len = this->getSize();
        T value;
        for (unsigned i = 0; i < len; ++i) {
            value = (*this)[i][row_index1];
            (*this)[i][row_index1] = (*this)[i][row_index2];
            (*this)[i][row_index2] = value;
        }
    }

    template<class T>
    void ArrayMatrix<T>::exchangeCols(unsigned col_index1, unsigned col_index2) {
        unsigned len = this->getSize();
        T value;
        for (unsigned i = 0; i < len; ++i) {
            value = (*this)[col_index1][i];
            (*this)[col_index1][i] = (*this)[col_index2][i];
            (*this)[col_index2][i] = value;
        }
    }

    template<class T>
    void ArrayMatrix<T>::set(unsigned col_index, unsigned row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        cols_[col_index]->getRef(row_index) = value;
    }

    template<class T>
    ArraySequence<T> &ArrayMatrix<T>::operator[](unsigned col_index) {
        return *(cols_[col_index]);
    }

    template<class T>
    ArraySequence<T> &ArrayMatrix<T>::operator[](unsigned col_index) const {
        return *(cols_[col_index]);
    }

    template<class T>
    void ArrayMatrix<T>::mapThis(T (*func)(T)) {
        shared_ptr<ArraySequence<T>> col;
        for (unsigned i = 0; i < size_; ++i) {
            col = shared_ptr<ArraySequence<T>>(cols_[i]->map(func));
            cols_[i] = col;
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
        unsigned len = this->getSize();
        auto new_matrix = new ArrayMatrix<T>(this->getSize());
        T value1;
        T value2;
        for (unsigned col_index = 0; col_index < len; ++col_index) {
            for (unsigned row_index = 0; row_index < len; ++row_index) {
                (*new_matrix)[col_index][row_index] = T();
                for (unsigned k = 0; k < len; k++) {
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
    ArrayMatrix<T> &ArrayMatrix<T>::operator*(T scalar) const {
        MulWrapper<T>::setValue(scalar);
        T (*func)(T) = MulWrapper<T>::Mul;
        ArrayMatrix<T> *new_matrix = map(func);
        return *new_matrix;
    }

    template<class T>
    void ArrayMatrix<T>::operator+=(const IMatrix<T> &matrix) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
                this->set(i, j, this->get(i, j) + matrix.get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator-=(const IMatrix<T> &matrix) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
                this->set(i, j, this->get(i, j) - matrix.get(i, j));
            }
        }
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(const IMatrix<T> &matrix) {
        auto new_matrix = (*this) * matrix;
        this->cols_ = new_matrix.cols_;
    }

    template<class T>
    void ArrayMatrix<T>::operator*=(T scalar) {
        MulWrapper<T>::setValue(scalar);
        this->mapThis(MulWrapper<T>::Mul);
    }

    template<class T>
    ArrayMatrix<T> *ArrayMatrix<T>::clone() const {
        auto new_matrix = new ArrayMatrix<T>(this->getSize());
        for (unsigned i = 0; i < size_; ++i) {
            for (unsigned j = 0; j < size_; ++j) {
                new_matrix->set(i, j, this->get(i, j));
            }
        }
        return new_matrix;
    }

}