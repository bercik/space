#ifndef WORMHOLE_H
#define WORMHOLE_H

#include <math.h>
#include <stdio.h>

#include <allegro5/allegro.h>

#include "vector2.h"
#include "consts.h"
#include "helper.h"

typedef struct
{
    float r; // promien tunelu
    float d; // srednica tunelu
    Vector2 pos; // srodek okregu obrotu
    float rot_r; // promien okregu obrotu
    Vector2 rot_pos; // pozycja uwzgledniajaca rotacje
    Vector2 last_rot_pos; // ostatnia pozycja uwzgledniajaca rotacje
    float rot; // kat rotacji
    float d_rot; // zmiana katu rotacji w czasie DT
    float self_rot; // obrot wlasny tunelu
    float last_self_rot; // ostatni kat obrotu wlasnego tunelu
    float d_self_rot; // zmiana katu obrotu własnego w czasie DT (wyliczana na podstawie rot_r i d_rot)
    Vector2 center; // srodek bitmapy
    Vector2 scale; // współczynnik skalowania
    ALLEGRO_BITMAP* bitmap; // bitmapa
}Wormhole;

// CreateWormhole: pos - wektor pozycji, r - promien, rot_r - promien okregu obrotu, d_rot - zmiana katu rotacji, bitmap - bitmapa
Wormhole CreateWormhole(Vector2 pos, float r, float rot_r, float d_rot, ALLEGRO_BITMAP* bitmap);
// UpdateWormhole: aktualizuje położenie i rotację tunelu
void UpdateWormhole(Wormhole* const wormhole);
// DrawWormhole: rysuje tunel
void DrawWormhole(const Wormhole* const wormhole);

#endif
