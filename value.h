#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>

typedef struct
{
    float value;
    float min;
    float max;
} FloatValue;

// CreateFloatValue: tworzy strukturę FloatValue
FloatValue CreateFloatValue(float value, float min, float max);
/* AddFloatValue: dodaje do value wartość add i zwraca czy operację udało się przeprowadzić
   (jeżeli przekroczyliśmy zakres max to obcina wartość value do max)*/
bool AddFloatValue(FloatValue* const value, float add);
/* SubtractFloatValue: odejmuje od value wartość subtract i zwraca czy operację udało się przeprowadzić
   (jeżeli przekroczyliśmy zakres min to obcina wartość value do min)*/
bool SubtractFloatValue(FloatValue* const value, float subtract);
/* MultiplieFloatValue: przemnaża value przez wartość multiplier i zwraca czy operację udało się przeprowadzić
   (jeżeli przekroczyliśmy zakres max to obcina wartość value do max, jeżeli przekroczyliśmy zakres min to obcina wartość value do min)*/
bool MultiplieFloatValue(FloatValue* const value, float multiplier);
/* DivideFloatValue: dzieli value przez wartość divider i zwraca czy operację udało się przeprowadzić
   (jeżeli przekroczyliśmy zakres max to obcina wartość value do max, jeżeli przekroczyliśmy zakres min to obcina wartość value do min)*/
bool DivideFloatValue(FloatValue* const value, float divider);

#endif
