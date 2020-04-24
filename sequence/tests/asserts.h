#pragma once

#include <string>
#include <exception>

using std::to_string;

namespace tests {
    struct AssertError : public std::exception {
        std::string message_;

        explicit AssertError(const std::string &message) { message_ = message; }

        const char *what() const noexcept override { return message_.c_str(); }
    };

    template<class T>
    bool assert_equal(T value, T expected_value) {
        if (value == expected_value) return true;
        throw AssertError("expected " + to_string(value) + " to equal " + to_string(expected_value));
    }

    template<class T>
    bool assert_equal(T value, T expected_value, const std::string& file,  int line) {
        if (value == expected_value) return true;
        throw AssertError("expected " + to_string(value) + " to equal " + to_string(expected_value)
                          + '[' + file + ", line " + to_string(line) + ']');
    }
}

