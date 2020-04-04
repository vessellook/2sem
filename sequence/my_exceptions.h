#pragma once

#include <string>
#include <exception>

struct MyError: public std::exception {
    static const std::string default_message;
    std::string message;
    explicit MyError(const std::string message = MyError::default_message) {
        this->message = message;
    }
    const char * what () const noexcept override {
        return this->message.c_str();
    }
};

const std::string MyError::default_message = "Just Some Error :)";
