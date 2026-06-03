// Mróz Bartłomiej

/**
 * @file LibHuffman.cpp
 * @brief Implementacja algorytmu Huffmana z użyciem std::priority_queue.
 */

#include "LibHuffman.h"
#include "HuffmanException.h"
#include <queue>
#include <vector>

// Komparator dla kolejki priorytetowej — MNIEJSZA waga = wyższy priorytet
// (std::priority_queue domyślnie to max-heap, więc musimy odwrócić porównanie)
struct CompareNode {
    bool operator()(const HuffNode* a, const HuffNode* b) const
    {
        return a->weight > b->weight;
    }
};

HuffNode* f_buildTree(const char* symbols, const double* weights, int n)
{
    if (n <= 0) throw HuffmanException("Liczba symboli musi byc dodatnia");

    // Kolejka priorytetowa (min-heap) węzłów wg wagi
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareNode> pq;

    // Krok 1: dla każdego symbolu utwórz liść i włóż do kolejki
    for (int i = 0; i < n; i++) {
        if (weights[i] < 0)
            throw HuffmanException("Waga nie moze byc ujemna");

        HuffNode* leaf = new HuffNode;
        leaf->symbol = symbols[i];
        leaf->weight = weights[i];
        leaf->left = nullptr;
        leaf->right = nullptr;
        leaf->isLeaf = true;
        pq.push(leaf);
    }

    // Przypadek szczególny — tylko jeden symbol
    if (pq.size() == 1) {
        // Jeden liść = jedyny węzeł, sam jest korzeniem
        return pq.top();
    }

    // Krok 2: dopóki więcej niż jedno drzewo
    while (pq.size() > 1) {
        // Weź dwa o najmniejszych wagach (t1 mniejsze lub równe t2)
        HuffNode* t1 = pq.top(); pq.pop();
        HuffNode* t2 = pq.top(); pq.pop();

        // Utwórz nowy węzeł wewnętrzny z dziećmi t1 i t2
        HuffNode* parent = new HuffNode;
        parent->symbol = '\0';                  // nie jest liściem
        parent->weight = t1->weight + t2->weight;
        parent->left = t1;                      // mniejszy w lewo (skojarzymy 0)
        parent->right = t2;                     // większy w prawo (skojarzymy 1)
        parent->isLeaf = false;

        pq.push(parent);
    }

    // Pozostał jeden korzeń
    return pq.top();
}

void f_generateCodes(HuffNode* node, const std::string& prefix,
                     HuffCode* out, int& count)
{
    if (node == nullptr) return;

    // Liść — zapisujemy kod dla symbolu
    if (node->isLeaf) {
        out[count].symbol = node->symbol;
        out[count].weight = node->weight;
        // Przypadek szczególny: drzewo z jednym liściem — kod = "0"
        out[count].code = prefix.empty() ? "0" : prefix;
        count++;
        return;
    }

    // Lewa krawędź => dodaj "0"
    f_generateCodes(node->left, prefix + "0", out, count);
    // Prawa krawędź => dodaj "1"
    f_generateCodes(node->right, prefix + "1", out, count);
}

void f_deleteTree(HuffNode* node)
{
    if (node == nullptr) return;
    f_deleteTree(node->left);
    f_deleteTree(node->right);
    delete node;
}

void f_printTree(std::ofstream& out, HuffNode* node, int depth)
{
    if (node == nullptr) return;

    // Najpierw prawe poddrzewo (góra w wizualizacji)
    f_printTree(out, node->right, depth + 1);

    // Wcięcie zależne od głębokości
    for (int i = 0; i < depth; i++) out << "    ";

    if (node->isLeaf) {
        out << "[" << node->symbol << ":" << node->weight << "]" << std::endl;
    } else {
        out << "(" << node->weight << ")" << std::endl;
    }

    // Lewe poddrzewo
    f_printTree(out, node->left, depth + 1);
}
