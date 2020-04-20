#pragma once

namespace my_namespace {

    template<class T>
    class MulWrapper {
    private:
        static T hidden_value_;
    public:
        static void setValue(T value) {
            hidden_value_ = value;
        }

        static T Mul(T value) {
            return value * hidden_value_;
        }
    };

    template <class T>
    T MulWrapper<T>::hidden_value_;

    template <class T> T SqrSumForReduce(T value, T sum) {
        sum += value * value;
    }

}