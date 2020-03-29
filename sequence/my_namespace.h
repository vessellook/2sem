#ifndef SEQUENCE_MY_NAMESPACE_H

namespace my_namespace {
    template <class T>
    class Sequence {
    public:
        Sequence();
        Sequence(T* items, int count);
        Sequence(const Sequence<T> & list);
        virtual Sequence<T> * GetSubsequence(int startIndex, int endIndex) = 0;
        virtual Sequence <T>* Concat(Sequence <T> *list) = 0;
        virtual T GetFirst() = 0;
        virtual T GetLast() = 0;
        virtual T Get(int index) = 0;
        virtual int GetLength() = 0;
        virtual void Append(T item) = 0;
        virtual void Prepend(T item) = 0;
        virtual void InsertAt(T item, int index) = 0;
    };

    template <class T>
    class ListSequence: public Sequence {
    public:
        ListSequence() {
            items = new LinkedList<T>() ;
        }
        ListSequence(T* items, int count)) {
            items = new LinkedList<T>();
        }
        ListSequence(const Sequence<T> & list) {
            items = new LinkedList<T>();
        }
    protected:
        LinkedList<T> items;
    };

    template <class T>
    class LinkedList {
    public:
        struct Node {T data, struct Node* next};

        LinkedList() {
            head = nullptr;
        };

        LinkedList (T* items, int count) {
            
        };
    private:
        struct Node * head;
    };

    template <class T>
    class ArraySequence: public Sequence {
        DynamicArray<T> items;
//
    };

    template <class T>
    class DynamicArray {
//
    };

    template <class T>
    class SquatrixL: public ListSequence {
//
    };

    template <class T>
    class SquatrixA: public ArraySequence {
//
    };
}


#define SEQUENCE_MY_NAMESPACE_H

#endif //SEQUENCE_MY_NAMESPACE_H
