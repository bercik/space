#include "audio.h"

void LoadSamples(Audio* const audio)
{
    al_reserve_samples(10);

    audio->song_sample = al_load_sample("song.ogg");
    audio->song_sample_instance = al_create_sample_instance(audio->song_sample);
    al_set_sample_instance_playmode(audio->song_sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(audio->song_sample_instance, al_get_default_mixer());

    audio->samples[AT_EXPLOSION] = al_load_sample("explosion.wav");
    audio->samples[AT_RESTART] = al_load_sample("restart.wav");
    audio->samples[AT_TRANSPORT] = al_load_sample("transport.wav");
    audio->samples[AT_WHIZ] = al_load_sample("whiz.wav");
}

void DestroySamples(Audio* const audio)
{
    al_destroy_sample(audio->song_sample);
    audio->song_sample = NULL;
    al_destroy_sample_instance(audio->song_sample_instance);
    audio->song_sample_instance = NULL;

    int i;
    for (i = 0; i < AT_NUMBER_OF_TYPES; ++i)
    {
        al_destroy_sample(audio->samples[i]);
        audio->samples[i] = NULL;
    }
}

void Play(const Audio* const audio, enum AUDIO_TYPE audio_type)
{
    al_play_sample(audio->samples[audio_type], 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
}

void PlaySong(Audio* const audio)
{
    al_play_sample_instance(audio->song_sample_instance);
}

void StopSong(Audio* const audio)
{
    al_stop_sample_instance(audio->song_sample_instance);
}
