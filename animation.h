#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro5/allegro.h>

#include "size.h"
#include "vector2.h"
#include "consts.h"

typedef struct
{
    Vector2 pos; // pozycja
    int max_frame; // ilość klatek
    int cur_frame; // aktualna klatka
    int frame_count; // licznik
    int frame_delay; // szybkość przewijania klatek
    Size frame_source_size; // wielkość źródłowa klatki
    Size frame_dest_size; // wielkość docelowa klatki
    int animation_columns; // ilość kolumn bitmapy

    ALLEGRO_BITMAP* bitmap; // bitmapa
}Animation;

// CreateAnimation: tworzy obiekt animacji
Animation CreateAnimation(Vector2 pos, int max_frame, int frame_delay, Size frame_source_size, Size frame_dest_size, ALLEGRO_BITMAP* bitmap);
// UpdateAnimation: aktualizuje obiekt animacji, zwraca czy animacja się zakończyła
bool UpdateAnimation(Animation* const animation);
// UpdateAnimationPos: aktualizuje pozycje animacji
inline void UpdateAnimationPos(Animation* const animation, Vector2 new_pos);
// DrawAnimation: rysuje animacje
void DrawAnimation(const Animation* const animation);
// RestartAnimation: ustawia parametry animacji na poczatkowe
inline void RestartAnimation(Animation* const animation);

#endif
