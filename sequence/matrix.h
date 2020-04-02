#pragma once

#ifndef SEQUENCE_MATRIX_H
#define SEQUENCE_MATRIX_H

template <class T>
class Matrix {
public:
    virtual Matrix<T>* Add(Matrix<T> matrix) = 0;
    virtual Matrix<T>* Multiply(T scalar) = 0;
    virtual Matrix<T>* MultiplyRow(int index, T scalar) = 0;
    virtual Matrix<T>* MultiplyCol(int index, T scalar) = 0;
    virtual Matrix<T>* ExchangeRows(int index1, int index2) = 0;
    virtual Matrix<T>* ExchangeCols(int index1, int index2) = 0;
    virtual Matrix<T>* Transpose() = 0;
    virtual Matrix<T>* operator+=(Matrix<T> matrix) = 0;
};

#endif //SEQUENCE_MATRIX_H
