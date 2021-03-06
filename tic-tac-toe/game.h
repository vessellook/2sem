#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "tree.h"

class Game : private Tree {
public:
    explicit Game(int dim);

    Game(int dim, const std::vector<int>& comb);

    void restart();

    void restart(const std::vector<int>& comb);

    void changeCombination(const std::vector<int> &comb);

    void makeBestChoice(int &row, int &col, int &sign);

    bool isOver();

    using Tree::isValid;

private:
    Tree::Cursor cursor;

};


#endif //TIC_TAC_TOE_GAME_H
