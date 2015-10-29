#ifndef PLANET_H
#define PLANET_H

#include <allegro5/allegro.h>
#include <math.h>
#include "vector2.h"
#include "consts.h"
#include "animation.h"

typedef struct
{
    Vector2 pos; // pozycja
    float r; // promien
    float d; // srednica
    float gravity_const; // stała grawitacyjna danej planety
    Animation animation; // obiekt animacji
}Planet;

// CreatePlanet: pos - pozycja, r - promien, bitmap - bitmapa
Planet CreatePlanet(Vector2 pos, float r, ALLEGRO_BITMAP* bitmap);
// UpdatePlanet: Aktualizuje planete
void UpdatePlanet(Planet* const planet);
// UpdatePlanets: aktualizuje planety, planets - tablica planet, n - ilość planet
void UpdatePlanets(Planet* const planets, int n);
// DrawPlanet: planet - planeta
void DrawPlanet(const Planet* const planet);
// DrawPlanets: planets - tablica planet, n - aktualna liczba planet
void DrawPlanets(const Planet* const planets, int n);

#endif
