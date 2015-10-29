#include "size.h"

Size CreateSize(int w, int h)
{
    Size size;

    size.w = w;
    size.h = h;

    return size;
}

void AddSize(Size* const size, const Size* const add)
{
    size->w += add->w;
    size->h += add->h;
}

void SubtractSize(Size* const size, const Size* const subtract)
{
    size->w -= subtract->w;
    size->h -= subtract->h;
}

void MultiplieSize(Size* const size, int multiplier)
{
    size->w *= multiplier;
    size->h *= multiplier;
}

void DivideSize(Size* const size, int divider)
{
    assert(divider);

    size->w /= divider;
    size->h /= divider;
}
