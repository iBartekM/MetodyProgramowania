/**
 * @file LibStackList.h
 * @brief Implementacja stosu na liście jednokierunkowej.
 */

#ifndef LIBSTACKLIST_H
#define LIBSTACKLIST_H

struct Node {
    int val;
    Node* next;
};

struct StackList {
    Node* top;       // wskaźnik na szczyt stosu
    int size;        // liczba elementów
};

StackList f_listCreate();
bool f_listIsEmpty(const StackList& s);
int f_listSize(const StackList& s);
int f_listTop(const StackList& s);
void f_listPush(StackList& s, int val);
void f_listPop(StackList& s);
void f_listDelete(StackList& s);

#endif
