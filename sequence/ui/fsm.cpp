#include <memory>
#include <string>
#include <utility>

#include "fsm.h"

using namespace std;

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

int default_number_of_edges = 9;

FSM::FSM(string* buffer) : matrix_(default_number_of_edges),
                                      word_(""),
                                      is_halt_(false),
                                      state_(States::Start), buffer_(buffer) {
    initDefaultMatrix();
}

bool FSM::input(char chr) {
    for(int i = 0; i < matrix_.getSize(); i++) {
        Edge edge = matrix_[i];
        if(edge.from == state_) {
            if(edge.check(chr)) {
                word_ += edge.convert(chr);
                state_ = edge.to;
                return true;
            }
        }
    }
    halt();
    return false;
}

bool FSM::isHalt() const { return is_halt_; }

string FSM::output() const { return word_; }

void FSM::halt() {
    *buffer_ = word_;
    is_halt_ = true;
}

string FSM::restart() {
    auto result = word_;
    is_halt_ = false;
    word_ = "";
    state_ = States::Start;
    return result;
}

void FSM::initDefaultMatrix() {
    matrix_.set(0, Edge(States::Start, States::Start, is_space, empty));
    matrix_.set(1, Edge(States::Start, States::Number, is_digit, identity));
    matrix_.set(2, Edge(States::Number, States::Number, is_digit, identity));
    matrix_.set(3, Edge(States::Start, States::Word, is_letter, identity));
    matrix_.set(4, Edge(States::Word, States::Word, is_letter_or_digit, identity));
    matrix_.set(5, Edge(States::Start, States::Plus, is_plus, identity));
    matrix_.set(6, Edge(States::Start, States::Minus, is_minus, identity));
    matrix_.set(7, Edge(States::Start, States::Asterisk, is_asterisk, identity));
    matrix_.set(8, Edge(States::Start, States::Slash, is_slash, identity));
}
