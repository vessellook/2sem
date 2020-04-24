#pragma once

#include <string>

#include "../ui/simple_ui.h"

#include "matrix.h"
#include "../sequence/linked_list_sequence.h"
#include "../common/exceptions.h"
# include "../common/my_functions.h"

using namespace std;

namespace my_namespace {

    template<class T>
    class ListMatrix : public IMatrix<T> {
    private:
        LinkedListSequence<shared_ptr<LinkedListSequence<T>>> cols_;
        unsigned size_ = 0;
    public:
        explicit ListMatrix(unsigned size);

        explicit ListMatrix(const IMatrix<T>& matrix);

        unsigned getSize() const { return size_; }

        T get(unsigned col_index, unsigned row_index) const override;

        T &getRef(unsigned col_index, unsigned row_index) override { return (*this)[col_index][row_index]; }

        ListMatrix<T> *clone() const override;

        ListMatrix<T> *map(T (*func)(T)) const override;

        ListMatrix<T> *transposeNew() const override;

        void mapThis(T (*func)(T)) override;

        void mulRow(unsigned row_index, T scalar) override;

        void mulCol(unsigned col_index, T scalar) override;

        ListMatrix<T> *minorNew(unsigned col_index, unsigned row_index) const override;

        void addToRow(unsigned row_index1, unsigned row_index2, T mul) const override;

        void addToCol(unsigned col_index1, unsigned col_index2, T mul) const override;

        void exchangeRows(unsigned row_index1, unsigned row_index2) override;

        void exchangeCols(unsigned col_index1, unsigned col_index2) override;

        void set(unsigned col_index, unsigned row_index, T value);

        ListMatrix<T> &operator*(T scalar) const override;

        ListMatrix<T> &operator*(const IMatrix<T> &matrix) const override;

        ListMatrix<T> &operator+(const IMatrix<T> &matrix) const override;

        ListMatrix<T> &operator-(const IMatrix<T> &matrix) const override;

        void operator*=(T scalar) override;

        void operator*=(const IMatrix<T> &matrix) override;

        void operator+=(const IMatrix<T> &matrix) override;

        void operator-=(const IMatrix<T> &matrix) override;

        LinkedListSequence<T> &operator[](unsigned col_index) const override;

        LinkedListSequence<T> &operator[](unsigned col_index) override;
    };


    template<class T>
    ListMatrix<T>::ListMatrix(unsigned size): size_(size), cols_() {
        if (size <= 0) {
            throw ZeroSizeOfMatrixError("size = " + to_string(size), __FILE__, __func__, __LINE__);
        }
        shared_ptr<LinkedListSequence<T>> col;
        T value;
        for (unsigned i = 0; i < size; ++i) {

            col = std::make_shared<LinkedListSequence<T>>();
            for (unsigned j = 0; j < size; ++j) {
                col->prepend(T());
            }
            cols_.prepend(col);
        }
    }

    template<class T>
    ListMatrix<T>::ListMatrix(const IMatrix<T>& matrix): size_(matrix.getSize()), cols_() {
        auto len = matrix.getSize();
        for (unsigned i = 0; i < len; ++i) {
            cols_.prepend(std::make_shared<LinkedListSequence<T>>());
            const ISequence<T> &sequence = matrix[i];
            for (unsigned j = 0; j < len; ++j) {
                cols_.getRef(i)->prepend(sequence[j]);
            }
        }
    }

    template<class T>
    T ListMatrix<T>::get(unsigned col_index, unsigned row_index) const {
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
        unsigned len = this->getSize();
        auto new_matrix = new ListMatrix<T>(len);
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
                new_matrix->set(i, j, this->get(j, i));
            }
        }
        return new_matrix;
    }

    template<class T>
    void ListMatrix<T>::mulRow(unsigned row_index, T scalar) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[i][row_index] *= scalar;
        }
    }

    template<class T>
    void ListMatrix<T>::mulCol(unsigned col_index, T scalar) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[col_index][i] *= scalar;
        }
    }

    template<class T>
    ListMatrix<T> *ListMatrix<T>::minorNew(unsigned col_index, unsigned row_index) const {
        unsigned len = size_;
        if (col_index < 0 || len <= col_index ||
            row_index < 0 || len <= row_index) {
            throw MyError("Wrong indeces of matrix");
        }
        auto minor = new ListMatrix<T>(len - 1);
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
    void ListMatrix<T>::addToRow(unsigned row_index1, unsigned row_index2, T mul) const {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[i][row_index1] += mul * this->get(i, row_index2);
        }
    }

    template<class T>
    void ListMatrix<T>::addToCol(unsigned col_index1, unsigned col_index2, T mul) const {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            (*this)[col_index1][i] += mul * this->get(col_index2, i);
        }
    }

    template<class T>
    void ListMatrix<T>::exchangeRows(unsigned row_index1, unsigned row_index2) {
        unsigned len = this->getSize();
        T value;
        for (unsigned i = 0; i < len; ++i) {
            value = (*this)[i][row_index1];
            (*this)[i][row_index1] = (*this)[i][row_index2];
            (*this)[i][row_index2] = value;
        }
    }

    template<class T>
    void ListMatrix<T>::exchangeCols(unsigned col_index1, unsigned col_index2) {
        unsigned len = this->getSize();
        T value;
        for (unsigned i = 0; i < len; ++i) {
            value = (*this)[col_index1][i];
            (*this)[col_index1][i] = (*this)[col_index2][i];
            (*this)[col_index2][i] = value;
        }
    }

    template<class T>
    void ListMatrix<T>::set(unsigned col_index, unsigned row_index, T value) {
        if (col_index < 0 || size_ <= col_index ||
            row_index < 0 || size_ <= row_index) {
            throw IndexOutOfRangeError("IndexOutOfRangeError", __FILE__, __func__, __LINE__);
        }
        cols_[col_index]->getRef(row_index) = value;
    }

    template<class T>
    LinkedListSequence<T> &ListMatrix<T>::operator[](unsigned col_index) {
        return *(cols_[col_index]);
    }

    template<class T>
    LinkedListSequence<T> &ListMatrix<T>::operator[](unsigned col_index) const {
        return *(cols_[col_index]);
    }

    template<class T>
    void ListMatrix<T>::mapThis(T (*func)(T)) {
        shared_ptr<LinkedListSequence<T>> col;
        for (unsigned i = 0; i < size_; ++i) {
            col = shared_ptr<LinkedListSequence<T>>(cols_[i]->map(func));
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
        unsigned len = this->getSize();
        auto new_matrix = new ListMatrix<T>(this->getSize());
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
    ListMatrix<T> &ListMatrix<T>::operator*(T scalar) const {
        MulWrapper<T>::setValue(scalar);
        T (*func)(T) = MulWrapper<T>::Mul;
        ListMatrix<T> *new_matrix = map(func);
        return *new_matrix;
    }

    template<class T>
    void ListMatrix<T>::operator+=(const IMatrix<T> &matrix) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
                this->set(i, j, this->get(i, j) + matrix.get(i, j));
            }
        }
    }

    template<class T>
    void ListMatrix<T>::operator-=(const IMatrix<T> &matrix) {
        unsigned len = this->getSize();
        for (unsigned i = 0; i < len; ++i) {
            for (unsigned j = 0; j < len; ++j) {
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
        for (unsigned i = 0; i < size_; ++i) {
            for (unsigned j = 0; j < size_; ++j) {
                new_matrix->set(i, j, this->get(i, j));
            }
        }
        return new_matrix;
    }

}