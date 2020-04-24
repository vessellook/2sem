#include <iostream>
#include <string>
#include <memory>

#include "ui/fsm.h"
#include "sequence/linked_list_sequence.h"

using namespace std;
using my_namespace::LinkedListSequence;

string identity(char chr) { return string(1, chr); }

string empty(char) { return ""; }

bool is_space(char chr) { return chr == ' '; }

bool is_digit(char chr) { return '0' <= chr && chr <= '9'; }

bool is_letter(char chr) { return ('a' <= chr && chr <= 'z') || ('A' <= chr && chr <= 'Z'); }

bool is_letter_or_digit(char chr) { return ('a' <= chr && chr <= 'z') || ('A' <= chr && chr <= 'Z') || ('0' <= chr && chr <= '9'); }

bool is_plus(char chr) { return chr == '+'; }

bool is_minus(char chr) { return chr == '-'; }

bool is_asterisk(char chr) { return chr == '*'; }

bool is_slash(char chr) { return chr == '/'; }

void initDefaultMatrix(FSM &machine) {
    machine.setEdge(0, 0, is_space, empty);
    machine.setEdge(0, 1, is_digit, identity);
    machine.setEdge(1, 1, is_digit, identity);
    machine.setEdge(0, 2, is_letter, identity);
    machine.setEdge(2, 2, is_letter_or_digit, identity);
    machine.setEdge(0, 3, is_plus, identity);
    machine.setEdge(0, 4, is_minus, identity);
    machine.setEdge(0, 5, is_asterisk, identity);
    machine.setEdge(0, 6, is_slash, identity);
}

string get_line() {
    string result;
    getline(cin, result);
    result += '\n';
    return result;
}

shared_ptr<LinkedListSequence<string>> get_word_list(const string& line) {
    auto buffer = make_shared<string>();
    auto machine = FSM(buffer);
    initDefaultMatrix(machine);
    auto word_list = make_shared<LinkedListSequence<string>>();
    for(char chr : line) {
        cout << chr << "|";
        machine.input(chr);
        if (machine.isHalt()) {
            word_list->prepend(*buffer);
            machine.restart();
            if(chr == '\n') break;
            machine.input(chr);
            if (machine.isHalt()) {
                // введён недопустимый символ
                cout << "error!" << endl;
                throw exception();
            }
        }
    }
    return word_list;
}


int main() {
    string line = get_line();
    shared_ptr<LinkedListSequence<string>> word_list = get_word_list(line);
    for (unsigned i = 0; i < word_list->getLength(); ++i) {
        cout << word_list->get(i);
    }

    for (unsigned i = 0; i < word_list->getLength(); ++i) {
        cout << word_list->get(i) << " *** ";
    }
    return 0;
}