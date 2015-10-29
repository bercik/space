#include "main.h"

// LOKALNE FUNKCJE
// AllegroInitL: inicjalizuje allegro i wszystkie używane dodatki:
static bool AllegroInitL(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer);
// RestarGameL: restartuje plansze:
static void RestartGameL(enum GAME_STATE* const game_state, Map* const map, Input* const input, Audio* const audio);
// LoadMapL: ładuje mape i w razie niepowodzenia wyświetla komunikat błędu i zwraca false:
static bool LoadMapL(const char* const path, Map* const map, Input* const input, const Bitmaps* const bitmaps, const ALLEGRO_DISPLAY* const display);
// DrawBackgroundL: rysuje tło
static void DrawBackgroundL(ALLEGRO_BITMAP* background);
// DrawGuiL: Rysuje interfejs użytkownika
static void DrawGuiL(ALLEGRO_FONT* gui_font_large, ALLEGRO_FONT* gui_font_small, const char* const map_name, int a_map, int number_of_maps);
// !-LOKALNE FUNKCJE-!

int main(int argc, char **argv)
{
    // inicjalizacja ziarna losowania
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    // DEKLARACJA ZMIENNYCH
    Bitmaps bitmaps; // bitmapy
    Input input; // input
    Map map; // mapa
    Maps maps; // ścieżki do kolejnych map
    Audio audio; // audio
    Stars stars; // gwiazdy
    ALLEGRO_BITMAP* load_bitmap; // bitmapa wyświetlana przy ładowaniu gry
    ALLEGRO_FONT* gui_font_large; // duża czcionka używana do wyświetlania elementów GUI
    ALLEGRO_FONT* gui_font_small; // mała czczionka używana do wyświetlania elementów GUI

    enum GAME_STATE game_state; // stan gry
    bool redraw; // czy przerysowywac plansze

    ALLEGRO_DISPLAY *display = NULL; // ekran
    ALLEGRO_EVENT_QUEUE *event_queue = NULL; // kolejka zdarzeń
    ALLEGRO_TIMER *timer = NULL; // "stoper"
    // !-DEKLARACJA ZMIENNYCH-!

    // INICJALIZACJA ZMIENNYCH
    // inicjalizacja allegro, jeśli nie udana to niszczymy obiekty i wychodzimy z aplikacji
    if (!AllegroInitL(&display, &event_queue, &timer))
    {
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);

        return -1;
    }

    // ładujemy i wyświetlamy bitmapę ładowania
    load_bitmap = al_load_bitmap("load.png");
    int w = al_get_bitmap_width(load_bitmap);
    int h = al_get_bitmap_height(load_bitmap);
    al_draw_scaled_bitmap(load_bitmap, 0, 0, w, h, 0, 0, SCREEN_W, SCREEN_H, 0);
    al_flip_display();

    // ładujemy czcionki:
    gui_font_large = al_load_ttf_font("Zantroke.otf", GUI_LARGE_FONT_SIZE, 0);
    gui_font_small = al_load_ttf_font("Zantroke.otf", GUI_SMALL_FONT_SIZE, 0);

    // ładujemy dźwięki:
    LoadSamples(&audio);

    // inicjalizujemy ścieżki do kolejnych map:
    maps = CreateMaps();
    if (!LoadMapsPaths(&maps, "maps"))
    {
        al_show_native_message_box(display, "Błąd", "Błąd", "Nie udało się wczytać pliku maps", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // ładujemy bitmapy:
    LoadBitmaps(&bitmaps);
    // tworzymy obiekt stars:
    stars = CreateStars(bitmaps.star);
    // ustawiamy zmienne sterujące grą i rysowaniem:
    game_state = GAME_STATE_INPUT;
    redraw = true;
    // !-INICJALIZACJA ZMIENNYCH-!

    // załadowanie pierwszej planszy:
    if (!LoadMapL(GetCurrentMapPath(&maps), &map, &input, &bitmaps, display)) return -1; // jeśli nie udało się załadować mapy to przerywamy program

    // "tutorial":
    //al_show_native_message_box(display, "Sterowanie", "Sterowanie",
        //"strzałki lewo/prawo - zmiana kierunku\nspacja - wystrzeliwanie\nr - restart gry\nescape - wyjście", NULL, 0);

    // startujemy nasz timer
    al_start_timer(timer);

    // rozpoczynamy odtwarzanie muzyki
    PlaySong(&audio);

    // PETLA GLOWNA PROGRAMU
    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            // aktualizujemy pozycje tunelu czasoprzestrzennego
            UpdateWormhole(&map.wormhole);
            // aktualizujemy animacje planet
            UpdatePlanets(map.planets, map.number_of_planets);
            // aktualizujemy gwiazdy
            UpdateStars(&stars);

            if (game_state == GAME_STATE_INPUT)
            {
                UpdateInput(&input);
            }
            else if (game_state == GAME_STATE_PLAY)
            {
                // aktualizujemy pozycje obiektu
                switch (UpdateObject(&map.object, &map.wormhole, map.planets, map.number_of_planets))
                {
                    case END_EXPLOSION:
                        RestartGameL(&game_state, &map, &input, &audio);
                        break;
                    case END_ENTRANCE_ANIMATION:
                        // wczytujemy kolejna mape, jeżeli nie ma to kończymy gre
                        if (!IncreaseActualMap(&maps))
                        {
                            al_show_native_message_box(display, "Wygrałeś", "Wygrałeś",
                                "Gratulacje! Udało Ci się przejść wszystkie plansze.\n\nSpace v1.0:\n\nAutor: Robert Cebula\nrobert.cebula1@gmail.com\n\n"
                                "Grafika: Arkadiusz Pasternak\narekin1@wp.pl", NULL, 0);

                            return 0;
                        }

                        LoadMapL(GetCurrentMapPath(&maps), &map, &input, &bitmaps, display);
                        ResetStars(&stars);

                        game_state = GAME_STATE_INPUT;
                        break;
                    case EXPLOSION_OR_ENTRANCE:
                        break;
                    case NOTHING:
                        // sprawdzamy czy wystapila kolizja z planetami
                        if (CheckCollisionObjectPlanets(&map.object, map.planets, map.number_of_planets))
                            Play(&audio, AT_EXPLOSION);
                        // sprawdzamy czy wystapila kolizja z tunelem czasoprzestrzennym
                        if (CheckCollisionObjectWormhole(&map.object, &map.wormhole))
                            Play(&audio, AT_TRANSPORT);

                        break;
                }
            }

            // ustawiamy flage na przerysowanie planszy
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP || ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (UpdateKeyboardInput(&input, &ev, game_state))
            {
                Play(&audio, AT_WHIZ);
                game_state = GAME_STATE_PLAY;
                map.object.vel = CountVelocityVectorFromInput(&input);
            }

            if (input.exit)
                break;

            if (IsRestartInput(&input)) // restart gry
            {
                RestartGameL(&game_state, &map, &input, &audio);
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            DrawBackgroundL(bitmaps.background);
            DrawStars(&stars);
            DrawPlanets(map.planets, map.number_of_planets);
            DrawWormhole(&map.wormhole);
            DrawObject(&map.object);
            DrawExplosion(&map.object.explosion);
            if (game_state == GAME_STATE_INPUT) DrawInput(&input);
            DrawGuiL(gui_font_large, gui_font_small, GetCurrentMapPath(&maps), maps.a_map, maps.number_of_maps);

            al_flip_display();
        }
    }
    // !-PETLA GLOWNA PROGRAMU

    // DESTRUKCJA ZMIENNYCH
    DestroySamples(&audio);
    al_destroy_font(gui_font_small);
    al_destroy_font(gui_font_large);
    al_destroy_bitmap(load_bitmap);
    DestroyBitmaps(&bitmaps);
    // !-DESTRUKCJA ZMIENNYCH-!

    return 0;
}

