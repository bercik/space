#ifndef OBJECT_H
#define OBJECT_H

#include <math.h>

#include <allegro5/allegro.h>

#include "vector2.h"
#include "planet.h"
#include "wormhole.h"
#include "consts.h"
#include "explosion.h"
#include "entrance_animation.h"

enum UPDATE_OBJECT_RETURN { NOTHING, END_EXPLOSION, END_ENTRANCE_ANIMATION, EXPLOSION_OR_ENTRANCE };

typedef struct Object Object;

struct Object
{
    Vector2 pos; // pozycja
    Vector2 vel; // predkosc
    Vector2 acc; // przyspieszenie
    float r; // promien
    float d; // srednica
    bool first_update; // czy pierwszy raz wywołujemy funkcję update
    Explosion explosion; // obiekt eksplozji
    EntranceAnimation entrance_animation; // animacja wejścia do tunelu
    ALLEGRO_BITMAP* bitmap; // bitmapa
};

// CreateObject: pos - wektor pozycji srodka, r - promien, bitmap - bitmapa
Object CreateObject(Vector2 pos, float r, ALLEGRO_BITMAP* obj_bitmap, ALLEGRO_BITMAP* exp_bitmap);
// UpdateObject: object - obiekt, wormhole - tunel, planets - planety, n - aktualna ilość planet, zwraca informację o stanie obiektu
enum UPDATE_OBJECT_RETURN UpdateObject(Object* const object, const Wormhole* const wormhole, const Planet* const planets, int n);
// CheckCollisionObject: object - obiekt, planets - tablica planet, n - aktualna ilość planet, zwraca true jeżeli nastąpiła kolizja
bool CheckCollisionObjectPlanets(Object* const object, const Planet* const planets, int n);
// CheckCollisionObjectWormhole: sprawdza czy wystąpiła kolizja między obiektem, a tunelem
bool CheckCollisionObjectWormhole(Object* const object, const Wormhole* const wormhole);
// DrawObject: object - obiekt
void DrawObject(const Object* const object);
// ChangeRadius: zmienia promien obiektu
void ChangeRadiusObject(Object* const object, float new_r);

#endif
