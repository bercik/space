#include "vector2.h"

Vector2 CreateVector2(float x, float y)
{
    Vector2 vec2;
    vec2.x = x;
    vec2.y = y;

    return vec2;
}

void AddVector2(Vector2* const vector2, const Vector2* const add)
{
    vector2->x += add->x;
    vector2->y += add->y;
}

void SubtractVector2(Vector2* const vector2, const Vector2* const subtract)
{
    vector2->x -= subtract->x;
    vector2->y -= subtract->y;
}

void MultiplieVector2(Vector2* const vector2, float multiplier)
{
    vector2->x *= multiplier;
    vector2->y *= multiplier;
}

void DivideVector2(Vector2* const vector2, float divider)
{
    assert(divider);

    vector2->x /= divider;
    vector2->y /= divider;
}

float DistanceSquaredVector2(const Vector2* const v1, const Vector2* const v2)
{
    return ((v1->x - v2->x) * (v1->x - v2->x) + (v1->y - v2->y) * (v1->y - v2->y));
}

float DistanceVector2(const Vector2* const v1, const Vector2* const v2)
{
    return sqrt(DistanceSquaredVector2(v1, v2));
}

Vector2 NormalizedDirectionVector2(const Vector2* const v1, const Vector2* const v2)
{
    Vector2 temp = *v2;
    SubtractVector2(&temp, v1);
    NormalizeVector2(&temp);

    return temp;
}

void NormalizeVector2(Vector2* const vector2)
{
    float length = LengthVector2(vector2);
    DivideVector2(vector2, length);
}

float LengthVector2(const Vector2* const vector2)
{
    return sqrt(vector2->x * vector2->x + vector2->y * vector2->y);
}

void RotateVector2(Vector2* const vector2, float angle)
{
    Vector2 temp = *vector2;

    vector2->x = temp.x * cos(angle) - temp.y * sin(angle);
    vector2->y = temp.x * sin(angle) + temp.y * cos(angle);
}

void RotateAroundPointVector2(Vector2* const vector2, const Vector2* const center, float angle)
{
    Vector2 temp = *vector2;
    SubtractVector2(&temp, center);

    vector2->x = temp.x * cos(angle) - temp.y * sin(angle);
    vector2->y = temp.x * sin(angle) + temp.y * cos(angle);

    AddVector2(vector2, center);
}
