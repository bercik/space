#include "map.h"

bool LoadMap(Map* const map, Input* const input, const char* const path, const Bitmaps* const bitmaps)
{
    FILE* file = fopen(path, "r");

    if (!file)
        return false; // jeżeli nie udało się otworzyć pliku zwracamy false

    // zmienne pomocnicze:
    int number_of_planets, rot, i;
    float x, y, r, rot_r, d_rot;
    char temp[40];

    // wczytujemy obiekt:
    fscanf(file, "%s", temp);
    fscanf(file, "%f %f %f %d", &x, &y, &r, &rot);
    map->original_object = CreateObject(CreateVector2(x, y), r, bitmaps->object, bitmaps->explosion);
    map->object = map->original_object;
    *input = CreateInput(&map->object, rot, bitmaps->arrow, bitmaps->bar);

    // wczytujemy planety:
    fscanf(file, "%s", temp);
    fscanf(file, "%d", &number_of_planets);

    if (number_of_planets <= MAX_PLANETS)
    {
        map->number_of_planets = number_of_planets;

        for (i = 0; i < number_of_planets; ++i)
        {
            fscanf(file, "%f %f %f", &x, &y, &r);
            map->planets[i] = CreatePlanet(CreateVector2(x, y), r, bitmaps->planets[rand() % NUMBER_OF_PLANET_BITMAPS]); // losujemy obrazek planety
        }
    }
    else
    {
        return false; // jeżeli liczba planet jest większa od liczby możliwych planet zwracamy false
    }

    // wczytujemy tunel czasoprzestrzenny:
    fscanf(file, "%s", temp);
    fscanf(file, "%f %f %f %f %f", &x, &y, &r, &rot_r, &d_rot);
    map->wormhole = CreateWormhole(CreateVector2(x, y), r, rot_r, d_rot, bitmaps->wormhole);

    return true;
}
