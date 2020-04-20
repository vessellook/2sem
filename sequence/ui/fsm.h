#pragma once

#include <utility>

#include "../dynamic_array/dynamic_array.h"
#include "../matrix/array_matrix.h"

using my_namespace::DynamicArray;

class FSM {
    //этот класс я буду использовать для разбора входящих символов в строки
private:
    enum class States {Start, Number, Word, Plus, Minus, Asterisk, Slash};
private:
    struct Edge {
        States from;
        States to;
        bool(*check)(char);
        string(*convert)(char);
        Edge(States from, States to, bool(*check)(char), string(*convert)(char)) {
            this->from = from;
            this->to = to;
            this->check = check;
            this->convert = convert;
        }
    };
private:
    DynamicArray<Edge> matrix_;
    States state_;
    std::string word_;
    bool is_halt_;
    shared_ptr<string> buffer_;
private:
    void halt();
public:
    explicit FSM(string*);
    bool input(char);
    bool isHalt() const;
    std::string output() const;
    string restart();

    void initDefaultMatrix();
//    void initDefaultSequence();
};

extern int default_number_of_states;