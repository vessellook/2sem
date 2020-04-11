#pragma once

#include <iostream>

#include "../config.h"
#include "../dynamic_array/dynamic_array.h"
#include "../linked_list/linked_list.h"
#include "../sequence/sequence.h"
#include "../matrix/matrix.h"

namespace simple_ui {

    template <class T>
    void show(const my_namespace::ISequence<T> *list, const std::string& name = "") {
        int length = list->GetLength();
        if(name.empty()) {
            std::cout << "list (length " << length << "): ";
        } else {
            std::cout << "list \"" << name << "\" (length " << length << "): ";
        }

        for (int i = 0; i < length; i++) {
            std::cout << list->Get(i) << " ";
        }
        std::cout << std::endl << std::endl;
    }

    template <class T>
    void show(const my_namespace::IMatrix<T> *matrix, const std::string& name = "") {
        int size = matrix->GetSize();
        if(name.empty()) {
            std::cout << "matrix " << size << "x" << size << std::endl;
        } else {
            std::cout << "matrix \"" << name << "\" " << size << "x" << size << std::endl;
        }

        for (int i = 0; i < size; i++) {
            std::cout << "|";
            for (int j = 0; j < size; j++) {
                printf("%4d", (*matrix)[j][i]);
            }
            std::cout << "   |" << std::endl;
        }
        std::cout << std::endl;
    }
}
