#pragma once

#include <string>
#include <memory>
#include <utility>

#include"../sequence/array_sequence.h"

class FSM {
    //этот класс я буду использовать для разбора входящих символов в строки
public:
    static const unsigned start_state;
public:
    struct Edge {
        unsigned from;
        unsigned to;

        bool (*check)(char);

        std::string (*convert)(char);

        Edge(unsigned from, unsigned to, bool(*check)(char), std::string(*convert)(char)) {
            this->from = from;
            this->to = to;
            this->check = check;
            this->convert = convert;
        }

        Edge() : from(), to(), check(nullptr), convert(nullptr) {}
    };

private:
    my_namespace::ArraySequence<Edge> matrix_;
    std::shared_ptr<std::string> buffer_;
    std::string word_;
    unsigned state_;
    bool is_halt_;
private:
    void halt();

public:
    explicit FSM(std::shared_ptr<std::string>);

    bool input(char);

    bool isHalt() const;

    std::string output() const;

    std::string restart();

    unsigned getState();

    void setEdge(unsigned from, unsigned to, bool(*check)(char), std::string(*convert)(char));

    void setEdge(Edge edge);

};