#pragma once

template <class T>
class MulWrapper {
private:
    T value_;
public:
    MulWrapper(T value) {
        this->value_ = value;
    }
    T Mul(T value) {
        return value * this->value_;
    }
};
