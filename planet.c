#include "planet.h"

Planet CreatePlanet(Vector2 pos, float r, ALLEGRO_BITMAP* bitmap)
{
    Planet planet;
    planet.pos = pos;
    planet.r = r;
    planet.d = 2 * r;
    planet.gravity_const = pow(r, 3) * GRAVITY_CONST;

    // inicjalizujemy obiekt animacji (parametry na podstawie pliku graficznego):
    planet.animation = CreateAnimation(pos, 64, 3, CreateSize(256, 256), CreateSize(planet.d, planet.d), bitmap);

    return planet;
}

void UpdatePlanet(Planet* const planet)
{
    UpdateAnimation(&planet->animation);
}

void UpdatePlanets(Planet* const planets, int n)
{
    int i;
    for (i = 0; i < n; ++i)
        UpdatePlanet(planets + i);
}

void DrawPlanet(const Planet* const planet)
{
    DrawAnimation(&planet->animation);
}

void DrawPlanets(const Planet* const planets, int n)
{
    int i;

    for (i = 0; i < n; ++i)
    {
        DrawPlanet(planets + i);
    }
}
