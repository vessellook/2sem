#ifndef SEQUENCE_MY_EXCEPTIONS_H
#define SEQUENCE_MY_EXCEPTIONS_H

#include <exception>

struct IndexOutOfRange: public std::exception {
    const char * what () const noexcept override {
        return "IndexOutOfRange";
    }
};

struct MemoryAllocationError: public std::exception {
    const char * what () const noexcept override {
        return "MemoryAllocationError";
    }
};

#endif //SEQUENCE_MY_EXCEPTIONS_H
