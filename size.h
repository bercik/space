#ifndef SIZE_H
#define SIZE_H

#include <assert.h>

typedef struct
{
    int w;
    int h;
}Size;

// CreateSize: tworzy obiekt size
Size CreateSize(int w, int h);
// AddSize: size - wskaźnik do obiektu size do którego zostanie dodana wartość, add - obiekt size który dodajemy
void AddSize(Size* const size, const Size* const add);
// SubtractSize: size - wskaźnik do obiektu size od którego zostanie odjęta wartość, subtract - obiektu size który odejmujemy
void SubtractSize(Size* const size, const Size* const subtract);
// MultiplieSize: size - wskaźnik do obiektu size którego składowe zostana pomnożone, multiplier - skalar przez który mnożymy
void MultiplieSize(Size* const size, int multiplier);
// DivideSize: size - wskaźnik do obiektu size którego składowe zostana podzielone, divider - skalar przez który dzielimy
void DivideSize(Size* const size, int divider);

#endif
