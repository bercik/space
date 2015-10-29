#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "animation.h"

typedef struct
{
    Animation animation; // animacja
    bool active; // czy jest aktualnie aktywna
}Explosion;

// CreateExplosion: tworzy eksplozje
Explosion CreateExplosion(Animation animation);
// StartExplosion: zaczyna eksplozje
inline void StartExplosion(Explosion* const explosion, Vector2 pos);
// StopExplosion: zatrzymuje eksplozje
inline void StopExplosion(Explosion* const explosion);
// UpdateExplosion: aktualizuje eksplozje, zwraca true w momencie skończenia animacji
bool UpdateExplosion(Explosion* const explosion);
// DrawExplosion: rysuje eksplozje
void DrawExplosion(const Explosion* const explosion);

#endif
