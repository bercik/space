#ifndef STARS_H
#define STARS_H

#include <allegro5/allegro.h>

#include <stdbool.h>

#include "consts.h"
#include "vector2.h"
#include "size.h"

enum { MAX_STARS = 32 }; // maksymalna liczba gwiazd

typedef struct
{
    Vector2 pos; // pozycja gwiazdy
    float size; // rozmiar gwiazdy (bok kwadratu)
    float opacity; // przeźroczystość
    float delta_opacity; // szybkość zmian przeźroczystości
    bool active; // czy gwiazda jest aktywna
    int opacity_dir; // kierunek zmiany przeźroczystości
}Star;

// CreateStar: tworzy gwiazdę, ustawia jako aktywną
Star CreateStar(float opacity);
// UpdateStar: aktualizuje gwiazdę
void UpdateStar(Star* const star);
// DrawStar: rysuje gwiazdę
void DrawStar(const Star* const star, ALLEGRO_BITMAP* star_bitmap);

typedef struct
{
    Star stars[MAX_STARS]; // tablica gwiazd
    float curr_time; // aktualny czas od stworzenia ostatniej gwiazdy
    float star_time; // czas po jakim stworzona zostanie nowa gwiazda
    ALLEGRO_BITMAP* star_bitmap; // bitmapa gwiazdy
}Stars;

// CreateStars: tworzy obiekt stars
Stars CreateStars(ALLEGRO_BITMAP* star_bitmap);
// UpdateStars: aktualizuje gwiazdy
void UpdateStars(Stars* const stars);
// DrawStars: rysuje gwiazdy
void DrawStars(const Stars* const stars);
// ResetStars: resetuje i tworzy losowo kilka gwiazd
void ResetStars(Stars* const stars);

#endif
