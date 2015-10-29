#ifndef VECTOR2_H
#define VECTOR2_H

#include <assert.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
}Vector2;

// CreateVector2: Tworzy wektor o współrzędnych [x, y]
Vector2 CreateVector2(float x, float y);
// AddVector2: vector2 - wskaźnik do wektora do którego zostanie dodana wartość, add - wektor który dodajemy
void AddVector2(Vector2* const vector2, const Vector2* const add);
// SubtractVector2: vector2 - wskaźnik do wektora od którego zostanie odjęta wartość, subtract - wektor który odejmujemy
void SubtractVector2(Vector2* const vector2, const Vector2* const subtract);
// MultiplieVector2: vector2 - wskaźnik do wektora którego składowe zostana pomnożone, multiplier - skalar przez który mnożymy
void MultiplieVector2(Vector2* const vector2, float multiplier);
// DivideVector2: vector2 - wskaźnik do wektora którego składowe zostana podzielone, divider - skalar przez który dzielimy
void DivideVector2(Vector2* const vector2, float divider);
// DistanceSquaredVector2: zwraca kwadrat odległości między dwoma wektorami
float DistanceSquaredVector2(const Vector2* const v1, const Vector2* const v2);
// DistanceVector2: zwraca odległość między dwoma wektorami
float DistanceVector2(const Vector2* const v1, const Vector2* const v2);
// NormalizedDirectionVector2: zwraca wektor normalny w kierunku od v1 do v2
Vector2 NormalizedDirectionVector2(const Vector2* const v1, const Vector2* const v2);
// NormalizeVector2: normalizuje wektor
void NormalizeVector2(Vector2* const vector2);
// LengthVector2: zwraca długość wektora
float LengthVector2(const Vector2* const vector2);
// RotateVector2: obraca wektor o zadany kąt w radianach wokół punktu (0,0)
void RotateVector2(Vector2* const vector2, float angle);
// RotateAroundPointVector2: obraca wektor o zadany kąt w radianach wokół podanego punktu
void RotateAroundPointVector2(Vector2* const vector2, const Vector2* const center, float angle);

#endif
