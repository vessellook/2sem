#pragma once

#include <iostream>

#include "../dynamic_array/dynamic_array.h"
#include "../linked_list/singly_linked_list.h"
#include "../sequence/sequence.h"
#include "../matrix/matrix.h"

namespace simple_ui {

    template <class T>
    void show(const my_namespace::ISequence<T> *list, const std::string& name = "") {
        unsigned length = list->getLength();
        if(name.empty()) {
            std::cout << "list (length " << length << "): ";
        } else {
            std::cout << "list \"" << name << "\" (length " << length << "): ";
        }

        for (unsigned i = 0; i < length; ++i) {
            std::cout << list->get(i) << " ";
        }
        std::cout << std::endl << std::endl;
    }

    template <class T>
    void show(const my_namespace::IMatrix<T> *matrix, const std::string& name = "") {
        unsigned size = matrix->getSize();
        if(name.empty()) {
            std::cout << "matrix " << size << "x" << size << std::endl;
        } else {
            std::cout << "matrix \"" << name << "\" " << size << "x" << size << std::endl;
        }

        for (unsigned i = 0; i < size; ++i) {
            std::cout << "|";
            for (unsigned j = 0; j < size; ++j) {
                std::cout << " " << (*matrix)[j][i];
            }
            std::cout << "   |" << std::endl;
        }
        std::cout << std::endl;
    }
}
