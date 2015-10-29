#include "bitmaps.h"

void LoadBitmaps(Bitmaps* const bitmaps)
{
    int i; // zmienna pomocnicza
    char path[12]; // sciezka do plikow graficznych z planetami ("planet[dig].png")
    strcpy(path, "planet0.png");

    bitmaps->object = al_load_bitmap("object.png");
    bitmaps->arrow = al_load_bitmap("arrow.png");
    bitmaps->bar = al_load_bitmap("bar.png");
    bitmaps->wormhole = al_load_bitmap("wormhole.png");
    bitmaps->explosion = al_load_bitmap("explosion.png");
    bitmaps->background = al_load_bitmap("background.png");
    bitmaps->star = al_load_bitmap("star.png");

    for (i = 0; i < NUMBER_OF_PLANET_BITMAPS; ++i)
    {
        path[6] = '0' + i;
        al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
        bitmaps->planets[i] = al_load_bitmap(path);
    }
}

void DestroyBitmaps(Bitmaps* bitmaps)
{
    int i; // zmienna pomocnicza

    al_destroy_bitmap(bitmaps->object);
    bitmaps->object = NULL;
    al_destroy_bitmap(bitmaps->arrow);
    bitmaps->arrow = NULL;
    al_destroy_bitmap(bitmaps->bar);
    bitmaps->bar = NULL;
    al_destroy_bitmap(bitmaps->wormhole);
    bitmaps->wormhole = NULL;
    al_destroy_bitmap(bitmaps->explosion);
    bitmaps->explosion = NULL;
    al_destroy_bitmap(bitmaps->background);
    bitmaps->background = NULL;
    al_destroy_bitmap(bitmaps->star);
    bitmaps->star = NULL;

    for (i = 0; i < NUMBER_OF_PLANET_BITMAPS; ++i)
    {
        al_destroy_bitmap(bitmaps->planets[i]);
        bitmaps->planets[i] = NULL;
    }
}
