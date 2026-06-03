/**
 * @file LibStackArray.cpp
 * @brief Definicje funkcji stosu na tablicy dynamicznej.
 */

#include "LibStackArray.h"

StackArray f_arrayCreate(int capacity)
{
    StackArray s;
    s.capacity = capacity;
    s.size = 0;
    s.data = new int[capacity];
    return s;
}

bool f_arrayIsEmpty(const StackArray& s)
{
    return s.size == 0;
}

int f_arraySize(const StackArray& s)
{
    return s.size;
}

int f_arrayTop(const StackArray& s)
{
    // Szczyt stosu to ostatni element tablicy
    return s.data[s.size - 1];
}

void f_arrayPush(StackArray& s, int val)
{
    // Jeśli brak miejsca — powiększamy tablicę 2x
    if (s.size == s.capacity) {
        int newCap = s.capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < s.size; i++)
            newData[i] = s.data[i];
        delete[] s.data;
        s.data = newData;
        s.capacity = newCap;
    }
    s.data[s.size++] = val;
}

void f_arrayPop(StackArray& s)
{
    if (s.size > 0) s.size--;
}

void f_arrayDelete(StackArray& s)
{
    delete[] s.data;
    s.data = nullptr;
    s.size = 0;
    s.capacity = 0;
}
