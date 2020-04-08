#pragma once

namespace my_namespace {

    template<class T>
    class MulWrapper {
    private:
        static T hidden_value;
    public:
        static void setValue(T value) {
            hidden_value = value;
        }

        static T Mul(T value) {
            return value * hidden_value;
        }
    };

    template <class T>
    T MulWrapper<T>::hidden_value;

    template <class T> T SqrSumForReduce(T value, T sum) {
        sum += value * value;
    }

}