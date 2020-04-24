#pragma once

#include "exceptions.h"

namespace my_namespace {
    template<class T>
    class Optional {
    private:
        T value_;
        bool has_value_;
    public:
        Optional() {
            has_value_ = false;
        }

    public:
        Optional(T value) {
            value_ = value;
            has_value_ = true;
        }

        T getValue() const {
            if (has_value_) {
                return value_;
            }
            throw EmptyValueError("", __FILE__, __func__, __LINE__);
        }

        T &getRef() {
            if (has_value_) {
                return value_;
            }
            throw EmptyValueError("", __FILE__, __func__, __LINE__);
        }

        bool hasValue() const { return has_value_; }

        void setValue(T value) { value_ = value; has_value_ = true; }

        bool tryGetValue(T &value) const {
            if (has_value_) {
                value = value_;
                return true;
            }
            return false;
        }

    public:
        bool operator==(const Optional<T> &other) const {
            return !(has_value_ || other.has_value_) || (has_value_ && other.has_value_ && value_ == other.value_);
        }
    };
}