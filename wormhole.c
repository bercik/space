#include "wormhole.h"

// LOKALNE FUNKCJE
// CountRotPosL: oblicza pozycję rotacji
static void CountRotPosL(Wormhole* const wormhole);
// !-LOKALNE FUNKCJE-!

Wormhole CreateWormhole(Vector2 pos, float r, float rot_r, float d_rot, ALLEGRO_BITMAP* bitmap)
{
    Wormhole wormhole;

    wormhole.pos = pos;
    wormhole.r = r;
    wormhole.d = 2 * r;

    wormhole.rot_r = rot_r;
    wormhole.rot = 0.0f;
    wormhole.d_rot = d_rot;
    wormhole.self_rot = 0.0f;

    // wyliczamy zmianę kąta obrotu własnego
    if (wormhole.d_rot == 0.0f)
    {
        // dla zerowej zmiany kąta obrotu
        wormhole.rot_r = 0.0f;
        wormhole.d_self_rot = 90.0f;
    }
    else
    {
        float t = (2 * ALLEGRO_PI * wormhole.rot_r) / (wormhole.d_rot); // czas w którym tunel robi jeden obrót
        wormhole.d_self_rot = (360.0f / t) * NUMBER_OF_WORMHOLE_SELF_ROT; // zmiana kątu obrotu własnego tunelu (pełny obrót * ilość obrotów)
    }

    float cx = al_get_bitmap_width(bitmap) / 2.0f;
    float cy = al_get_bitmap_height(bitmap) / 2.0f;
    wormhole.center = CreateVector2(cx, cy);
    float sx = wormhole.d / al_get_bitmap_width(bitmap);
    float sy = wormhole.d / al_get_bitmap_height(bitmap);
    wormhole.scale = CreateVector2(sx, sy);
    wormhole.bitmap = bitmap;

    CountRotPosL(&wormhole);

    return wormhole;
}

static void CountRotPosL(Wormhole* const wormhole)
{
    wormhole->last_rot_pos = wormhole->rot_pos;

    wormhole->rot_pos.x = wormhole->pos.x + wormhole->rot_r * cos(DegToRad(wormhole->rot));
    wormhole->rot_pos.y = wormhole->pos.y + wormhole->rot_r * sin(DegToRad(wormhole->rot));
}

void UpdateWormhole(Wormhole* const wormhole)
{
    wormhole->last_self_rot = wormhole->self_rot;

    wormhole->self_rot += wormhole->d_self_rot * DT * GAME_SPEED;
    if (wormhole->self_rot > 360.0f)
        wormhole->self_rot -= 360.0f;

    wormhole->rot += wormhole->d_rot * DT * GAME_SPEED;
    if (wormhole->rot > 360.0f)
        wormhole->rot -= 360.0f;

    CountRotPosL(wormhole);
}

void DrawWormhole(const Wormhole* const wormhole)
{
    al_draw_scaled_rotated_bitmap(wormhole->bitmap, wormhole->center.x, wormhole->center.y, wormhole->rot_pos.x, wormhole->rot_pos.y,
        wormhole->scale.x, wormhole->scale.y, DegToRad(wormhole->self_rot), 0);
}
