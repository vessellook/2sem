// comb_vector has size of dim*dim

#define comb_vector vector<int>
#define comb_size dim*dim


#include <iostream>
#include "tree.h"

using namespace std;

void print(Tree::CombNode *node) {
    for (int i : node->comb.comb) {
        std::cout << i << " ";
    }
}

void print(const std::vector<int> &comb) {
    for (int i : comb) {
        std::cout << i << " ";
    }
}

void Tree::createNodes() {
    int level = 0;
    auto comb = comb_vector(comb_size);
    for (int &el : comb) {
        el = 0;
    }
    auto zero_comb = comb;
    nodes[level].push_front(new CombNode(comb));

    for (;;) {

        // change comb
        for (int k = comb_size - 1; k >= 0; k--) {
            comb[k]++;
            if (comb[k] < 3) break;
            comb[k] = 0;
        }

        if (!isValid(comb)) continue;

        level = comb_size;
        // get level
        for (int &el : comb) {
            if (el == 0) level--;
        }

        nodes[level].push_front(new CombNode(comb));
        if (comb == zero_comb) break;
    }
}

bool Tree::isParentAndChild(Tree::CombNode *parent, Tree::CombNode *child) {
    return isParentAndChild(parent, child->comb.comb);
}

bool
Tree::isParentAndChild(Tree::CombNode *parent, const comb_vector &comb) {
    int k = 0;
    for (int i = 0; i < comb_size; i++) {
        if (parent->comb.comb[i] == comb[i]) continue;
        if (parent->comb.comb[i] != 0) {
            return false;
        }
        k++;
    }
    return k == 1;
}

bool Tree::isAncestorAndChild(Tree::CombNode *ancestor,
                              const comb_vector &comb) {
    for (int i = 0; i < comb_size; i++) {
        if (ancestor->comb.comb[i] == comb[i]) continue;
        if (ancestor->comb.comb[i] != 0) {
            return false;
        }
    }
    return true;
}

bool Tree::isWin(const comb_vector &comb, int num) {
    // horizontal search
    for (int i = 0; i < dim; i++) {
        int k = 0;
        for (int j = 0; j < dim; j++) {
            if (comb[i * dim + j] != num) break;
            k++;
        }
        if (k == dim) return true;
    }
    // vertical search
    for (int i = 0; i < dim; i++) {
        int k = 0;
        for (int j = 0; j < dim; j++) {
            if (comb[i + j * dim] != num) break;
            k++;
        }
        if (k == dim) return true;
    }
    // main diagonal search
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (comb[i * (dim + 1)] != num) break;
        k++;
    }
    if (k == dim) return true;
    // side diagonal search
    k = 0;
    for (int i = 0; i < dim; i++) {
        if (comb[(i + 1) * (dim - 1)] != num) break;
        k++;
    }
    return k == dim;
}

bool Tree::isWin(Tree::CombNode *node, int num) {
    return isWin(node->comb.comb, num);
}

bool Tree::isLeaf(Tree::CombNode *node) {
    return node->children.empty();
}

void Tree::markLeaf(Tree::CombNode *node) {
    // TODO: it can be optimized
    if (isWin(node, 1) || isWin(node, 2)) {
        node->comb.type = 'W';
    } else {
        node->comb.type = 'D';
    }
}

char parentType(char parent_type, char child_type) {
    char result;
    if (child_type == 'W') result = 'F';
    else if (child_type == 'F') result = parent_type;
    else if (parent_type == 'F') result = 'F';
    else result = 'D';
    return result;
}

void Tree::setParents() {
    for (int level = comb_size; level > 0; level--) {
        for (CombNode *child : nodes[level]) {
            // if child is leaf, it should be marked 'W'(Win) or 'D'(Draw)
            if (isLeaf(child)) {
                markLeaf(child);
            }
            for (CombNode *parent : nodes[level - 1]) {
                if (isParentAndChild(parent, child) &&
                    !isWin(parent, 1) &&
                    !isWin(parent, 2)) {

                    parent->children.push_back(child);
                    parent->comb.type = parentType(parent->comb.type,
                                                   child->comb.type);
                }
            }
        }
    }
}

Tree::Tree(int dim) : dim(dim), nodes(comb_size + 1) {
    createNodes();
    setParents();
    root = nodes[0].front();
    for (list<CombNode *> &el : nodes) {
        el.clear();
    }
    nodes.clear();
}

bool Tree::isValid(const comb_vector &comb) {
    int k1 = 0, k2 = 0;
    for (int i = 0; i < comb_size; i++) {
        switch (comb[i]) {
            case 1:
                k1++;
                break;
            case 2:
                k2++;
                break;
        }
    }
    if (k1 < k2 || k2 + 1 < k1) return false;
    return !(isWin(comb, 1) && isWin(comb, 2));
}

Tree::Cursor::Cursor(Tree *master) : master(master) {
    current_node = master->root;
}

Tree::Cursor::Cursor(Tree *master, const comb_vector &comb) : master(
        master) {
    current_node = master->root;
    while (current_node->comb.comb != comb) {
        if (current_node->children.empty()) throw exception();
        for (CombNode *candidate : current_node->children) {
            if (master->isAncestorAndChild(candidate, comb)) {
                current_node = candidate;
                break;
            }
        }
    }
}

void Tree::Cursor::moveToChild(const comb_vector &comb) {
    if (!master->isParentAndChild(current_node, comb)) throw exception();
    for (CombNode *child : current_node->children) {
        if (child->comb.comb == comb) {
            current_node = child;
            return;
        }
    }
    throw exception();
}

void Tree::Cursor::makeBestChoice(int &row, int &col, int &sign) {
    char type = current_node->comb.type;
    switch(type) {
        case 'W':
            type = 'F';
            break;
        case 'F':
            type = 'W';
            break;
        default:
            type = 'D';
            break;
    }
    int k;
    for(CombNode *child : current_node->children) {
        if(child->comb.type == type) {
            for(int i = 0; i < master->dim; i++) {
                for(int j = 0; j < master->dim; j++) {
                    k = i*master->dim + j;
                    if(child->comb.comb[k] - current_node->comb.comb[k] != 0) {
                        row = i;
                        col = j;
                        sign = child->comb.comb[k];
                        current_node = child;
                        return;
                    }
                }
            }
        }
    }
    throw exception();
}

bool Tree::Cursor::isGameOver() {
    return isLeaf(current_node);
}
