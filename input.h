#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include <math.h>
#include "vector2.h"
#include "object.h"
#include "helper.h"
#include "value.h"
#include "game_state.h"

enum KEY { KEY_LEFT, KEY_RIGHT, KEY_SPACE };

typedef struct
{
    FloatValue strength;
    bool add_strength;
    float strength_scale1;
    float strength_scale2;
    float angle;

    Vector2 arrow_pos, bar_pos;
    Vector2 arrow_scale;
    ALLEGRO_BITMAP* arrow_bitmap;
    ALLEGRO_BITMAP* bar_bitmap;

    bool keys[3];

    bool exit;
    bool restart;
} Input;

// CreateInput: tworzy input na podstawie obiektu i podanej rotacji (rot: 0-3)
Input CreateInput(const Object* const object, int rot, ALLEGRO_BITMAP* arrow_bitmap, ALLEGRO_BITMAP* bar_bitmap);
// DrawInput: rysuje input
void DrawInput(const Input* const input);
// UpdateKeyboardInput: Aktualizuje klawiature, zwraca true jeżeli obiekt został wystrzelony
bool UpdateKeyboardInput(Input* const input, const ALLEGRO_EVENT* const event, enum GAME_STATE game_state);
// UpdateInput: aktualizuje input
void UpdateInput(Input* const input);
// IsRestartInput: sprawdza czy zostal wcisniety klawisz R
bool IsRestartInput(Input* const input);
// RestartInput: restartuje input, ustawia wartość siły na minimalną, zeruje klawisze
void RestartInput(Input* const input);
// CountVelocityVectorFromInput: oblicza współrzędne wektora predkosci na podstawie input
Vector2 CountVelocityVectorFromInput(const Input* const input);

#endif
