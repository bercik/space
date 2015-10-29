#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#include <allegro5/allegro_native_dialog.h>

#include "consts.h"
#include "planet.h"
#include "input.h"
#include "object.h"
#include "bitmaps.h"
#include "vector2.h"
#include "wormhole.h"

typedef struct
{
    int number_of_planets; // liczba planet na aktualnej planszy
    Object object; // obiekt
    Planet planets[MAX_PLANETS]; // planety
    Object original_object; // wczytany z pliku obiekt
    Wormhole wormhole; // tunel
} Map;

// LoadMap: ładuje mapę z pliku (path), zapisuje informacje w strukturze map
bool LoadMap(Map* const map, Input* const input, const char* const path, const Bitmaps* const bitmaps);

#endif
