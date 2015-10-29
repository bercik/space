#include "object.h"

// LOKALNE FUNKCJE
// UpdatePositionObjectL: Aktualizuje pozycję obiektu
static void UpdatePositionObjectL(Object* const object);
// UpdateVelocityObjectL: Aktualizuje prędkość obiektu
static void UpdateVelocityObjectL(Object* const object, const Vector2* const new_acc);
// CheckCollisionObjectL (funkcja lokalna dla jednej planety): object - obiekt, planet - planeta
static bool CheckCollisionObjectL(const Object* const object, const Planet* const planet);
// CheckCollisionObjectBoundariesL: sprawdza czy obiekt nie wyleciał poza ekran
static bool CheckCollisionObjectBoundariesL(const Object* const object);
// CountAccelerationObjectPlanetL: object - obiekt, planet - planeta
static Vector2 CountAccelerationObjectPlanetL(const Object* const object, const Planet* const planet);
// CountAccelerationObjectPlanetsL: object - obiekt, planets - tablica planet, n - ilość planet
static Vector2 CountAccelerationObjectPlanetsL(const Object* const object, const Planet* const planets, int n);
// !-LOKALNE FUNKCJE-!

Object CreateObject(Vector2 pos, float r, ALLEGRO_BITMAP* obj_bitmap, ALLEGRO_BITMAP* exp_bitmap)
{
    Object object;
    object.pos = pos;
    object.vel = CreateVector2(0, 0);
    object.acc = CreateVector2(0, 0);
    object.r = r;
    object.d = 2 * r;
    object.first_update = true;

    // inicjalizujemy obiekt eksplozji (parametry na podstawie pliku graficznego):
    object.explosion = CreateExplosion(CreateAnimation(object.pos, 38, 1, CreateSize(128, 128), CreateSize(object.d * 4, object.d * 4), exp_bitmap));
    object.entrance_animation.active = false;

    object.bitmap = obj_bitmap;

    return object;
}

enum UPDATE_OBJECT_RETURN UpdateObject(Object* const object, const Wormhole* const wormhole, const Planet* const planets, int n)
{
    if (object->entrance_animation.active)
    {
        if (UpdateEntranceAnimation(&object->entrance_animation, object, wormhole))
        {
            return END_ENTRANCE_ANIMATION;
        }
        else
        {
            return EXPLOSION_OR_ENTRANCE;
        }
    }
    else if(object->explosion.active)
    {
        if (UpdateExplosion(&object->explosion)) // zwraca true jezeli zakonczono animacje kolizji
        {
            return END_EXPLOSION;
        }
        else
        {
            return EXPLOSION_OR_ENTRANCE;
        }
    }
    else
    {
        // jeżeli pierwszy raz wywołujemy funkcję update to musimy obliczyć początkowe przyspieszenie
        if (object->first_update)
        {
            object->acc = CountAccelerationObjectPlanetsL(object, planets, n);

            object->first_update = false;
        }

        UpdatePositionObjectL(object);
        Vector2 new_acc = CountAccelerationObjectPlanetsL(object, planets, n);
        UpdateVelocityObjectL(object, &new_acc);
        object->acc = new_acc;

        return NOTHING;
    }
}

static void UpdatePositionObjectL(Object* const object)
{
    Vector2 temp;

    // liczymy predkosc i dodajemy do polozenia
    temp = object->vel;
    MultiplieVector2(&temp, DT * GAME_SPEED);
    AddVector2(&object->pos, &temp);

    // liczymy przyspieszenie i dodajemy do polozenia
    temp = object->acc;
    MultiplieVector2(&temp, 0.5f * DT * DT * GAME_SPEED * GAME_SPEED);
    AddVector2(&object->pos, &temp);
}

static void UpdateVelocityObjectL(Object* const object, const Vector2* const new_acc)
{
    Vector2 temp = *new_acc;
    AddVector2(&temp, &object->acc);
    MultiplieVector2(&temp, 0.5f * DT * GAME_SPEED);
    AddVector2(&object->vel, &temp);
}

static Vector2 CountAccelerationObjectPlanetL(const Object* const object, const Planet* const planet)
{
    Vector2 acc;

    // liczymy odległość między planetą, a obiektem podniesioną do potęgi 3
    float d3;
    Vector2 temp = planet->pos;
    SubtractVector2(&temp, &object->pos);
    acc = temp;
    d3 = sqrt(temp.x * temp.x + temp.y * temp.y);
    d3 = pow(d3, 3);

    // liczymy przyspieszenie
    MultiplieVector2(&acc, planet->gravity_const);
    DivideVector2(&acc, d3);

    // zwracamy
    return acc;
}

static Vector2 CountAccelerationObjectPlanetsL(const Object* const object, const Planet* const planets, int n)
{
    int i;
    Vector2 acc = CreateVector2(0, 0);
    Vector2 temp;

    for (i = 0; i < n; ++i)
    {
        temp = CountAccelerationObjectPlanetL(object, planets + i);
        AddVector2(&acc, &temp);
    }

    return acc;
}

bool CheckCollisionObjectWormhole(Object* const object, const Wormhole* const wormhole)
{
    float d2 = DistanceSquaredVector2(&object->pos, &wormhole->rot_pos);
    float r2 = (object->r + wormhole->r) * (object->r + wormhole->r);

    if (r2 > d2)
    {
        object->entrance_animation = CreateEntranceAnimation(object, wormhole);
        object->entrance_animation.active = true;

        return true;
    }
    else
    {
        return false;
    }
}

bool CheckCollisionObjectPlanets(Object* const object, const Planet* const planets, int n)
{
    int i;

    // sprawdzamy kolizje z planetami:
    for (i = 0; i < n; ++i)
    {
        if (CheckCollisionObjectL(object, planets + i))
        {
            StartExplosion(&object->explosion, object->pos);
            return true;
        }
    }

    // sprawdzamy czy obiekt nie wyszedł poza granice ekranu
    if (CheckCollisionObjectBoundariesL(object))
    {
        StartExplosion(&object->explosion, object->pos);
        return true;
    }

    // jeżeli żadne z powyższych to nie ma kolizji
    return false;
}

static bool CheckCollisionObjectL(const Object* const object, const Planet* const planet)
{
    float d2 = DistanceSquaredVector2(&object->pos, &planet->pos);
    float r2 = (object->r + planet->r) * (object->r + planet->r);

    return (r2 > d2);
}

static bool CheckCollisionObjectBoundariesL(const Object* const object)
{
    // lewa krawędź
    if (object->pos.x - object->r < 0)
        return true;
    // prawa krawędź
    if (object->pos.x + object->r > SCREEN_W)
        return true;
    // górna krawędź
    if (object->pos.y - object->r < 0)
        return true;
    // dolna krawędź
    if (object->pos.y + object->r > SCREEN_H)
        return true;

    return false;
}

void ChangeRadiusObject(Object* const object, float new_r)
{
    object->r = new_r;
    object->d = 2 * new_r;
}

void DrawObject(const Object* const object)
{
    if (!object->explosion.active)
        al_draw_scaled_bitmap(object->bitmap, 0, 0, al_get_bitmap_width(object->bitmap), al_get_bitmap_height(object->bitmap),
            object->pos.x - object->r, object->pos.y - object->r, object->d, object->d, 0);
}
