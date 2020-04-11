#pragma once

#include "../sequence/sequence.h"
#include "../matrix/matrix.h"
using my_namespace::ISequence;
using my_namespace::IMatrix;

class TextBlock {
public:
    TextBlock(const char* text_line, index_type N): width(N), height(1);
    template <int N> TextBlock(const char text_line[N]): width(N), height(1);
    explicit TextBlock(const TextBlock& text_block): width(text_block.GetWidth()), height(text_block.GetHeight());
    TextBlock(const ISequence<char>& text_line): width(text_line.GetLength()), height(1);
    template <class T> TextBlock(const IMatrix<T>& matrix): width(matrix.GetSize()), height(matrix.GetSize());
    virtual ~TextBlock();

    index_type GetWidth() const;
    index_type GetHeight() const;

    virtual void Print();
    void Add(const TextBlock& text_block);
    void Add(const ISequence<char>& text_line);
    void Add(const char* text_line, index_type N);
    void Extend(const TextBlock& text_block);
    template <index_type N> void Add(const char text_line[N]) { Add(text_line, N); };
    template <index_type N>  void operator+=(const char text_line[N]) { Add(text_line); };
protected:
    index_type width;
    index_type height;
};