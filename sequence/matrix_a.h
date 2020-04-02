#pragma once

#ifndef SEQUENCE_MATRIX_A_H
#define SEQUENCE_MATRIX_A_H

#include "matrix.h"
#include "array_sequence.h"
#include "my_exceptions.h"

template <class T>
class MatrixA: public Matrix<T> {
public:
    static MatrixA<T> Addition();
    static MatrixA<T> Multiplication();
    explicit MatrixA(int size);
    int GetSize();
    void Set(int col_index, int row_index, T value);
    T Get(int col_index, int row_index);
    void Add(Matrix<T> matrix) override;
    void Mul(T scalar) override;
    void Mul()
    void MulRow(int index, T scalar) override;
    void MulCol(int index, T scalar) override;
    void ExchangeRows(int index1, int index2) override;
    void ExchangeCols(int index1, int index2) override;
    void Transpose() override;
    void operator+=(Matrix<T> matrix) override;
    ArraySequence<T> & operator[](int col_index) override;
private:
    int size = 0;
    ArraySequence<ArraySequence<T>* >* cols = nullptr;
};

template <class T>
MatrixA<T>::MatrixA(int size) {
    if(size <= 0) {
        throw MyError("IndexOutOfRangeError");
    }
    this->width = size;
    this->cols = new ArraySequence<ArraySequence<T>*>(size);
    for(int i = 0; i < size; i++) {
        this->cols[i] = new ArraySequence<T>(size);
    }
}

template <class T>
int MatrixA<T>::GetSize() {
    return this->size;
}

template <class T>
void MatrixA<T>::Set(int col_index, int row_index, T value) {
    if (col_index < 0 || this->size <= col_index ||
        row_index < 0 || this->size <= row_index) {
        throw MyError("IndexOutOfRangeError");
    }
    this->cols[col_index][row_index] = value;
}

template <class T>
T MatrixA<T>::Get(int col_index, int row_index) {
    if (col_index < 0 || this->size <= col_index ||
        row_index < 0 || this->size <= row_index) {
        throw MyError("IndexOutOfRangeError");
    }
    return this->cols[col_index][row_index];
}

template<class T>
void MatrixA<T>::Add(Matrix<T> matrix) {
    if(this->size != matrix.GetSize()) {
        throw MyError("MatrixSizeError");
    }
    for(int col_index = 0; col_index < this->height; col_index++) {
        for(int row_index = 0; row_index < this->width; row_index++) {
            this->items[col_index][row_index];
        }
    }
}

template<class T>
ArraySequence<T> & MatrixA<T>::operator[](int col_index) {
    return this->cols[col_index];
}

#endif //SEQUENCE_MATRIX_A_H
