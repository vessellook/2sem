#pragma once

#include <iostream>

#include "../sequence/sequence.h"
#include "../sequence/array_sequence.h"
#include "../sequence/linked_list_sequence.h"
#include "../matrix/matrix.h"

using my_namespace::ISequence;
using my_namespace::ArraySequence;
using my_namespace::LinkedListSequence;
using my_namespace::IMatrix;

class TextBlock {
friend std::ostream& operator<<(std::ostream& os, const TextBlock& text_block);
public:
    TextBlock(): width_(0), height_(0), lines_(new LinkedListSequence<ISequence<char>*>) {};
    TextBlock(const char* text_line, int N) { Create(text_line, N); };
    template <int N> TextBlock(const char text_line[N]) { Create(text_line, N); };
    explicit TextBlock(const TextBlock& text_block);
    TextBlock(const ISequence<char>& text_line) { Create(text_line); };
    virtual ~TextBlock();

    int GetWidth() const { return width_; };
    int GetHeight() const { return height_; };
    char Get(int line_num, int column_num) const { return (*((*lines_)[line_num]))[column_num]; };
    TextBlock *Clone() const { return new TextBlock(*this); };

    void Create(const char* text_line, int N);
    void Create(const ISequence<char>& text_line);
    void Add(const TextBlock& text_block);
    void Add(const ISequence<char>& text_line);
    void Add(const char* text_line, int N);
    void Extend(const TextBlock& text_block);
    template <int N> void Add(const char text_line[N]) { Add(text_line, N); };
    template <int N>  void operator+=(const char text_line[N]) { Add(text_line); };
protected:
    int width_;
    int height_;
    ISequence<ISequence<char>*>* lines_ = nullptr;
};

TextBlock::TextBlock(const TextBlock &text_block): width_(text_block.GetWidth()), height_(text_block.GetHeight()) {
    lines_ = new LinkedListSequence<ISequence<char>*>();
    for(int i = 0; i < height_; i++) {
        lines_->Prepend((*(text_block.lines_))[i]->Clone());
    }
}

TextBlock::~TextBlock() {
    for(int i = 0; i < height_; i++) {
        delete (*lines_)[i];
    }
    delete lines_;
    lines_ = nullptr;
}

void TextBlock::Create(const char *text_line, int N) {
    width_ = N;
    height_ = 1;
    lines_ = new LinkedListSequence<ISequence<char>*>();
    lines_->Prepend(new ArraySequence<char>(text_line, N));
}

void TextBlock::Create(const ISequence<char> &text_line) {
    width_ = text_line.GetLength();
    height_ = 1;
    lines_ = new LinkedListSequence<ISequence<char>*>();
    lines_->Prepend(new ArraySequence<char>(text_line));
}

void TextBlock::Add(const TextBlock &text_block) {
    if (text_block.width_ > width_) {
        //TODO add some spaces to this
    } else if (text_block.width_ < width_) {
        //TODO add some spaces to text_block
    }
    //TODO add text_block ti this. Line by line
}

void TextBlock::Add(const ISequence<char> &text_line) {
    lines_->Prepend(text_line.Clone());
}

void TextBlock::Add(const char *text_line, int N) {
    lines_->Prepend(new ArraySequence<char>(text_line, N));
}

void TextBlock::Extend(const TextBlock &text_block) {
    for(int i = 0; i < height_; i++) {
        for(int j = width_; j < width_ + text_block.width_; j++) {
            (*lines_)[i]->Prepend(text_block.Get(i, j));
        }
    }
    width_ += text_block.width_;
}

std::ostream &operator<<(std::ostream &os, const TextBlock &text_block) {
    for (int i = 0; i < height_; i++) {
        for(int j = 0; j < width_; j++) {
           os << (*((*(text_block.lines_))[i]))[j];
        }
        os << std::endl;
    }
    return os;
}





