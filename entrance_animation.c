#include "entrance_animation.h"

// LOKALNE FUNKCJE
// GetRadiusL: zwraca promien na podstawie przebytej przez obiekt drogi
static inline float GetRadiusL(const EntranceAnimation* const entrance_animation, float distance);
// CountCoefficientsL: wylicza współczynniki prostej (funkcji) GetRadiusL
static void CountCoefficientsL(EntranceAnimation* const entrance_animation, const Object* const object, const Wormhole* const wormhole);
// MoveTowardsCenterOfWormholeL: przesuwa obiekt w kierunku środa tunelu
static void MoveTowardsCenterOfWormholeL(EntranceAnimation* const entrance_animation, Object* const object, const Wormhole* const wormhole);
// !-LOKALNE FUNKCJE-!

EntranceAnimation CreateEntranceAnimation(const Object* const object, const Wormhole* const wormhole)
{
    EntranceAnimation entrance_animation;

    entrance_animation.shift_speed = ENTRANCE_ANIMATION_SPEED * (object->r + wormhole->r);
    entrance_animation.direction_vec = NormalizedDirectionVector2(&object->pos, &wormhole->rot_pos);
    entrance_animation.last_direction_vec = CreateVector2(0, 0);
    entrance_animation.active = false;

    CountCoefficientsL(&entrance_animation, object, wormhole);

    return entrance_animation;
}
/* UpdateEntranceAnimation: aktualizuje EntranceAnimation za pomocą wcześniej zapisanego wskaźnika do obiektu,
zwraca true jeżeli obiekt dotarł do środka tunelu*/
bool UpdateEntranceAnimation(EntranceAnimation* const entrance_animation, Object* const object, const Wormhole* const wormhole)
{
    if (entrance_animation->active)
    {
        // przesuwamy obiekt w kierunku środka tunelu
        MoveTowardsCenterOfWormholeL(entrance_animation, object, wormhole);
        // wyliczamy nowy promien obiektu
        float distance = DistanceVector2(&object->pos, &wormhole->rot_pos);
        if (distance < 2.0f * GAME_SPEED)
        {
            return true; // jeżeli obiekt zbliżył się wystarczająco blisko środka to zwracamy true
        }

        ChangeRadiusObject(object, GetRadiusL(entrance_animation, distance));

        // wyliczamy kąt o jaki obrócił się tunel i zamieniamy na radiany
        float d_angle = DegToRad(wormhole->self_rot - wormhole->last_self_rot);
        // obracamy obiekt o taki sam kąt o jaki obrócił się tunel
        RotateAroundPointVector2(&object->pos, &wormhole->rot_pos, d_angle);
        // przesuwamy obiekt o takie samo przesunięcie jakie wykonał tunel względem środka okręgu obrotu
        Vector2 shift_vec = wormhole->rot_pos;
        SubtractVector2(&shift_vec, &wormhole->last_rot_pos);
        AddVector2(&object->pos, &shift_vec);
        // wyliczamy nowy wektor kierunku
        entrance_animation->last_direction_vec = entrance_animation->direction_vec;
        entrance_animation->direction_vec = NormalizedDirectionVector2(&object->pos, &wormhole->rot_pos);
    }

    return false;
}

static inline float GetRadiusL(const EntranceAnimation* const entrance_animation, float distance)
{
    return (entrance_animation->a * distance);
}

static void CountCoefficientsL(EntranceAnimation* const entrance_animation, const Object* const object, const Wormhole* const wormhole)
{
    entrance_animation->a = (object->r / (object->r + wormhole->r));
}

static void MoveTowardsCenterOfWormholeL(EntranceAnimation* const entrance_animation, Object* const object, const Wormhole* const wormhole)
{
    Vector2 shift_vec = entrance_animation->direction_vec;
    AddVector2(&shift_vec, &entrance_animation->last_direction_vec);
    MultiplieVector2(&shift_vec, 0.5f * entrance_animation->shift_speed * DT * GAME_SPEED);

    AddVector2(&object->pos, &shift_vec);
}
