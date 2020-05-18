#include <iostream>
#include <vector>
#include "game.h"

auto PROMPT = ">> ";
auto AUTO_PROMPT = "<< ";
auto WARNING = "game: ";

using namespace std;

void print(const vector<int> &comb, int dim = 3) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << comb[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

enum status_e {
    Error,
    GameOver,
    UsualStep
};

status_e user_step(Game &game, vector<int> &comb, int dim) {
    int row, col, sign;
    vector<int> new_comb = comb;

    cout << PROMPT;
    cin >> row >> col >> sign;
    new_comb[row * dim + col] = sign;
    try {
        game.changeCombination(new_comb);
    } catch (exception e) {
        cout << WARNING << "error!" << endl;
        return Error;
    }

    if (game.isOver()) {
        cout << WARNING << "game over!" << endl;
        comb = move(new_comb);
        return GameOver;
    }
    comb = move(new_comb);
    return UsualStep;
}

status_e pc_step(Game &game, vector<int> &comb, int dim) {
    int row, col, sign;

    game.makeBestChoice(row, col, sign);
    comb[row * dim + col] = sign;
    cout << AUTO_PROMPT << row << " " << col << " " << sign << endl;

    if (game.isOver()) {
        cout << WARNING << "game over!" << endl;
        return GameOver;
    }
    return UsualStep;
}

// fpu means First Player is User
bool step(Game &game, vector<int> &comb, int dim, bool pve, bool &fpu) {
    if (fpu) {
        print(comb);

        switch(user_step(game, comb, dim)) {
            case Error:
                return false;
            case GameOver:
                return true;
            case UsualStep:
                break;
        }

        print(comb);

            return pve && pc_step(game, comb, dim) == GameOver;

    } else {
        print(comb);

        if (pc_step(game, comb, dim) == GameOver) return true;

        print(comb);

        switch(user_step(game, comb, dim)) {
            case GameOver:
                return true;
            case Error:
                fpu = true;
                return false;
            case UsualStep:
                return false;
        }
    }


}

void play(Game &game, vector<int> &comb, int dim, bool pve, bool fpu) {
    while (!step(game, comb, dim, pve, fpu)) {}
    print(comb);
}

int main() {

    int dim = 3;
    cout << WARNING << "start building tree" << endl;
    Game game(dim);
    cout << WARNING << "finish building tree" << endl;
    vector<int> comb(dim * dim);
    for (int i = 0; i < dim * dim; i++) {
        comb[i] = 0;
    }
    cout << "Would you like to play with me?[y/n]" << endl;
    char c;
    cout << PROMPT;
    cin >> c;
    if (c == 'y' || c == 'Y') {
        cout << "Would you like to be the first player?[y/n]" << endl;
        cout << PROMPT;
        cin >> c;
        cout << WARNING << "start pve play" << endl;
        if(c == 'y' || c == 'Y') {
            play(game, comb, dim, true, true);
        } else {
            play(game, comb, dim, true, false);
        }
    } else {
        cout << WARNING << "start pvp play" << endl;
        play(game, comb, dim, false, true);
    }
    return 0;
}
