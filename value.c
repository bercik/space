#include "value.h"

FloatValue CreateFloatValue(float value, float min, float max)
{
    FloatValue float_value;
    float_value.value = value;
    float_value.min = min;
    float_value.max = max;

    return float_value;
}

// funkcje pomocnicze
static bool IsGreater(FloatValue* const value)
{
    if (value->value > value->max)
    {
        value->value = value->max;
        return true;
    }

    return false;
}

static bool IsSmaller(FloatValue* const value)
{
    if (value->value < value->min)
    {
        value->value = value->min;
        return true;
    }

    return false;
}
// !-funkcje pomocnicze-!

bool AddFloatValue(FloatValue* const value, float add)
{
    value->value += add;

    return IsGreater(value);
}

bool SubtractFloatValue(FloatValue* const value, float subtract)
{
    value->value -= subtract;

    return IsSmaller(value);
}

bool MultiplieFloatValue(FloatValue* const value, float multiplier)
{
    value->value *= multiplier;

    return (IsGreater(value) && IsSmaller(value));
}

bool DivideFloatValue(FloatValue* const value, float divider)
{
    if (divider != 0)
    {
        value->value /= divider;

        return (IsGreater(value) && IsSmaller(value));
    }
    else
    {
        return false;
    }
}
