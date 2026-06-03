/**
 * @file LibGraphList.cpp
 * @brief Implementacja listy incydencji grafu nieskierowanego
 *        (lista jednokierunkowa - własna struktura Node).
 */

#include "LibGraphList.h"
#include <cstdio>

Edge f_parseEdge(const std::string& line)
{
    Edge e;
    sscanf(line.c_str(), "%d-%d", &e.v1, &e.v2);
    return e;
}

int f_findMaxVertex(Edge* edges, int k)
{
    int maxV = 0;
    for (int i = 0; i < k; i++) {
        if (edges[i].v1 > maxV) maxV = edges[i].v1;
        if (edges[i].v2 > maxV) maxV = edges[i].v2;
    }
    return maxV;
}

IncList* f_createLists(int n)
{
    // n pustych list (po jednej dla każdego wierzchołka)
    IncList* lists = new IncList[n];
    for (int i = 0; i < n; i++) {
        lists[i].head = nullptr;
        lists[i].size = 0;
    }
    return lists;
}

void f_listAppend(IncList& list, int val)
{
    // Nowy węzeł na końcu listy jednokierunkowej
    Node* node = new Node{ val, nullptr };
    if (list.head == nullptr) {
        list.head = node;
    } else {
        // Idziemy do ostatniego elementu
        Node* cur = list.head;
        while (cur->next != nullptr) cur = cur->next;
        cur->next = node;
    }
    list.size++;
}

void f_listDelete(IncList& list)
{
    // Zwalniamy każdy węzeł po kolei
    Node* cur = list.head;
    while (cur != nullptr) {
        Node* del = cur;
        cur = cur->next;
        delete del;
    }
    list.head = nullptr;
    list.size = 0;
}

void f_deleteLists(IncList* lists, int n)
{
    for (int i = 0; i < n; i++) f_listDelete(lists[i]);
    delete[] lists;
}

void f_buildIncidence(IncList* lists, Edge* edges, int k)
{
    // Krawędź {a,b} -> dodajemy b do listy a ORAZ a do listy b
    // (graf nieskierowany — krawędź "widzi" oba końce)
    for (int i = 0; i < k; i++) {
        int a = edges[i].v1;
        int b = edges[i].v2;
        f_listAppend(lists[a - 1], b);
        f_listAppend(lists[b - 1], a);
    }
}

void f_printLists(std::ofstream& out, IncList* lists, int n)
{
    for (int i = 0; i < n; i++) {
        out << "v" << (i + 1) << ": ";
        Node* cur = lists[i].head;
        if (cur == nullptr) {
            out << "(brak)";
        } else {
            while (cur != nullptr) {
                out << cur->val;
                if (cur->next != nullptr) out << " -> ";
                cur = cur->next;
            }
        }
        out << std::endl;
    }
}

void f_printDegrees(std::ofstream& out, IncList* lists, int n)
{
    for (int i = 0; i < n; i++) {
        out << "deg(v" << (i + 1) << ") = " << lists[i].size << std::endl;
    }
}
