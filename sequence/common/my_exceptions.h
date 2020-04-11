#pragma once

#include "../config.h"
#include <string>
#include <exception>

namespace my_namespace {

    struct MyError : public std::exception {
        std::string message_;
        std::string file_;
        std::string func_;
        int line_;

        explicit MyError(const std::string &message) {
            message_ = message;
        }

        MyError(const std::string &message,
                const std::string &file,
                const std::string &func,
                int line) {
            message_ = message;
            file_ = file;
            func_ = func;
            line_ = line;
        }

        const char *what() const noexcept override {
            return (message_ + " [ERROR in " + file_ + " in " + func_ + ", line " + std::to_string(line_) +
                    "]").c_str();
        }
    };

    struct IndexOutOfRangeError : public MyError {
        IndexOutOfRangeError(const std::string &message,
                             const std::string &file,
                             const std::string &func,
                             int line) : MyError(message, file, func, line) {};
    };

    struct MemoryAllocationError : public MyError {
        MemoryAllocationError(const std::string &message,
                              const std::string &file,
                              const std::string &func,
                              int line) : MyError(message, file, func, line) {};
    };

    struct ResizeToNegativeSizeError : public MyError {
        ResizeToNegativeSizeError(const std::string &message,
                                  const std::string &file,
                                  const std::string &func,
                                  int line) : MyError(message, file, func, line) {};
    };

    struct ZeroSizeOfMatrixError : public MyError {
        ZeroSizeOfMatrixError(const std::string &message,
                              const std::string &file,
                              const std::string &func,
                              int line) : MyError(message, file, func, line) {};
    };

}