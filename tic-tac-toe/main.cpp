#include <iostream>
#include <vector>
#include "game.h"

using namespace std;

void print(const vector<int>& comb, int dim = 3) {
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            cout << comb[i*3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int dim = 3;
    cout << "start build tree\n";
    Game game(dim);
    cout << "finish build tree\n";
    vector<int> comb(dim*dim);
    for(int i = 0; i < dim * dim; i++) {
        comb[i] = 0;
    }
    int row, col, sign;
    bool a = true;
    while(a) {
        print(comb);
        vector<int> new_comb = comb;
        cout << ">>";
        cin >> row >> col >> sign;
        new_comb[row*dim + col] = sign;
        try {
            game.changeCombination(new_comb);
        } catch (exception e) {
            cout << "error!\n";
            continue;
        }
        print(new_comb);
        if(game.isOver()) {
            cout << "game over!\n";
        } else {
            game.makeBestChoice(row, col, sign);
            new_comb[row*dim + col] = sign;
            cout << "<<" << row << " " << col << " " << sign << endl;
        }
        comb = move(new_comb);
    }
    return 0;
}
