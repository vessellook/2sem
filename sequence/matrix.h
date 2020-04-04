#pragma once

template <class T>
class Matrix {
public:
    virtual int GetSize() const = 0;
    virtual T Get(int col_index, int row_index) const = 0;
    virtual Matrix<T>* Map(T (*func)(T)) const = 0;
    virtual Matrix<T>* TransposeNew() const = 0;
    virtual Matrix<T>* MulRowNew(int row_index, T scalar) const = 0;
    virtual Matrix<T>* MulColNew(int col_index, T scalar) const = 0;
    virtual Matrix<T>* MinorNew(int col_index, int row_index) const = 0;
    virtual Matrix<T>* AddToRowNew(int row_index1, int row_index2) const = 0;
    virtual Matrix<T>* AddToColNew(int col_index1, int col_index2) const = 0;
    virtual Matrix<T>* ExchangeRowsNew(int row_index1, int row_index2) const = 0;
    virtual Matrix<T>* ExchangeColsNew(int col_index1, int col_index2) const = 0;

    virtual void Set(int col_index, int row_index, T value) = 0;
//    virtual void Transpose() = 0;
//    virtual void MulRow(int index, T scalar) = 0;
//    virtual void MulCol(int index, T scalar) = 0;
//    virtual void ExchangeRows(int index1, int index2) = 0;
//    virtual void ExchangeCols(int index1, int index2) = 0;

    virtual Matrix<T>* operator*(T scalar) const = 0;
    virtual Matrix<T>* operator*(const Matrix<T>* matrix) const = 0;
    virtual Matrix<T>* operator+(const Matrix<T>* matrix) const = 0;
    virtual Matrix<T>* operator-(const Matrix<T>* matrix) const = 0;

    virtual void operator*=(T scalar) = 0;
    virtual void operator*=(const Matrix<T>* matrix) = 0;
    virtual void operator+=(const Matrix<T>* matrix) = 0;
    virtual void operator-=(const Matrix<T>* matrix) = 0;
    virtual Sequence<T> & operator[](int index) = 0;
};


