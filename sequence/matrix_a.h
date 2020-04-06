#pragma once

#include "matrix.h"
#include "array_sequence.h"
#include "my_exceptions.h"
# include "common.h"

template <class T>
class MatrixA: public Matrix<T> {
public:
    explicit MatrixA(int size);
    explicit MatrixA(const Matrix<T>& matrix);
    ~MatrixA() override;

    int GetSize() const;
    T Get(int col_index, int row_index) const override;
    MatrixA<T>* Map(T (*func)(T)) const override;
    MatrixA<T>* TransposeNew() const override;
    MatrixA<T>* MulRowNew(int row_index, T scalar) const override;
    MatrixA<T>* MulColNew(int col_index, T scalar) const override;
    MatrixA<T>* MinorNew(int col_index, int row_index) const override;
    MatrixA<T>* AddToRowNew(int row_index1, int row_index2) const override;
    MatrixA<T>* AddToColNew(int col_index1, int col_index2) const override;
    MatrixA<T>* ExchangeRowsNew(int row_index1, int row_index2) const override;
    MatrixA<T>* ExchangeColsNew(int col_index1, int col_index2) const override;

    void Set(int col_index, int row_index, T value);
//    void MulRow(int index, T scalar) override;
//    void MulCol(int index, T scalar) override;
//    void ExchangeRows(int index1, int index2) override;
//    void ExchangeCols(int index1, int index2) override;
//    void Transpose() override;

    MatrixA<T>& operator*(T scalar) const override;
    MatrixA<T>& operator*(const Matrix<T>& matrix) const override;
    MatrixA<T>& operator+(const Matrix<T>& matrix) const override;
    MatrixA<T>& operator-(const Matrix<T>& matrix) const override;

    void operator*=(T scalar) override;
    void operator*=(const Matrix<T>& matrix) override;
    void operator+=(const Matrix<T>& matrix) override;
    void operator-=(const Matrix<T>& matrix) override;
    ArraySequence<T> & operator[](int col_index) override;
private:
    int size = 0;
    ArraySequence<ArraySequence<T>* >* cols = nullptr;

    void MapThis(T (*func)(T));
};


template <class T>
MatrixA<T>::MatrixA(int size) {
    if(size <= 0) {
        throw MyError("IndexOutOfRangeError");
    }
    this->size = size;
    this->cols = new ArraySequence<ArraySequence<T>*>();
    ArraySequence<T>* col;
    T value;
    for(int i = 0; i < size; i++) {
        col = new ArraySequence<T>();
        for(int j = 0; j < size; j++) {
            col->Prepend(T());
        }
        this->cols->Prepend(col);
    }
}

template<class T>
MatrixA<T>::MatrixA(const Matrix<T> &matrix) {
    this->cols = new ArraySequence<ArraySequence<T>*>();
    ArraySequence<T>* sequence;
    int len = matrix.GetSize();
    for(int i = 0; i < len; i++) {
        this->cols[i] = new ArraySequence<T>();
        sequence = matrix[i];
        for(int j = 0; j < len; j++) {
            this->Set(i, j, sequence[j]);
        }
    }
}

template <class T>
MatrixA<T>::~MatrixA() {
    delete this->cols;
}

template<class T>
int MatrixA<T>::GetSize() const {
    return this->size;
}

template <class T>
T MatrixA<T>::Get(int col_index, int row_index) const {
    if (col_index < 0 || this->size <= col_index ||
        row_index < 0 || this->size <= row_index) {
        throw MyError("IndexOutOfRangeError");
    }
    return (*((*(this->cols))[col_index]))[row_index];
}

