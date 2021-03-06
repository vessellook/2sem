#ifndef TIC_TAC_TOE_TREE_H
#define TIC_TAC_TOE_TREE_H

#include <utility>
#include <vector>
#include <list>

class Tree {
public:
    explicit Tree(int dim);

private:
    // comb ~ combination
    struct Comb {
        std::vector<int> comb;
        char type{};
    };

    struct CombNode {
        Comb comb;
        std::vector<CombNode *> children;

        explicit CombNode(std::vector<int> comb) {
            this->comb.comb = std::move(comb);
            /* 'W' ~ if player makes the move to this comb he can win
             * 'D' ~ if player makes the move to this comb he only can make draw
             * 'F' ~ if player makes the move to this comb he definitely fail
             */
            this->comb.type = 'W';
        }
    };

friend void print(CombNode* node);

protected:
    bool isValid(const std::vector<int> &comb);

    class Cursor {
    public:
        explicit Cursor(Tree *master);

        Cursor(Tree *master, const std::vector<int> &comb);

        void moveToChild(const std::vector<int> &comb);

        void makeBestChoice(int &row, int &col, int &sign);

        bool isGameOver();

    private:
        Tree *master;
        CombNode *current_node;
    };

private:

    CombNode *root{};
    // size of playing matrix
    int dim;

    // TODO: it can be optimized
    std::vector<std::list<CombNode *>> nodes;

    void createNodes();

    void setParents();

    void markLeaf(CombNode *node);

    bool isParentAndChild(CombNode *parent, CombNode *child);

    bool isParentAndChild(CombNode *parent, const std::vector<int> &comb);

    bool isAncestorAndChild(CombNode *ancestor, const std::vector<int> &comb);

    bool isWin(CombNode *node, int num);

    bool isWin(const std::vector<int> &comb, int num);

    static bool isLeaf(CombNode *node);
};


#endif //TIC_TAC_TOE_TREE_H
