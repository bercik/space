#include "stars.h"

static const float MIN_STAR_SIZE = 5.0f; // minimalny rozmiar gwiazdy
static const float MAX_STAR_SIZE = 10.0f; // maksymalny rozmiar gwiazdy
static const float MIN_DELTA_OPACITY = 0.2f; // maksymalna zmiana przeźroczystości w ciągu sekundy
static const float MAX_DELTA_OPACITY = 0.4f; // minimalna zmiana przeźroczystości w ciągu sekundy
static const float MIN_STAR_TIME = 0.5f; // minimalny czas pojawienia się nowej gwiazdy
static const float MAX_STAR_TIME = 1.0f; // maksymalny czas pojawienia się nowej gwiazdy
static const int MIN_RESET_STARS = 6; // minimalna liczba stworzonych gwiazd przy ich resecie
static const int MAX_RESET_STARS = 10; // maksymalna liczba stworzonych gwiazd przy ich resecie

Star CreateStar(float opacity)
{
    Star star;

    star.active = true;
    star.opacity = opacity;
    star.opacity_dir = 1.0f;

    // losujemy szybkość zmiany przeźroczystości gwiazdy:
    star.delta_opacity = (MAX_DELTA_OPACITY - MIN_DELTA_OPACITY) * ((float)rand() / (float)RAND_MAX) + MIN_DELTA_OPACITY;

    // losujemy rozmiar gwiazdy:
    star.size = (MAX_STAR_SIZE - MIN_STAR_SIZE) * ((float)rand() / (float)RAND_MAX) + MIN_STAR_SIZE;

    // losujemy pozycję gwiazdy:
    float x = (float)(SCREEN_W - star.size) * ((float)rand() / (float)RAND_MAX);
    float y = (float)(SCREEN_H - star.size) * ((float)rand() / (float)RAND_MAX);
    star.pos = CreateVector2(x ,y);

    return star;
}

void UpdateStar(Star* const star)
{
    star->opacity += star->opacity_dir * star->delta_opacity * GAME_SPEED * DT;

    if (star->opacity > 1.0f)
        star->opacity_dir = -1.0f;
    else if (star->opacity < 0.0f && star->opacity_dir == -1.0f)
        star->active = false;
}

void DrawStar(const Star* const star, ALLEGRO_BITMAP* star_bitmap)
{
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    int w = al_get_bitmap_width(star_bitmap);
    int h = al_get_bitmap_height(star_bitmap);
    al_draw_tinted_scaled_bitmap(star_bitmap, al_map_rgba_f(1, 1, 1, star->opacity), 0, 0, w, h, star->pos.x, star->pos.y, star->size, star->size, 0);

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}

Stars CreateStars(ALLEGRO_BITMAP* star_bitmap)
{
    Stars stars;

    stars.curr_time = 0.0f;
    stars.star_time = 0.0f;
    stars.star_bitmap = star_bitmap;

    ResetStars(&stars);

    return stars;
}

void UpdateStars(Stars* const stars)
{
    int i;

    for (i = 0; i < MAX_STARS; ++i)
    {
        // aktualizujemy tylko aktywne gwiazdy
        if (stars->stars[i].active)
            UpdateStar(&stars->stars[i]);
    }

    stars->curr_time += DT * GAME_SPEED;

    // tworzymy nową gwiazdę po przekroczeniu odpowiedniego czasu
    if (stars->curr_time > stars->star_time)
    {
        // zerujemy licznik czasu, losujemy nową wartość czasu pojawaienia się kolejnej gwiazdy
        stars->curr_time = 0.0f;
        stars->star_time = (MAX_STAR_TIME - MIN_STAR_TIME) * ((float)rand() / (float)RAND_MAX) + MIN_STAR_TIME;

        // szukamy nieaktywnej ("wolnej") gwiazdy
        for (i = 0; i < MAX_STARS; ++i)
        {
            if (!stars->stars[i].active)
            {
                // w miejscu wolnej gwiazdy tworzymy nową
                stars->stars[i] = CreateStar(0.0f);
                break;
            }
        }
    }
}

void DrawStars(const Stars* const stars)
{
    int i;

    for (i = 0; i < MAX_STARS; ++i)
    {
        // rysujemy tylko aktywne gwiazdy
        if (stars->stars[i].active)
            DrawStar(&stars->stars[i], stars->star_bitmap);
    }
}

void ResetStars(Stars* const stars)
{
    int i;
    int number_of_stars = rand() % (MAX_RESET_STARS - MIN_RESET_STARS + 1) + MIN_RESET_STARS;
    float opacity;

    for (i = 0; i < number_of_stars; ++i)
    {
        opacity = (float)rand() / (float)RAND_MAX;
        stars->stars[i] = CreateStar(opacity);
    }
    for (i = number_of_stars; i < MAX_STARS; ++i)
    {
        stars->stars[i].active = false;
    }
}
