
#include "game.h"

using namespace std;

Game::Game(int dim) : Tree(dim), cursor(this) {}

Game::Game(int dim, const vector<int> &comb) : Tree(dim),
                                               cursor(this, comb) {}

void Game::restart() {
    cursor = Tree::Cursor(this);
}

void Game::restart(const vector<int> &comb) {
    cursor = Tree::Cursor(this, comb);
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
