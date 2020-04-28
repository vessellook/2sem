#pragma once

#include <memory>

#include "singly_linked_node.h"
#include "../common/exceptions.h"

namespace my_namespace {

    template<class T>
    class SinglyLinkedListBase {
        // простой список, базовые функции
        // использует shared_ptr и SinglyLinkedNode
        // IndexOutOfRangeError для ошибок
    protected:
        unsigned length_;
        // sentinel_ будет указывать на голову
        // я читал, что это классно, модно, молодёжно, поэтому его включил в реализацию
        std::shared_ptr<SinglyLinkedNode<T>> sentinel_;
        // указатель на хвост нужен для быстрого добавления данных в конец списка
        // при пустом списке равен sentinel_
        std::shared_ptr<SinglyLinkedNode<T>> tail_;
    protected:
        // сюда спрятал цикл, который делает count переходов от узла node
        // небезопасная функция, использовать только если уверен, что (node != tail_)
        std::shared_ptr<SinglyLinkedNode<T>>
        moveForward(std::shared_ptr<SinglyLinkedNode<T>> node, unsigned count = 1) const;

        // функция убирает следующий элемент
        // небезопасная функция, использовать только если уверен, что
        // node != tail_ и node->getNext() != tail_ (потому что тогда tail_ будет указывать непонятно куда)
        void skipNext(std::shared_ptr<SinglyLinkedNode<T>> node) {
            node->setNext(node->getNext()->getNext());
            length_--;
        }

        // используй эту функцию для удаления конца
        // либо удаляй вручную и устанавливай новое значение tail_
        void removeTail() {
            tail_ = moveForward(sentinel_, length_);
            tail_->clearNext();
            length_--;
        }

    public:
        SinglyLinkedListBase();

        SinglyLinkedListBase(const T *, unsigned);

        explicit SinglyLinkedListBase(const SinglyLinkedListBase<T> &);

        unsigned getLength() const { return length_; };

        // получить элемент по индексу
        // получение последнего элемента оптимизировано
        // если запрошен элемент, которого не существует, бросается исключение IndexOutOfRangeError
        T get(unsigned) const;

        // получить ссылку на элемент по индексу
        // получение последнего элемента оптимизировано
        // если запрошен элемент, которого не существует, бросается исключение IndexOutOfRangeError
        T &getRef(unsigned);

        // добавление элемента в конец, оптимизировано. Добавление в начало можно выполнить
        // через insertAt(0, item)
        SinglyLinkedListBase<T> *prepend(T);


        SinglyLinkedListBase<T> *insertAt(T, unsigned);

        SinglyLinkedListBase<T> *append(T item) { insertAt(item, 0); return this; }

        // поменять значение элемента в списке по индексу
        // изменение последнего элемента оптимизировано
        // если запрошен элемент, которого не существует, бросается исключение IndexOutOfRangeError
        SinglyLinkedListBase<T> *set(unsigned, T);

        // удаление элемента по индексу
        // если запрошен элемент, которого не существует, бросается исключение IndexOutOfRangeError
        SinglyLinkedListBase<T> *remove(unsigned);

        std::shared_ptr<SinglyLinkedNode<T>> getHandle();
    };

    template<class T>
    SinglyLinkedListBase<T>::SinglyLinkedListBase() : sentinel_(new SinglyLinkedNode<T>()), length_(0) {
        tail_ = sentinel_;
    }

    template<class T>
    SinglyLinkedListBase<T>::SinglyLinkedListBase(const T *items, unsigned count): sentinel_(
            new SinglyLinkedNode<T>()), length_(0) {
        tail_ = sentinel_;
        for (unsigned index = 0; index < count; index++) {
            prepend(items[index]);
        }
    }

    template<class T>
    SinglyLinkedListBase<T>::SinglyLinkedListBase(SinglyLinkedListBase<T> const &other): sentinel_(
            new SinglyLinkedNode<T>()), length_(0) {
        tail_ = sentinel_;
        auto node = other.sentinel_;
        for (unsigned index = 0; index < other.length_; index++) {
            node = node->getNext();
            prepend(node->getData());
        }
    }

    template<class T>
    T SinglyLinkedListBase<T>::get(unsigned index) const {
        if (length_ <= index) {
            throw IndexOutOfRangeError("length <= index", __FILE__, __func__, __LINE__);
        }
        if(index == length_ - 1) {
            return tail_->getData();
        }
        return moveForward(sentinel_, index + 1)->getData();
    }

    template<class T>
    SinglyLinkedListBase<T> *SinglyLinkedListBase<T>::prepend(T item) {
        tail_->setNext(std::make_shared<SinglyLinkedNode<T>>(item));
        tail_ = tail_->getNext();
        length_++;
        return this;
    }

    template<class T>
    SinglyLinkedListBase<T> *SinglyLinkedListBase<T>::insertAt(T item, unsigned index) {
        if (length_ < index) {
            throw IndexOutOfRangeError("length_ < index", __FILE__, __func__, __LINE__);
        }
        if (index < length_) {
            auto node = moveForward(sentinel_, index);
            node->setNext(std::make_shared<SinglyLinkedNode<T>>(item, node->getNext()));
            length_++;
        } else {
            prepend(item);
        }
        return this;
    }

    template<class T>
    SinglyLinkedListBase<T> *SinglyLinkedListBase<T>::set(unsigned index, T item) {
        if (length_ <= index) {
            throw IndexOutOfRangeError("length <= index", __FILE__, __func__, __LINE__);
        }
        moveForward(sentinel_, index + 1)->setData(item);
        return this;
    }

    template<class T>
    SinglyLinkedListBase<T> *SinglyLinkedListBase<T>::remove(unsigned index) {
        if (length_ <= index) {
            throw IndexOutOfRangeError("length <= index", __FILE__, __func__, __LINE__);
        }
        if(length_ == index - 1) {
            tail_ = moveForward(sentinel_, index);
            tail_->clearNext();
        } else {
            skipNext(moveForward(sentinel_, index));
        }
        return this;
    }

    template<class T>
    typename std::shared_ptr<SinglyLinkedNode<T>>
    SinglyLinkedListBase<T>::moveForward(std::shared_ptr<SinglyLinkedNode<T>> node, unsigned count) const {
        // небезопасная функция — не проверяется, индекс превышает длину
        for (unsigned i = 0; i < count; i++) {
            node = node->getNext();
        }
        return node;
    }

    template<class T>
    T &SinglyLinkedListBase<T>::getRef(unsigned index) {
        if (length_ <= index) {
            throw IndexOutOfRangeError("length <= index", __FILE__, __func__, __LINE__);
        }
        if(index == length_ - 1) {
            return tail_->getDataRef();
        }
        return moveForward(sentinel_, index + 1)->getDataRef();
    }

    template <class T>
    std::shared_ptr<SinglyLinkedNode<T>> SinglyLinkedListBase<T>::getHandle() {
        return sentinel_->getNext();
    }

}