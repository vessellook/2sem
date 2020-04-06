#pragma once

#include <string>
#include <exception>

struct MyError: public std::exception {
    std::string message;
    explicit MyError(const std::string & message) {
        this->message = message;
    }
    MyError(const std::string & message,
            const std::string & file,
            const std::string & func,
            int line) {
        this->message = message + " [ERROR in " + file + " in " + func + ", line " + std::to_string(line) + "]";
    }
    const char * what () const noexcept override {
        return this->message.c_str();
    }
};

struct IndexOutOfRangeError: public MyError {
    IndexOutOfRangeError(const std::string & message,
            const std::string & file,
            const std::string & func,
            int line) : MyError(message, file, func, line) {};
};

struct MemoryAllocationError: public MyError {
    MemoryAllocationError(const std::string & message,
                          const std::string & file,
                          const std::string & func,
                          int line) : MyError(message, file, func, line) {};
};

struct ResizeToNegativeSizeError: public MyError {
    ResizeToNegativeSizeError(const std::string & message,
                          const std::string & file,
                          const std::string & func,
                          int line) : MyError(message, file, func, line) {};
};