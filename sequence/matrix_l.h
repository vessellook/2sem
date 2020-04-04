#pragma once

template <class T>
class MatrixL: public Matrix<T> {
public:
    explicit MatrixL(int size);
    explicit MatrixL(const Matrix<T>& matrix);
    ~MatrixL();

    int GetSize() const;
    T Get(int col_index, int row_index) const override;
    Matrix<T>* Map(T (*func)(T)) const override;
    Matrix<T>* TransposeNew() const override;
    Matrix<T>* MulNew(T scalar) const override;
    Matrix<T>* AddNew(const Matrix<T>* matrix) const override;
    Matrix<T>* SubNew(const Matrix<T>* matrix) const override;
    Matrix<T>* MulNew(const Matrix<T>* matrix) const override;
    Matrix<T>* MulRowNew(int row_index, T scalar) const override;
    Matrix<T>* MulColNew(int col_index, T scalar) const override;
    Matrix<T>* MinorNew(int col_index, int row_index) const override;
    Matrix<T>* AddToRowNew(int row_index1, int row_index2) const override;
    Matrix<T>* AddToColNew(int col_index1, int col_index2) const override;
    Matrix<T>* ExchangeRowsNew(int row_index1, int row_index2) const override;
    Matrix<T>* ExchangeColsNew(int col_index1, int col_index2) const override;
};

template<class T>
MatrixL<T>::MatrixL(int size) {

}
