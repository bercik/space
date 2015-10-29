#include "explosion.h"

Explosion CreateExplosion(Animation animation)
{
    Explosion explosion;

    explosion.animation = animation;
    explosion.active = false;

    return explosion;
}

inline void StartExplosion(Explosion* const explosion, Vector2 pos)
{
    UpdateAnimationPos(&explosion->animation, pos);
    explosion->active = true;
}

inline void StopExplosion(Explosion* const explosion)
{
    explosion->active = false;
    RestartAnimation(&explosion->animation);
}

bool UpdateExplosion(Explosion* const explosion)
{
    if (explosion->active)
    {
        if (UpdateAnimation(&explosion->animation))
        {
            explosion->active = false;

            return true;
        }
    }

    return false;
}

void DrawExplosion(const Explosion* const explosion)
{
    if (explosion->active)
    {
        DrawAnimation(&explosion->animation);
    }
}
