#include "animation.h"

// LOKALNE FUNKCJE
// CenterPositionL: centruje pozycje
static void CenterPositionAnimationL(Animation* const animation);
// !-LOKALNE FUNKCJE-!

Animation CreateAnimation(Vector2 pos, int max_frame, int frame_delay, Size frame_source_size, Size frame_dest_size, ALLEGRO_BITMAP* bitmap)
{
    Animation animation;

    animation.pos = pos;
    animation.max_frame = max_frame;
    animation.cur_frame = 0;
    animation.frame_delay = frame_delay;
    animation.frame_count = 0;
    animation.frame_source_size = frame_source_size;
    animation.frame_dest_size = frame_dest_size;
    animation.animation_columns = al_get_bitmap_width(bitmap) / animation.frame_source_size.w;

    animation.bitmap = bitmap;

    CenterPositionAnimationL(&animation);

    return animation;
}

bool UpdateAnimation(Animation* const animation)
{
    ++animation->frame_count;
    if (animation->frame_count >= animation->frame_delay)
    {
        animation->frame_count = 0;

        ++animation->cur_frame;
        if (animation->cur_frame >= animation->max_frame)
        {
            animation->cur_frame = 0;

            return true;
        }
    }

    return false;
}

inline void UpdateAnimationPos(Animation* const animation, Vector2 new_pos)
{
    animation->pos = new_pos;

    CenterPositionAnimationL(animation);
}

void DrawAnimation(const Animation* const animation)
{
    int fx = (animation->cur_frame % animation->animation_columns) * animation->frame_source_size.w;
    int fy = (animation->cur_frame / animation->animation_columns) * animation->frame_source_size.h;

    al_draw_scaled_bitmap(animation->bitmap, fx, fy, animation->frame_source_size.w, animation->frame_source_size.h,
        animation->pos.x, animation->pos.y, animation->frame_dest_size.w, animation->frame_dest_size.h, 0);
}

inline void RestartAnimation(Animation* const animation)
{
    animation->cur_frame = 0;
    animation->frame_count = 0;
}

static void CenterPositionAnimationL(Animation* const animation)
{
    Size temp = animation->frame_dest_size;
    DivideSize(&temp, 2);
    animation->pos.x -= temp.w;
    animation->pos.y -= temp.h;
}
