#ifndef CONSTS_H
#define CONSTS_H

enum { NUMBER_OF_PLANET_BITMAPS = 3 }; // liczba obrazków planet
enum { MAX_PLANETS = 8 }; // maksymalna liczba możliwych planet na planszy
enum { MAX_MAPS = 64 }; // maksymalna liczba możliwych map

extern const float GAME_SPEED; // predkosc gry

enum { FPS = 60 }; // ilosc klatek
extern const float DT; // różnica czasu pomiędzy kolejnymi klatkami

extern const int SCREEN_H; // wysokość ekranu
extern const int SCREEN_W; // szerokość ekranu

extern const float GRAVITY_CONST; // stała grawitacyjna (określa siłę jaką planety przyciągają obiekt)

extern const float NUMBER_OF_WORMHOLE_SELF_ROT; // ilość obrotów własnych tunelu w czasie jednego obrotu

extern const float ENTRANCE_ANIMATION_SPEED; // czas w którym obiekt wleci do środka tunelu to: 1/ENTRANCE_ANIMATION_SPEED [s]

extern const int GUI_X_OFFSET; // przesunięcie interfejsu użytkownika na osi poziomej
extern const int GUI_Y_OFFSET; // przesunięcie interfejsu użytkownika na osi pionowej
extern const int GUI_LARGE_FONT_SIZE; // rozmiar dużej czczionki interfejsu użytkownika
extern const int GUI_SMALL_FONT_SIZE; // rozmiar małej czczionki interfejsu użytkownika

#endif
