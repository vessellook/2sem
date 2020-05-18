#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "tree.h"

class Game : private Tree {
public:
    explicit Game(int dim);

    Game(int dim, const std::vector<int>& v);

    void restart();

    void restart(const std::vector<int>& v);

    void changeCombination(const std::vector<int> &comb);

    void makeBestChoice(int &row, int &col, int &sign);

    bool isOver();

private:
    Tree::Cursor cursor;

};


#endif //TIC_TAC_TOE_GAME_H
