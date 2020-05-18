
#include "game.h"

using namespace std;

Game::Game(int dim) : Tree(dim), cursor(this) {}

Game::Game(int dim, const vector<int> &v) : Tree(dim),
                                                 cursor(this, v) {}

void Game::restart() {
    cursor = Tree::Cursor(this);
}

void Game::restart(const vector<int> &v) {
    cursor = Tree::Cursor(this, v);
}

void Game::changeCombination(const vector<int> &comb) {
    if(isValid(comb)) {
        cursor.moveToChild(comb);
    } else {
        throw exception();
    }
}

void Game::makeBestChoice(int &row, int &col, int &sign) {
    cursor.makeBestChoice(row, col, sign);
}

bool Game::isOver() {
    return cursor.isGameOver();
}