template<class T>
MatrixA<T> *MatrixA<T>::Map(T (*func)(T)) const {
    int len = this->size;
    auto new_matrix = new MatrixA<T>(len);
    new_matrix->MapThis(func);
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::TransposeNew() const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(len);
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            new_matrix->Set(i, j, this->Get(j, i));
        }
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::MulRowNew(int row_index, T scalar) const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(*this);
    for(int i = 0; i < len; i++) {
        new_matrix->Set(i, row_index, new_matrix->Get(i, row_index) * scalar);
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::MulColNew(int col_index, T scalar) const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(*this);
    for(int i = 0; i < len; i++) {
        new_matrix->Set(col_index, i, new_matrix->Get(col_index, i) * scalar);
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::MinorNew(int col_index, int row_index) const {
    int len = this->size;
    if(col_index < 0 || len <= col_index ||
       row_index < 0 || len <= row_index) {
        throw MyError("Wrong indeces of matrix");
    }
    auto minor = new MatrixA<T>(len-1);
    int x = 0;
    int y;
    for(int i = 0; i < len; i++) {
        if(i != col_index) {
            y = 0;
            for(int j = 0; j < len; j++) {
                if(j != row_index) {
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
MatrixA<T> *MatrixA<T>::AddToRowNew(int row_index1, int row_index2) const {
    auto new_matrix = new MatrixA<T>(*this);
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        (*new_matrix)[i][row_index1] += this->Get(i, row_index2);
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::AddToColNew(int col_index1, int col_index2) const {
    auto new_matrix = new MatrixA<T>(*this);
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        (*new_matrix)[col_index1][i] += this->Get(col_index2, i);
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::ExchangeRowsNew(int row_index1, int row_index2) const {
    auto new_matrix = new MatrixA<T>(*this);
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        (*new_matrix)[i][row_index1] = this->Get(i, row_index2);
        (*new_matrix)[i][row_index2] = this->Get(i, row_index1);
    }
    return new_matrix;
}

template<class T>
MatrixA<T> *MatrixA<T>::ExchangeColsNew(int col_index1, int col_index2) const {
    auto new_matrix = new MatrixA<T>(*this);
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        (*new_matrix)[col_index1][i] = this->Get(col_index2, i);
        (*new_matrix)[col_index2][i] = this->Get(col_index1, i);
    }
    return new_matrix;
}

template <class T>
void MatrixA<T>::Set(int col_index, int row_index, T value) {
    if (col_index < 0 || this->size <= col_index ||
        row_index < 0 || this->size <= row_index) {
        throw MyError("IndexOutOfRangeError");
    }
    (*((*(this->cols))[col_index]))[row_index] = value;
}

template<class T>
ArraySequence<T> & MatrixA<T>::operator[](int col_index) {
    return *((*(this->cols))[col_index]);
}

template<class T>
void MatrixA<T>::MapThis(T (*func)(T)) {
    int len = this->size;
    ArraySequence<T>* col;
    for(int i = 0; i < len; i++) {
        col = (*this->cols)[i]->Map(func);
        delete &this->cols[i];
        (*(this->cols))[i] = col;
    }
}

template<class T>
MatrixA<T> &MatrixA<T>::operator+(const Matrix<T> &matrix) const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(len);
    *new_matrix += matrix;
    return *new_matrix;
}

template<class T>
MatrixA<T> &MatrixA<T>::operator-(const Matrix<T> &matrix) const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(len);
    *new_matrix -= matrix;
    return *new_matrix;
}

template<class T>
MatrixA<T> &MatrixA<T>::operator*(const Matrix<T> &matrix) const {
    int len = this->GetSize();
    auto new_matrix = new MatrixA<T>(len);
    *new_matrix *= matrix;
    return *new_matrix;
}

template<class T>
MatrixA<T> &MatrixA<T>::operator*(T scalar) const {
    MulWrapper<T>::setValue(scalar);
    T(*func)(T) = MulWrapper<T>::Mul;
    MatrixA<T>* new_matrix = this->Map(func);
    return *new_matrix;
}

template<class T>
void MatrixA<T>::operator+=(const Matrix<T> &matrix) {
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            this->Set(i, j, this->Get(i, j) + matrix.Get(i, j));
        }
    }
}

template<class T>
void MatrixA<T>::operator-=(const Matrix<T> &matrix) {
    int len = this->GetSize();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            this->Set(i, j, this->Get(i, j) - matrix.Get(i, j));
        }
    }
}

template<class T>
void MatrixA<T>::operator*=(const Matrix<T> &matrix) {
    int len = this->GetSize();
    auto new_cols = new ArraySequence<ArraySequence<T>*>(*(this->cols));
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            new_cols[i][j] = 0;
            for(int k = 0; k < len; k++) {
                (*(*(new_cols))[i])[j] += this->Get(i, k) * matrix.Get(k, j);
            }
        }
    }
    delete this->cols;
    this->cols = new_cols;
}

template<class T>
void MatrixA<T>::operator*=(T scalar) {
    MulWrapper<T>::setValue(scalar);
    this->MapThis(MulWrapper<T>::Mul);
}


//

//
//template<class T>
//void MatrixA<T>::Add(Matrix<T> matrix) {
//    if(this->size != matrix.GetSize()) {
//        throw MyError("MatrixSizeError");
//    }
//    for(int col_index = 0; col_index < this->height; col_index++) {
//        for(int row_index = 0; row_index < this->width; row_index++) {
//            this->items[col_index][row_index];
//        }
//    }
//}
//

