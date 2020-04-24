#pragma once

#include <memory>

namespace my_namespace {
    template<class T>
    class SinglyLinkedNode {
    private:
        T data_;
        std::shared_ptr<SinglyLinkedNode> next_;
    public:
        SinglyLinkedNode(T data, std::shared_ptr<SinglyLinkedNode> next): data_(data), next_(next) { }

        explicit SinglyLinkedNode(T data): data_(data), next_(nullptr) { }

        SinglyLinkedNode(): data_(), next_(nullptr) { }

        void setNext(std::shared_ptr<SinglyLinkedNode> next) { next_ = next; }

        void clearNext() { next_.reset(); }

        void setData(T data) { data_ = data; }

        std::shared_ptr<SinglyLinkedNode> getNext() const { return next_; }

        T getData() const { return data_; }

        T &getDataRef() { return data_; }
    };
}