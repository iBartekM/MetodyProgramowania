/**
 * @file LibStackArray.h
 * @brief Implementacja stosu na tablicy dynamicznej jednowymiarowej.
 */

#ifndef LIBSTACKARRAY_H
#define LIBSTACKARRAY_H

struct StackArray {
    int* data;       // tablica dynamiczna
    int capacity;    // pojemność tablicy
    int size;        // ilość elementów aktualnie na stosie
};

// Tworzy nowy stos o zadanej pojemności początkowej
StackArray f_arrayCreate(int capacity);

// Czy stos jest pusty
bool f_arrayIsEmpty(const StackArray& s);

// Ilość elementów na stosie
int f_arraySize(const StackArray& s);

// Zwraca wartość elementu na szczycie (bez zdejmowania)
int f_arrayTop(const StackArray& s);

// Umieszcza element na szczycie
void f_arrayPush(StackArray& s, int val);

// Zdejmuje element ze szczytu
void f_arrayPop(StackArray& s);

// Zwalnia pamięć
void f_arrayDelete(StackArray& s);

#endif