static bool AllegroInitL(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer)
{
    fprintf(stdout, "allegro version: %s\n", ALLEGRO_VERSION_STR);

    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return false;
    }

    if(!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize image addon!\n");
        return false;
    }

    if(!al_install_keyboard())
    {
        fprintf(stderr, "failed to install the keyboard!\n");
        return false;
    }

    if(!al_install_audio())
    {
        fprintf(stderr, "failed to install the audio!\n");
        return false;
    }

    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize acodec addon!\n");
        return false;
    }

    al_init_font_addon();

    if(!al_init_ttf_addon())
    {
        fprintf(stderr, "failed to initialize ttf addon!\n");
        return false;
    }

    *timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return false;
    }

    *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return false;
    }

    *event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        return false;
    }

    al_register_event_source(*event_queue, al_get_display_event_source(*display));
    al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
    al_register_event_source(*event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    return true;
}

static void RestartGameL(enum GAME_STATE* const game_state, Map* const map, Input* const input, Audio* const audio)
{
    Play(audio, AT_RESTART);
    map->object = map->original_object;
    *game_state = GAME_STATE_INPUT;
    RestartInput(input);
}

static bool LoadMapL(const char* const path, Map* const map, Input* const input, const Bitmaps* const bitmaps, const ALLEGRO_DISPLAY* const display)
{
    if (!LoadMap(map, input, path, bitmaps))
    {
        char messg[64] = "Nie udało się załadować mapy ";
        strcat(messg, path);
        strcat(messg, "!");

        al_show_native_message_box((ALLEGRO_DISPLAY*)display, "Błąd", "Błąd", messg, NULL, ALLEGRO_MESSAGEBOX_ERROR);

        return false;
    }

    return true;
}

static void DrawBackgroundL(ALLEGRO_BITMAP* background)
{
    int w = al_get_bitmap_width(background);
    int h = al_get_bitmap_height(background);

    al_draw_scaled_bitmap(background, 0, 0, w, h, 0, 0, SCREEN_W, SCREEN_H, 0);
}

static void DrawGuiL(ALLEGRO_FONT* gui_font_large, ALLEGRO_FONT* gui_font_small, const char* const map_name, int a_map, int number_of_maps)
{
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    al_draw_text(gui_font_small, color, GUI_X_OFFSET, GUI_Y_OFFSET, ALLEGRO_ALIGN_LEFT, map_name);

    char text[6];
    char temp[3];
    sprintf(text, "%d", a_map + 1);
    strcat(text, "/");
    sprintf(temp, "%d", number_of_maps);
    strcat(text, temp);

    al_draw_text(gui_font_large, color, GUI_X_OFFSET, GUI_Y_OFFSET + GUI_SMALL_FONT_SIZE, ALLEGRO_ALIGN_LEFT, text);
}
