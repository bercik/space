#ifndef ENTRANCE_ANIMATION_H
#define ENTRANCE_ANIMATION_H

#include "consts.h"
#include "vector2.h"
#include "helper.h"
#include "wormhole.h"

typedef struct EntranceAnimation EntranceAnimation;
typedef struct Object Object;

struct EntranceAnimation
{
    Vector2 direction_vec; // wektor kierunku do środka tunelu
    Vector2 last_direction_vec; // ostatni wektor kierunku do środka tunelu
    float a; // wsp. kierunkowy prostej (funkcji) liczącej proemiń na podstawie przebytej odległości
    float shift_speed; // szybkość przesuwania w kierunku środka tunelu
    bool active; // czy animacja wejścia jest aktualnie aktywna
};

#include "object.h"

/* CreateEntranceAnimation: tworzy obiekt EntranceAnimation, wskaźnik do obiektu jest zapamiętywany
i później wykorzystywany do zmiany jego położenia i promienia*/
EntranceAnimation CreateEntranceAnimation(const Object* const object, const Wormhole* const wormhole);
/* UpdateEntranceAnimation: aktualizuje EntranceAnimation za pomocą wcześniej zapisanego wskaźnika do obiektu,
zwraca true jeżeli obiekt dotarł do środka tunelu*/
bool UpdateEntranceAnimation(EntranceAnimation* const entrance_animation, Object* const object, const Wormhole* const wormhole);

#endif
