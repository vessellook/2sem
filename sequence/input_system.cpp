#include <iostream>
#include <string>
#include <memory>

#include "ui/fsm.h"
#include "sequence/linked_list_sequence.h"

using namespace std;
using my_namespace::LinkedListSequence;

int main() {
    char chr = 0;
    string buffer;
    auto machine = FSM(&buffer);
    auto word_list = make_shared<LinkedListSequence<string>>();
    while (chr != '\n') {
        cin.get(chr);
        cout << chr << "|";
        machine.input(chr);
        if (machine.isHalt()) {
            word_list->prepend(buffer);
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

    for (int i = 0; i < word_list->getLength(); i++) {
        cout << word_list->getRef(i);
    }
    return 0;
}