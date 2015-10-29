#ifndef BITMAPS_H
#define BITMAPS_H

#include <allegro5/allegro.h>
#include "consts.h"

typedef struct
{
    ALLEGRO_BITMAP* object;
    ALLEGRO_BITMAP* arrow;
    ALLEGRO_BITMAP* bar;
    ALLEGRO_BITMAP* planets[NUMBER_OF_PLANET_BITMAPS];
    ALLEGRO_BITMAP* wormhole;
    ALLEGRO_BITMAP* explosion;
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* star;
}Bitmaps;

// LoadBitmaps: ładuje bitmapy
void LoadBitmaps(Bitmaps* bitmaps);
// DestroyBitmaps: usuwa bitmapy
void DestroyBitmaps(Bitmaps* bitmaps);

#endif
