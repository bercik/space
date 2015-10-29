#include "input.h"

static const float DELTA_ANGLE = 120.0f;
static const float DELTA_STRENGTH = 360.0f;
static const float STRENGTH_MAX = 300.0f;
static const float STRENGTH_MIN = 50.0f;
static const float BAR_HEIGHT = 10.0f;
static const float BAR_WIDTH = 50.0f;
static const float ARROW_WIDTH_SCALE = 2.0f; // ile razy strzełka ma być szersza od promienia obiektu
static const float ARROW_HEIGHT_SCALE = 4.0f; // ile razy strzełka ma być wyższa od promienia obiektu

Input CreateInput(const Object* const object, int rot, ALLEGRO_BITMAP* arrow_bitmap, ALLEGRO_BITMAP* bar_bitmap)
{
    int i; // zmienna pomocnicza

    Input input;

    input.exit = false;
    input.restart = false;

    input.arrow_bitmap = arrow_bitmap;
    input.bar_bitmap = bar_bitmap;

    for (i = 0; i < 3; ++i)
        input.keys[i] = false;

    input.angle = rot * 90.0f;
    input.strength = CreateFloatValue(STRENGTH_MIN, STRENGTH_MIN, STRENGTH_MAX);
    input.strength_scale1 = al_get_bitmap_width(bar_bitmap) / STRENGTH_MAX;
    input.strength_scale2 = BAR_WIDTH / STRENGTH_MAX;
    input.add_strength = true;

    input.bar_pos = CreateVector2(object->pos.x + object->r, object->pos.y + object->r);
    input.arrow_pos = object->pos;
    input.arrow_scale.x = object->r / al_get_bitmap_height(arrow_bitmap) * ARROW_WIDTH_SCALE;
    input.arrow_scale.y = object->r / al_get_bitmap_width(arrow_bitmap) * ARROW_HEIGHT_SCALE;

    return input;
}

void DrawInput(const Input* const input)
{
    float bar_bitmap_height = al_get_bitmap_height(input->bar_bitmap);
    al_draw_scaled_bitmap(input->bar_bitmap, 0, 0, input->strength.value * input->strength_scale1, bar_bitmap_height, input->bar_pos.x,
        input->bar_pos.y, input->strength.value * input->strength_scale2, BAR_HEIGHT, 0);

    float cx = 0;
    float cy = al_get_bitmap_height(input->arrow_bitmap) / 2;
    al_draw_scaled_rotated_bitmap(input->arrow_bitmap, cx, cy, input->arrow_pos.x, input->arrow_pos.y,
        input->arrow_scale.x, input->arrow_scale.y, DegToRad(input->angle), 1);
}

bool UpdateKeyboardInput(Input* const input, const ALLEGRO_EVENT* const event, enum GAME_STATE game_state)
{
    if (game_state == GAME_STATE_INPUT)
    {
        if(event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event->keyboard.keycode)
            {
                case ALLEGRO_KEY_LEFT:
                    input->keys[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    input->keys[KEY_RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    input->keys[KEY_SPACE] = true;
                    break;
            }
        }
        else if(event->type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(event->keyboard.keycode)
            {
                case ALLEGRO_KEY_LEFT:
                    input->keys[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    input->keys[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    if (input->keys[KEY_SPACE])
                    {
                        input->keys[KEY_SPACE] = false;
                        return true; // jesli wczesniej spacja byla wcisnieta to wystrzeliwujemy obiekt (zwracamy true)
                    }
                    break;
            }
        }
    }
    else if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == ALLEGRO_KEY_R)
    {
        input->restart = true;
    }

    if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
    {
        input->exit = true;
    }

    return false;
}

void UpdateInput(Input* const input)
{
    if (input->keys[KEY_SPACE])
    {
        if (input->add_strength)
        {
            if (AddFloatValue(&(input->strength), DELTA_STRENGTH * GAME_SPEED * DT))
            {
                input->add_strength = !input->add_strength;
            }
        }
        else
        {
            if (SubtractFloatValue(&(input->strength), DELTA_STRENGTH * GAME_SPEED * DT))
            {
                input->add_strength = !input->add_strength;
            }
        }
    }

    if (input->keys[KEY_LEFT])
    {
        input->angle -= DELTA_ANGLE * GAME_SPEED * DT;
    }
    if (input->keys[KEY_RIGHT])
    {
        input->angle += DELTA_ANGLE * GAME_SPEED * DT;
    }

    if (input->angle > 360.0f)
        input->angle -= 360.0f;
    else if (input->angle < 0.0f)
        input->angle += 360.0f;
}

bool IsRestartInput(Input* const input)
{
    if (input->restart)
    {
        input->restart = false;
        return true;
    }

    return false;
}

void RestartInput(Input* const input)
{
    int i;
    input->strength.value = STRENGTH_MIN;

    for (i = 0; i < 3; ++i)
        input->keys[i] = false;
}

Vector2 CountVelocityVectorFromInput(const Input* const input)
{
    Vector2 vel;
    vel.x = input->strength.value * cos(DegToRad(input->angle));
    vel.y = input->strength.value * sin(DegToRad(input->angle));

    return vel;
}
