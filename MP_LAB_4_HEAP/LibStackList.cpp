/**
 * @file LibStackList.cpp
 * @brief Definicje funkcji stosu na liście jednokierunkowej.
 */

#include "LibStackList.h"

StackList f_listCreate()
{
    return { nullptr, 0 };
}

bool f_listIsEmpty(const StackList& s)
{
    return s.top == nullptr;
}

int f_listSize(const StackList& s)
{
    return s.size;
}

int f_listTop(const StackList& s)
{
    return s.top->val;
}

void f_listPush(StackList& s, int val)
{
    // Nowy węzeł trafia na początek listy (= szczyt stosu)
    Node* node = new Node{ val, s.top };
    s.top = node;
    s.size++;
}

void f_listPop(StackList& s)
{
    if (s.top == nullptr) return;
    Node* del = s.top;
    s.top = s.top->next;
    delete del;
    s.size--;
}

void f_listDelete(StackList& s)
{
    while (s.top != nullptr) f_listPop(s);
}
